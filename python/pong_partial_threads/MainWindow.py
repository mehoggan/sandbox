'''
Created on Nov 28, 2009
@author: Matthew Hoggan
'''
import sys

from PyQt4.QtCore import *
from PyQt4.QtGui import *
from GraphicsContainer import *
from l_Thread import *
from r_Thread import *
from b_Thread import *

class MainWindow(QGraphicsView):
    def __init__(self):
        QGraphicsView.__init__(self)
        self.setGeometry(600, 400, 0, 0)
        self.setMinimumSize(QSize(400, 350))
        self.setMaximumSize(QSize(400, 350))
        self.setHorizontalScrollBarPolicy(1)
        self.setVerticalScrollBarPolicy(1)
        self.Container = GraphicsContainer(400, 350)
        self.setScene(self.Container)
        self.l_Paddle = l_Thread()
        self.r_Paddle = r_Thread()
        self.p_Paddle = b_Thread()
        self.connect(self.l_Paddle, SIGNAL("terminated()"), self.Container.l_paddle.move_paddle)
        self.connect(self.l_Paddle, SIGNAL("finished()"), self.Container.l_paddle.move_paddle)
        self.connect(self.l_Paddle, SIGNAL("output(int)"), self.Container.l_paddle.move_paddle)
        self.connect(self.r_Paddle, SIGNAL("terminated()"), self.Container.l_paddle.move_paddle)
        self.connect(self.r_Paddle, SIGNAL("finished()"), self.Container.l_paddle.move_paddle)
        self.connect(self.r_Paddle, SIGNAL("output(int)"), self.Container.l_paddle.move_paddle)
        
        
    def keyPressEvent(self, event):
        if event.key() == Qt.Key_Escape:
            self.close()
        if event.key() == Qt.Key_Q:
            #self.Container.l_paddle.move_paddle(-1, event.key())
            self.l_Paddle.initiate(-1, event.key)
        elif event.key() == Qt.Key_A:
            #self.Container.l_paddle.move_paddle(1, event.key())
            self.l_Paddle.initiate(1, event.key)
        elif event.key() == Qt.Key_P:
            #self.Container.r_paddle.move_paddle(-1, event.key())
            self.l_Paddle.initiate(-1, event.key)
        elif event.key() == Qt.Key_L:
            #self.Container.r_paddle.move_paddle(1, event.key())
            self.l_Paddle.initiate(1, event.key)

'''
This is for comments
'''