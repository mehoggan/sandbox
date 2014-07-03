'''
Created on Nov 28, 2009
@author: Matthew Hoggan
'''

import sys

from PyQt4.QtCore import *
from PyQt4.QtGui import *
from MainWindow import *

class Paddle(QGraphicsRectItem):
    def __init__(self, x, y, w, h, mh, name):
        QGraphicsEllipseItem.__init__(self)
        self.x_pos = x
        self.y_pos = y
        self.width = w
        self.height = h
        self.name = name
        self.MaxHeight = (mh/2)
        print "Building " + name + " which has a x_pos = " + (str)(self.x_pos) + " y_pos = " + (str)(self.y_pos) + " width = " + (str)(self.width) + " height = " + (str)(self.height) + " and Maximum Height = " + (str)(self.MaxHeight)
        brush = QBrush(QColor("#000000"))
        pen = QPen(QColor("#000000"))
        self.setPen(pen)
        self.setBrush(brush)
        self.setRect(self.x_pos, self.y_pos, self.width, self.height)
    
    def move_paddle(self, val, key):
        print "Move paddle function called"    
        if((key == Qt.Key_Q or key == Qt.Key_P)):
            if(self.y_pos > 0):
                self.y_pos = self.y_pos + val
                self.setRect(self.x_pos, self.y_pos, self.width, self.height)
        elif((key == Qt.Key_A or key == Qt.Key_L)):
            if(self.y_pos < 250):
                self.y_pos = self.y_pos + val
                self.setRect(self.x_pos, self.y_pos, self.width, self.height)
        else:
            print "???"
        