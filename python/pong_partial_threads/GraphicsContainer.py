'''
Created on Nov 28, 2009
@author: Matthew Hoggan
'''

import sys

from PyQt4.QtCore import *
from PyQt4.QtGui import *
from MainWindow import *
from Ball import *
from Paddle import *

class GraphicsContainer(QGraphicsScene):
    def __init__(self, w, h):
        QGraphicsScene.__init__(self)
        self.MaxWidth = w
        self.MaxHeight = h
        self.setSceneRect(0, 0, 400, 350)
        self.ball = Ball(200, 175, 10, 10, self.MaxWidth, self.MaxHeight)
        self.l_paddle = Paddle(0, 125, 20, 100, self.MaxHeight, "Left Paddle")
        self.r_paddle = Paddle(380, 125, 20, 100, self.MaxHeight, "Right Paddle")
        self.addItem(self.ball)
        self.addItem(self.l_paddle)
        self.addItem(self.r_paddle)