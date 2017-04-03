import csv
import dateutil.parser
import sys
import tkinter              # Required for PyInstaller to function.
import tkinter.filedialog   # Required for PyInstaller to function.
from PyQt4 import QtGui, QtCore
from customWidgets import GraphArea #DataStore, SensorEnableBox, SensorEnableStates


# TODO: Implementation - plot spectrometer data


class StartQT4(QtGui.QMainWindow):
    def __init__(self, parent=None):
        # Data variables.
        self.current_file = ""
        self.csv_type = ""
        #self.ds = DataStore()
        self.spectrometer_data = []
        #self.sensorEnableBools = SensorEnableStates()

        # Main Window information
        QtGui.QWidget.__init__(self, parent)
        self.setWindowTitle("Ehrenfreund")
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
        self.inputFrame.addWidget(self.fileInput)
        self.inputFrame.addWidget(self.importButton)
        self.inputFrame.addItem(spacer_item)

        # Layout contains all elements required for display of information (essentially everything else)
        self.displayFrame = QtGui.QHBoxLayout()
        self.displayFrame.setMargin(11)
        self.displayFrame.setSpacing(6)

        # Contains a tab for each type of graph. Will eventually contain tabs for additional info (i.e. pictures)
        self.graphTabs = QtGui.QTabWidget()

        # Contains all elements relevant to display of basic sensor data
        self.basic = QtGui.QWidget()
        self.basicGraphLayout = QtGui.QHBoxLayout(self.basic)
        self.basicGraphLayout.setMargin(0)
        self.basicGraphLayout.setSpacing(2)
        # SensorEnableBox - custom widget for enabling/disabling rover sensor display
        #self.sensorEnables = SensorEnableBox(self.basicGraphLayout)
        #self.basicGraphLayout.addWidget(self.sensorEnables)
        # GraphArea - custom widget for display of Matplotlib graphs of basic and spectrometer readings
        self.basicGraph = GraphArea()
        self.basicGraphLayout.addWidget(self.basicGraph)
        self.graphTabs.addTab(self.basic, "Temp/Humid")

        # Contains all elements relevant to display of spectrometer data
        self.spectrometer = QtGui.QWidget()
        self.spectrometerGraphLayout = QtGui.QHBoxLayout(self.spectrometer)
        self.spectrometerGraphLayout.setMargin(0)
        self.spectrometerGraph = GraphArea()
        self.spectrometerGraphLayout.addWidget(self.spectrometerGraph)
        self.graphTabs.addTab(self.spectrometer, "Spectrometer")

        # Contains all elements relevant to display pictures
        self.picture = QtGui.QWidget()
        self.scrollbar = QtGui.QScrollBar()
        self.pictureLayout = QtGui.QHBoxLayout(self.picture)
        self.pictureLayout.setMargin(0)
        self.pictureLayout.setSpacing(2)
        self.graphTabs.addTab(self.picture, "Site Pictures")

        self.digMainLayout.addLayout(self.inputFrame)
        self.displayFrame.addWidget(self.graphTabs)
        self.digMainLayout.addLayout(self.displayFrame)

        self.connect(self.fileInput, QtCore.SIGNAL("returnPressed()"), self.enterfile)
        self.connect(self.importButton, QtCore.SIGNAL("clicked()"), self.enterfile)
        #self.connect(self.sensorEnables.saveGraphsButton, QtCore.SIGNAL("clicked()"), lambda: self.basicGraph.graph_basic(self.ds, self.sensorEnableBools))
        #self.connect(self.sensorEnables.tsheath1.stateChanged.connect(lambda: self.updateSensorBools(self.sensorEnables.tsheath1)))

        self.setCentralWidget(self.centralWidget)

    def enterfile(self):
        """ Enters the file contents to graphing area. Grabs the name of file entered, parses that file,
            and graphs its data."""
        filename = self.fileInput.text()
        if filename != self.current_file:
            if filename.lower().endswith('.csv'):
                # Assuming basic temp/humid.
                self.parsecsv(filename)
                self.current_file = filename
                # TODO: Add check for Spectrometer data and conditional graph call.
                if self.csv_type == "basic":
                    # self.basicGraph.graph_basic(self.ds, sensorEnableBools)
                    # TODO: Refactor to handle sensor class
                    pass
                elif self.csv_type == "spectrometer":
                    self.spectrometerGraph.graph_spectrometer(self.spectrometer_data)
            elif filename.lower().endswith('.png'):
                self.showpicture(filename)
            else:
                self.showdialogue("Unsupported file type. Please input a .csv or .png file.")

        else:
            self.showdialogue("File requested is already entered.")

    def showpicture(self, pic_name):
        """" Displays a picture """
        self.pictureLabel = QtGui.QLabel()
        self.picturePixmap = QtGui.QPixmap(pic_name)
        self.pictureLabel.setPixmap(self.picturePixmap)
        self.pictureLayout.addWidget(self.pictureLabel)
        self.pictureLayout.addWidget(self.picture)
        self.picture.show()
        self.pictureLayout.addWidget(self.scrollbar)

    def parsecsv(self, csv_name):
        """ Parses a CSV file containing MRDT-2016 formatted basic or spectrometer data.
            Places data in relevant data store. """
        with open(csv_name, 'r') as csvfile:
            reader = csv.reader(csvfile, delimiter=' ')
            # check header for Spectrometer or Temp/Humid readings.
            header = next(reader)
            if header == ['datetime', 'sensor', 'measurement']:
                self.csv_type = "basic"
            elif header == ["wavelength", "intensity"]:
                self.csv_type = "spectrometer"

            for row in reader:
                try:
                    if self.csv_type == "basic":
                        datestamp, sensor, raw_data = row
                        if sensor == "Temp1":
                            self.ds.temp1.append((dateutil.parser.parse(datestamp), raw_data))
                        elif sensor == "Temp2":
                            self.ds.temp2.append((dateutil.parser.parse(datestamp), raw_data))
                        elif sensor == "Temp3":
                            self.ds.temp3.append((dateutil.parser.parse(datestamp), raw_data))
                        elif sensor == "Temp4":
                            self.ds.temp4.append((dateutil.parser.parse(datestamp), raw_data))
                        elif sensor == "Humid1":
                            self.ds.humid1.append((dateutil.parser.parse(datestamp), raw_data))
                        elif sensor == "Humid2":
                            self.ds.humid2.append((dateutil.parser.parse(datestamp), raw_data))
                        elif sensor == "Humid3":
                            self.ds.humid3.append((dateutil.parser.parse(datestamp), raw_data))
                        elif sensor == "Humid4":
                            self.ds.humid4.append((dateutil.parser.parse(datestamp), raw_data))
                    if self.csv_type == "spectrometer":
                        wavelength, intensity = row
                        # TODO: We completely forgot to test this. Ehrenfreund v1.1 needs to add this as well.
                        if type(wavelength) != "str" and type(intensity) != "str":
                            self.spectrometer_data.append((wavelength, intensity))
                except StopIteration:
                        pass

    def showdialogue(self, errormessage):
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
