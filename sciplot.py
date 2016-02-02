######## Missouri University of Science and Technology########
#        Mars Rover Design Team                              #
#        Author: Matthew Healy    mhrh3@mst.edu              #
#                                                            #
#    SciPlot is a graphing module that plots data from a     #
#    serial input in real time.                              #
#                                                            #
#  Usage: python3.4 sciplot.py [-h] [-p] [-b] [-f] [-m] [-s] #
##############################################################



import serial 						
import numpy						
import matplotlib.pyplot as plt
import csv
import argparse
import glob
import sys

global count
global MAX_PLOT_SIZE
global beginData
global endData
global filename
global port
global sensor

count = 0
relativeCount = []
plt.ion()
dataStore = []
graphStore = []

MAX_PLOT_SIZE = 7

dataRange = []
beginData = 0
endData = 0

plt.plot(graphStore, 'r,', label='Humidity')
port = 0
baudrate = 9600


def serial_ports():
    """ Lists serial port names

        :raises EnvironmentError:
            On unsupported or unknown platforms
        :returns:
            A list of the serial ports available on the system
    """
    if sys.platform.startswith('win'):
        ports = ['COM%s' % (i + 1) for i in range(256)]
    elif sys.platform.startswith('linux') or sys.platform.startswith('cygwin'):
        # this excludes your current terminal "/dev/tty"
        ports = glob.glob('/dev/tty[A-Za-z]*')
    elif sys.platform.startswith('darwin'):
        ports = glob.glob('/dev/tty.*')
    else:
        return 0

    result = []
    for port in ports:
        try:
            s = serial.Serial(port)
            s.close()
            result.append(port)
        except (OSError, serial.SerialException):
            pass
    return result


def serial_check(list_of_ports):
    valid_ports = []
    for port in list_of_ports:
        testinput = serial.Serial(port, 9600, timeout=1)
        print("testing input: ",port)
        testdata = testinput.readline()
        try:
            testdata
        except (NameError):
            print("passing port: ",port)
            pass
        else:
            print("made it to else clause")
            valid_ports.append(port)
    if len((valid_ports) == 1):
        return port
    else:
        print("wrong number of availible ports, must be specified by -p tag")
        print(valid_ports)


def graph():
    global count
    if (count < MAX_PLOT_SIZE):
        plt.clf()
        plt.scatter(count,graphStore[count])
        plt.ylim(-5,100)
        plt.grid(True)
        plt.title(sensor)
        plt.plot(graphStore)
        plt.show()
        count += 1
    else:
        plt.clf()
        endData = count+1
        beginData = (count - MAX_PLOT_SIZE)
        dataRange = numpy.arange(beginData,(endData))
        plt.ylim(-5,100)
        plt.grid(True)
        plt.title(sensor)
        plt.scatter(dataRange,graphStore)
        plt.plot(dataRange,graphStore)
        plt.show
        count += 1
        graphStore.pop(0)
    plt.pause(0.0001)

def main():
        print("entered main")
        portslist = serial_ports()
        print("found portslist")
        print(portslist)
        serialport = serial_check(portslist)
        
        parser = argparse.ArgumentParser(description='plot scientific data in real time')
        parser.add_argument('-p', default=serialport, action="store", dest="port",help="name of serial input")
        parser.add_argument('-b', default=9600, action="store", dest="baudrate", help="baudrate for data transfer")
        parser.add_argument('-f', default="sensor_data", action="store", dest="filename", help="name of file for data to be stored in")
        parser.add_argument('-m', default=7, action="store", dest="MAX_PLOT_SIZE", help="maximum size for x axis (recommended < 10)")
        parser.add_argument('-s', default="Sensor Data", action="store", dest="sensor", help="sensor being used, in order to correctly title plot")

        args = parser.parse_args()
        global MAX_PLOT_SIZE
        global filename
        global port
        MAX_PLOT_SIZE = args.MAX_PLOT_SIZE
        port = args.port
        filename = args.filename + '.csv'
        serialData = serial.Serial(port, baudrate)
        sensor = args.sensor
        while(True):
                
                try:
                        y = float(serialData.readline())
                        dataStore.append(y)
                        graphStore.append(y)
                        graph()
                except(KeyboardInterrupt,SystemExit):
                        with open(filename,'w') as data_output:
                                datawriter = csv.writer(data_output, delimiter = ',')
                                datawriter.writerow(dataStore)

if __name__=="__main__":
        main()
