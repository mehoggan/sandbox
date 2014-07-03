#!/usr/bin/python

ins = open( "kernel.dump", "r" )
array = []
for line in ins:
    array.append( line )
ins.close( )

ins = open( "kernel.dump.rev", "w" )
for bytes in array:
    bytes = bytes.rstrip( )
    line = bytes.split( ' ' )
    line.reverse();
    string = ''.join(line)
    string += '\n'
    ins.write(string);
ins.close( )
