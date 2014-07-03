#!/usr/bin/perl

use File::Path qw(make_path remove_tree);
use strict;

# Only run program on valid input MAX/MIN_INPUT = 1
if ( @ARGV == 1 ) {
	my $file = $ARGV[0];
	#Do some regular expression verrification
	&dot_svn_del_func ( $ARGV[0] );
} else {
	die "ERROR: to many arguments passed";
}

sub dot_svn_del_func {
	my $path = shift;
	opendir (DIR, $path) or die "Unable to open $path: $!";
	my @files = grep { !/^\.{1,2}$/ } readdir (DIR);
	closedir (DIR);
        @files = map { $path . '/' . $_ } @files;
        for (@files) {
        	if (-d $_) {
                	my $svn_found = 0;
                        my $path = $_;
                        my @path_components = split(/\//,$path);
                        my $path_count = 0;
                        foreach my $new_path (@path_components) {
                        	if ( $new_path eq ".svn" ) {
		                        remove_tree($_,1,1);
                		        $svn_found = 1;
                        	}
	                        $path_count++;
                        }
                        if ( $svn_found == 0 ) {
        	                #print "Making recursive calls from ".$_."\n";
                                    &dot_svn_del_func ( $_ );
			}
		}
	}
}
