#!/afs/jpl/rep/p/perl/bin/perl5.8.8
#-*-Perl-*-
use strict;
use warnings;

# $Header: /afs/jpl/group/ft/www/RCS/signup-automated.cgi,v 1.1 2010/05/14 20:31:42 pjscott Exp pjscott $

use HTML::Template;
use File::Slurp;
use Readonly;
use Inline::Files;
use CGI qw(header param);
use AFS::KTC_PRINCIPAL;
use AFS::KTC_TOKEN;
use ARS;
use Net::LDAPS;
use Net::LDAP::Control::ProxyAuth;
use Net::SSH::Perl;

# Template assignments
Readonly my $ERROR_TEMPLATE      => 'signup-automated-error.tmpl';
Readonly my $FATAL_TEMPLATE      => 'signup-automated-fatal-error.tmpl';
Readonly my $DONE_TEMPLATE       => 'signup-automated-done.tmpl';
Readonly my $MAIL_TEMPLATE       => 'signup-automated-mail.tmpl';

# SSH provisioning assignments
Readonly my $PROVISION_HOST      => 'sftp.jpl.nasa.gov';
Readonly my $PROVISION_SSH_DIR   => '/opt/home/webservd/.ssh';
Readonly my $PROVISION_HOME      => '/sftp';
Readonly my $PROVISION_SCRIPT    => '/usr/local/sbin/add_sftp_account.sh';
Readonly my $SUDO                => '/usr/bin/sudo';

# LDAP assignments
Readonly my $JPLBASE             => 'dc=dir,dc=jpl,dc=nasa,dc=gov';
Readonly my $SFTP                => 'JPLIT-sftp';
Readonly my $SFTPONLY            => 'sftponly';
Readonly my $PERSON_BASE         => "ou=personnel,$JPLBASE";
Readonly my $BASE                => "ou=$SFTP,ou=projects,$JPLBASE";
Readonly my $NET_GROUP           => "cn=sftp,ou=NetGroups,$BASE";
Readonly my $POSIX_GROUP         => "cn=$SFTPONLY,ou=Groups,$BASE";
Readonly my $PERSONNEL_GROUP     => "cn=jpl.Proj.$SFTP.$SFTPONLY,$PERSON_BASE";
Readonly my $ACCT_BASE           => "ou=accounts,$BASE";
Readonly my $APPLICATION_BASE    => "ou=Applications,$JPLBASE";
Readonly my $LDAP_ADMIN          => "uid=sftpadmin,$APPLICATION_BASE";
Readonly my $LDAP_AUTHZID        => "dn:uid=pgroupadmin,$APPLICATION_BASE";
Readonly my $LDAP_PASSWORD       => 'dref.juit1';
Readonly my $LDAP_SERVER         => 'ldap.jpl.nasa.gov';
Readonly my $LDAP_DEV_SERVER     => 'int-ldap.jpl.nasa.gov';
Readonly my @LDAP_OBJECT_CLASSES => qw(top account posixaccount shadowaccount
				       jplprojectaccnt inetOrgPerson
				       organizationalPerson person);
Readonly my @LDAP_PERSON_ATTRS   => qw(cn jplbadgenumber givenName displayName
				       sn uidNumber mail jplusperson
				       departmentNumber);

# Remedy assignments
Readonly my $ARS_USERNAME        => 'webrequest';
Readonly my $ARS_PASSWORD        => '******';
Readonly my $ARS_SERVER          => 'remedy.jpl.nasa.gov';
Readonly my $ARS_DEV_SERVER      => 'int-remedy-ars.jpl.nasa.gov';
Readonly my $ARS_SCHEMA          => 'Provisioning Form';
Readonly my $REQUEST_DESCRIPTION => 'SFTP Provisioning Request';
Readonly my $SUBMITTER_FULL_NAME => 'Rudy E Gutierrez';
Readonly my $SUBMITTER_BADGE     => '111914';
Readonly my $SUBMITTER_EMAIL     => 'Rudy.E.Gutierrez@jpl.nasa.gov';

# Misc assignments
Readonly my $MAIL_PROG           => '/usr/lib/sendmail -oi -t';
Readonly my $TIMEOUT             => 45;   # Seconds to get the job done
Readonly my $USP_IS_NO           => <<'EOT';
You are not a US Person and are therefore ineligible for SFTP use.

If you believe this decision is in error please file a JPL IT
Service Request.
EOT
Readonly my $USP_IS_UNKNOWN      => <<'EOT';
We cannot tell whether you are a US Person and therefore are
unable to fulfill your request for SFTP service.

If you believe this decision is in error please file a JPL IT
Service Request.
EOT

# Development note: Provisioning (in create_home_directory()) requires
# making an SSH connection as the webservd user and therefore is only possible
# as the web user on the web server.  Therefore the program does not have
# a command-line mode.  Standalone testing of every other function is
# still possible due to the architecture.

run() unless caller;


sub run
{
  my $username = init();

  initial_check( $username );
  open_ticket( $username );
  provision_user( $username );
  send_email( $username );
  display_response( $username );
  close_ticket( $username );
}


# All error returns from this routine must call exit()
sub initial_check
{
  my $username = shift;

  if ( already_provisioned( $username ) )
  {
    user_error( "According to our data, $username already has SFTP access." );
  }
  elsif ( my $reason = is_ineligible( $username ) )
  {
    user_error( $reason );
  }
}


sub is_ineligible
{
  my $username = shift;

  my $person = ldap_find_person( $username );
  my $usp = $person->get_value( 'jplusperson' ) || '';
  return if $usp =~ /\Ay/i;
  return $USP_IS_NO if $usp =~ /\An/i;
  return $USP_IS_UNKNOWN;
  for my $attr ( qw(cn givenName sn uidNumber mail) )
  {
    my $value = $person->get_value( $attr );
    defined $value && length $value or return <<"EOT";
There is no value for the '$attr' attribute of the '$username'
entry in the JPL LDAP directory, and this process needs there
to be one.  Perhaps you are using a pseudo account instead of
one belonging to a real person.

If you believe this decision is in error please file a JPL IT
Service Request.
EOT
  }
  return;
}


{
  my $ticket_id;

  sub open_ticket
  {
    my $username = shift;

    my $person    = ldap_find_person( $username );
    my $badge     = $person->get_value( 'jplbadgenumber' );
    my $full_name = $person->get_value( 'displayName' );
    my %open = (
	       'Session ID'                   => '',
		User_Badge_Number             => $badge,
		User_Full_Name                => $full_name,
		UCS_Service_Code              => 'LFT',
		Charge_Type_Code              => 'SFTP_PROVISION',
		Service_Action_Type           => 'ADD',
		JPL_Username                  => $username,
		JPL_User_Name                 => $username,
		Request_Description           => $REQUEST_DESCRIPTION,
		Auto_Execute_Flag             => 'No',
	       'JPL Password Change required' => 'No',
		Submitter_Fullname            => $SUBMITTER_FULL_NAME,
		Submitter_Badge_ID            => $SUBMITTER_BADGE,
		submitter_email_address       => $SUBMITTER_EMAIL,
	       );
    $ticket_id = create_ticket( %open );
  }

  sub close_ticket
  {
    my %closed = (
		  Process_Successful_Flag => 'Yes',
		  Status                  => 'Closed',
		 );
    modify_ticket( $ticket_id, %closed );
  }

  sub update_ticket
  {
    my ($username, $error) = @_;

    my %changed = (
		   Process_Successful_Flag => 'No',
		   Status               => 'Pending (Problem with Processing)',
		   Process_Results      => $error,
		  'Process Result Log'  => $error,
		  );
    modify_ticket( $ticket_id, %changed ) if $ticket_id;
  }
}


# Got to keep $ars alive because connection will close otherwise
{
  my ($ars, $form);

  sub open_remedy_connection
  {
    my $server = in_dev() ? $ARS_DEV_SERVER : $ARS_SERVER;
    $ars = ARS->new( -server   => $server,
		     -username => $ARS_USERNAME,
		     -password => $ARS_PASSWORD,
		     -catch    => { ARS::AR_RETURN_ERROR,
				    \&remedy_error_handler },
		   );
    $form = $ars->openForm( -form => $ARS_SCHEMA );
  }

  sub create_ticket
  {
    my %param = @_;

    $form->create( -values => \%param );
  }

  sub modify_ticket
  {
    my ($id, %param) = @_;

    $form->set( -entry  => $id,
		-values => \%param );
  }
}


sub remedy_error_handler
{
  my $msg = $_[1];

  die "REMEDY: Someone else is modifying this record at the same time"
    if $msg =~ /has been modified since/;
  die "REMEDY: Unable to connect to remedy server $1\n"
    if $msg =~ /RPC:.*?\b([\w-]+)\.jpl\.nasa/s
    || $msg =~ /\b([\w-]+)\.jpl\.nasa.*?RPC/s
    || $msg =~ /Message not in catalog.*?\b([\w-]+)\.jpl\.nasa\.gov/s;

  if (my ($max, $id) = $msg =~ /limits .*? \(max length - (\d+)\) : (\d+)\)/)
  {
    my $name = _get_field_of_id($id, $max);
    die "REMEDY: More than the $max characters allowed "
        . "for the $name field were entered.\n";
  }

  ARS::internalDie( 'REMEDY: ', @_ );
}


# A more sustainable long-term approach would be to use
# pure Kerberos modules here
sub validate_user
{
  my ($username, $password) = @_;

  defined && length or user_error( "You must supply both inputs" )
    for ($username, $password);

  my $user    = AFS::KTC_PRINCIPAL->new( $username );
  my $auth_ok = AFS::KTC_TOKEN->UserAuthenticateGeneral($user, $password, 300,
				    &AFS::KA_USERAUTH_VERSION
				  | &AFS::KA_USERAUTH_DOSETPAG,
				    my $pwexp, my $reason);
  AFS::KTC_TOKEN->ForgetAllTokens;
  return if $auth_ok;

  $reason =~ /password was incorrect|user doesn't exist/ and
    user_error( "I'm sorry, that is not the correct password for $username" );

  die "Cannot authenticate $username: " . ($reason || 'unknown failure');
}


sub provision_user
{
  my $username = shift;

  unless ( eval
	   {
	     make_ldap_modifications( $username );
	     create_home_directory( $username );
	     1;
           }
	 )
  {
    if ( $@ =~ /ALREADYEXISTS/ )
    {
      user_error( <<'EOT' );
I found an SFTP home directory already created in your name
even though the LDAP directory thought you didn't have one.  Everything
should be okay but please let us know if it is not working properly.
EOT
    }
    else
    {
      die "Provisioning error: $@";
    }
  }
}


sub make_ldap_modifications
{
  my $username = shift;

  add_ldap_account( $username );
  add_to_ldap_groups( $username );
}


{
  my $ldap;

  sub open_ldap_connection
  {
    my $server = in_dev() ? $LDAP_DEV_SERVER : $LDAP_SERVER;
    $ldap = Net::LDAPS->new( $server, onerror => 'die' );
    $@ and die "LDAP server $server connection problem: $@";
    $ldap->bind( $LDAP_ADMIN, password => $LDAP_PASSWORD );
  }

  sub already_provisioned
  {
    my $username = shift;

    my $res  = $ldap->search( base   => $ACCT_BASE,
			      attrs => [ 'cn' ],
			      filter => "(uid=$username)" );
    $res->count;
  }

  sub add_ldap_account
  {
    my $username = shift;

    my $person = ldap_find_person( $username );
    my $server = in_dev() ? 'int-afs' : 'jpl';
    my @attrs = ( cn            => $person->get_value( 'cn' ),
		  gidNumber     => 1000,
		  givenName     => $person->get_value( 'givenName' ),
		  homeDirectory => "$PROVISION_HOME/$username",
		  loginShell    => '/usr/local/libexec/sftp-server',
		  objectClass   => \@LDAP_OBJECT_CLASSES,
		  sn            => $person->get_value( 'sn' ),
		  uid           => $username,
		  uidNumber     => $person->get_value( 'uidNumber' ),
		  userPassword  => "{KRB5}$username\@\U$server.nasa.gov",
		);
    my $dn = "uid=$username,$ACCT_BASE";
    $ldap->add( $dn, attrs => \@attrs );
  }

  sub add_to_ldap_groups
  {
    my $username = shift;

    $ldap->modify( $POSIX_GROUP, add => { memberUid => $username } );
    $ldap->modify( $NET_GROUP,   add => { nisNetgroupTriple
					    => "(,$username,)" } );

    my $dn = "uid=$username,$PERSON_BASE";
    my $auth = Net::LDAP::Control::ProxyAuth->new( authzID => $LDAP_AUTHZID );
    $ldap->modify( $PERSONNEL_GROUP,
		   control => [ $auth ],
		   add     => { uniqueMember => $dn } );
  }

  my $person;

  sub ldap_find_person
  {
    $person and return $person;

    my $username = shift;

    my $res = $ldap->search( base    => $PERSON_BASE,
			     filter  => "(jplusername=$username)",
			     scope   => 'sub',
			     attrs   => \@LDAP_PERSON_ATTRS,
			   );
    $res->count and return $person = $res->shift_entry;

    die "Can't find $username in the directory!\n";
  }
}


sub create_home_directory
{
  my $username = shift;

  my $ssh = Net::SSH::Perl->new( $PROVISION_HOST => protocol => 2,
			         identity_files =>
			          [ "$PROVISION_SSH_DIR/id_dsa" ],
			         user_known_hosts =>
			          "$PROVISION_SSH_DIR/known_hosts" );
  $ssh->login();
  my $home_dir = "$PROVISION_HOME/$username";

  my ($out, $err, $exit) = $ssh->cmd( "/bin/ls -d $home_dir" );
  die 'ALREADYEXISTS' unless $exit;

  my $cmd = "$PROVISION_SCRIPT $username";
  ($out, $err, $exit) = $ssh->cmd( "$SUDO $cmd" );
  die "Error in creating home directory: $err" if $exit;
}


sub send_email
{
  my $username = shift;

  my $person = ldap_find_person( $username );
  my $tem    = my_template( filename => $MAIL_TEMPLATE );
  $tem->param(
	       username     => $username,
	       fullname     => $person->get_value( 'displayName' )      || '?',
	       badge        => $person->get_value( 'jplbadgenumber' )   || '?',
	       email        => $person->get_value( 'mail' ),
	       date         => scalar localtime,
	       organization => $person->get_value( 'departmentNumber' ) || '?'
	     );
  send_raw_email ( $tem->output );
}


sub send_raw_email
{
  my $content = shift;

  # YES, $MAIL_PROG HAS TO BE STRINGIFIED... bizarre property of Readonly
  # And I have no idea why the 3-arg version of open doesn't work here.
  open my $fh, "|$MAIL_PROG" or die "Can't open $MAIL_PROG: $!\n";
  print {$fh} $content;
  close $fh;
}


sub display_response
{
  my $username = shift;

  my $tem = my_template( filename => $DONE_TEMPLATE );
  $tem->param( username => $username );
  print header, $tem->output;
}


sub init
{
  my ($username, $password) = map { param( $_ ) } qw(user pass);
  my @chars = ($username =~ /(\W)/g);
  @chars and user_error( <<"EOT" );
Unsuccessful attempt to subvert security with illegal character(s)
`@chars' in username.
EOT

  $SIG{__DIE__} = sub { fatal_error( $username, @_ ) };
  $SIG{ALRM}    = sub { die "TIMEOUT" };
  alarm $TIMEOUT;  # Give us $TIMEOUT seconds to get this thing launched

  validate_user( $username, $password );

  # For developer to do testing

  if ( in_dev()
    && $username eq 'pjscott'
    && ( my $alternate_user = param( 'alternate_user' ) ) )
  {
    $username = $alternate_user;
  }

  open_remedy_connection();
  open_ldap_connection();

  $username;
}


sub usage
{
  require Pod::Text;
  my $parser = Pod::Text->new( sentence => 0, width => 78 );
  $parser->no_whining( 1 );
  $parser->parse_from_filehandle( \*POD );
}


sub fatal_error
{
  my $username = shift;
  my $text = join '', "PROGRAM ERROR:\n", @_;

  if ( @_ && $_[0] =~ /TIMEOUT/ )
  {
    $text = <<'EOT';
The process of provisioning your account took longer than it should
and rather than waiting indefinitely, I have chosen to come back to
you with this error message.  Your account may have been created correctly
but a member of staff will verify that explicitly.
EOT
  }
  else
  {
    my $in_eval = 0;
    for ( my $stack = 1;  my $sub = (CORE::caller($stack))[3]; $stack++ )
    {
      $in_eval = 1 if $sub =~ /^\(eval\)/;
    }
    return if $in_eval;
  }

  my @extra = ( @_ && $_[0] =~ /REMEDY/ ) ? ( remedy_error => 1 ) : ();
  @_ && $_[0] =~ /LDAP/ and push @extra, ldap_error => 1;
  my $contents = read_file( $FATAL_TEMPLATE, err_mode => 'quiet' );
  $contents ||= do { local $/; <ERROR> };  # Fallback... *must* not fail
  my $tem = my_template( scalarref => \$contents );
  $tem->param( username => $username, text => $text, @extra );
  print header, $tem->output;

  # Email developer & maybe ops, update ticket if possible
  {
    my $tem = my_template( filehandle => \*MAIL );
    $tem->param( username => $username, text => $text, @extra );
    update_ticket( $username, $text ) unless @extra;
    send_raw_email( $tem->output );
  }

  exit;
}


sub user_error
{
  my $text = join '', @_;

  my $tem = my_template( filename => $ERROR_TEMPLATE );
  $tem->param( text => $text );
  print header, $tem->output;
  exit;
}


{
  my $location;

  # Are we in the dev environment? (path contains /dev)
  # Because FindBin takes so long (4-6 seconds in this location due to
  # its abs_path() calls running lstat() over most of /afs/jpl/group)
  # we will use SCRIPT_NAME.
  sub in_dev
  {
    $location ||= $ENV{SCRIPT_NAME};

    # For debugging:
    $location or return 1;

    scalar $location =~ m!/dev!;
  }
}

sub my_template
{
  my $tem = HTML::Template->new( @_,
				 die_on_bad_params => 0,
				 global_vars => 1,
				 loop_context_vars => 1 );
  $tem->param( in_dev => in_dev() );
  $tem;
}

__MAIL__
From: Automated.Submission
To: pjscott@jpl.nasa.gov<TMPL_UNLESS NAME="in_dev"><TMPL_IF NAME="remedy_error">,rgutier@jpl.nasa.gov</TMPL_IF></TMPL_UNLESS>
Subject: Error with SFTP User Account for <TMPL_VAR NAME="username">

<TMPL_VAR NAME="text">
<TMPL_IF NAME="remedy_error">**** This error refers to a problem with Remedy and therefore an automated
ticket for handling the situation likely has not been created.
Please follow up by creating an incident ticket manually.
</TMPL_IF>
<TMPL_IF NAME="ldap_error">**** This error refers to a problem with LDAP and therefore an automated
ticket for handling the situation likely has not been created (couldn't
look up the information on the user to populate the ticket).
Please follow up by creating an incident ticket manually.
</TMPL_IF>

<TMPL_IF NAME="in_dev">This message is from the development area.</TMPL_IF>

__ERROR__
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml" lang="en">
<head><title>Message from Provisioning System</title></head>
<body>
<h1>Message from Provisioning System</h1>
<P>
(Fallback error text.)
</P>
<pre>

<TMPL_VAR NAME="text">

</pre>
</body>
__POD__

=head1 NAME

signup-automated.cgi - provide SFTP account for OCIO user

=head1 SYNOPSIS

htps://.../signup-automated.cgi

=head2 POST Arguments

=over 4

=item user

Visible input: JPL Username

=item password

Visible input: JPL password

=item authentication

Hidden, fixed, value: C<request>

=item submit

Form submit button, value: C<Submi>

=back

Form name: C<login>

=head1 DESCRIPTION

This program is primarily intended to be run as a CGI program.

=head1 AUTHOR

C<Peter.J.Scott@jpl.nasa.gov>

=cut
