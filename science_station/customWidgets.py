import matplotlib.pyplot as plt
import numpy as np
from PyQt4 import QtGui, QtCore
from matplotlib.backends.backend_qt4agg import FigureCanvasQTAgg as FigureCanvas
from matplotlib.backends.backend_qt4agg import NavigationToolbar2QT as NavigationToolbar


class Sensor(QtGui.QCheckBox):
    def __init__(self, sensor_type, parent=None):
        # def __init__(self, parent=None):
        super(Sensor, self).__init__()
        self.data = []
        self.type = sensor_type


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

    def graph_basic(self, sensors):

        temp_subplot = self.fig.add_subplot(2, 1, 1)
        temp_subplot.set_title("Temperature")
        temp_subplot.set_ylabel("Temperature (Celsius)")
        temp_subplot.grid(True)
        temp_subplot.set_ylim(0, 50)

        humid_subplot = self.fig.add_subplot(2, 1, 2)
        humid_subplot.set_title("Humidity")
        humid_subplot.set_ylabel("Water Content (%)")
        humid_subplot.grid(True)
        humid_subplot.set_ylim(0, 100)

        temp_handles = []
        humid_handles = []

        for s in sensors:
            if len(np.array(s.data)) > 0:  # skip sensors with no readings
                t, measure = np.array(s.data).T  # transpose two-tuples into two data sets
                print(s.isChecked())
                if s.isChecked():
                    if s.type == "temperature":
                        handle, = temp_subplot.plot_date(x=t, y=measure, label=s.text(), mew=0)  # color
                        temp_handles.append(handle)
                    elif s.type == "humidity":
                        handle, = humid_subplot.plot_date(x=t, y=measure, color="gold", label=s.text(), mew=0)
                        humid_handles.append(handle)

        try:
            temp_subplot.legend(handles=temp_handles)
        except UnboundLocalError:
            pass
        try:
            humid_subplot.legend(handles=humid_handles)
        except UnboundLocalError:
            pass

        self.fig.set_tight_layout(True)
        self.canvas.draw()

    # TODO: Change to (wavelength, intensity) format.
    # Data must be in format [(#,#),(#,#),(#,#)] i.e. a list of tuples.
    def graph_spectrometer(self, data_tuples):
        """ Graphs spectrometer data """
        wavelength, intensity = np.array(data_tuples).T
        print(wavelength)
        print(intensity)
        wavelength_f = []
        intensity_f = []
        for i in range(len(wavelength)):
            wavelength_f.append(float(wavelength[i]))
        for i in range(len(intensity)):
            intensity_f.append(float(intensity[i]))
        spectro_plot = self.fig.add_subplot(1,1,1)
        spectro_plot.set_title("Spectral Response")
        spectro_plot.set_ylabel("Intensity")
        spectro_plot.set_xlabel("Wavelength (nm)")
        spectro_plot.grid(True)
        spectro_plot.plot(wavelength_f, intensity_f, 'bo')

        self.fig.set_tight_layout(True)
        self.canvas.draw()


class SensorEnableBox(QtGui.QWidget):
    """ Contains all elements relevant to enabling and disabling basic sensors. """
    def __init__(self, parent):
        """ Initial setup of the UI """
        super(SensorEnableBox, self).__init__()
        self.sensors = []

        self.sensorEnables = QtGui.QVBoxLayout()
        self.sensorEnables.setSpacing(0)
        self.sensorEnables.setContentsMargins(-1, 0, -1, -1)

        self.humidSensors = QtGui.QGroupBox()
        self.humidLayout = QtGui.QVBoxLayout(self.humidSensors)
        self.humidLayout.setSpacing(7)

        # self.humidSensors.setMaximumSize(QtCore.QSize(100, 150))
        self.hsheath1 = Sensor("humidity", self.humidSensors)
        self.hsheath2 = Sensor("humidity", self.humidSensors)
        self.hdrill1 = Sensor("humidity", self.humidSensors)
        self.hdrill2 = Sensor("humidity", self.humidSensors)

        self.hsheath1.setText("HSheath1")
        self.hsheath2.setText("HSheath2")
        self.hdrill1.setText("HDrill1")
        self.hdrill2.setText("HDrill2")

        self.sensors.append(self.hsheath1)
        self.sensors.append(self.hsheath2)
        self.sensors.append(self.hdrill1)
        self.sensors.append(self.hdrill2)

        self.tempSensors = QtGui.QGroupBox()
        # self.tempSensors.setMaximumSize(QtCore.QSize(100, 150))
        self.tempLayout = QtGui.QVBoxLayout(self.tempSensors)

        self.tempLayout.setSpacing(7)
        self.tsheath1 = Sensor("temperature", parent=self.tempSensors)
        self.tsheath2 = Sensor("temperature", parent=self.tempSensors)
        self.tdrill1 = Sensor("temperature", parent=self.tempSensors)
        self.tdrill2 = Sensor("temperature", parent=self.tempSensors)

        self.tsheath1.setText("TSheath1")
        self.tsheath2.setText("TSheath2")
        self.tdrill1.setText("TDrill1")
        self.tdrill2.setText("TDrill2")

        self.sensors.append(self.tsheath1)
        self.sensors.append(self.tsheath2)
        self.sensors.append(self.tdrill1)
        self.sensors.append(self.tdrill2)

        for s in self.sensors:
            if s.type == "humidity":
                self.humidLayout.addWidget(s)
            elif s.type == "temperature":
                self.tempLayout.addWidget(s)

        self.sensorEnables.addWidget(self.humidSensors)
        self.sensorEnables.addWidget(self.tempSensors)

        self.refreshButton = QtGui.QPushButton()
        self.refreshButton.setText("Refresh Graph")
        self.sensorEnables.addWidget(self.refreshButton)

        spacer_item = QtGui.QSpacerItem(40, 20, QtGui.QSizePolicy.Minimum, QtGui.QSizePolicy.Expanding)
        self.sensorEnables.addItem(spacer_item)

        parent.addLayout(self.sensorEnables)


# color picker: http://www.w3schools.com/colors/colors_hex.asp
