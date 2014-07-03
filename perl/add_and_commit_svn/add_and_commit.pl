#!/usr/bin/perl

use strict;
use warnings;
use File::Path qw(make_path remove_tree);
use Cwd;

&dot_svn_del_func(getcwd);

sub dot_svn_del_func 
{
    my $path = shift;
    opendir (DIR, $path) or die "Unable to open $path: $!";
    my @files = grep { !/\.{1,2}$/ } readdir (DIR);
    @files = grep { !/\.svn/ } @files;
    closedir (DIR);
    @files = map { $path . '/' . $_ } @files;
    print "\n\nWorking at: ${path}\n";
    foreach my $file (@files) {
        my @add = ("svn", "add", $file);
        my @commit = ("svn", "commit", $file, "-m \"file commited by perl script\"");
        print "@add\n";
        system(@add);
        print "@commit\n";
        system(@commit);
        if (-d $file) {
            &dot_svn_del_func($file)
        }
    }
}    
