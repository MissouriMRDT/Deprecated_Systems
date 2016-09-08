import sys
from PyQt4 import QtCore, QtGui
from ui_mainwindow import Ui_MainWindow

class StartQT4(QtGui.QMainWindow):
    def __init__(self, parent=None):
        QtGui.QWidget.__init__(self, parent)
        self.ui = Ui_MainWindow()
        self.ui.setupUi(self)

    def fix_margins(self):
        """
            Spacing doesn't go through with pyuic4 utility for some reason.
            This block just shifts to how it should be done in ui_mainwindow.py
        """
        self.ui.verticalLayout_2.setContentsMargins(0, 11, 11, 11)
        self.ui.verticalLayout_2.setSpacing(0)
        self.ui.inputFrame.setContentsMargins(25, 11, 11, 0)

        
if __name__ == "__main__":
    app = QtGui.QApplication(sys.argv)
    myapp = StartQT4()
    myapp.show()
    sys.exit(app.exec_())