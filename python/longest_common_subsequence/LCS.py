#!/usr/bin/python2.7

'''
Created On 11/10/2010
editor: Matthew Hoggan
'''

import sys
import random

#	PROXY MAIN FUNCTION REAL
def main():
	args=len(sys.argv)						#	Obtain the num of arguments passed on command line
	if args<=1:							#	No arguments passed on command line
		sys.stdout.write ('Error: Two Few Arguments\n')										
		sys.exit(1)
	elif args>3:							#	More than the program and two strings passed in
		sys.stdout.write ('LCS only solves for two strings\n')
		sys.exit(1)
	else:								#	Only two
		str1="0"+sys.argv[1]					#	The length of sequence 1 m
		str2="0"+sys.argv[2]					#	The length of sequence 2 n
		SIZE1=len(str1)						#	Sequence 2
		SIZE2=len(str2)						#	Sequence 1
		sys.stdout.write ('\nGoing to solve for: %s(%d) & %s(%d)\n' % (str1,len(str1),str2,len(str2)))	
	sys.stdout.write('\n')
	T = []								#	Table used when computing											
	TT = []
	#	FILL IN THE TABLE
	for row in range(0, SIZE2):					#	SIZE2 number of rows (string 2)
		T.append([])						#	Append a list at each row																	
		TT.append([])
		for col in range(0, SIZE1):				#	SIZE1 number of columns (string 1)
			T[row].append(0)				#	Append m 0's to the list
			TT[row].append("0")
	
	for row in range(1, SIZE2):
		for col in range(1,SIZE1):
			if str1[col]==str2[row]:
				T[row][col]=T[row-1][col-1]+1
				store="\\"+str(T[row-1][col-1]+1)
				TT[row][col]=store
			elif str1[col]!=str2[row]:
				T[row][col]=max(T[row][col-1],T[row-1][col])
				store=max_val_str(TT,T[row][col-1],T[row-1][col])
				TT[row][col]=store
	print()								#	display(T,str1,str2)
	display_graphics(TT,str1,str2) 					#	Display end result

#	FUNCTION TO FIND MAX OF TWO NUMBERS
def max(val1,val2):
	if val1 > val2:
		return val1
	elif val2 >= val1:
		return val2
	
#	FUNCTION TO FIND MAX OF TWO NUMBERS AND STORE IN STRING TABLE
def max_val_str(TT,val1,val2):
	str_val=""
	if val1 > val2:
		str_val="-"+str(val1)
	elif val2 >= val1:
		str_val="|"+str(val2)
	return str_val
	
#	FUNCTION TO DIPLAY TABLE
def display(T,str1,str2):						
	SIZE1=len(str1)							#	Get length of str1
	SIZE2=len(str2)							#	Get length of str2
	sys.stdout.write ('    ')					
	for col in range(0, SIZE1):					#	Print out str1
		sys.stdout.write ("%8s" % (str1[col]))
	sys.stdout.write ('\n')
	for col in range(0, SIZE1):					#	Print out divider
		sys.stdout.write ("%s" % "---------") 
	sys.stdout.write('\n')
	for row in range(0, SIZE2):					#	Print out col and str2
		sys.stdout.write ("%2s |\n" % ("  "))			#	Print out formating
		sys.stdout.write ("%2s |" % str2[row]) 			#	Print out row_th char
		for col in range(0, SIZE1):
			sys.stdout.write ("%8s" % T[row][col])		#	Iterate over list at row and print out table
		print ('')
	print ('\n\t\t\tDONE\n')
	
def display_graphics(TT,str1,str2):						
	SIZE1=len(str1)							#	Get length of str1
	SIZE2=len(str2)							#	Get length of str2
	sys.stdout.write ('    ')											
	for col in range(0, SIZE1):					#	Print out str1
		sys.stdout.write ("%8s" % (str1[col]))
	sys.stdout.write ('\n')
	for col in range(0, SIZE1):					#	Print out divider
		sys.stdout.write ("%s" % "---------") 
	sys.stdout.write('\n')
	for row in range(0, SIZE2):					#	Print out col and str2
		sys.stdout.write ("%2s |\n" % ("  "))			#	Print out formating
		sys.stdout.write ("%2s |" % str2[row]) 			#	Print out row_th char
		for col in range(0, SIZE1):
			sys.stdout.write ("%8s" % TT[row][col])		#	Iterate over list at row and print out table
		print ('')
	print ('\n\t\t\tDONE\n')

#	DEFINE A MAIN FUNCTION TO BE LIKE C	
if __name__ == "__main__":
	main()
