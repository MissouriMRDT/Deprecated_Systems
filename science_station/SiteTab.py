import matplotlib.pyplot as plt
from PyQt4 import QtCore
from PyQt4 import QtGui
from matplotlib.backends.backend_qt4agg import FigureCanvasQTAgg as FigureCanvas
from matplotlib.backends.backend_qt4agg import NavigationToolbar2QT as NavigationToolbar


try:
    _fromUtf8 = QtCore.QString.fromUtf8
except AttributeError:
    def _fromUtf8(s):
        return s


class SiteTab(QtGui.QWidget):
    def __init__(self, parent=None):
        """ Initial setup of the UI """
        super(SiteTab, self).__init__()

    def setup(self):
        displayFrame = QtGui.QVBoxLayout(self)
        self.fig = plt.figure(1)
        canvas = FigureCanvas(self.fig)
        toolbar = NavigationToolbar(canvas, self)
        displayFrame.addWidget(canvas)
        displayFrame.addWidget(toolbar)