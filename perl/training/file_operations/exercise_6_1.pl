#!/usr/bin/perl

use warnings;
use strict;

use Data::Dumper;
use Storable;
use Date::Calc qw(:all);

my %table = ();
if( @ARGV > 0 ) {
	foreach my $arg ( @ARGV ) {
		# Build Single Log File the Data Structure
		# Put Perl into slurp mode to read entire file
		open( IFILE, "<", $arg ) or next;
		undef $/;
		my $data = <IFILE>;
		my @data = split( m/\n/, $data );
		foreach my $line ( @data ) {
			my @info = split( m/\s{1}/, $line );
			my $key = $info[0]." ".$info[1];
			my $value = $info[2];
			$table{$key} += $value;
		}
		close( IFILE );
	}
	
	while( ( my $key, my $value ) = each( %table ) ) {
		print $key." => ".$value."\n";
	}
} else {
	# Get the date to open up log file
	# First line is not needed just practice with ref
	my $date = [ Today() ];
	my @date = @$date;

	if ( $date[1] < 10 ) {
		$date[1] = "0".$date[1];
	}

	if ( $date[2] < 10 ) {
		$date[2] = "0".$date[2];
	}

	my $file = "@date.log";
	$file =~ s/ //g;
	# Build Single Log File the Data Structure
	# Put Perl into slurp mode to read entire file
	open( IFILE, "<", $file ) or die "ERROR: $! ($file)\n";
	undef $/;
	my $data = <IFILE>;
	my @data = split( m/\n/, $data );
	foreach my $line ( @data ) {
		my @info = split( m/\s{1}/, $line );
		my $key = $info[0]." ".$info[1];
		my $value = $info[2];
		$table{$key} = $value;
	}
	close( IFILE );
}

# Build Main Log File Data Structure
# Put Perl into slurp mode to read entire file
# Also open it up for writing (+>)
open( IMAINFILE, "+>", 'main.log' ) or die "ERROR: $! (main.log)\n";
undef $/;
my $main_data = <IMAINFILE>;
my @main_data = split( m/\n/, $main_data );
my %main_table = ();

foreach my $line ( @main_data ) {
	my( $from, $to, $bytes ) = split( m/\s{1}/, $line );
	my $key = $from." ".$to;
	my $value = $bytes;
	$main_table{$key} = $value;
}

while( ( my $key, my $value ) = each %table ) {
	$main_table{$key} += $value;
	print IMAINFILE $key." ".$value."\n";
}

close( IMAINFILE );
