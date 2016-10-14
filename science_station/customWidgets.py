import matplotlib.pyplot as plt
import numpy as np
from PyQt4 import QtGui
from matplotlib.backends.backend_qt4agg import FigureCanvasQTAgg as FigureCanvas
from matplotlib.backends.backend_qt4agg import NavigationToolbar2QT as NavigationToolbar


class DataStore:
    def __init__(self):
        self.temp1 = []
        self.temp2 = []
        self.temp3 = []
        self.temp4 = []
        self.humid1 = []
        self.humid2 = []
        self.humid3 = []
        self.humid4 = []


class GraphArea(QtGui.QWidget):
    def __init__(self):
        """ Initial setup of the UI """
        super(GraphArea, self).__init__()
        # self.ccd_data = [[] for y in range(numline)]
        self.fig = plt.figure()  # this may cause a problem with multiple figures
        self.canvas = FigureCanvas(self.fig)
        self.data_len = []
        self.max_len = 0
        self.row_count = 0
        self.setup()

    def setup(self):
        display_frame = QtGui.QVBoxLayout(self)
        toolbar = NavigationToolbar(self.canvas, self)
        display_frame.addWidget(self.canvas)
        display_frame.addWidget(toolbar)

    def graph_basic(self, ds: DataStore):
        if len(np.array(ds.temp1)) > 0:
            temp1_time, temp1_data = np.array(ds.temp1).T
        if len(np.array(ds.temp2)) > 0:
            temp2_time, temp2_data = np.array(ds.temp2).T
        if len(np.array(ds.temp3)) > 0:
            temp3_time, temp3_data = np.array(ds.temp3).T
        if len(np.array(ds.temp4)) > 0:
            temp4_time, temp4_data = np.array(ds.temp4).T

        if len(np.array(ds.humid1)) > 0:
            humid1_time, humid1_data = np.array(ds.humid1).T
        if len(np.array(ds.humid2)) > 0:
            humid2_time, humid2_data = np.array(ds.humid2).T
        if len(np.array(ds.humid3)) > 0:
            humid3_time, humid3_data = np.array(ds.humid3).T
        if len(np.array(ds.humid4)) > 0:
            humid4_time, humid4_data = np.array(ds.humid4).T

        # Temperature Subplot
        temp_subplot = self.fig.add_subplot(2, 1, 1)
        temp_subplot.set_title("Temperature")
        temp_subplot.set_ylabel("Temperature (Celsius)")
        temp_subplot.grid(True)
        temp_subplot.set_ylim(0, 50)

        # TODO: Talk to science team about color, markers
        if len(np.array(ds.temp1)) > 0:
            t1_plot, = temp_subplot.plot_date(x=temp1_time, y=temp1_data, color="blue", label="temp1")
        if len(np.array(ds.temp2)) > 0:
            t2_plot, = temp_subplot.plot_date(x=temp2_time, y=temp2_data, color="black", label="temp2")
        if len(np.array(ds.temp3)) > 0:
            t3_plot, = temp_subplot.plot_date(x=temp3_time, y=temp3_data, color="DarkGreen", label="temp3")
        if len(np.array(ds.temp4)) > 0:
            t4_plot, = temp_subplot.plot_date(x=temp4_time, y=temp4_data, color="maroon", label="temp4")
        try:
            temp_subplot.legend(handles=[t1_plot, t2_plot, t3_plot, t4_plot])
        except UnboundLocalError:
            pass

        # Humidity Subplot
        humid_subplot = self.fig.add_subplot(2, 1, 2)
        humid_subplot.set_title("Humidity")
        humid_subplot.set_ylabel("Water Content (%)")
        humid_subplot.grid(True)
        humid_subplot.set_ylim(0, 100)

        # TODO: Talk to science team about colors, markers.
        if len(np.array(ds.humid1)) > 0:
            h1_plot = humid_subplot.plot_date(x=humid1_time, y=humid1_data, color="gold", label="humid1", mew = 0)
        if len(np.array(ds.humid2)) > 0:
            h2_plot = humid_subplot.plot_date(x=humid2_time, y=humid2_data, color="salmon", label="humid2")
        if len(np.array(ds.humid3)) > 0:
            h3_plot = humid_subplot.plot_date(x=humid3_time, y=humid3_data, color="medium orchid", label="humid3")
        if len(np.array(ds.humid4)) > 0:
            h4_plot = humid_subplot.plot_date(x=humid4_time, y=humid4_data, color="light green", label="humid4")
        try:
            humid_subplot.legend(handles=[h1_plot, h2_plot, h3_plot, h4_plot])
        except UnboundLocalError:
            pass

        self.fig.set_tight_layout(True)
        self.canvas.draw()

    # TODO: Test after talking with Owen about data formats.
    def graph_spectrometer(self):
        # plt.ion()
        plt.delaxes()
        plt.grid(True)
        plt.xlim(xmin=0, xmax=self.max_len)
        plt.ylim(ymin=0, ymax=1023)
        plt.plot(np.arange(start=0, stop=self.data_len[self.row_count], step=1), self.ccd_data[self.row_count])
        plt.show()
        plt.pause(0.0001)

# color picker: http://www.w3schools.com/colors/colors_hex.asp
