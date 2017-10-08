import csv
import os.path
import sys

import tkinter              # Required for PyInstaller to function.
import tkinter.filedialog   # Required for PyInstaller to function.
import dateutil.parser
from PyQt5 import QtWidgets, QtCore, QtGui

from science_station.customWidgets import GraphArea, Picture, Sensor


class StartQT4(QtWidgets.QMainWindow):
    def __init__(self, parent=None):
        # Data variables.
        self.current_file = ""
        self.csv_type = ""
        self.pictures_held = []
        self.spectrometer_data = []

        self.sensor_list = [Sensor(reading_type='weather', name='pressure'),
                            Sensor(reading_type='weather', name='methane'),
                            Sensor(reading_type='weather', name='uv'),
                            Sensor(reading_type='air', name='air_temp'),
                            Sensor(reading_type='air', name='air_humid'),
                            Sensor(reading_type='soil', name='soil_temp'),
                            Sensor(reading_type='soil', name='soil_humid')]

        self.air_sensors = list(filter(lambda x: x.type == 'air', self.sensor_list))
        self.soil_sensors = list(filter(lambda x: x.type == 'soil', self.sensor_list))
        self.weather_sensors = list(filter(lambda x: x.type == 'weather', self.sensor_list))

        # Main Window information
        QtWidgets.QWidget.__init__(self, parent)
        self.setWindowTitle("Ehrenfreund")
        self.resize(946, 542)
        self.setSizeIncrement(QtCore.QSize(1, 1))
        centralWidget = QtWidgets.QWidget(self)

        # Layout contains all information for a single digsite.
        digMainLayout = QtWidgets.QVBoxLayout(centralWidget)
        digMainLayout.setContentsMargins(11, 11, 11, 11)
        digMainLayout.setSpacing(6)

        # Layout should contain all elements relevant to data input (file or otherwise)
        inputFrame = QtWidgets.QHBoxLayout()
        inputFrame.setContentsMargins(11, 11, 11, 11)
        inputFrame.setSpacing(6)

        self.fileInput = QtWidgets.QLineEdit(centralWidget)
        self.fileInput.setMinimumSize(QtCore.QSize(400, 0))
        self.fileInput.setMaximumSize(QtCore.QSize(400, 16777215))
        spacer_item = QtWidgets.QSpacerItem(40, 20, QtWidgets.QSizePolicy.Expanding, QtWidgets.QSizePolicy.Minimum)
        importButton = QtWidgets.QPushButton("Import", centralWidget)
        fileBrowseButton = QtWidgets.QPushButton("Browse", centralWidget)

        # Add widgets in left->right order
        inputFrame.addWidget(self.fileInput)
        inputFrame.addWidget(importButton)
        inputFrame.addWidget(fileBrowseButton)
        inputFrame.addItem(spacer_item)

        # Layout contains all elements required for display of information (essentially everything else)
        displayFrame = QtWidgets.QHBoxLayout()
        displayFrame.setContentsMargins(11, 11, 11, 11)
        displayFrame.setSpacing(6)

        # Contains a tab for each type of graph, and other displayed information (e.g. pictures)
        self.graphTabs = QtWidgets.QTabWidget()

        # Soil Temperature and Humidity
        self.soilGraph = GraphArea()
        self.graphTabs.addTab(self.soilGraph, "Soil Temp/Humid")

        # Air Temperature and Humidity
        self.airGraph = GraphArea()
        self.graphTabs.addTab(self.airGraph, "Air Temp/Humid")

        # Spectrometer Data
        self.spectrometerGraph = GraphArea()
        self.graphTabs.addTab(self.spectrometerGraph, "Spectrometer")

        # Weather
        self.weatherGraph = GraphArea()
        self.graphTabs.addTab(self.weatherGraph, "Weather")

        # Site Pictures
        self.picture_tab = QtWidgets.QWidget()
        self.pictureLayout = QtWidgets.QGridLayout(self.picture_tab)
        self.pictureLayout.setContentsMargins(3, 3, 3, 3)
        self.pictureLayout.setSpacing(0)
        self.graphTabs.addTab(self.picture_tab, "Site Pictures")

        digMainLayout.addLayout(inputFrame)
        displayFrame.addWidget(self.graphTabs)
        digMainLayout.addLayout(displayFrame)

        self.fileInput.returnPressed.connect(self.enterfile)
        importButton.clicked.connect(self.enterfile)
        fileBrowseButton.clicked.connect(self.selectfile)

        self.setCentralWidget(centralWidget)
        self.showMaximized()

    def enterfile(self):
        """ Enters the file contents to graphing area. Grabs the name of file entered, parses that file,
            and graphs its data."""
        filename = self.fileInput.text()
        if os.path.isfile(filename):
            if filename != self.current_file:
                if filename.lower().endswith('.csv') or filename.lower().endswith('.dat'):
                    # Assuming basic temp/humid.
                    print(filename)
                    if self.parsecsv(filename):
                        self.current_file = filename
                        if self.csv_type == "basic":
                            self.soilGraph.graph_temp_humid(self.soil_sensors)
                            self.airGraph.graph_temp_humid(self.air_sensors)
                            self.weatherGraph.graph_weather(self.weather_sensors)
                            self.graphTabs.setCurrentWidget(self.soilGraph)
                        elif self.csv_type == "spectrometer":
                            self.spectrometerGraph.graph_spectrometer(self.spectrometer_data)
                            self.graphTabs.setCurrentWidget(self.spectrometerGraph)
                elif any([filename.lower().endswith(x) for x in ['.png', '.jpeg', '.jpg']]):
                    self.showpicture(filename)
                    self.graphTabs.setCurrentWidget(self.picture_tab)
                else:
                    self.showdialogue("Unsupported file type. Please input a .csv, .png, .jpeg file")
            else:
                self.showdialogue("File requested is already entered.")
        else:
            self.showdialogue("File does not exist")
        self.fileInput.clear()

    def selectfile(self):
        # getOpenFileName() returns a tuple, idx 0 is the one we want, idx 1 is all files...
        self.fileInput.setText(QtWidgets.QFileDialog.getOpenFileName()[0])
        self.enterfile()

    def showpicture(self, pic_name):
        """ Displays a picture within the given window """
        if len(self.pictures_held) >= 4:
            self.showdialogue("Maximum pictures held")
            return
        picture = Picture(pic_name)
        pos = [(1, 1), (1, 2), (2, 1), (2, 2)]
        x, y = pos[len(self.pictures_held)]

        self.pictures_held.append(pic_name)
        self.pictureLayout.addWidget(picture, x, y)
        self.picture_tab.show()

    # noinspection PyAttributeOutsideInit
    def parsecsv(self, csv_name):
        """ Parses a CSV file containing MRDT-2016 formatted basic or spectrometer data.
            Places data in relevant data store. """

        # Easy dictionary conversion from RED standard sensor identifier to more readable names
        sensor_ids = {'Sensor00': 'air_temp',
                      'Sensor01': 'soil_temp',
                      'Sensor02': 'air_humid',
                      'Sensor03': 'soil_humid',
                      'Sensor04': 'uv',
                      'Sensor05': 'pressure',
                      'Sensor06': 'methane'}

        try:
            with open(csv_name, 'r') as csvfile:
                reader = csv.reader(csvfile, delimiter=' ')

                self.csv_type = None

                # Clear old data so plots don't overlap
                for s in self.sensor_list:
                    s.data = []

                for row in reader:
                    try:
                        # On first line, determine type of readings from number of columns
                        # Note: I hate that we don't use CSV headers but I don't write the generator for it.
                        #       This breaks as soon as we introduce data files with a header line because lazy.
                        if self.csv_type is None:
                            if len(row) == 3:
                                self.csv_type = "basic"
                            else:  # len(row) == 2:
                                self.csv_type = "spectrometer"

                        if self.csv_type == "basic":
                            datestamp, sid, raw_data = row
                            s = next(filter(lambda x: x.name == sensor_ids[sid], self.sensor_list))
                            s.data.append((dateutil.parser.parse(datestamp), raw_data))
                        elif self.csv_type == "spectrometer":
                            wavelength, intensity = row
                            if type(wavelength) != 'str' and type(intensity) != 'str':
                                self.spectrometer_data.append((wavelength, intensity))
                    except StopIteration:
                        return True
                    except KeyError:
                        self.showdialogue("KeyError: CSV could not be parsed properly because a sensor name did not "
                                          "match. Check format of file.")
                        return False
            return True

        except FileNotFoundError:
            self.showdialogue("Error 404: Could not find file %s" % csv_name)
            return False

    @staticmethod
    def showdialogue(errormessage):
        """ Error dialogue window used for file entry. """
        msg = QtWidgets.QMessageBox()
        msg.setIcon(QtWidgets.QMessageBox.Critical)
        msg.setText(errormessage)
        msg.setWindowTitle("ERROR")
        msg.setStandardButtons(QtWidgets.QMessageBox.Ok)
        msg.exec_()


def main():
    app = QtWidgets.QApplication(sys.argv)
    myapp = StartQT4()
    myapp.setWindowIcon(QtGui.QIcon("mrdt_logo.jpg"))
    myapp.show()
    sys.exit(app.exec_())

if __name__ == "__main__":
    main()
