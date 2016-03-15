# Missouri University of Science and Technology
# Mars Rover Design Team
# Shannon Klaus         smk43b@mst.edu

import serial
import numpy
import matplotlib.pyplot as plt
import csv
import argparse
import glob
import sys

global count
global MAX_PLOT_SIZE
global begin_data
global end_data
global file_name
global port
global PACKET_SIZE

port = 'COM5'
plt.ion()
data_store = []
baud_rate = 9600
PACKET_SIZE = 3648
MAX_PLOT_SIZE = 4096


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
            Pass
    return result

def serial_check(list_of_ports):
    valid_ports = []
    for port in list_of_ports:
        test_input = serial.Serial(port, 9600, timeout=.001)
        print("Testing serial input: ",port)
        test_data = test_input.readline()
        try:
            print(float(test_data))
        except (NameError, ValueError):
            print("Serial input invalid: ",port)
            Pass
        else:
            print("made it to else clause")
            valid_ports.append(port)
    if (len(valid_ports) == 1):
        return port
    else:
        print("There is more than one valid serial input, you must specify which to use by using th -p tag.")
        print("These are the valid inputs: ",valid_ports)

def graph(data_store):    # confirmed working
    plt.clf()
    plt.title('CCD Visualizer')
    plt.ylim(0,MAX_PLOT_SIZE)
    plt.grid(True)
    lines = plt.plot(data_store)
    plt.setp(lines, linewidth=2, color='r')
    plt.show()


def main():
    data_store = []
   
    serial_data = serial.Serial(port, baud_rate)
    while(True):
        try:
            for x in range(PACKET_SIZE):
                print(x)
                y = float(serial_data.readline())
                data_store.append(y)
            graph(data_store)
        except(KeyboardInterrupt,SystemExit):
            with open(file_name,'w') as data_output:
                datawriter = csv.writer(data_output, delimiter = ',')
                datawriter.writerow(data_store)
    

if __name__=="__main__":
        main()
