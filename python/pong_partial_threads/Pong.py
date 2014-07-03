'''
Created on Nov 28, 2009
@author: Matthew Hoggan
'''

import sys

from PyQt4.QtCore import *
from PyQt4.QtGui import *
from MainWindow import *

def main(argv = sys.argv):
    app = QApplication(argv)
    Pong = MainWindow()
    Pong.show()
    return app.exec_()

if __name__ == "__main__":
    sys.exit(main())