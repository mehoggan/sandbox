#!/usr/bin/perl

use strict;
use warnings;


&main;
my @MatrixA = ();
my @MatrixB = ();
my $rowsA; 
my $colsA;
my $rowsB;
my $colsB;

sub main {
	if ( @ARGV == 4 ) {
		$rowsA = shift ( @_ );
		$colsA = shift ( @_ );
		$rowsB = shift ( @_ );	
		$colsB = shift ( @_ );
	} else {
		my @str = ();
		my $var = "";
		while ( chomp ( $var ) ne 'quit' ) {
			print "Please input number of rowsXcolumns (in this format): ";
			chomp ( ( @str = split ( m/x|X/, $var = <STDIN> ) ) );
			last if ( @str == 2 );
		}
		exit ( 0 ) if ( $var eq 'quit' );
		$rowsA = $str[0];
		$colsA = $str[1];
		&build_identity;
	}
}

sub build_identity {
	print "Building $rowsA X $colsA Identity Matrix\n";
	for ( my $i = 0; $i < $rowsA; $i++ ) {
		print "| ";
		for ( my $j = 0; $j < $colsA; $j++ ) {
			if ( $i == $j ) {
				${$MatrixA[$i]}[$j] = 1;
			}
			else {
				${$MatrixA[$i]}[$j] = 0;
			}
			print ${$MatrixA[$i]}[$j]." ";
		}
		print " |\n";
	}
}
