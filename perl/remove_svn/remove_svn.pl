#!/usr/bin/perl

use File::Find;
use File::Path;
use strict;
use warnings;

die "Why did you give me 0 args?" unless @ARGV;

my @directories = @ARGV;
find(\&remove_svn, @directories);

exit(0);

sub remove_svn {
	return unless ('.svn' eq $_);
	print $File::Find::name."\n";
	rmtree($File::Find::name,1,1);
}

