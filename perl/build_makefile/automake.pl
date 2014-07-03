#!/usr/bin/perl

use strict;
use warnings;

my $path;
my $args = $#ARGV + 1;
if ($args != 1) {
	$path = "/home/mehoggan/arcgis-new/GraphicsCore_Dev/Runtime/Core/Map";
} elsif ($args == 1) {
    # Note program name not passed in as argument hence [0]
    $path=$ARGV[0];
}
die "$path: Does not exist" unless ( -d $path );
open (MYFILE, '> Makefile') or die "File does not exist";
&write_makefile_header_func("libArcGISMap.a");
print MYFILE "SRC = \\\n";
my @source_list;
&build_source_list_func($path);
&remove_trailing_char();
open (MYFILE, '>> Makefile') or die "File does not exist";
print MYFILE "OBJ = \\\n";
my @object_list;
&build_object_list_func($path);
&remove_trailing_char();
open (MYFILE, '>> Makefile') or die "File does not exist";
my %hash_table;
@hash_table{@source_list} = @object_list;
&build_build_rules_func();
close (MYFILE); 
exit;

sub remove_trailing_char
{
    close (MYFILE);
    local $/ = undef;
    open (FILE, '< Makefile') or die "File does not exist";
    my $string = <FILE>;
    close (FILE);
    $string =~ s/\\$//g;
    open (FILE, '> Makefile') or die "File does not exist";
    print FILE $string;
    close (FILE);
}

sub write_makefile_header_func
{
    my $target = shift;
    print MYFILE "BUILD_MODE = release\n";
    print MYFILE "OS_ARCH = 64\n";
    print MYFILE "OBJS_DIR = \$(BUILD_MODE)\$(OS_ARCH)\n";
    print MYFILE "CC = gcc -fPIC\n";
    print MYFILE "COPTS = -m\$(OS_ARCH) -O2\n";
    print MYFILE "CDEFS = -DLINUXx86\n";
    print MYFILE "CFLAGS = \$(COPTS) \$(CDEFS) \$(CINCS)\n";
    print MYFILE "TARGET = $target\n";
}

sub build_build_rules_func
{
    while ( (my $key, my $value) = each %hash_table ) {
       print MYFILE "$value : $key\n";
       print MYFILE "\t\$(CC) -c \$(CFLAGS) -o \$@ \$<\n";
    }
}

sub build_source_list_func 
{
    my $full_path =  shift;
    opendir (DIR, $full_path) or die "Unable to open $full_path: $!";
    my @files = grep { !/^\.{1,2}$/ } readdir (DIR);
    closedir (DIR);
    @files = map { $full_path . '/' . $_ } @files;
    for (@files) {
        if (-d $_) {
            my $full_path = $_;
            my @path_components = split(/\//,$full_path);
            my $dir = $path_components[$#path_components];
            if ($dir eq "libtess") {
            } else {
                &build_source_list_func ($_);
            }
        } else {
            my $relative_path = $_;
            $relative_path =~ s/$path/\./g;
            if ( $relative_path =~ m/\.cpp$/ ) {
                print MYFILE "    $relative_path \\\n";
                my $my_val = $relative_path;
                unshift @source_list, $my_val;
            }
        }
    } 
}

sub build_object_list_func 
{
    my $full_path = shift;
    opendir (DIR, $full_path) or die "Unable to open $full_path: $!";
    my @files = grep { !/^\.{1,2}$/ } readdir (DIR);
    closedir (DIR);
    @files = map { $full_path . '/' . $_ } @files;
    for (@files) {
        if (-d $_) {
            my $full_path = $_;
            my @path_components = split(/\//,$full_path);
            my $dir = $path_components[$#path_components];
            if ($dir eq "libtess") {
            } else {
                &build_object_list_func ($_);
            }
        } else {
            my $relative_path = $_;
            my @path_components = split(/\//,$relative_path);
            my $source_file = $path_components[$#path_components];
            if ( $source_file =~ m/\.cpp/ ) {
                my $object_file = $source_file;
                $object_file =~ s/^/\$\(OBJS_DIR\)\//g;
                $object_file =~ s/\.cpp$/\.o/g;
                print MYFILE "    $object_file \\\n";
                my $my_val = $object_file;
                unshift @object_list, $my_val;
            }
        }
    } 
}
