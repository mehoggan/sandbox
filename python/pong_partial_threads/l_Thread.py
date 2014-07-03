'''
Created on Nov 29, 2009

@author: Matthew
'''


from PyQt4.QtCore import *
from PyQt4.QtGui import *
from GraphicsContainer import *

class l_Thread(QThread):
    def __init__(self):
        QThread.__init__(self)
        self.direction = 0
        
    def __del__(self):
        self.exiting()
        self.wait()
    
    def run(self):
        print "Thread called"
        self.emit(SIGNAL("output(int)"), self.direction)
        
    def initiate(self, val, paddle):
        self.direction =  val
        self.paddle = paddle
        print "The value to be added to " + paddle + " paddle is" + (str)(self.direction)
        self.start()