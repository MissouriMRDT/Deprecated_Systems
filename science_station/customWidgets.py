import matplotlib.pyplot as plt
import numpy as np
from PyQt4 import QtGui, QtCore
from matplotlib.backends.backend_qt4agg import FigureCanvasQTAgg as FigureCanvas
from matplotlib.backends.backend_qt4agg import NavigationToolbar2QT as NavigationToolbar


class Sensor(QtGui.QCheckBox):
    def __init__(self):
        super().__init__()
        self.data = [] # Array of tuples of form (time, data)
        self.type = '' # temp or humid
        self.color = ''
        self.displayname = ''

class GraphArea(QtGui.QWidget):
    """ Creates a Matplotlib graphing area tailored for MRDT 2017 basic and spectrometer readings in Ehrenfreund. """
    def __init__(self):
        """ Initial setup of the UI """
        super().__init__()
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

    def graph_basic(self, sensorArray):
        """ Graphs basic data """
        # Temperature Subplot
        temp_subplot = self.fig.add_subplot(2, 1, 1)
        temp_subplot.set_title("Temperature")
        temp_subplot.set_ylabel("Temperature (Celsius)")
        temp_subplot.grid(True)
        temp_subplot.set_ylim(0, 50)
        temp_handles = []

        # Humidity Subplot
        humid_subplot = self.fig.add_subplot(2, 1, 2)
        humid_subplot.set_title("Humidity")
        humid_subplot.set_ylabel("Water Content (%)")
        humid_subplot.grid(True)
        humid_subplot.set_ylim(0, 100)
        humid_handles = []

        for sensor in sensorArray:
            if sensor.isChecked() and len(np.array(sensor.data)):
                if sensor.type == "temp":
                    time, data = np.array(sensor.data).T
                    temp_plot, = temp_subplot.plot_date(x=time, y=data, color=sensor.color, label=sensor.displayname, mew=0)
                    temp_handles.append(temp_plot)
                elif sensor.type == "humid":
                    time, data = np.array(sensor.data).T
                    humid_plot, = humid_subplot.plot_date(x=time, y=data, color=sensor.color, label=sensor.displayname, mew=0)
                    humid_handles.append(humid_plot)

        try:
            temp_subplot.legend(handles=temp_handles)
        except UnboundLocalError:
            pass

        try:  # Shouldn't ever fail due to conditional append. Try block kept just to be safe.
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
        self.sensorEnables = QtGui.QVBoxLayout()
        self.sensorEnables.setSpacing(0)
        self.sensorEnables.setContentsMargins(-1, 0, -1, -1)

        self.tempSensors = QtGui.QGroupBox()
        # self.tempSensors.setMaximumSize(QtCore.QSize(100, 150))
        self.tempLayout = QtGui.QVBoxLayout(self.tempSensors)
        self.tempLayout.setSpacing(7)
        self.tsheath1 = Sensor()
        self.tsheath1.setText("Temp1")
        self.tsheath1.setChecked(True)
        self.tempLayout.addWidget(self.tsheath1)
        self.tsheath2 = QtGui.QCheckBox(self.tempSensors)
        self.tsheath2.setText("Temp2")
        self.tsheath2.setChecked(True)
        self.tempLayout.addWidget(self.tsheath2)
        self.tdrill1 = QtGui.QCheckBox(self.tempSensors)
        self.tdrill1.setText("Temp3")
        self.tdrill1.setChecked(True)
        self.tempLayout.addWidget(self.tdrill1)
        self.tdrill2 = QtGui.QCheckBox(self.tempSensors)
        self.tdrill2.setText("Temp4")
        self.tdrill2.setChecked(True)
        self.tempLayout.addWidget(self.tdrill2)
        self.sensorEnables.addWidget(self.tempSensors)

        self.humidSensors = QtGui.QGroupBox()
        # self.humidSensors.setMaximumSize(QtCore.QSize(100, 150))
        self.hsheath1 = QtGui.QCheckBox(self.humidSensors)
        self.hsheath1.setText("Humid1")
        self.hsheath1.setChecked(True)
        self.humidLayout = QtGui.QVBoxLayout(self.humidSensors)
        self.humidLayout.setSpacing(7)
        self.humidLayout.addWidget(self.hsheath1)
        self.hsheath2 = QtGui.QCheckBox(self.humidSensors)
        self.hsheath2.setText("Humid2")
        self.hsheath2.setChecked(True)
        self.humidLayout.addWidget(self.hsheath2)
        self.hdrill1 = QtGui.QCheckBox(self.humidSensors)
        self.hdrill1.setText("Humid3")
        self.hdrill1.setChecked(True)
        self.humidLayout.addWidget(self.hdrill1)
        self.hdrill2 = QtGui.QCheckBox(self.humidSensors)
        self.hdrill2.setText("Humid4")
        self.hdrill2.setChecked(True)
        self.humidLayout.addWidget(self.hdrill2)
        self.sensorEnables.addWidget(self.humidSensors)

        self.saveGraphsButton = QtGui.QPushButton()
        self.saveGraphsButton.setText("Refresh Graph")
        self.sensorEnables.addWidget(self.saveGraphsButton)

        spacer_item = QtGui.QSpacerItem(40, 20, QtGui.QSizePolicy.Minimum, QtGui.QSizePolicy.Expanding)
        self.sensorEnables.addItem(spacer_item)

        parent.addLayout(self.sensorEnables)


# color picker: http://www.w3schools.com/colors/colors_hex.asp
