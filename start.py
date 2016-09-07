import sys
from PyQt4 import QtGui
from matplotlib.backends.backend_qt4agg import FigureCanvasQTAgg as FigureCanvas # Canvas object
from matplotlib.backends.backend_qt4agg import NavigationToolbar2QT as NavigationToolbar # Toolbar object
import matplotlib.pyplot as plt
import random

from ui_mainwindow import Ui_MainWindow

class StartQT4(QtGui.QMainWindow):
    def __init__(self, parent=None):
        QtGui.QWidget.__init__(self, parent)

        self.ui = Ui_MainWindow()
        self.ui.setupUi(self)

        self.tempGraphFigure = plt.figure(1)
        # create canvas
        self.tempGraphCanvas = FigureCanvas(self.tempGraphFigure)
        # create toolbar
        self.tempGraphToolbar = NavigationToolbar(self.tempGraphCanvas, self)
        # layout the graph area
        tempGraphLayout = QtGui.QVBoxLayout()
        tempGraphLayout.addWidget(self.tempGraphCanvas)
        tempGraphLayout.addWidget(self.tempGraphToolbar)

        # TODO: delet this
        self.button = QtGui.QPushButton('Plot')
        self.button.clicked.connect(self.plot)
        tempGraphLayout.addWidget(self.button)

        # add widget into horizontalLayout_3
        self.ui.horizontalLayout_3.addLayout(tempGraphLayout)

        # self.plainTextEdit_4 = QtGui.QPlainTextEdit(self.ui.tab_4)
        # self.plainTextEdit_4.setObjectName(_fromUtf8("plainTextEdit_4"))

    def plot(self):
        data = [random.random() for i in range(10)]
        ax = self.tempGraphFigure.add_subplot(111)
        ax.hold(False)
        ax.plot(data, '*-')
        self.tempGraphCanvas.draw()

if __name__ == "__main__":
    app = QtGui.QApplication(sys.argv)
    myapp = StartQT4()
    myapp.show()
    sys.exit(app.exec_())