#!/usr/bin/perl

use strict;
use warnings;
use File::Path qw( rmtree );

my $dir = ".";

opendir( my $dir_handle, $dir ) or die $!;

while( my $file = readdir( $dir_handle ) ) {
	my $list;
	if( -M $file > 14 ) {
		print $file," = ",-M $file,"\n";
		rmtree( $file, { result => \$list } );
	}
	print "unlinked $_\n" for @$list;
}

closedir( DIR );
