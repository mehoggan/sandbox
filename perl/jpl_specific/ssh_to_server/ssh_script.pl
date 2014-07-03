#!/usr/bin/perl
use strict;
use warnings;
use Text::ParseWords;

my $numArgs = @ARGV;
print "thanks, you gave me $numArgs command-line arguments:\n";

# Check to make sure that you hace specified a line
# in the file to select. If not die
if($numArgs == 0) {
	die("You need to specifiy which line to load\n");
}

my $count = 0;			# Which line to load

# Check for a string that starts(^) with a sign and 
# 1 or more numbers if so that will set the line that
# you want to select if the command line argument is 
# not a decimal value then exit
if($ARGV[0] =~ /^[+-]?\d+$/ ) {
	$count = $ARGV[0];
	print "Loading: argv[$ARGV[0]]\n";
}else{
	die "Cannot Load None Numeric Data Types";
}

# This code loops through the text file jpl_ipaddrs
# it will go to the line you specified at the end
# if the number you specified is greater than the
# number of lines the script will fail
my $server = "blank";
my $line_count = 0;
my $verify_count = 0;
open( MYINPUTFILE, "<", "jpl_ipaddrs" );
while( <MYINPUTFILE> ) {
	my $line = $_;
 	chomp($line);
	$line_count += 1;

	if( $line_count == $count ) {
		$server = $line;
		$verify_count = $line_count;
        }
}
if( $verify_count != $count ) {
	close( MYINPUTFILE );
	die "You do not have $count servers listed\n";
}
# Make sure that you close the file
close( MYINPUTFILE );

# If all goes well you will get the server from
# infor from the string extracted above. Once extracted
# the exec command will atempt to login to server over ssh
print "Going to SSH to: $server\n";
my @words = &quotewords('\s+', 1, $server);
print "$words[1]\n";

my $command = "ssh mehoggan@".$server;
exec ($command) or print STDERR "couldn't exec ssh: $!";





