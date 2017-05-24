import matplotlib.dates as mdates
import matplotlib.pyplot as plt
import numpy as np
from PyQt4 import QtGui, QtCore
from matplotlib.backends.backend_qt4agg import FigureCanvasQTAgg as FigureCanvas
from matplotlib.backends.backend_qt4agg import NavigationToolbar2QT as NavigationToolbar


class Sensor(QtGui.QCheckBox):
    def __init__(self, reading_type, name, color=""):
        super(Sensor, self).__init__()
        self.data = []
        self._type = reading_type
        self._name = name
        self.setText(self.name)
        self.color = color

    @property
    def type(self):
        return self._type

    @property
    def name(self):
        return self._name


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

    def graph_weather(self, sensors):
        self.fig.clf()

        # Barometric Pressure
        pressure_ax = self.fig.add_subplot(311)
        pressure_ax.set_title("Barometric Pressure")
        pressure_ax.set_ylabel("Pressure (atms)")
        pressure_ax.grid(True)
        # pressure_ax.set_ylim(ymin, ymax)  # TODO: Barometer y-limits?

        # Methane levels
        methane_ax = self.fig.add_subplot(312, sharex=pressure_ax)
        methane_ax.set_title("Methane Concentration")
        methane_ax.set_ylabel("Concentration (ppm)")
        methane_ax.grid(True)
        # methane_ax.set_ylim(ymin, ymax)  # TODO: Methane y-limits?

        # UV Intensity
        uv_ax = self.fig.add_subplot(313, sharex=pressure_ax)
        uv_ax.set_title("UV Intensity")
        uv_ax.set_xlabel("Time (min:sec)")
        uv_ax.set_ylabel(r'Irradiance (mW / c$^2$)')
        uv_ax.grid(True)
        # uv_ax.set_ylim(ymin, ymax)  # TODO: UV y-limits?

        # Iterate through sensors marked as weather sensors
        for s in list(filter(lambda x: x.type == 'weather', sensors)):
            if len(np.array(s.data)) > 0:  # Skip those with no readings
                t, measure = np.array(s.data).T  # Transpose two-tuples into two data sets
                if s.name == 'methane':
                    methane_ax.plot_date(x=t, y=measure, label=s.text(), mew=0)  # TODO: Color
                elif s.name == 'pressure':
                    pressure_ax.plot_date(x=t, y=measure, label=s.text(), mew=0)  # TODO: Color
                elif s.name == 'uv':
                    uv_ax.plot_date(x=t, y=measure, label=s.text(), mew=0)  # TODO: Color

        fmt = mdates.DateFormatter('%M:%S')
        pressure_ax.xaxis.set_major_formatter(fmt)
        methane_ax.xaxis.set_major_formatter(fmt)
        uv_ax.xaxis.set_major_formatter(fmt)

        self.fig.autofmt_xdate(rotation=15)
        self.fig.set_tight_layout(True)
        self.canvas.draw()

    def graph_temp_humid(self, sensors):
        self.fig.clf()

        temp_ax = self.fig.add_subplot(211)
        temp_ax.set_title("Temperature")
        temp_ax.set_ylabel("Temperature (Celsius)")
        temp_ax.grid(True)
        # temp_ax.set_ylim(0, 50)

        humid_ax = self.fig.add_subplot(212, sharex=temp_ax)
        humid_ax.set_title("Humidity")
        humid_ax.set_xlabel("Time (min:sec)")
        humid_ax.set_ylabel("Water Content (%)")
        humid_ax.grid(True)
        # humid_ax.set_ylim(0, 100)

        for s in sensors:
            if len(np.array(s.data)) > 0:  # skip sensors with no readings*
                t, measure = np.array(s.data).T  # transpose two-tuples into two data sets
                if s.name.endswith('temp'):
                    temp_ax.plot_date(x=t, y=measure, label=s.text(), mew=0)  # TODO: color
                elif s.name.endswith('humid'):
                    humid_ax.plot_date(x=t, y=measure, label=s.text(), mew=0)  # TODO: color

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
            try:
                wavelength_f.append(float(wavelength[i]))
            except ValueError:  # If the given file has a header this will be thrown. Skips any line of text.
                pass
        for i in range(len(intensity)):
            try:
                intensity_f.append(float(intensity[i]))
            except ValueError:  # If the given file has a header this will be thrown. Skips any line of text.
                pass
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
        # TODO: Modify to accept list of sensors as parameter. Make box for that list.
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
        self._image = QtGui.QImage(image)
        self.pixmap = QtGui.QPixmap(self._image)

    def paintEvent(self, event):
        size = self.size()
        painter = QtGui.QPainter(self)
        point = QtCore.QPoint(0, 0)  # This change?
        scaledPix = self.pixmap.scaled(size, QtCore.Qt.KeepAspectRatio)
        point.setX((size.width() - scaledPix.width())/2)
        point.setY((size.height() - scaledPix.height())/2)
        painter.drawPixmap(point, scaledPix)


class PicturePopup(QtGui.QWidget):
    def __init__(self, image):
        super(PicturePopup, self).__init__()
        self.pixmap = QtGui.QPixmap(image)

    def paintEvent(self, QPaintEvent):
        size = self.size()
        painter = QtGui.QPainter(self)
        point = QtCore.QPoint(0, 0)  # This change?
        scaledPix = self.pixmap.scaled(size, QtCore.Qt.KeepAspectRatio)
        point.setX((size.width() - scaledPix.width())/2)
        point.setY((size.height() - scaledPix.height())/2)
        painter.drawPixmap(point, scaledPix)

    def keyPressEvent(self, e):
        if e.key() == QtCore.Qt.Key_Escape:
            self.close()


class Picture(QtGui.QWidget):
    def __init__(self, image):
        super(Picture, self).__init__()
        self._image = image

        vbox = QtGui.QVBoxLayout()
        vbox.setSpacing(0)
        vbox.setMargin(0)

        self._desc_text, ok = QtGui.QInputDialog.getText(self, "Add description of photo", "Description: ")
        self.desc = QtGui.QLabel()
        self.desc.setText(self._desc_text)
        self.desc.setMaximumHeight(30)

        vbox.addWidget(PictureLabel(self._image))
        vbox.addWidget(self.desc, 0, QtCore.Qt.AlignHCenter)
        self.setLayout(vbox)

        self.popup = QtGui.QWidget()
        self.mouseDoubleClickEvent = self.fullscreenPicture

    def fullscreenPicture(self, event):
        # TODO: Full-screen widget
        self.popup = PicturePopup(self._image)
        self.popup.setWindowTitle(self._desc_text)
        self.popup.showFullScreen()


# color picker: http://www.w3schools.com/colors/colors_hex.asp
