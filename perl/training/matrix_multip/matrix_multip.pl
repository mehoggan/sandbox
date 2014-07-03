#!/usr/bin/perl

use strict;
use warnings;
use XML::Simple;
use Data::Dumper;

my @MatrixChain = ();

&main;

sub main {
	if ( @ARGV >= 1 ) {
		my $matrix_file = shift ( @ARGV );
		print "Going to process ".$matrix_file."...\n";
		die "ERROR: ".$!." ".$matrix_file unless ( -f $matrix_file );
		my @check = split ( m/\./, $matrix_file );
		chomp ( @check );
		die "ERROR: Invalid File Name -- Must End In .xml" unless ( $check[$#check] =~ /xml$/i );
		$matrix_file = XMLin ( $matrix_file );
		&build_matrix_chain ( $matrix_file, "");
	}
}

sub build_matrix_chain {
	my %hash = %{(shift)};
	my $format = shift;
	my $matrix_count = 0;
	while ( ( my $key, my $value ) = each %hash ) {
		if ( $key ~~ /^[a-zA-Z0-9]$/ ) {
			my %matrix = %{$value};
			my $rows = $matrix{'rows'};
			my $cols = $matrix{'cols'};
			# Identify each matrix by a key, used to sort
			# because hashes suck balls
			my @matrix_vector = ($key);
			for ( my $i = 1; $i < $rows; $i++ ) {
				$matrix_vector[$i] = \$matrix{"row".$i};
				my @temp = ${$matrix_vector[$i]};
				print "@temp\n";				
			}
			$MatrixChain[$matrix_count] = \@matrix_vector;
			$matrix_count++;	
		} elsif ( ref ( $value ) eq "HASH" ) {
			&build_matrix_chain ( $value, $format."\t");
		}
	}
}
