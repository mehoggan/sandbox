'''
Created On 11/10/2010
editor: Matthew Hoggan
'''

import sys
import random
import fileinput
import string

LONG_MAX=9223372036854775807

class Edge:
	def __init__(self,u,v,edgeVal):
		self.u=u
		self.v=v
		self.edgeWeight=edgeVal
		
class Vertex:
	def __init__(self,key,distance,parent):
		self.key=key
		self.d=distance
		self.p=parent

		#	DEFINE A MAIN FUNCTION TO BE LIKE C	
		
#	PROXY MAIN FUNCTION REAL
def main():
	args=len(sys.argv)																		#	Obtain the num of arguments passed on command line
	if args<=1:																				#	No arguments passed on command line
		sys.stdout.write ('Error (0): Two Few Arguments\n')										
		sys.exit(1)
	else:
		file=sys.argv[1]
	
	EList = []
	VList=[]
	sys.stdout.write ('\nStatic: Johnson Algorithm with Bellman-Ford and Dijkstra on File: %s' % file)	
	sys.stdout.write('\n')
	
	#	READ DATA IN FROM FILE
	sys.stdout.write('-----------------------------------------------------------------------------\n')
	sys.stdout.write('Initialization State\n')
	sys.stdout.write('-----------------------------------------------------------------------------\n')
	linecount=0	
	for line in fileinput.input([file]):
		data=line.split(',')
		u=data[0]
		v=data[1]
		d=int(data[2])
		if linecount == 0 and u != 's':
			sys.stdout.write('Error (1): You Must place s as very first vertex\n')
			sys.exit(1)
		else:
			linecount+=1
		if listDoesNotContainVertex(VList, u):
			if u == 's':
				VList.append(Vertex(u,LONG_MAX,None))
			else:
				VList.append(Vertex(u,0,VList[0]))
		if listDoesNotContainVertex(VList, v):
			VList.append(Vertex(v,0,VList[0]))
		u_insert=locateVertex(VList,u)
		v_insert=locateVertex(VList,v)
		if u_insert==None or v_insert==None:
			sys.stdout.write('Error (2): Edge Insertion Error\n')
			sys.exit(2)
		else:
			EList.append(Edge(u_insert,v_insert,d))	
	if not EList or not VList:
		sys.stdout.write('Error (3): Empty Lists Do Not Help\n')
		sys.exit(3)
	EDGES=len(EList)
	VERTICES=len(VList)
	printEdgeList(EList)
	printVertexInfo(VList)
	sys.stdout.write('Post Initialization\n')
	sys.stdout.write('-----------------------------------------------------------------------------\n')
	sys.stdout.write('$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$\n')
	#	END OF READ DATA FROM FILE
	
	#	BELLMAN-FORD ALGORITHM
	sys.stdout.write('-----------------------------------------------------------------------------\n')
	sys.stdout.write('The size of the adjacency list contains (%d) edges and there are (%d) vertices\n' % (EDGES, VERTICES))
	for V in range(0,VERTICES):
		for E in range(0,EDGES):
			if EList[E].v.d > EList[E].u.d + EList[E].edgeWeight:
				EList[E].v.d = EList[E].u.d + EList[E].edgeWeight
				EList[E].v.p = EList[E].u
	#	END OF BELLMAN-FORD ALGORITHM
	
	#	GET RID OF S AND ITS EDGES
	sys.stdout.write('-----------------------------------------------------------------------------\n')
	for E in range(0,VERTICES-1):
		EList.pop(0)
	EDGES=len(EList)
	VList.pop(0)
	VERTICES=len(VList)
	printEdgeList(EList)
	printVertexInfo(VList)
	sys.stdout.write('After Bellman-Ford there are (%d) edges and there are (%d) vertices\n' % (EDGES, VERTICES))
	sys.stdout.write('-----------------------------------------------------------------------------\n')
	sys.stdout.write('$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$\n')
	#	FINISHED GETTING RID OF S AND ITS EDGES
	
	#	JOHNSON REDUCTION FORMULA
	sys.stdout.write('-----------------------------------------------------------------------------\n')
	sys.stdout.write('Johnson Reduction Formula\n')
	sys.stdout.write('-----------------------------------------------------------------------------\n')
	for E in range(0,EDGES):
		EList[E].edgeWeight = EList[E].edgeWeight + EList[E].u.d - EList[E].v.d	
	printEdgeList(EList)
	printVertexInfo(VList)
	sys.stdout.write('End of Johnson Reduction (Prepare for Dijkstra\'s\n')
	sys.stdout.write('-----------------------------------------------------------------------------\n')
	sys.stdout.write('$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$\n')
	#	END OF JOHNSON REDUCTION FORMULA
	
	# DIJKSTRA'S ALGORITHM V TIMES
	sys.stdout.write('-----------------------------------------------------------------------------\n')
	sys.stdout.write('Dijkstra\'s Algorithm V Times\n')
	sys.stdout.write('-----------------------------------------------------------------------------\n')
	for V in range(0,VERTICES):
		VQueue=list(VList)
		start=VQueue[V]
		for X in VQueue:
			X.d=LONG_MAX
			X.p=None
		start.d=0				
		while VQueue:
			VQueue=sorted(VQueue, key=distance)	
			u=VQueue.pop(0)
			sys.stdout.write('%s -- (%d)' % (u.key, u.d))
			if u.p:
				sys.stdout.write('-- (%s)\n' % (u.p.key))
			else:
				sys.stdout.write('\n')
			for E in EList:
				if E.u.key==u.key:
					v=E.v
					if v.d > u.d + E.edgeWeight:
						v.d = u.d + E.edgeWeight
						v.p = u
						
		sys.stdout.write('------------------------------\n')
	#	END OF DIJKSTRA'S ALGORITHM

#	FUNCTION TO RETURN THE DISTANCE CONTAINED IN VECTOR
def distance(v):
	return v.d
		
#	FUNCTION THAT RETURNS A POINTER TO A VERTEX IN LIST
def locateVertex(VList,key):
	n=None
	for i in range(0, len(VList)):
		if VList[i].key==key:
			n=VList[i]
			break
	return n
	
# 	FUNCTION THAT CHECKS LIST IF IT CONTAINS VALUE
def listDoesNotContainVertex(VList, key):
	if not VList:
		return True
	else:
		for i in range(0, len(VList)):
			if VList[i].key==key:
				return False
	return True
	
#	FUNTION TO PRINT OUT THE WEIGHTS OF VERTICIES
def printVertexInfo(VList):
	sys.stdout.write('Vertex List\n')
	for i in range(0,len(VList)):
		sys.stdout.write('Key = %4s ' % VList[i].key)
		if VList[i].d==LONG_MAX:
			sys.stdout.write('-- Distance = infinity')
		else:
			sys.stdout.write('-- Distance = %8d' % VList[i].d)
		if VList[i].p != None:
			sys.stdout.write(' -- Parent = %4s\n' % VList[i].p.key)
		else:
			sys.stdout.write('\n')
	sys.stdout.write('-----------------------------------------------------------------------------\n')
	
#	FUNCTION TO PRINT OUT EDGELIST	
def printEdgeList(EList):
	for E in EList:
		sys.stdout.write('%s --> %s (%d)\n' % (E.u.key, E.v.key, E.edgeWeight))
	sys.stdout.write('-----------------------------------------------\n')
		
#	TEST DATA AREA
def Initialize(EList, VList):
	VList.append(Vertex('s',LONG_MAX,None))					#	VList[0]=s
	VList.append(Vertex('a',0,VList[0]))					#	VList[1]=a
	VList.append(Vertex('b',0,VList[0]))					#	VList[2]=b
	VList.append(Vertex('c',0,VList[0]))					#	VList[3]=c
	VList.append(Vertex('d',0,VList[0]))					#	VList[4]=d
	VList.append(Vertex('e',0,VList[0]))					#	VList[5]=e
	VList.append(Vertex('f',0,VList[0]))					#	VList[6]=f
	VList.append(Vertex('g',0,VList[0]))					#	VList[7]=g
		
	EList.append(Edge(VList[0],VList[1],0))					#	(s,a)
	EList.append(Edge(VList[0],VList[2],0))					#	(s,b)
	EList.append(Edge(VList[0],VList[3],0))					#	(s,c)
	EList.append(Edge(VList[0],VList[4],0))					#	(s,d)
	EList.append(Edge(VList[0],VList[5],0))					#	(s,e)
	EList.append(Edge(VList[0],VList[6],0))					#	(s,f)
	EList.append(Edge(VList[0],VList[7],0))					#	(s,g)
	EList.append(Edge(VList[1],VList[2],4))					#	(a,b)
	EList.append(Edge(VList[1],VList[6],7))					#	(a,f)
	EList.append(Edge(VList[2],VList[7],-6))				#	(b,g)
	EList.append(Edge(VList[3],VList[2],-3))				#	(c,b)
	EList.append(Edge(VList[3],VList[6],10))				#	(c,f)
	EList.append(Edge(VList[4],VList[2],20))				#	(d,b)
	EList.append(Edge(VList[4],VList[3],28))				#	(d,c)
	EList.append(Edge(VList[5],VList[1],-5))				#	(e,a)
	EList.append(Edge(VList[5],VList[2],7))					#	(e,b)
	EList.append(Edge(VList[5],VList[4],16))				#	(e,d)
	EList.append(Edge(VList[5],VList[6],-1))				#	(e,f)
	EList.append(Edge(VList[6],VList[4],-8))				#	(f,d)
	EList.append(Edge(VList[7],VList[3],12))				#	(g,c)
	EList.append(Edge(VList[7],VList[4],5))					#	(g,d)
	EList.append(Edge(VList[7],VList[6],-2))				#	(g,f)
	
#	IF PYTHON MOULE SPECIFIED AT COMMAND LINE THEN THIS IS ENTRY INTO PROGRAM
if __name__ == "__main__":
	main()

	
	