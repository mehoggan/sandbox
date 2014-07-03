!/usr/bin/perl

use strict;
use warnings;
use File::Find;
use File::Path;

die "ERROR: You Need to Specify One or More Directories" unless @ARGV;
find \&modify_file, @ARGV;


sub modify_file {
	return unless $_ =~ /\.php$/ || $_ =~ /!(\. | \.\.)/;
	print $_."\n";
	open ( FILE, "<", $_ ) if -f $_;
	# Put Perl into slurp mode to read entire file
	undef $/;
	my $file = <FILE>;
	$file =~ s/\.html/\.php/g;
	close ( FILE );
	open ( OUTPUT, ">", $_ );
	print OUTPUT $file;
	close ( OUTPUT );
}
