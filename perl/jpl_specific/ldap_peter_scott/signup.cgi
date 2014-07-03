#!/usr/ets/bin/perl

####
#    LFT (Interim) Signup Tool
#    Megan Mickelson <Megan.C.Mickelson@jpl.nasa.gov>
#    1/26/2010
####

use CGI qw(all -nosticky) ;
use DBI;
use Data::Dumper;
#use LWP::Agent;
use Net::LDAP;
use Net::LDAPS;

my $CC = "";
my $MAILPROG = "/usr/lib/sendmail -t -oi";

my $cgi = new CGI;
#my $dbh = DBI->connect("DBI:mysql:IT_Portfolio:icis-dtamysql-001.jpl.nasa.gov:4155","cmickels","120267") || -1;
my $sth;

my $username = $cgi->param('user');
my $password = $cgi->param('pass');

#### AUTHENTICATE LDAP ####
my $attrs = ['*'];#
my $searchAttr = "cn";
my $search = "*";

my $HOST    = 'ldap.jpl.nasa.gov';
my $BASE    = 'ou=personnel,dc=dir,dc=jpl,dc=nasa,dc=gov';
my $SCOPE  = 'sub';

my $ldap;
$ldap = Net::LDAPS->new($HOST, async => 1, cafile => "cacert.pem") or print "Couldn't connect to ldap: $!";

my $return = $ldap->bind("uid=$username,$BASE", password => $password, noauth => 0);

$allowed_in = 1 if ($return->code == LDAP_SUCCESS);

my $r;
$r = $ldap->search(base => $BASE, filter => "(uid=$username)", attrs  => $attrs, scope  => $SCOPE);

my $personsname, $email, $badge, $org;
my @results;
my $i = 0;
while (my $entry = $r->pop_entry) {
   $personsname = $entry->get_value('displayName');
   $email = $entry->get_value('mail');
   $badge = $entry->get_value('jplbadgenumber');
   $org = $entry->get_value('jpldepartmentname');
}


if (!$allowed_in) {
   print $cgi->header(status=>'403');
   print $cgi->h1("You do not have authorization to view this page");
   exit;
}

#### END AUTHENTICATE LDAP ####

open (TEMPLATE, "signup-email.tmpl");
my @template = <TEMPLATE>;
my $template = join '', @template;
close (TEMPLATE);

my $datetime = localtime(time);

$template =~ s/%TO%/Joseph.C.Marphis.III\@jpl.nasa.gov, Rudy.E.Gutierrez\@jpl.nasa.gov, jplis-lft\@list.jpl.nasa.gov, Douglas.S.Hughes\@jpl.nasa.gov/g;
$template =~ s/%CC%/$email/g;
$template =~ s/%NAME%/$personsname/g;
$template =~ s/%BADGE%/$badge/g;
$template =~ s/%USERNAME%/$username/g;
$template =~ s/%EMAIL%/$email/g;
$template =~ s/%ORG%/$org/g;
$template =~ s/%DATETIME%/$datetime/g;

open (MAIL, "|$MAILPROG") or print "Can't open $MAILPROG: $!\n";
print MAIL $template;
close MAIL;

my $uri = $ENV{'REQUEST_URI'};
$uri =~ s#/[^/]*$#/#;
print "Location: https://$ENV{'HTTP_HOST'}$uri/complete.php\n\n"
