'''
Created On 11/10/2010
editor: Matthew Hoggan
'''

import sys
import random
import fileinput
import string
import os

#	EXPERIMENT CLASS USED TO STORE THE EXPERIMENT NUMBER AND THE AMOUNT OF PAY GIVEN FOR THAT EXPERIMENT
class Experiment:																						
	def __init__(self,key,pay):																					#	CONSTRUCTOR
		self.key = key																							#	Experiment Number
		self.pay = pay																							#	Amount Earned for Experiment
		self.instruments=[]																						#	List of all instruments associated with experiment
	def insert(self, instrument, cost):																			#	Insert MEMBER FUNCTION
		instr=Instrument(instrument,cost)																		#	Create and instrument from data passed to insert
		self.instruments.append(instr)																			#	Insert the instrument just created

#	INSTRUMENT CLASS USED TO STORE COST TO USE INSTRUMENT AND THE INSTRUMENTS NUMBER
class Instrument:						
	def __init__(self,key,cost):																				#	CONSTRUCTOR
		self.key=key																							#	Instrument Number
		self.cost=cost																							#	Cost of Number

#	MAIN FUNCTION CALLED FROM 'if __name__ == "__main__":' BELOW
def main():																									
	args=len(sys.argv)																							#	Find out how many arguments were passed in							
	if args<=2:																									#	If file name and # of expereiments not passed in
		sys.stdout.write ('Error (0): Two Few Arguments\n')														#	Notify user
		sys.exit(1)																								#	Exit program
	else:																										#	Continue to extract command line arguments
		file1=sys.argv[1]																						#	File name is first
		num_of_instruments = int(sys.argv[2])																	#	Number of instruments is second
	if os.path.isfile('main_log.conf'):																			#	Check to see if first output file exists
		os.remove('main_log.conf')																				#	Delete first output file if it exists
	file_out = open('main_log.conf', 'w')																		#	Open the first output file
	file_out.write("Output From MaxFlow\n")																		#	Write Title Out to first output file
	file_out.write("-------------------------")																
	ExperimentList=[]																							#	We will need a list of Experiments
	Set=[]																										#	This is used to generate power set of all possible
																												#	experiments that can be done
	SetReadFromFile(Set, ExperimentList, file1)																	#	Read in from file the set of experiemnts as well as
																												#	the Experiemtns and associated instruments
	powset = power_set(Set)																						#	Generate all possible ways to conduct experiment
	Costs=[]																									#	We need to keep track of total cost to use 
																												#	insturments associated with experiement
	for i in range(0, len(powset)):																				#	Initialize all costs to 0
		Costs.append(0);
	Used_Instruments=[]																							#	Keep track of instruments used for previous
																												#	experiemnt
	for x in range(0, num_of_instruments):																		#	Initialize all to 0
		Used_Instruments.append(0)
	FinalCut=[]																									#	Keep Track of Final Income (Expenses Included)
	for i in range(0, len(powset)):																				#	Take the ith power set
		file_out.write('~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n')
		file_out.write('List Of Experiments --> %r\n' % ((powset[i])))
		file_out.write('~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n')
		Income=[]																								#	List of total income
		for j in range(0, len(powset[i])):																		#	Iterate over experiemtns listed in ith power set
			Income.append(int(ExperimentList[int(powset[i][j])-1].pay))											#	Each experiemtn has X income
			for  k in range(0, len(ExperimentList[int(powset[i][j])-1].instruments)):							#	Goin to check all instruments for an experiment
				if Used_Instruments[int(ExperimentList[int(powset[i][j])-1].instruments[k].key)-1] == 0:		#	If not in used instruments for set of experiments 
					file_out.write('Experiment: %3d Instrument: %3d\t\tCost: %6d\n' % (int(powset[i][j]), (int(ExperimentList[int(powset[i][j])-1].instruments[k].key)), (int(ExperimentList[int(powset[i][j])-1].instruments[k].cost))))
					Costs[i] +=  int(ExperimentList[int(powset[i][j])-1].instruments[k].cost)					#	Keep track of cost to use specific instrument once
					Used_Instruments[int(ExperimentList[int(powset[i][j])-1].instruments[k].key)-1] = 1			#	Mark instrument as alread used
		restoreUsedInstrumentsToZero(Used_Instruments, num_of_instruments)										#	Prepare for next power set of experiments
		pay = 0																									#	Initialize pay for power set of experiments
		for income in Income:																					#	Sum up all incomes for all experiments in power set
			pay += income							
		file_out.write('Total Pay: %4d\n' % (pay))								
		file_out.write('~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n')
		file_out.write('Done:\t\t\t\t\t\t\tTotal Cost: %4d' % (Costs[i]))
		file_out.write('%4s-%4d\t=%4d\n' % (' ', pay, (Costs[i]-pay)))
		file_out.write('~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n\n\n')
		FinalCut.append(Costs[i]-pay)																			#	What you really earn is -1*(costs - pay)
		Income=None																								#	Get ready for next power set of experiments
	printFinalCut(FinalCut, powset)
	
def restoreUsedInstrumentsToZero(Used_Instruments, num_of_instruments):
	for j in range(0, num_of_instruments):
			Used_Instruments[j]=0

def printFinalCut(FinalCut, powset):
	num = 0
	if os.path.isfile('final_cut_log.conf'):
		os.remove('final_cut_log.conf')
	file_out = open('final_cut_log.conf', 'w')
	for i in FinalCut:
		file_out.write('Final Cut on(%5d): ' % (num+1))
		file_out.write('%r' % powset[num])
		file_out.write(' = %d\n' % (i))
		num += 1
	file_out.write('\n\n\n')
	file_out.write('~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n')
	FinalCut.sort()
	count = 0;
	for i in FinalCut:
		if count != 0 and count%20 == 0:
			file_out.write('\n\n')
		file_out.write('%4d ' % i)
		count+=1
			
def printCosts(Costs, powset):
	num = 0
	for i in Costs:
		sys.stdout.write('Cost for :')
		sys.stdout.write('%r' % powset[num])
		sys.stdout.write(' = %d\n' % (i))
		num += 1
		
def printPowSet(powset):
	for i in powset:
		sys.stdout.write('%r\n' % i)

def printData(ExperimentList):
	item = 0
	for i in ExperimentList:
		sys.stdout.write('%s(%s) -> ' % (i.key,i.pay))
		list_of_instruments = ExperimentList[item].instruments
		item += 1
		for j in list_of_instruments:
			sys.stdout.write('%s(%s) -> ' % (j.key,j.cost))
		sys.stdout.write('\n')
	
def power_set(Set):
    r = [[]]
    for e in Set:
        r += [x+[e] for x in r]
    return r
		
def SetReadFromFile(Set, DataList, file):
	linecount=0
	for line in fileinput.input([file]):
		data=line.split(',')
		str=data[0]
		info=str.split('|')
		Set.append(info[0])
		ex = Experiment(info[0],info[1])
		for i in range(1, len(data)):
			instrument_data = data[i].split('|')
			ex.insert(instrument_data[0].rstrip('\n'),instrument_data[1].rstrip('\n'))
		DataList.append(ex)
	linecount += linecount
		
if __name__ == "__main__":
	main()

	
	
