import matplotlib.pyplot as plt
import numpy as np
from PyQt4 import QtGui
from matplotlib.backends.backend_qt4agg import FigureCanvasQTAgg as FigureCanvas
from matplotlib.backends.backend_qt4agg import NavigationToolbar2QT as NavigationToolbar

class GraphArea(QtGui.QWidget):
    def __init__(self, parent=None):
        """ Initial setup of the UI """
        super(GraphArea, self).__init__()

        self.temp1_data = []
        self.temp2_data = []
        self.temp3_data = []
        self.temp4_data = []

        self.temp1_time = []
        self.temp2_time = []
        self.temp3_time = []
        self.temp4_time = []

        self.humid1_data = []
        self.humid2_data = []
        self.humid4_data = []
        self.humid3_data = []

        self.humid1_time = []
        self.humid2_time = []
        self.humid3_time = []
        self.humid4_time = []

        #self.ccd_data = [[] for y in range(numline)]
        self.data_len = []
        self.max_len = 0
        self.row_count = 0

        self.setup()

    def setup(self):
        displayFrame = QtGui.QVBoxLayout(self)
        self.fig = plt.figure(1) # this may cause a problem with multiple figures
        canvas = FigureCanvas(self.fig)
        toolbar = NavigationToolbar(canvas, self)
        displayFrame.addWidget(canvas)
        displayFrame.addWidget(toolbar)

    def graphBasic(self):
        plt.ion()
        plt.suptitle("Soil Readings", fontsize=17)

        # Temperature Subplot
        plt.subplot(2, 1, 1)
        plt.title("Temperature")
        plt.ylabel("Temperature (Celsius)")
        plt.grid(True)
        plt.ylim(0, 50)
        plt.xticks(ha='right', rotation=15)
        plt.plot_date(x=self.temp1_time, y=self.temp1_data, color = "blue", label = "temp1")
        plt.plot_date(x=self.temp2_time, y=self.temp2_data, color = "black", label = "temp2")
        plt.plot_date(x=self.temp3_time, y=self.temp3_data, color = "dark green", label = "temp3")
        plt.plot_date(x=self.temp4_time, y=self.temp4_data, color = "maroon", label = "temp4")

        # Humidity Subplot
        plt.subplot(2, 1, 2)
        plt.title("Humidity")
        plt.ylabel("Water Content (%)")
        plt.grid(True)
        plt.ylim(0, 100)
        plt.xticks(ha='right', rotation=15)
        plt.plot_date(x=self.humid1_time, y=self.humid1_data, color = "gold", label = "humid1")
        plt.plot_date(x=self.humid2_time, y=self.humid2_data, color = "salmon", label = "humid2")
        plt.plot_date(x=self.humid3_time, y=self.humid3_data, color = "medium orchid", label = "humid3")
        plt.plot_date(x=self.humid4_time, y=self.humid4_data, color = "light green", label = "humid4")

        plt.show()

    def graphSpectrometer(self):
        plt.ion()
        plt.delaxes()
        plt.grid(True)
        plt.xlim(xmin=0, xmax=self.max_len)
        plt.ylim(ymin=0, ymax=1023)
        plt.plot(np.arange(start=0, stop=self.data_len[self.row_count], step=1), self.ccd_data[self.row_count])
        plt.show()
        plt.pause(0.0001)


# color picker: http://www.w3schools.com/colors/colors_hex.asp