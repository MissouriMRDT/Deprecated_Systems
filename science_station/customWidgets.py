import matplotlib.dates as mdates
import matplotlib.pyplot as plt
import numpy as np
from PyQt4 import QtGui, QtCore
from matplotlib.backends.backend_qt4agg import FigureCanvasQTAgg as FigureCanvas
from matplotlib.backends.backend_qt4agg import NavigationToolbar2QT as NavigationToolbar


class Sensor(QtGui.QCheckBox):
    def __init__(self, sensor_type, name, color=""):
        super(Sensor, self).__init__()
        self.data = []
        self.type = sensor_type
        self.setText(name)
        self.color = color


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
        self.fig.clf()

        temp_ax = self.fig.add_subplot(211)
        temp_ax.set_title("Temperature")
        temp_ax.set_ylabel("Temperature (Celsius)")
        temp_ax.grid(True)
        temp_ax.set_ylim(0, 50)

        humid_ax = self.fig.add_subplot(212, sharex=temp_ax)
        humid_ax.set_title("Humidity")
        humid_ax.set_xlabel("Time (min:sec)")
        humid_ax.set_ylabel("Water Content (%)")
        humid_ax.grid(True)
        humid_ax.set_ylim(0, 100)

        temp_handles = []
        humid_handles = []

        for s in sensors:
            if len(np.array(s.data)) > 0:  # skip sensors with no readings
                t, measure = np.array(s.data).T  # transpose two-tuples into two data sets
                if s.isChecked():
                    if s.type == "temperature":
                        handle, = temp_ax.plot_date(x=t, y=measure, label=s.text(), mew=0)  # TODO: color
                        temp_handles.append(handle)
                    elif s.type == "humidity":
                        handle, = humid_ax.plot_date(x=t, y=measure, label=s.text(), mew=0)  # TODO: color
                        humid_handles.append(handle)

        try:
            temp_ax.legend(handles=temp_handles)
        except UnboundLocalError:
            pass
        try:
            humid_ax.legend(handles=humid_handles)
        except UnboundLocalError:
            pass

        fmt = mdates.DateFormatter('%M:%S')
        temp_ax.xaxis.set_major_formatter(fmt)
        humid_ax.xaxis.set_major_formatter(fmt)

        self.fig.autofmt_xdate(rotation=15)
        self.fig.set_tight_layout(True)
        self.canvas.draw()

    # Data must be in format [(#,#),(#,#),(#,#)] i.e. a list of tuples.
    def graph_spectrometer(self, data_tuples):
        """ Graphs spectrometer data """
        wavelength, intensity = np.array(data_tuples).T
        wavelength_f = []
        intensity_f = []
        for i in range(len(wavelength)):
            wavelength_f.append(float(wavelength[i]))
        for i in range(len(intensity)):
            intensity_f.append(float(intensity[i]))
        self.fig.clf()
        spectro_plot = self.fig.add_subplot(1, 1, 1)
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
        self.hsheath1 = Sensor("humidity", name="HSheath1")
        self.hsheath2 = Sensor("humidity", name="HSheath2")
        self.hdrill1 = Sensor("humidity", name="HDrill1")
        self.hdrill2 = Sensor("humidity", name="HDrill2")

        self.sensors.append(self.hsheath1)
        self.sensors.append(self.hsheath2)
        self.sensors.append(self.hdrill1)
        self.sensors.append(self.hdrill2)

        self.tempSensors = QtGui.QGroupBox()
        # self.tempSensors.setMaximumSize(QtCore.QSize(100, 150))
        self.tempLayout = QtGui.QVBoxLayout(self.tempSensors)

        self.tempLayout.setSpacing(7)
        self.tsheath1 = Sensor("temperature", name="TSheath1")
        self.tsheath2 = Sensor("temperature", name="TSheath2")
        self.tdrill1 = Sensor("temperature", name="TDrill1")
        self.tdrill2 = Sensor("temperature", name="TDrill2")

        self.sensors.append(self.tsheath1)
        self.sensors.append(self.tsheath2)
        self.sensors.append(self.tdrill1)
        self.sensors.append(self.tdrill2)

        for s in self.sensors:
            s.setChecked(True)
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


class PictureLabel(QtGui.QLabel):
    def __init__(self, image):
        super(PictureLabel, self).__init__()
        self.setFrameStyle(QtGui.QFrame.StyledPanel)
        self.pixmap = QtGui.QPixmap(image)

    def paintEvent(self, event):
        size = self.size()
        painter = QtGui.QPainter(self)
        point = QtCore.QPoint(0, 0)  # This change?
        scaledPix = self.pixmap.scaled(size, QtCore.Qt.KeepAspectRatio)
        point.setX((size.width() - scaledPix.width())/2)
        point.setY((size.height() - scaledPix.height())/2)
        painter.drawPixmap(point, scaledPix)


class Picture(QtGui.QWidget):
    def __init__(self, image):
        super(Picture, self).__init__()
        vbox = QtGui.QVBoxLayout()
        vbox.setSpacing(0)
        vbox.setMargin(0)

        text, ok = QtGui.QInputDialog.getText(self, "Add description of photo", "Description: ")
        desc = QtGui.QLabel()
        desc.setText(text)
        desc.setMaximumHeight(30)

        vbox.addWidget(PictureLabel(image))
        vbox.addWidget(desc, 0, QtCore.Qt.AlignHCenter)
        self.setLayout(vbox)

# color picker: http://www.w3schools.com/colors/colors_hex.asp
