'''
Created on Nov 29, 2009

@author: Matthew
'''

from PyQt4.QtCore import *
from PyQt4.QtGui import *
from GraphicsContainer import *

class b_Thread(QThread):
    def __init__(self):
        QThread.__init__(self)
        
    def run(self):
        print "Thread called"
        