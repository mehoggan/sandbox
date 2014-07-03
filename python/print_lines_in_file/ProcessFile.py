import fileinput

def OpenFile(filein, fileout):
	FILE = open(fileout, 'w')
	for line in fileinput.input([filein]):
		print line
		FILE.writeln(line)

OpenFile("C:\Documents and Settings\Matthew\Desktop\PythonScripts\Process_List.txt", "C:\Documents and Settings\Matthew\Desktop\PythonScripts\Process_List_Out.txt")
	