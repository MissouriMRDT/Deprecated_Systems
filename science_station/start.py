import sys
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

class StartQT4(QtGui.QMainWindow):
    __site_num = 0

    def __init__(self, parent=None):
        QtGui.QWidget.__init__(self, parent)

        self.ui = Ui_MainWindow()
        self.ui.setupUi(self)

        # TODO: delet this
        self.ui.saveGraphsButton.clicked.connect(self.save)

    def save(self):
        self.__site_num += 1
        self.newTab = SiteTab()
        self.newTab.setup()
        self.ui.digsiteTabs.addTab(self.newTab, QString("Digsite #%s" % (self.__site_num)))


if __name__ == "__main__":
    app = QtGui.QApplication(sys.argv)
    myapp = StartQT4()
    myapp.show()
    sys.exit(app.exec_())