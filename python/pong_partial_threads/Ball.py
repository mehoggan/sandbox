'''
Created on Nov 28, 2009
@author: Matthew Hoggan
'''

import sys

from PyQt4.QtCore import *
from PyQt4.QtGui import *
from MainWindow import *

class Ball(QGraphicsEllipseItem):
    def __init__(self, x, y, w, h, mw, mh):
        QGraphicsEllipseItem.__init__(self)
        self.MaxWidth = mw
        self.MaxHeight = mh
        self.brush = QBrush(QColor("#000000"))
        self.pen = QPen(QColor("#000000"))
        self.setPen(self.pen)
        self.setBrush(self.brush)
        self.setRect(x, y, w, h)