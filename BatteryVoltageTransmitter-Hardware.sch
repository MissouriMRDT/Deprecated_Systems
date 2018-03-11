EESchema Schematic File Version 2
LIBS:power
LIBS:device
LIBS:switches
LIBS:relays
LIBS:motors
LIBS:transistors
LIBS:conn
LIBS:linear
LIBS:regul
LIBS:74xx
LIBS:cmos4000
LIBS:adc-dac
LIBS:memory
LIBS:xilinx
LIBS:microcontrollers
LIBS:dsp
LIBS:microchip
LIBS:analog_switches
LIBS:motorola
LIBS:texas
LIBS:intel
LIBS:audio
LIBS:interface
LIBS:digital-audio
LIBS:philips
LIBS:display
LIBS:cypress
LIBS:siliconi
LIBS:opto
LIBS:atmel
LIBS:contrib
LIBS:valves
LIBS:MRDT-Actives
LIBS:MRDT-Connectors
LIBS:MRDT-Devices
LIBS:MRDT-Drill_Holes
LIBS:MRDT-Headers
LIBS:MRDT-ICs
LIBS:MRDT-Passives
LIBS:MRDT-Shields
LIBS:MRDT-Silkscreens
LIBS:MRDT-Switches
LIBS:BatteryVoltageTransmitter-Hardware-cache
EELAYER 25 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title "Battery Voltage Transmitter"
Date "2018-03-10"
Rev "1"
Comp "Missouri S&T's Mars Rover Design Team"
Comment1 ""
Comment2 "for easy remote monitoring of the pack."
Comment3 "Raspberry PI Zero W. The PI will transmit batt pack data over wifi to a Slack channel"
Comment4 "This is a booster that sits on top of an MSP_EXP432 launchpad that has headers for a "
$EndDescr
$Comp
L MSP_EXP432P401R_Launchpad_Shield U1
U 1 1 5AA4548A
P 2750 3050
F 0 "U1" H 2800 1550 60  0000 C CNN
F 1 "MSP_EXP432P401R_Launchpad_Shield" H 3000 4400 60  0000 C CNN
F 2 "MRDT-Shields:MSP_EXP432P401R_Launchpad_FULL_Booster" H 2750 3050 60  0001 C CNN
F 3 "" H 2750 3050 60  0001 C CNN
	1    2750 3050
	1    0    0    -1  
$EndComp
$Comp
L Raspberry_Pi U2
U 1 1 5AA454D4
P 5600 3900
F 0 "U2" H 5650 3850 60  0000 C CNN
F 1 "Raspberry_Pi" H 5900 6100 60  0000 C CNN
F 2 "MRDT-Shields:RASPBERRY_PI_HEADERS" H 5600 5050 60  0001 C CNN
F 3 "" H 5600 5050 60  0001 C CNN
	1    5600 3900
	1    0    0    -1  
$EndComp
Wire Wire Line
	3600 2000 3600 2100
Wire Wire Line
	3500 2100 3750 2100
Wire Wire Line
	6600 1850 6600 2050
Wire Wire Line
	6400 1950 6600 1950
Wire Wire Line
	6400 2550 6600 2550
Wire Wire Line
	6600 4100 6600 2150
Wire Wire Line
	6600 2150 6400 2150
Connection ~ 6600 2550
Wire Wire Line
	6400 2850 6600 2850
Connection ~ 6600 2850
Wire Wire Line
	6400 3350 6600 3350
Connection ~ 6600 3350
Wire Wire Line
	6600 3550 6400 3550
Connection ~ 6600 3550
Wire Wire Line
	6600 2050 6400 2050
Connection ~ 6600 1950
Wire Wire Line
	5400 2350 5150 2350
Wire Wire Line
	5150 2350 5150 4100
Wire Wire Line
	5400 3850 5150 3850
Connection ~ 5150 3850
Wire Wire Line
	5400 3150 5150 3150
Connection ~ 5150 3150
Wire Wire Line
	5150 4100 6600 4100
Wire Wire Line
	5900 4200 5900 4100
Connection ~ 5900 4100
Wire Wire Line
	3500 2200 4000 2200
Wire Wire Line
	4000 2200 4000 3500
Wire Wire Line
	4000 3450 3500 3450
Connection ~ 4000 3450
$Comp
L R R1
U 1 1 5AA45B26
P 3900 2100
F 0 "R1" V 3800 2100 50  0000 C CNN
F 1 "100" V 3900 2100 50  0000 C CNN
F 2 "Resistors_SMD:R_0805_HandSoldering" V 3830 2100 50  0001 C CNN
F 3 "" H 3900 2100 50  0001 C CNN
	1    3900 2100
	0    1    1    0   
$EndComp
Connection ~ 3600 2100
$Comp
L LED D1
U 1 1 5AA45B9B
P 4250 2250
F 0 "D1" H 4250 2350 50  0000 C CNN
F 1 "LED" H 4250 2150 50  0000 C CNN
F 2 "LEDs:LED_0603_HandSoldering" H 4250 2250 50  0001 C CNN
F 3 "" H 4250 2250 50  0001 C CNN
	1    4250 2250
	0    -1   -1   0   
$EndComp
Wire Wire Line
	4250 2100 4050 2100
Connection ~ 4000 2200
NoConn ~ 6400 2250
NoConn ~ 6400 2450
NoConn ~ 6400 2650
NoConn ~ 6400 2750
NoConn ~ 6400 2950
NoConn ~ 6400 3050
NoConn ~ 6400 3150
NoConn ~ 6400 3250
NoConn ~ 6400 3450
NoConn ~ 6400 3650
NoConn ~ 6400 3750
NoConn ~ 6400 3850
NoConn ~ 5400 3750
NoConn ~ 5400 3650
NoConn ~ 5400 3550
NoConn ~ 5400 3450
NoConn ~ 5400 3350
NoConn ~ 5400 3250
NoConn ~ 5400 3050
NoConn ~ 5400 2950
NoConn ~ 5400 2850
NoConn ~ 5400 2750
NoConn ~ 5400 2650
NoConn ~ 5400 2550
NoConn ~ 5400 2450
NoConn ~ 5400 2250
NoConn ~ 5400 2150
NoConn ~ 5400 2050
NoConn ~ 5400 1950
NoConn ~ 3500 2300
NoConn ~ 3500 2400
NoConn ~ 3500 2500
NoConn ~ 3500 2600
NoConn ~ 3500 2700
NoConn ~ 3500 2800
NoConn ~ 3500 2900
NoConn ~ 3500 3000
NoConn ~ 3500 3550
NoConn ~ 3500 3650
NoConn ~ 3500 3750
NoConn ~ 3500 3850
NoConn ~ 3500 3950
NoConn ~ 3500 4050
NoConn ~ 3500 4150
NoConn ~ 3500 4250
NoConn ~ 3500 4350
NoConn ~ 2550 2100
NoConn ~ 2550 2200
NoConn ~ 2550 2300
NoConn ~ 2550 2400
NoConn ~ 2550 2500
NoConn ~ 2550 2600
NoConn ~ 2550 2700
NoConn ~ 2550 2800
NoConn ~ 2550 2900
NoConn ~ 2550 3000
NoConn ~ 2550 3450
NoConn ~ 2550 3550
NoConn ~ 2550 3650
NoConn ~ 2550 3750
NoConn ~ 2550 3850
NoConn ~ 2550 3950
NoConn ~ 2550 4150
NoConn ~ 2550 4250
NoConn ~ 2550 4350
Connection ~ 5400 3850
Connection ~ 5400 3150
Connection ~ 5400 2350
Connection ~ 6400 2550
Connection ~ 6400 2850
Connection ~ 6400 3350
Connection ~ 6400 3550
Connection ~ 6600 2050
$Comp
L PWR_FLAG #FLG01
U 1 1 5AA47E1D
P 1050 1300
F 0 "#FLG01" H 1050 1375 50  0001 C CNN
F 1 "PWR_FLAG" H 1050 1450 50  0000 C CNN
F 2 "" H 1050 1300 50  0001 C CNN
F 3 "" H 1050 1300 50  0001 C CNN
	1    1050 1300
	1    0    0    -1  
$EndComp
Wire Wire Line
	1050 1300 1050 1600
Wire Wire Line
	1600 1300 1600 1600
$Comp
L PWR_FLAG #FLG02
U 1 1 5AA47F8B
P 1600 1300
F 0 "#FLG02" H 1600 1375 50  0001 C CNN
F 1 "PWR_FLAG" H 1600 1450 50  0000 C CNN
F 2 "" H 1600 1300 50  0001 C CNN
F 3 "" H 1600 1300 50  0001 C CNN
	1    1600 1300
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR03
U 1 1 5AA47FFD
P 1600 1600
F 0 "#PWR03" H 1600 1350 50  0001 C CNN
F 1 "GND" H 1600 1450 50  0000 C CNN
F 2 "" H 1600 1600 50  0001 C CNN
F 3 "" H 1600 1600 50  0001 C CNN
	1    1600 1600
	1    0    0    -1  
$EndComp
$Comp
L +5V #PWR04
U 1 1 5AA4801D
P 1050 1600
F 0 "#PWR04" H 1050 1450 50  0001 C CNN
F 1 "+5V" H 1050 1740 50  0000 C CNN
F 2 "" H 1050 1600 50  0001 C CNN
F 3 "" H 1050 1600 50  0001 C CNN
	1    1050 1600
	-1   0    0    1   
$EndComp
$Comp
L +5V #PWR05
U 1 1 5AA480F1
P 6600 1850
F 0 "#PWR05" H 6600 1700 50  0001 C CNN
F 1 "+5V" H 6600 1990 50  0000 C CNN
F 2 "" H 6600 1850 50  0001 C CNN
F 3 "" H 6600 1850 50  0001 C CNN
	1    6600 1850
	1    0    0    -1  
$EndComp
$Comp
L +5V #PWR06
U 1 1 5AA48151
P 3600 2000
F 0 "#PWR06" H 3600 1850 50  0001 C CNN
F 1 "+5V" H 3600 2140 50  0000 C CNN
F 2 "" H 3600 2000 50  0001 C CNN
F 3 "" H 3600 2000 50  0001 C CNN
	1    3600 2000
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR07
U 1 1 5AA4829D
P 4000 3500
F 0 "#PWR07" H 4000 3250 50  0001 C CNN
F 1 "GND" H 4000 3350 50  0000 C CNN
F 2 "" H 4000 3500 50  0001 C CNN
F 3 "" H 4000 3500 50  0001 C CNN
	1    4000 3500
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR08
U 1 1 5AA48309
P 5900 4200
F 0 "#PWR08" H 5900 3950 50  0001 C CNN
F 1 "GND" H 5900 4050 50  0000 C CNN
F 2 "" H 5900 4200 50  0001 C CNN
F 3 "" H 5900 4200 50  0001 C CNN
	1    5900 4200
	1    0    0    -1  
$EndComp
Wire Wire Line
	2550 4050 2150 4050
Text GLabel 2150 4050 0    60   Output ~ 0
MSP432_TX_to_PI_RX
Wire Wire Line
	6400 2350 6850 2350
Text GLabel 6850 2350 2    60   Input ~ 0
MSP432_TX_to_PI_RX
Wire Wire Line
	4250 2400 4000 2400
Connection ~ 4000 2400
$Comp
L MRDT_Logo S1
U 1 1 5AA4D166
P 1050 2100
F 0 "S1" H 1100 2050 60  0000 C CNN
F 1 "MRDT_Logo" H 1300 2150 60  0000 C CNN
F 2 "MRDT-Silkscreens:MRDT_Logo_7.5mm" H 1050 2100 60  0001 C CNN
F 3 "" H 1050 2100 60  0001 C CNN
	1    1050 2100
	1    0    0    -1  
$EndComp
$EndSCHEMATC
