import csv
import os.path
import sys

import tkinter              # Required for PyInstaller to function.
import tkinter.filedialog   # Required for PyInstaller to function.
import dateutil.parser
from PyQt4 import QtGui, QtCore

from customWidgets import GraphArea, Picture, Sensor


class StartQT4(QtGui.QMainWindow):
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

        # Main Window information
        QtGui.QWidget.__init__(self, parent)
        self.setWindowTitle("Ehrenfreund")
        self.setWindowIcon(QtGui.QIcon("mrdt_logo.jpg"))
        self.resize(946, 542)
        self.setSizeIncrement(QtCore.QSize(1, 1))
        self.centralWidget = QtGui.QWidget(self)

        # Layout contains all information for a single digsite.
        self.digMainLayout = QtGui.QVBoxLayout(self.centralWidget)
        self.digMainLayout.setMargin(11)
        self.digMainLayout.setSpacing(6)

        # Layout should contain all elements relevant to data input (file or otherwise)
        self.inputFrame = QtGui.QHBoxLayout()
        self.inputFrame.setMargin(11)
        self.inputFrame.setSpacing(6)

        self.fileInput = QtGui.QLineEdit(self.centralWidget)
        self.fileInput.setMinimumSize(QtCore.QSize(400, 0))
        self.fileInput.setMaximumSize(QtCore.QSize(400, 16777215))
        spacer_item = QtGui.QSpacerItem(40, 20, QtGui.QSizePolicy.Expanding, QtGui.QSizePolicy.Minimum)
        self.importButton = QtGui.QPushButton("Import", self.centralWidget)
        fileBrowseButton = QtGui.QPushButton("Browse", self.centralWidget)

        self.inputFrame.addWidget(self.fileInput)
        self.inputFrame.addWidget(self.importButton)
        self.inputFrame.addWidget(fileBrowseButton)
        self.inputFrame.addItem(spacer_item)

        # Layout contains all elements required for display of information (essentially everything else)
        self.displayFrame = QtGui.QHBoxLayout()
        self.displayFrame.setMargin(11)
        self.displayFrame.setSpacing(6)

        # Contains a tab for each type of graph. Will eventually contain tabs for additional info (i.e. pictures)
        self.graphTabs = QtGui.QTabWidget()

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
        self.picture_tab = QtGui.QWidget()
        self.pictureLayout = QtGui.QGridLayout(self.picture_tab)
        self.pictureLayout.setMargin(3)
        self.pictureLayout.setSpacing(0)
        self.graphTabs.addTab(self.picture_tab, "Site Pictures")

        self.digMainLayout.addLayout(self.inputFrame)
        self.displayFrame.addWidget(self.graphTabs)
        self.digMainLayout.addLayout(self.displayFrame)

        self.connect(self.fileInput, QtCore.SIGNAL("returnPressed()"), self.enterfile)
        self.connect(self.importButton, QtCore.SIGNAL("clicked()"), self.enterfile)
        self.connect(fileBrowseButton, QtCore.SIGNAL("clicked()"), self.selectfile)

        self.setCentralWidget(self.centralWidget)
        self.showMaximized()

    def enterfile(self):
        """ Enters the file contents to graphing area. Grabs the name of file entered, parses that file,
            and graphs its data."""
        filename = self.fileInput.text()
        if os.path.isfile(filename):
            if filename != self.current_file:
                if filename.lower().endswith('.csv'):
                    # Assuming basic temp/humid.
                    self.parsecsv(filename)
                    self.current_file = filename
                    if self.csv_type == "basic":
                        self.soilGraph.graph_temp_humid(self.soil_sensors)
                        self.airGraph.graph_temp_humid(self.air_sensors)
                        self.weatherGraph.graph_weather(self.weather_sensors)
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
        self.fileInput.setText(QtGui.QFileDialog.getOpenFileName())
        self.enterfile()

    def showpicture(self, pic_name):
        """ Displays a picture within the given window """
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
        sensor_ids = {'Sensor1': 'air_temp',
                      'Sensor2': 'soil_temp',
                      'Sensor3': 'air_humid',
                      'Sensor4': 'soil_humid',
                      'Sensor5': 'uv',
                      'Sensor6': 'pressure',
                      'Sensor7': 'methane'}

        try:
            with open(csv_name, 'r') as csvfile:
                reader = csv.reader(csvfile, delimiter=' ')
                # check header for Spectrometer or Temp/Humid readings.
                # Assuming Temp/Humid
                header = next(reader)
                if header == ['datetime', 'sensor', 'measurement']:
                    self.csv_type = "basic"
                elif header == ["wavelength", "intensity"]:
                    self.csv_type = "spectrometer"

                # Clear old data so plots don't overlap
                for s in self.sensor_list:
                    s.data = []

                for row in reader:
                    try:
                        if self.csv_type == "basic":
                            datestamp, sid, raw_data = row
                            s = next(filter(lambda x: x.name == sensor_ids[sid], self.sensor_list))
                            s.data.append((dateutil.parser.parse(datestamp), raw_data))
                        elif self.csv_type == "spectrometer":
                            wavelength, intensity = row
                            if type(wavelength) != 'str' and type(intensity) != 'str':
                                self.spectrometer_data.append((wavelength, intensity))
                    except StopIteration:
                        pass

        except FileNotFoundError:
            self.showdialogue("Error 404: Could not find file %s" % csv_name)

    @staticmethod
    def showdialogue(errormessage):
        """ Error dialogue window used for file entry. """
        msg = QtGui.QMessageBox()
        msg.setIcon(QtGui.QMessageBox.Critical)
        msg.setText(errormessage)
        msg.setWindowTitle("ERROR")
        msg.setStandardButtons(QtGui.QMessageBox.Ok)
        msg.exec_()


def main():
    app = QtGui.QApplication(sys.argv)
    myapp = StartQT4()
    myapp.show()
    sys.exit(app.exec_())

if __name__ == "__main__":
    main()
