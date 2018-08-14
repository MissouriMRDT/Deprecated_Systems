import sys
<<<<<<< HEAD
from PyQt4 import QtGui
from PyQt4 import QtCore
try:
    from PyQt4.QtCore import QString
except ImportError:
    QString = str

# from matplotlib.backends.backend_qt4agg import FigureCanvasQTAgg as FigureCanvas # Canvas object
# from matplotlib.backends.backend_qt4agg import NavigationToolbar2QT as NavigationToolbar # Toolbar object
# import matplotlib.pyplot as plt
# import random

from SiteTab import SiteTab
from ui_mainwindow import Ui_MainWindow
=======
from PyQt4 import QtGui, QtCore
import customWidgets

# TO DO: functions - parse file name, parse file matching name if exists, plot data
>>>>>>> origin/barebones

class StartQT4(QtGui.QMainWindow):
    __site_num = 0

    def __init__(self, parent=None):
        QtGui.QWidget.__init__(self, parent)
<<<<<<< HEAD

        self.ui = Ui_MainWindow()
        self.ui.setupUi(self)

        # TODO: delet this
        self.ui.saveGraphsButton.clicked.connect(self.save)

    def save(self):
        self.__site_num += 1
        self.newTab = SiteTab()
        self.newTab.setup()
        self.ui.digsiteTabs.addTab(self.newTab, QString("Digsite #%s" % (self.__site_num)))
=======
        self.resize(946, 542)
        self.setSizeIncrement(QtCore.QSize(1,1))
        self.centralWidget = QtGui.QWidget(self)
        self.digMainLayout = QtGui.QVBoxLayout(self.centralWidget)
        self.digMainLayout.setMargin(11)
        self.digMainLayout.setSpacing(6)

        self.inputFrame = QtGui.QHBoxLayout()
        self.inputFrame.setMargin(11)
        self.inputFrame.setSpacing(6)

        self.fileInput = QtGui.QLineEdit(self.centralWidget)
        self.fileInput.setMinimumSize(QtCore.QSize(400, 0))
        self.fileInput.setMaximumSize(QtCore.QSize(400, 16777215))
        spacerItem = QtGui.QSpacerItem(40, 20, QtGui.QSizePolicy.Expanding, QtGui.QSizePolicy.Minimum)
        self.graphButton = QtGui.QPushButton("Graph", self.centralWidget)
        self.inputFrame.addWidget(self.fileInput)
        self.inputFrame.addWidget(self.graphButton)
        self.inputFrame.addItem(spacerItem)

        self.displayFrame = QtGui.QHBoxLayout()
        self.displayFrame.setMargin(11)
        self.displayFrame.setSpacing(6)

        # sensor enables go here

        self.graphTabs = QtGui.QTabWidget()

        self.basic = QtGui.QWidget()
        self.basicGraphLayout = QtGui.QHBoxLayout(self.basic)
        self.basicGraphLayout.setMargin(0)
        self.basicGraph = customWidgets.GraphArea(self.basic)
        self.basicGraphLayout.addWidget(self.basicGraph)
        self.graphTabs.addTab(self.basic, "Temp/Humid")

        self.spectrometer = QtGui.QWidget()
        self.spectrometerGraphLayout = QtGui.QHBoxLayout(self.spectrometer)
        self.spectrometerGraphLayout.setMargin(0)
        self.spectrometerGraph = customWidgets.GraphArea(self.spectrometer)
        self.spectrometerGraphLayout.addWidget(self.spectrometerGraph)
        self.graphTabs.addTab(self.spectrometer, "Spectrometer")

        self.digMainLayout.addLayout(self.inputFrame)
        self.displayFrame.addWidget(self.graphTabs)
        self.digMainLayout.addLayout(self.displayFrame)
        self.setCentralWidget(self.centralWidget)



>>>>>>> origin/barebones


if __name__ == "__main__":
    app = QtGui.QApplication(sys.argv)
    myapp = StartQT4()
    myapp.show()
    sys.exit(app.exec_())