#!/usr/bin/perl
use strict;
use warnings;
use Text::ParseWords;

# This searches the file access.conf for a line that
# allows all to a given set of services and then
# it writes the group that you want above that line.
my $line = " ";
my $prev_line = " ";
my $before_line_to_place = " ";
my $after_line_to_place = " ";
my $found = 0;
my $find = "+:ALL:";
open(FILE, "<", "access.conf" );
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
print "Going to replace between ".$before_line_to_place." ".$after_line_to_place."\n";
my $TASK_NAME = "perl_test";
my $insert = "+:@".${TASK_NAME}.":ALL";

open(FILE, "<", "access.conf" );
# Put Perl into slurp mode to read entire file
undef $/;
my $file = <FILE>;
# Matches the characters between \Q and \E literally, suppressing the 
# meaning of special characters.
print $file."\n";
$file =~ s/\Q$before_line_to_place\E\n\Q$after_line_to_place\E/$before_line_to_place\n$insert\n$after_line_to_place/;
print $file."\n";
close( FILE );

open(OUTPUT, ">", "access.conf.out");
print OUTPUT $file;
close(OUTPUT);
