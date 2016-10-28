import matplotlib.pyplot as plt
import numpy as np
from PyQt4 import QtGui, QtCore
from matplotlib.backends.backend_qt4agg import FigureCanvasQTAgg as FigureCanvas
from matplotlib.backends.backend_qt4agg import NavigationToolbar2QT as NavigationToolbar


class DataStore:
    """ Data storage structure formatted for basic readings """
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
    """ Creates a Matplotlib graphing area tailored for MRDT 2017 basic and spectrometer readings in Ehrenfreund. """
    def __init__(self):
        """ Initial setup of the UI """
        super(GraphArea, self).__init__()
        self.fig = plt.figure()
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
        """ Graphs basic data """
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
        # Plots data only if that data exists.
        temp_handles = []
        if len(np.array(ds.temp1)) > 0:
            t1_plot, = temp_subplot.plot_date(x=temp1_time, y=temp1_data, color="magenta", label="temp1", mew=0)
            temp_handles.append(t1_plot)
        if len(np.array(ds.temp2)) > 0:
            t2_plot, = temp_subplot.plot_date(x=temp2_time, y=temp2_data, color="cyan", label="temp2", mew=0)
            temp_handles.append(t2_plot)
        if len(np.array(ds.temp3)) > 0:
            t3_plot, = temp_subplot.plot_date(x=temp3_time, y=temp3_data, color="red", label="temp3", mew=0)
            temp_handles.append(t3_plot)
        if len(np.array(ds.temp4)) > 0:
            t4_plot, = temp_subplot.plot_date(x=temp4_time, y=temp4_data, color="black", label="temp4", mew=0)
            temp_handles.append(t4_plot)
        try:
            temp_subplot.legend(handles=temp_handles)
        except UnboundLocalError:
            pass

        # Humidity Subplot
        humid_subplot = self.fig.add_subplot(2, 1, 2)
        humid_subplot.set_title("Humidity")
        humid_subplot.set_ylabel("Water Content (%)")
        humid_subplot.grid(True)
        humid_subplot.set_ylim(0, 100)

        # TODO: Talk to science team about colors, markers.
        # Plots data only if that data exists.
        humid_handles = []
        if len(np.array(ds.humid1)) > 0:
            h1_plot = humid_subplot.plot_date(x=humid1_time, y=humid1_data, color="gold", label="humid1", mew=0)
            humid_handles.append(h1_plot)
        if len(np.array(ds.humid2)) > 0:
            h2_plot = humid_subplot.plot_date(x=humid2_time, y=humid2_data, color="salmon", label="humid2")
            humid_handles.append(h2_plot)
        if len(np.array(ds.humid3)) > 0:
            h3_plot = humid_subplot.plot_date(x=humid3_time, y=humid3_data, color="medium orchid", label="humid3")
            humid_handles.append(h3_plot)
        if len(np.array(ds.humid4)) > 0:
            h4_plot = humid_subplot.plot_date(x=humid4_time, y=humid4_data, color="light green", label="humid4")
            humid_handles.append(h4_plot)
        try:  # Shouldn't ever fail due to conditional append. Try block kept just to be safe.
            humid_subplot.legend(handles=humid_handles)
        except UnboundLocalError:
            pass

        self.fig.set_tight_layout(True)
        self.canvas.draw()

    # TODO: Change to (wavelength, intensity) format.
    def graph_spectrometer(self):
        """ Graphs spectrometer data """
        plt.delaxes()
        plt.grid(True)
        plt.xlim(xmin=0, xmax=self.max_len)
        plt.ylim(ymin=0, ymax=1023)
        plt.plot(np.arange(start=0, stop=self.data_len[self.row_count], step=1), self.ccd_data[self.row_count])
        plt.show()
        plt.pause(0.0001)


class SensorEnableBox(QtGui.QWidget):
    """ Contains all elements relevant to enabling and disabling basic sensors. """
    def __init__(self, parent):
        """ Initial setup of the UI """
        super(SensorEnableBox, self).__init__()
        self.sensorEnables = QtGui.QVBoxLayout()
        self.sensorEnables.setSpacing(0)
        self.sensorEnables.setContentsMargins(-1, 0, -1, -1)

        self.tempSensors = QtGui.QGroupBox()
        # self.tempSensors.setMaximumSize(QtCore.QSize(100, 150))
        self.tempLayout = QtGui.QVBoxLayout(self.tempSensors)
        self.tempLayout.setSpacing(7)
        self.tsheath1 = QtGui.QCheckBox(self.tempSensors)
        self.tsheath1.setText("Temp1")
        self.tempLayout.addWidget(self.tsheath1)
        self.tsheath2 = QtGui.QCheckBox(self.tempSensors)
        self.tsheath2.setText("Temp2")
        self.tempLayout.addWidget(self.tsheath2)
        self.tdrill1 = QtGui.QCheckBox(self.tempSensors)
        self.tdrill1.setText("Temp3")
        self.tempLayout.addWidget(self.tdrill1)
        self.tdrill2 = QtGui.QCheckBox(self.tempSensors)
        self.tdrill2.setText("Temp4")
        self.tempLayout.addWidget(self.tdrill2)
        self.sensorEnables.addWidget(self.tempSensors)

        self.humidSensors = QtGui.QGroupBox()
        # self.humidSensors.setMaximumSize(QtCore.QSize(100, 150))
        self.hsheath1 = QtGui.QCheckBox(self.humidSensors)
        self.hsheath1.setText("Humid1")
        self.humidLayout = QtGui.QVBoxLayout(self.humidSensors)
        self.humidLayout.setSpacing(7)
        self.humidLayout.addWidget(self.hsheath1)
        self.hsheath2 = QtGui.QCheckBox(self.humidSensors)
        self.hsheath2.setText("Humid2")
        self.humidLayout.addWidget(self.hsheath2)
        self.hdrill1 = QtGui.QCheckBox(self.humidSensors)
        self.hdrill1.setText("Humid3")
        self.humidLayout.addWidget(self.hdrill1)
        self.hdrill2 = QtGui.QCheckBox(self.humidSensors)
        self.hdrill2.setText("Humid4")
        self.humidLayout.addWidget(self.hdrill2)
        self.sensorEnables.addWidget(self.humidSensors)

        self.saveGraphsButton = QtGui.QPushButton()
        self.saveGraphsButton.setText("Refresh Graph")
        self.sensorEnables.addWidget(self.saveGraphsButton)

        spacer_item = QtGui.QSpacerItem(40, 20, QtGui.QSizePolicy.Minimum, QtGui.QSizePolicy.Expanding)
        self.sensorEnables.addItem(spacer_item)

        parent.addLayout(self.sensorEnables)


# color picker: http://www.w3schools.com/colors/colors_hex.asp
