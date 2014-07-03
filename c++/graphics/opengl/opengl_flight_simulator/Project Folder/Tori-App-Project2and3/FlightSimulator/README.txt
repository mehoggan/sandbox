This is the final project.

The contorls are according to spec, however I made the speed of the ship faster. Also if you hit 'd' while in game it will produce a new text area with debug
info for torpedos that are still flying around.

To make this project please do the following. Open up the visual studio command prompt, change directory into the folder where you have the files and type 'nmake
Makefile.mak' if you get a compiler error it is most likly because you need to open up the make file and change the following line

'VERSION = 10.0' to VERSION = <Your Version Here>

If this does not work for you, you can always take the source and add it to a Visual Studio Project. I have also tried to make it safe to be compiled in Linux. However,
one would have to modify a line in each header to set things up correctly.