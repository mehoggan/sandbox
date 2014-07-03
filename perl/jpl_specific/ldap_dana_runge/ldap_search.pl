#!/usr/bin/perl

use strict;
use warnings;
use Net::LDAP;
use File::Slurp;

use constant CONFIG_PATH => "./";
use constant CONFIG_FILE => CONFIG_PATH."/server_type.conf";
use constant BASE_SEARCH => "ou=projects,dc=dir,dc=jpl,dc=nasa,dc=gov";
die "ERROR: ".$! unless ( -d CONFIG_PATH &&  -f CONFIG_FILE );

my @data = read_file ( CONFIG_PATH."/".CONFIG_FILE  );
chomp ( @data );

my $server_type = $data[0];
die "ERROR: @data not valid" unless ( $server_type eq "webstack" || $server_type eq "rapsde" );


if ( $server_type eq "webstack" ) {
	
} elsif( $server_type eq 'rapsde' ) {
	my $project_name = $data[1];
	my $env_type = $data[2];
	die "ERROR: Key value not defined " if ( ! ( defined ( $project_name  ) && defined ( $env_type  ) ) );

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
		print "SUCCESS ou ".$project_name." exists\n";
	} else {
		print "ERROR: ou ".$project_name." not found\n";
	}
	$mesg = $ldap->unbind;
}
