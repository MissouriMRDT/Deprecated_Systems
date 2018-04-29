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
LIBS:MRDT_Actives
LIBS:MRDT_Connectors
LIBS:MRDT_Devices
LIBS:MRDT_Drill_Holes
LIBS:MRDT_Headers
LIBS:MRDT_ICs
LIBS:MRDT_Passives
LIBS:MRDT_Shields
LIBS:MRDT_Silkscreens
LIBS:MRDT_Switches
LIBS:Gimbal Mastboard ESP-cache
EELAYER 25 0
EELAYER END
$Descr USLetter 8500 11000 portrait
encoding utf-8
Sheet 1 1
Title "Gimbal Mastboard"
Date "2018-04-28"
Rev "Rev 3"
Comp "Mars Rover Design Team"
Comment1 "Andrew Van Horn"
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L ESP_8266_Breakout_Small U1
U 1 1 5AE48C38
P 2600 8400
F 0 "U1" H 2650 8350 60  0000 C CNN
F 1 "ESP_8266_Breakout_Small" H 2850 9300 60  0000 C CNN
F 2 "MRDT_Shields:ESP_8266_Breakout_Small" H 2400 8050 60  0001 C CNN
F 3 "" H 2400 8050 60  0001 C CNN
	1    2600 8400
	1    0    0    -1  
$EndComp
$Comp
L IMU_LSM90S1 U3
U 1 1 5AE48C9F
P 6400 8100
F 0 "U3" H 6100 8050 60  0001 C CNN
F 1 "IMU_LSM90S1" H 6400 8850 60  0000 C CNN
F 2 "MRDT_Devices:IMU_LSM90S1" H 6100 8100 60  0001 C CNN
F 3 "" H 6100 8100 60  0001 C CNN
	1    6400 8100
	1    0    0    -1  
$EndComp
$Comp
L Anderson_2 Conn1
U 1 1 5AE48F87
P 2250 5800
F 0 "Conn1" H 2600 6000 60  0000 C CNN
F 1 "Anderson_2" H 2350 6300 60  0000 C CNN
F 2 "MRDT_Connectors:Anderson_2_Horisontal_Side_by_Side" H 2300 5250 60  0001 C CNN
F 3 "" H 2300 5250 60  0001 C CNN
	1    2250 5800
	-1   0    0    -1  
$EndComp
$Comp
L OKI U2
U 1 1 5AE48FCA
P 3200 5850
F 0 "U2" H 3050 5600 60  0001 C CNN
F 1 "OKI-3.3V" H 3350 6200 60  0000 C CNN
F 2 "MRDT_Devices:OKI_Horisontal" H 2950 5750 60  0001 C CNN
F 3 "" H 2950 5750 60  0001 C CNN
	1    3200 5850
	1    0    0    -1  
$EndComp
$Comp
L C C1
U 1 1 5AE4902B
P 2500 5600
F 0 "C1" H 2525 5700 50  0000 L CNN
F 1 "10uF" H 2450 5600 50  0000 L CNN
F 2 "Capacitors_SMD:C_0603_HandSoldering" H 2538 5450 50  0001 C CNN
F 3 "" H 2500 5600 50  0001 C CNN
	1    2500 5600
	1    0    0    -1  
$EndComp
$Comp
L C C3
U 1 1 5AE491F2
P 2750 5600
F 0 "C3" H 2775 5700 50  0000 L CNN
F 1 "10uF" H 2650 5600 50  0000 L CNN
F 2 "Capacitors_SMD:C_0603_HandSoldering" H 2788 5450 50  0001 C CNN
F 3 "" H 2750 5600 50  0001 C CNN
	1    2750 5600
	1    0    0    -1  
$EndComp
Wire Wire Line
	2350 5450 3000 5450
Wire Wire Line
	3000 5450 3000 5600
Wire Wire Line
	2350 5750 3000 5750
Wire Wire Line
	3000 5750 3000 5700
$Comp
L C C4
U 1 1 5AE4922C
P 2750 5900
F 0 "C4" H 2775 6000 50  0000 L CNN
F 1 "10uF" H 2775 5800 50  0000 L CNN
F 2 "Capacitors_SMD:C_0603_HandSoldering" H 2788 5750 50  0001 C CNN
F 3 "" H 2750 5900 50  0001 C CNN
	1    2750 5900
	1    0    0    -1  
$EndComp
$Comp
L C C2
U 1 1 5AE49257
P 2500 5900
F 0 "C2" H 2525 6000 50  0000 L CNN
F 1 "10uF" H 2525 5800 50  0000 L CNN
F 2 "Capacitors_SMD:C_0603_HandSoldering" H 2538 5750 50  0001 C CNN
F 3 "" H 2500 5900 50  0001 C CNN
	1    2500 5900
	1    0    0    -1  
$EndComp
Wire Wire Line
	2500 6050 3050 6050
Wire Wire Line
	3000 6050 3000 5800
Connection ~ 2500 5450
Connection ~ 2750 5450
Connection ~ 2750 5750
Connection ~ 2500 5750
Connection ~ 2500 6050
Connection ~ 2750 6050
$Comp
L R R1
U 1 1 5AE492B1
P 2350 6200
F 0 "R1" V 2250 6200 50  0000 C CNN
F 1 "330" V 2350 6200 50  0000 C CNN
F 2 "Resistors_SMD:R_0603_HandSoldering" V 2280 6200 50  0001 C CNN
F 3 "" H 2350 6200 50  0001 C CNN
	1    2350 6200
	1    0    0    -1  
$EndComp
$Comp
L LED D1
U 1 1 5AE49362
P 2350 5900
F 0 "D1" H 2450 6000 50  0000 C CNN
F 1 "LED" H 2450 5800 50  0000 C CNN
F 2 "LEDs:LED_0603_HandSoldering" H 2350 5900 50  0001 C CNN
F 3 "" H 2350 5900 50  0001 C CNN
	1    2350 5900
	0    1    1    0   
$EndComp
Wire Wire Line
	2350 6350 2500 6350
Wire Wire Line
	2500 6350 2500 6050
Text Label 2900 5450 0    60   ~ 0
+12V
Text Label 2800 5750 0    60   ~ 0
GND
Text GLabel 3050 6050 2    60   Output ~ 0
+3V3
Connection ~ 3000 6050
Text GLabel 2400 7650 0    60   Input ~ 0
+3V3
Text GLabel 3250 7650 2    60   Input ~ 0
+3V3
Text GLabel 2400 7750 0    60   UnSpc ~ 0
GND
Text GLabel 5850 7550 0    60   Input ~ 0
SCL
Text GLabel 5850 7650 0    60   Input ~ 0
SDA
Text GLabel 5850 7450 0    60   Input ~ 0
+3V3
Text GLabel 6950 7500 2    60   UnSpc ~ 0
GND
Text GLabel 2400 8050 0    60   Output ~ 0
SDA
Text GLabel 2400 8150 0    60   Output ~ 0
SCL
$Comp
L Molex_SL_4 Conn2
U 1 1 5AE49A37
P 6200 5500
F 0 "Conn2" H 6250 5450 60  0001 C CNN
F 1 "Molex_SL_4" H 6250 5950 60  0000 C CNN
F 2 "MRDT_Connectors:MOLEX_SL_4_Horizontal" H 6200 5500 60  0001 C CNN
F 3 "" H 6200 5500 60  0001 C CNN
	1    6200 5500
	1    0    0    -1  
$EndComp
$Comp
L Molex_SL_3 Conn3
U 1 1 5AE49B23
P 6200 5950
F 0 "Conn3" H 6250 5900 60  0001 C CNN
F 1 "Molex_SL_3" H 6250 6300 60  0000 C CNN
F 2 "MRDT_Connectors:MOLEX_SL_3_Horizontal" H 6200 5950 60  0001 C CNN
F 3 "" H 6200 5950 60  0001 C CNN
	1    6200 5950
	1    0    0    -1  
$EndComp
Text Notes 6400 5300 0    60   ~ 0
I2C Out
Text Notes 6400 5800 0    60   ~ 0
PWM Out
Text GLabel 6000 5800 0    60   Input ~ 0
+3V3
Text GLabel 6000 5700 0    60   Input ~ 0
PWM_Out
Text GLabel 6000 5900 0    60   UnSpc ~ 0
GND
Text GLabel 3250 7950 2    60   Output ~ 0
PWM_Out
Text GLabel 6000 5450 0    60   UnSpc ~ 0
GND
Text GLabel 6000 5350 0    60   Input ~ 0
+3V3
Text GLabel 6000 5250 0    60   Input ~ 0
SDA
Text GLabel 6000 5150 0    60   Input ~ 0
SCL
Text GLabel 5850 7750 0    60   Input ~ 0
+3V3
Text GLabel 5850 7850 0    60   Input ~ 0
+3V3
Text GLabel 5850 7950 0    60   Input ~ 0
+3V3
Text GLabel 5850 8050 0    60   Input ~ 0
+3V3
Text GLabel 6950 7600 2    60   Input ~ 0
+3V3
Wire Wire Line
	6950 7700 6950 8100
Connection ~ 6950 8000
Connection ~ 6950 7900
Connection ~ 6950 7800
$Comp
L R R2
U 1 1 5AE4AD9D
P 6950 8250
F 0 "R2" V 7030 8250 50  0000 C CNN
F 1 "1M" V 6950 8250 50  0000 C CNN
F 2 "Resistors_SMD:R_0603_HandSoldering" V 6880 8250 50  0001 C CNN
F 3 "" H 6950 8250 50  0001 C CNN
	1    6950 8250
	1    0    0    -1  
$EndComp
Text GLabel 6950 8400 3    60   UnSpc ~ 0
GND
Text Notes 4850 8050 0    60   ~ 0
Sets I2C Mode
Text Notes 4750 7850 0    60   ~ 0
Sets I2C Address
Text Notes 7000 7950 0    60   ~ 0
Unused Interupts
$EndSCHEMATC
