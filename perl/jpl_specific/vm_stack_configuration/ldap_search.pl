#!/usr/bin/perl

use strict;
use warnings;
use Net::LDAP;
use File::Slurp;
use File::Path qw( mkpath ); 

use constant RAPSDE_RPM_REPO => "http://hstrepsvr.jpl.nasa.gov/rpm_forge/rapsde_repo/RHEL5/RPMS/rapsde-yum-repo-1.0-0.0.x86_64.rpm";
use constant WEBSTACK_RPM_REPO => "http://hstrepsvr.jpl.nasa.gov/rpm_forge/webstack_rhel5.5/RPMS/webstack_repo-1.0-0.0.x86_64.rpm";
use constant CONFIG_PATH => ".";
use constant CONFIG_FILE => CONFIG_PATH."/server_type.conf";
die "ERROR: ".$! unless ( -d CONFIG_PATH && -f CONFIG_FILE );
use constant BASE_SEARCH => "ou=projects,dc=dir,dc=jpl,dc=nasa,dc=gov";
use constant RAPSDE_CONFIG_FILES_PATH => CONFIG_PATH."/rapsde-config-files";
die "ERROR: ".$! unless ( -d RAPSDE_CONFIG_FILES_PATH );

&main;

sub main {
	my @data = read_file ( CONFIG_PATH."/".CONFIG_FILE  );
	chomp ( @data );

	my $server_type = $data[0];
	die "ERROR: @data not valid" unless ( $server_type eq "webstack" || $server_type eq "rapsde" );
	if ( $server_type eq "rapsde" ) {
		my $ldap_project_name = $data[1];
		my $include_sscae = $data[2];
		die "ERROR: Key value not defined " unless ( ( defined ( $ldap_project_name ) && defined ( $include_sscae ) ) );
		die unless (  &check_ldap_for_project ( $ldap_project_name ) );
		&configure_rapsde_server ( $ldap_project_name, $include_sscae );
	} elsif ( $server_type eq "webstack" ) {
		#&configure_webstack_server;
	}
}

sub configure_rapsde_server {
	my $ldap_project_name = shift ( @_ );
	my $env_type = shift ( @_ );
	die "ERROR: SSCAE-Software Status Not Specified " if ( !( defined ( $env_type ) ) );
	&modify_rapsde_ldap_configuration ( $ldap_project_name );
	&configure_rapsde_server_sscae ( $ldap_project_name  ) if ( $env_type eq "sscae" );
	&configure_rapsde_server_stand ( $ldap_project_name  ) if ( $env_type ne "sscae" );		
}

sub modify_rapsde_ldap_configuration {
	my $error_value = 0;

	my $ldap_project_name = shift ( @_ );
	die "Invalid Project Name\n" if ( chomp ( $ldap_project_name ) eq "" );
	print "Going to modify ldap configuration: ".$ldap_project_name."\n";
	
	my @certs = ( "LMCA_ca.pem", "self-signed_ca.pem", "verisign_ca.pem", "verisign_intermediate_ca_new.pem", "verisign_intermediate_ca.pem" );
	foreach my $cert ( @certs ) {
		die $cert." is not a file\n" unless ( -f RAPSDE_CONFIG_FILES_PATH."/".$cert );
		my @cp_ca_certs = ( "cp", RAPSDE_CONFIG_FILES_PATH."/".$cert, "/etc/openldap/cacerts/" );
		$error_value = system ( @cp_ca_certs );
		die "ERROR: Copying ".RAPSDE_CONFIG_FILES_PATH."/".$cert." to /etc/openldap/cacerts/ ".$?."\n" if ( $error_value );
		my @chmod = ( "/bin/chmod", "644", "/etc/openldap/cacerts/".$cert );
		$error_value = system ( @chmod );
		die "ERROR: chmoding /etc/openldap/cacerts/".$cert." ".$?."\n" if ( $error_value );
	}

	my @cp_nsswitch = ( "cp", RAPSDE_CONFIG_FILES_PATH."/nsswitch.conf", "/etc/" );
	$error_value = system ( @cp_nsswitch );
	die "ERROR: System Call Failure with errno $?\n" if ( $error_value );

	my @cp_system_auth = ( "cp", RAPSDE_CONFIG_FILES_PATH."/system-auth", "/etc/pam.d/" );
	$error_value = system ( @cp_system_auth );
	die "ERROR: Copying /etc/pam.d/system-auth $?\n" if ( $error_value );

	my @cp_sshd = ( "cp", RAPSDE_CONFIG_FILES_PATH."/sshd", "/etc/pam.d/" );
	$error_value = system ( @cp_sshd );
	die "ERROR: Copying /etc/pam.d/sshd $?\n" if ( $error_value );

	my @cp_access_conf = ( "cp", RAPSDE_CONFIG_FILES_PATH."/access.conf", "/etc/security/" );
	$error_value = system ( @cp_access_conf );
	die "ERROR: Copying /etc/security/access.conf $?\n" if ( $error_value );
	
	&modify_access_conf ( $ldap_project_name );

	my @ldap_command = ( 	"authconfig", "--enableshadow", "--enablemd5", "--disablenis", "--enableldap", 
				"--enableldapauth", "--ldapserver=ldap.jpl.nasa.gov", 
				"--ldapbasedn=ou=".$ldap_project_name.",ou=projects,dc=dir,dc=jpl,dc=nasa,dc=gov", 
				"--enableldaptls", "--disablekrb5", "--enablemkhomedir", "--update" );
	$error_value = system ( @ldap_command );
	die "ERROR: authconfig command failure $?\n" if ( $error_value );
}

sub configure_rapsde_server_sscae {
	my $project_name = shift ( @_ );
	&create_rapsde_sdf_directory_structure ( $project_name );
	
	my @args = ( "rpm", "-Uvh", RAPSDE_RPM_REPO );	
	system ( @args ) == 0 or die "System @args failed: $?\n";

	my @packages = qw(	
				cpp cvs doxygen doxygen-doxywizard
				firefox gcc gcc-c++ gcc-fortran 
				gcc-gnat gcc-java gcc-obj gcc-obj++ 
				gdb ghostscript gv httpd ImageMagick
				java-* jre perl python python-genshi
				subversion tetex trac valgrind 
				viewvc
			 );
	
	# 1. Install Packages
	# 2. Install Special Packages
}

sub configure_rapsde_server_stand {
	my $project_name = shift ( @_ );
	&create_rapsde_sdf_directory_structure ( $project_name );
	
	my @args = ( "rpm", "-Uvh", RAPSDE_RPM_REPO );	
	system ( @args ) == 0 or die "System @args failed: $?\n";

	my @packages = qw(	
				cpp cvs doxygen doxygen-doxywizard
				firefox gcc gcc-c++ gcc-fortran 
				gcc-gnat gcc-java gcc-obj gcc-obj++ 
				gdb ghostscript gv httpd ImageMagick
				java-* jre perl python python-genshi
				subversion tetex trac valgrind 
				viewvc
			 );

	# 1. Install Packages
	# 2. Install Special Packages
}

sub create_rapsde_sdf_directory_structure {
	my $error_value = 0;
	
	my $project_name = shift ( @_ );

	my $code_dir = "/".$project_name."/code/";
	my @code_dirs = ( "source", "repos", "tools", "builds" );
	foreach my $dir ( @code_dirs ) {
		mkpath ( $code_dir.$dir );
	}	

	my $test_dir = "/".$project_name."/test/";
	my @test_dirs = ( "TP1", "TP2", "TP3" );
	foreach my $dir ( @test_dirs ) {
		mkpath ( $test_dir.$dir );
	}

	my $task_management_dir = "/".$project_name."/task_management/";
	my @task_management_dirs = ( 	"issue-tracking", "templates",
					"planning/plans/SMP", "planning/plans/FFE-UFE",
					"planning/plans/WA", "planning/plans/SDSP_tailoring",
					"planning/SDSP", "planning/estimates", 
					"planning/schedule", "reviews/peer", "reviews/code",
					"reviews/MMR", "reviews/milestone", "reviews/SDSP_tailoring" );
	foreach my $dir ( @task_management_dirs ) {
		mkpath ( $task_management_dir.$dir );
	}

	my $engineering_dir = "/".$project_name."/engineering/";
	my @engineering_dirs = ( "architecture", "requirements", "interfaces", "design" );
	foreach my $dir ( @engineering_dirs ) {
		mkpath ( $engineering_dir.$dir );
	}

	my @chmod = ( "/bin/chmod", "770", "-R", "/".$project_name );
	$error_value = system ( @chmod );
	die "ERROR: chmoding /".$project_name." ".$?."\n" if ( $error_value );
	my @chown = ( "/bin/chown", "root:".$project_name, "-R", "/".$project_name );
	$error_value = system ( @chown );
	die "ERROR: chowning /".$project_name." ".$?."\n" if ( $error_value );
}

sub modify_access_conf {
	# This searches the file access.conf for a line that
	# allows all to a given set of services and then
	# it writes the group that you want above that line.
	my $ldap_project_name = shift ( @_ );
	die "ERROR: Invalid Project Name\n" if ( chomp ( $ldap_project_name ) eq "" );
	die "ERROR: /etc/security/access.conf DNE\n" unless ( -f "/etc/security/access.conf" );
        print "Going to modify access.conf to allow: ".$ldap_project_name." privilages\n";

	my $line = " ";
	my $prev_line = " ";
	my $before_line_to_place = " ";
	my $after_line_to_place = " ";
	my $found = 0;
	my $find = "+:ALL:";
	open(FILE, "<", "/etc/security/access.conf" );
	while ( <FILE> ) {
        	$prev_line = $line;
	        $line = $_;
        	chomp($line);
	        if($line =~ /\Q$find\E.[a-zA-Z0-9]/ && !$found) {
	                $found = 1;
        	        $before_line_to_place = $prev_line;
                	$after_line_to_place = $line;
	        }
	}
	my $TASK_NAME = $ldap_project_name;
	my $insert = "+:@".${TASK_NAME}.":ALL";
	open(FILE, "<", "/etc/security/access.conf" );
	# Put Perl into slurp mode to read entire file
	undef $/;
	my $file = <FILE>;
	# Matches the characters between \Q and \E literally, suppressing the 
	# meaning of special characters.
	$file =~ s/\Q$before_line_to_place\E\n\Q$after_line_to_place\E/$before_line_to_place\n$insert\n$after_line_to_place/;
	close( FILE );
	open( OUTPUT, ">", "/etc/security/access.conf" );
	print OUTPUT $file;
	close( OUTPUT );
}

sub check_ldap_for_project {
	my $project_name = shift ( @_ );
	my $ldap = Net::LDAP->new( 'ldap.jpl.nasa.gov' ) or die "$@";
	
	my $mesg = undef;
	$mesg = $ldap->start_tls();
	die $mesg->error if ( $mesg =~ m/Bad hostname/ );
	
	$mesg = $ldap->bind;	
	die $mesg->error if ( ! $mesg =~ m/Success/ );
	
	$mesg = $ldap->search ( base => BASE_SEARCH, filter => "ou=$project_name" );
	
	my $process_string = "";
	my $max = $mesg->count;
 	for ( my $i = 0 ; $i < $max ; $i++ ) {
   		my $entry = $mesg->entry ( $i );
   		foreach my $attr ( $entry->attributes ) {
     			$process_string = $process_string." ".$attr." ".$entry->get_value( $attr );
		}
	}
	if ( $process_string =~ m/ou $project_name/ ) {
		print "SUCCESS project: ".$project_name." exists\n";
		return 1;
	} else {
		print "ERROR: project: ".$project_name." not found in ldap\n";
		return 0;
	}
	$mesg = $ldap->unbind;
}

sub configure_webstack_server {
	my @args = ( "rpm", "-Uvh", WEBSTACK_RPM_REPO );	
	system ( @args ) == 0 or die "System @args failed: $?\n";

	my @packages = qw(
				webstack_repo 	
			 );
	
	#1. Install packages
}
