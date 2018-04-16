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
LIBS:GimbalVFDDriveIntegrationBoard-cache
EELAYER 25 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title "Gimbal VFD Drive Integration Board"
Date "2018-04-15"
Rev "Rev1"
Comp "Mars Rover Design Team"
Comment1 "Andrew Van Horn"
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L LAUNCHXL_F28069M_Launchpad_Full U1
U 1 1 5AD3C08C
P 1950 4100
F 0 "U1" H 2050 4050 60  0001 C CNN
F 1 "LAUNCHXL_F28069M_Launchpad_Full" H 3250 6800 60  0000 C CNN
F 2 "MRDT_Shields:LAUNCHXL_F28069M_Launchpad_FULL_Booster_SMD" H 1950 4100 60  0001 C CNN
F 3 "" H 1950 4100 60  0001 C CNN
	1    1950 4100
	1    0    0    -1  
$EndComp
$Comp
L TM4C129E_Launchpad_Full U2
U 1 1 5AD3C0A0
P 1950 6800
F 0 "U2" H 2050 6750 60  0001 C CNN
F 1 "TM4C129E_Launchpad_Full" H 3350 6000 60  0000 C CNN
F 2 "MRDT_Shields:TM4C129E_Launchpad_FULL_Booster_Bottom_SMD" H 1950 6800 60  0001 C CNN
F 3 "" H 1950 6800 60  0001 C CNN
	1    1950 6800
	1    0    0    -1  
$EndComp
$Comp
L Anderson_3 C1
U 1 1 5AD3C0BE
P 8400 1500
F 0 "C1" H 8450 1450 60  0000 C CNN
F 1 "Anderson_3" H 8550 2250 60  0000 C CNN
F 2 "MRDT_Connectors:Anderson_3_Horisontal_Side_by_Side" H 8450 950 60  0001 C CNN
F 3 "" H 8450 950 60  0001 C CNN
	1    8400 1500
	-1   0    0    -1  
$EndComp
Text Notes 8050 650  0    60   ~ 0
Power In
$Comp
L OKI U7
U 1 1 5AD3C167
P 9700 1050
F 0 "U7" H 9550 800 60  0001 C CNN
F 1 "OKI" H 9850 1400 60  0000 C CNN
F 2 "MRDT_Devices:OKI_Horisontal" H 9450 950 60  0001 C CNN
F 3 "" H 9450 950 60  0001 C CNN
	1    9700 1050
	1    0    0    -1  
$EndComp
Text Notes 7750 1200 0    60   ~ 0
12V_ACT
Text Notes 7700 1450 0    60   ~ 0
12V_Logic
Text Notes 7850 950  0    60   ~ 0
GND
Text GLabel 10100 1250 2    60   Input ~ 0
+3V3
Text Notes 10050 900  0    60   ~ 0
12V-3.3V Oki
Text GLabel 8550 1150 2    60   Input ~ 0
V_ACT
Text GLabel 9000 1400 2    60   Input ~ 0
V_Logic
Text GLabel 8550 2150 0    60   Input ~ 0
V_ACT
Text GLabel 8550 2450 0    60   UnSpc ~ 0
GND
Text GLabel 8550 2900 0    60   UnSpc ~ 0
GND
Text GLabel 8550 3350 0    60   UnSpc ~ 0
GND
Text GLabel 8550 2600 0    60   Input ~ 0
V_Logic
Text GLabel 8550 3050 0    60   Input ~ 0
+3V3
$Comp
L C C?
U 1 1 5AD3C25F
P 9400 2300
AR Path="/5AD3C3F6" Ref="C?"  Part="1" 
AR Path="/5AD3C25F" Ref="C11"  Part="1" 
F 0 "C11" H 9425 2400 50  0000 L CNN
F 1 "10uF" H 9425 2200 50  0000 L CNN
F 2 "Capacitors_SMD:C_0603_HandSoldering" H 9438 2150 50  0001 C CNN
F 3 "" H 9400 2300 50  0001 C CNN
	1    9400 2300
	1    0    0    -1  
$EndComp
$Comp
L C C5
U 1 1 5AD3C3D5
P 8900 2300
F 0 "C5" H 8925 2400 50  0000 L CNN
F 1 "10uF" H 8925 2200 50  0000 L CNN
F 2 "Capacitors_SMD:C_0603_HandSoldering" H 8938 2150 50  0001 C CNN
F 3 "" H 8900 2300 50  0001 C CNN
	1    8900 2300
	1    0    0    -1  
$EndComp
$Comp
L C C2
U 1 1 5AD3C3F6
P 8650 2300
F 0 "C2" H 8675 2400 50  0000 L CNN
F 1 "10uF" H 8675 2200 50  0000 L CNN
F 2 "Capacitors_SMD:C_0603_HandSoldering" H 8688 2150 50  0001 C CNN
F 3 "" H 8650 2300 50  0001 C CNN
	1    8650 2300
	1    0    0    -1  
$EndComp
$Comp
L C C8
U 1 1 5AD3C460
P 9150 2300
F 0 "C8" H 9175 2400 50  0000 L CNN
F 1 "10uF" H 9175 2200 50  0000 L CNN
F 2 "Capacitors_SMD:C_0603_HandSoldering" H 9188 2150 50  0001 C CNN
F 3 "" H 9150 2300 50  0001 C CNN
	1    9150 2300
	1    0    0    -1  
$EndComp
$Comp
L C C14
U 1 1 5AD3C487
P 9650 2300
F 0 "C14" H 9675 2400 50  0000 L CNN
F 1 ".1uF" H 9675 2200 50  0000 L CNN
F 2 "Capacitors_SMD:C_0603_HandSoldering" H 9688 2150 50  0001 C CNN
F 3 "" H 9650 2300 50  0001 C CNN
	1    9650 2300
	1    0    0    -1  
$EndComp
$Comp
L C C3
U 1 1 5AD3C81F
P 8650 2750
F 0 "C3" H 8675 2850 50  0000 L CNN
F 1 "10uF" H 8675 2650 50  0000 L CNN
F 2 "Capacitors_SMD:C_0603_HandSoldering" H 8688 2600 50  0001 C CNN
F 3 "" H 8650 2750 50  0001 C CNN
	1    8650 2750
	1    0    0    -1  
$EndComp
$Comp
L C C6
U 1 1 5AD3C84E
P 8900 2750
F 0 "C6" H 8925 2850 50  0000 L CNN
F 1 "10uF" H 8925 2650 50  0000 L CNN
F 2 "Capacitors_SMD:C_0603_HandSoldering" H 8938 2600 50  0001 C CNN
F 3 "" H 8900 2750 50  0001 C CNN
	1    8900 2750
	1    0    0    -1  
$EndComp
$Comp
L C C9
U 1 1 5AD3C87A
P 9150 2750
F 0 "C9" H 9175 2850 50  0000 L CNN
F 1 "10uF" H 9175 2650 50  0000 L CNN
F 2 "Capacitors_SMD:C_0603_HandSoldering" H 9188 2600 50  0001 C CNN
F 3 "" H 9150 2750 50  0001 C CNN
	1    9150 2750
	1    0    0    -1  
$EndComp
$Comp
L C C12
U 1 1 5AD3C8AF
P 9400 2750
F 0 "C12" H 9425 2850 50  0000 L CNN
F 1 "10uF" H 9425 2650 50  0000 L CNN
F 2 "Capacitors_SMD:C_0603_HandSoldering" H 9438 2600 50  0001 C CNN
F 3 "" H 9400 2750 50  0001 C CNN
	1    9400 2750
	1    0    0    -1  
$EndComp
$Comp
L C C15
U 1 1 5AD3C8E7
P 9650 2750
F 0 "C15" H 9675 2850 50  0000 L CNN
F 1 ".1uF" H 9675 2650 50  0000 L CNN
F 2 "Capacitors_SMD:C_0603_HandSoldering" H 9688 2600 50  0001 C CNN
F 3 "" H 9650 2750 50  0001 C CNN
	1    9650 2750
	1    0    0    -1  
$EndComp
$Comp
L C C4
U 1 1 5AD3C924
P 8650 3200
F 0 "C4" H 8675 3300 50  0000 L CNN
F 1 "10uF" H 8675 3100 50  0000 L CNN
F 2 "Capacitors_SMD:C_0603_HandSoldering" H 8688 3050 50  0001 C CNN
F 3 "" H 8650 3200 50  0001 C CNN
	1    8650 3200
	1    0    0    -1  
$EndComp
$Comp
L C C7
U 1 1 5AD3C962
P 8900 3200
F 0 "C7" H 8925 3300 50  0000 L CNN
F 1 "10uF" H 8925 3100 50  0000 L CNN
F 2 "Capacitors_SMD:C_0603_HandSoldering" H 8938 3050 50  0001 C CNN
F 3 "" H 8900 3200 50  0001 C CNN
	1    8900 3200
	1    0    0    -1  
$EndComp
$Comp
L C C10
U 1 1 5AD3C9A3
P 9150 3200
F 0 "C10" H 9175 3300 50  0000 L CNN
F 1 "10uF" H 9175 3100 50  0000 L CNN
F 2 "Capacitors_SMD:C_0603_HandSoldering" H 9188 3050 50  0001 C CNN
F 3 "" H 9150 3200 50  0001 C CNN
	1    9150 3200
	1    0    0    -1  
$EndComp
$Comp
L C C13
U 1 1 5AD3C9E7
P 9400 3200
F 0 "C13" H 9425 3300 50  0000 L CNN
F 1 "10uF" H 9425 3100 50  0000 L CNN
F 2 "Capacitors_SMD:C_0603_HandSoldering" H 9438 3050 50  0001 C CNN
F 3 "" H 9400 3200 50  0001 C CNN
	1    9400 3200
	1    0    0    -1  
$EndComp
$Comp
L C C16
U 1 1 5AD3CA2C
P 9650 3200
F 0 "C16" H 9675 3300 50  0000 L CNN
F 1 ".1uF" H 9675 3100 50  0000 L CNN
F 2 "Capacitors_SMD:C_0603_HandSoldering" H 9688 3050 50  0001 C CNN
F 3 "" H 9650 3200 50  0001 C CNN
	1    9650 3200
	1    0    0    -1  
$EndComp
$Comp
L R R1
U 1 1 5AD3CA68
P 9950 3050
F 0 "R1" V 10030 3050 50  0000 C CNN
F 1 "330" V 9950 3050 50  0000 C CNN
F 2 "Resistors_SMD:R_0603_HandSoldering" V 9880 3050 50  0001 C CNN
F 3 "" H 9950 3050 50  0001 C CNN
	1    9950 3050
	0    1    1    0   
$EndComp
$Comp
L LED D1
U 1 1 5AD3CAE5
P 10250 3200
F 0 "D1" H 10250 3300 50  0000 C CNN
F 1 "LED" H 10250 3100 50  0000 C CNN
F 2 "LEDs:LED_1206_HandSoldering" H 10250 3200 50  0001 C CNN
F 3 "" H 10250 3200 50  0001 C CNN
	1    10250 3200
	0    -1   -1   0   
$EndComp
$Comp
L Anderson_2 C18
U 1 1 5AD3F6E2
P 9800 5500
F 0 "C18" H 9850 5450 60  0000 C CNN
F 1 "DRV_1" V 10250 5700 60  0000 C CNN
F 2 "MRDT_Connectors:Anderson_2_Horisontal_Side_by_Side" H 9850 4950 60  0001 C CNN
F 3 "" H 9850 4950 60  0001 C CNN
	1    9800 5500
	0    -1   -1   0   
$EndComp
$Comp
L Anderson_2 C20
U 1 1 5AD3F91A
P 10600 5500
F 0 "C20" H 10650 5450 60  0000 C CNN
F 1 "DRV_2" V 11050 5700 60  0000 C CNN
F 2 "MRDT_Connectors:Anderson_2_Horisontal_Side_by_Side" H 10650 4950 60  0001 C CNN
F 3 "" H 10650 4950 60  0001 C CNN
	1    10600 5500
	0    -1   -1   0   
$EndComp
Text GLabel 10250 5650 3    60   Input ~ 0
V_ACT
Text GLabel 9450 5650 3    60   Input ~ 0
V_ACT
Text GLabel 9700 5650 3    60   UnSpc ~ 0
GND
Text GLabel 10500 5650 3    60   UnSpc ~ 0
GND
$Comp
L Molex_SL_3 U3
U 1 1 5AD3FBC7
P 7050 4050
F 0 "U3" H 7100 4000 60  0001 C CNN
F 1 "PWM_J1" H 7350 4200 60  0000 C CNN
F 2 "MRDT_Connectors:MOLEX_SL_3_Horizontal" H 7050 4050 60  0001 C CNN
F 3 "" H 7050 4050 60  0001 C CNN
	1    7050 4050
	1    0    0    -1  
$EndComp
$Comp
L Molex_SL_3 U4
U 1 1 5AD3FC5B
P 7050 4600
F 0 "U4" H 7100 4550 60  0001 C CNN
F 1 "PWM_J5" H 7350 4750 60  0000 C CNN
F 2 "MRDT_Connectors:MOLEX_SL_3_Horizontal" H 7050 4600 60  0001 C CNN
F 3 "" H 7050 4600 60  0001 C CNN
	1    7050 4600
	1    0    0    -1  
$EndComp
Text GLabel 6800 3900 0    60   Input ~ 0
+3V3
Text GLabel 6800 4000 0    60   UnSpc ~ 0
GND
Text GLabel 6800 4550 0    60   UnSpc ~ 0
GND
Text GLabel 6800 4450 0    60   Input ~ 0
+3V3
Text GLabel 1750 4550 0    60   Input ~ 0
+3V3
Text GLabel 1750 5850 0    60   Input ~ 0
+3V3
Text GLabel 1750 3150 0    60   Input ~ 0
+3V3
Text GLabel 1750 1750 0    60   Input ~ 0
+3V3
Text GLabel 2650 1850 2    60   UnSpc ~ 0
GND
Text GLabel 2650 3250 2    60   UnSpc ~ 0
GND
Text GLabel 4700 3150 2    60   UnSpc ~ 0
GND
Text GLabel 4700 1750 2    60   UnSpc ~ 0
GND
Text GLabel 2650 4650 2    60   UnSpc ~ 0
GND
Text GLabel 2650 5950 2    60   UnSpc ~ 0
GND
Text GLabel 4700 5850 2    60   UnSpc ~ 0
GND
Text GLabel 4700 4550 2    60   UnSpc ~ 0
GND
$Comp
L Jumper JP8
U 1 1 5AD44D61
P 5750 2250
F 0 "JP8" H 5750 2400 50  0000 C CNN
F 1 "Bottom VFD RX" H 5750 2170 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x02_Pitch1.27mm" H 5750 2250 50  0001 C CNN
F 3 "" H 5750 2250 50  0001 C CNN
	1    5750 2250
	0    1    1    0   
$EndComp
Text Label 5750 2600 3    60   ~ 0
UART_Bottom_RX
Text Label 4750 1950 0    60   ~ 0
UART_Bottom_RX_
Text Label 4750 2050 0    60   ~ 0
UART_Bottom_TX_
Text Label 1150 1950 0    60   ~ 0
UART_Top_RX_
Text Label 1150 2050 0    60   ~ 0
UART_Top_TX_
$Comp
L Jumper JP7
U 1 1 5AD45CFA
P 5500 2350
F 0 "JP7" H 5750 2400 50  0000 C CNN
F 1 "Bottom VFD TX" H 5500 2270 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x02_Pitch1.27mm" H 5500 2350 50  0001 C CNN
F 3 "" H 5500 2350 50  0001 C CNN
	1    5500 2350
	0    1    1    0   
$EndComp
Text Label 5500 2650 3    60   ~ 0
UART_Bottom_TX
$Comp
L Jumper JP2
U 1 1 5AD46545
P 1150 2350
F 0 "JP2" H 1150 2500 50  0000 C CNN
F 1 "Top VFD TX" H 1150 2270 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x02_Pitch1.27mm" H 1150 2350 50  0001 C CNN
F 3 "" H 1150 2350 50  0001 C CNN
	1    1150 2350
	0    1    1    0   
$EndComp
$Comp
L Jumper JP1
U 1 1 5AD465D4
P 900 2400
F 0 "JP1" H 900 2550 50  0000 C CNN
F 1 "Top VFD RX" H 900 2320 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x02_Pitch1.27mm" H 900 2400 50  0001 C CNN
F 3 "" H 900 2400 50  0001 C CNN
	1    900  2400
	0    1    1    0   
$EndComp
Text Label 1150 2650 3    60   ~ 0
UART_Top_TX
Text Label 900  2700 3    60   ~ 0
UART_Top_RX
Text Label 6450 3800 0    60   ~ 0
PWM_J1
Text Label 6500 4350 0    60   ~ 0
PWM_J5
$Comp
L Jumper JP5
U 1 1 5AD4A516
P 3650 2550
F 0 "JP5" H 3650 2700 50  0000 C CNN
F 1 "PWM_J1_Top" H 3650 2800 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x02_Pitch1.27mm" H 3650 2550 50  0001 C CNN
F 3 "" H 3650 2550 50  0001 C CNN
	1    3650 2550
	0    -1   -1   0   
$EndComp
$Comp
L Jumper JP6
U 1 1 5AD4A8EA
P 4900 3650
F 0 "JP6" H 4900 3800 50  0000 C CNN
F 1 "PWM_J5_Top" H 4900 3900 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x02_Pitch1.27mm" H 4900 3650 50  0001 C CNN
F 3 "" H 4900 3650 50  0001 C CNN
	1    4900 3650
	0    1    1    0   
$EndComp
$Comp
L Jumper JP4
U 1 1 5AD4AD11
P 2900 2550
F 0 "JP4" H 2900 2700 50  0000 C CNN
F 1 "PWM_J1_Bottom" H 2900 2800 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x02_Pitch1.27mm" H 2900 2550 50  0001 C CNN
F 3 "" H 2900 2550 50  0001 C CNN
	1    2900 2550
	0    1    1    0   
$EndComp
$Comp
L Jumper JP3
U 1 1 5AD4AEAC
P 1600 3650
F 0 "JP3" H 1600 3800 50  0000 C CNN
F 1 "PWM_J5_Bottom" H 1600 3900 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x02_Pitch1.27mm" H 1600 3650 50  0001 C CNN
F 3 "" H 1600 3650 50  0001 C CNN
	1    1600 3650
	0    -1   -1   0   
$EndComp
Text Label 3650 2250 1    60   ~ 0
PWM_J1_Top
Text Label 2800 2250 3    60   ~ 0
PWM_J1_Bottom
Text Label 1650 3350 2    60   ~ 0
PWM_J5_Bottom
Text Label 4750 3350 0    60   ~ 0
PWM_J5_Top
$Comp
L Anderson_2 C17
U 1 1 5AD4BDA5
P 9800 4800
F 0 "C17" H 9850 4750 60  0000 C CNN
F 1 "DRV_1" V 10250 5000 60  0000 C CNN
F 2 "MRDT_Connectors:Anderson_2_Horisontal_Side_by_Side" H 9850 4250 60  0001 C CNN
F 3 "" H 9850 4250 60  0001 C CNN
	1    9800 4800
	0    -1   -1   0   
$EndComp
$Comp
L Anderson_2 C19
U 1 1 5AD4BE1F
P 10600 4800
F 0 "C19" H 10650 4750 60  0000 C CNN
F 1 "DRV_2" V 11050 5000 60  0000 C CNN
F 2 "MRDT_Connectors:Anderson_2_Horisontal_Side_by_Side" H 10650 4250 60  0001 C CNN
F 3 "" H 10650 4250 60  0001 C CNN
	1    10600 4800
	0    -1   -1   0   
$EndComp
Wire Wire Line
	7650 900  9500 900 
Wire Wire Line
	7650 1400 9000 1400
Wire Wire Line
	9000 1400 9000 800 
Wire Wire Line
	9000 800  9500 800 
Wire Wire Line
	9500 1000 9500 1250
Wire Wire Line
	9500 1250 10100 1250
Wire Wire Line
	10250 3050 10100 3050
Wire Wire Line
	8550 3050 9800 3050
Wire Wire Line
	8550 2600 9650 2600
Wire Wire Line
	8550 2900 9650 2900
Wire Wire Line
	8550 2450 9650 2450
Wire Wire Line
	8550 2150 9650 2150
Wire Wire Line
	8550 3350 10250 3350
Connection ~ 8650 3350
Connection ~ 8900 3350
Connection ~ 9150 3350
Connection ~ 9400 3350
Connection ~ 9650 3350
Connection ~ 9400 3050
Connection ~ 9150 3050
Connection ~ 8900 3050
Connection ~ 8650 3050
Connection ~ 8650 2900
Connection ~ 8900 2900
Connection ~ 8900 2600
Connection ~ 8650 2600
Connection ~ 9150 2600
Connection ~ 9150 2900
Connection ~ 9400 2900
Connection ~ 9400 2600
Connection ~ 9400 2150
Connection ~ 9400 2450
Connection ~ 9150 2450
Connection ~ 9150 2150
Connection ~ 8900 2150
Connection ~ 8900 2450
Connection ~ 8650 2450
Connection ~ 8650 2150
Connection ~ 9650 3050
Wire Wire Line
	900  1950 1750 1950
Wire Wire Line
	1150 2050 1750 2050
Wire Wire Line
	4700 1950 5750 1950
Wire Wire Line
	4700 2050 5500 2050
Wire Wire Line
	5750 2550 5750 5550
Wire Wire Line
	900  1950 900  2100
Wire Wire Line
	5500 2650 5500 5650
Wire Wire Line
	1150 2650 1150 7000
Wire Wire Line
	900  2700 900  7150
Wire Wire Line
	2650 6650 2800 6650
Wire Wire Line
	2800 6650 2800 7000
Wire Wire Line
	2800 7000 1150 7000
Wire Wire Line
	900  7150 2700 7150
Wire Wire Line
	2700 7150 2700 6750
Wire Wire Line
	2700 6750 2650 6750
Wire Wire Line
	5500 5650 3000 5650
Wire Wire Line
	3000 5650 3000 6250
Wire Wire Line
	3000 6250 2650 6250
Wire Wire Line
	5750 5550 3100 5550
Wire Wire Line
	3100 5550 3100 6350
Wire Wire Line
	3100 6350 2650 6350
Wire Wire Line
	5350 3800 7650 3800
Wire Wire Line
	1600 4350 7650 4350
Wire Wire Line
	3650 2250 3800 2250
Wire Wire Line
	2900 2850 5350 2850
Wire Wire Line
	4900 3350 4700 3350
Wire Wire Line
	2650 2250 2900 2250
Wire Wire Line
	1750 3350 1600 3350
Wire Wire Line
	5350 2850 5350 3800
Connection ~ 3650 2850
Wire Wire Line
	1600 4350 1600 3950
Wire Wire Line
	4900 3950 4900 4350
Connection ~ 4900 4350
Wire Wire Line
	10500 4900 10500 5650
Wire Wire Line
	10250 4900 10250 5650
Connection ~ 10250 5600
Wire Wire Line
	9700 5650 9700 4900
Wire Wire Line
	9450 4900 9450 5650
Connection ~ 10500 5600
Connection ~ 9700 5600
Connection ~ 9450 5600
$Comp
L Molex_SL_3 U5
U 1 1 5AD4E4E1
P 7850 4050
F 0 "U5" H 7900 4000 60  0001 C CNN
F 1 "PWM_J1" H 8150 4200 60  0000 C CNN
F 2 "MRDT_Connectors:MOLEX_SL_3_Horizontal" H 7850 4050 60  0001 C CNN
F 3 "" H 7850 4050 60  0001 C CNN
	1    7850 4050
	1    0    0    -1  
$EndComp
$Comp
L Molex_SL_3 U6
U 1 1 5AD4E549
P 7850 4600
F 0 "U6" H 7900 4550 60  0001 C CNN
F 1 "PWM_J5" H 8150 4750 60  0000 C CNN
F 2 "MRDT_Connectors:MOLEX_SL_3_Horizontal" H 7850 4600 60  0001 C CNN
F 3 "" H 7850 4600 60  0001 C CNN
	1    7850 4600
	1    0    0    -1  
$EndComp
Connection ~ 6850 3800
Wire Wire Line
	6800 3900 7650 3900
Wire Wire Line
	7650 4450 6800 4450
Connection ~ 6850 4350
Wire Wire Line
	6800 4550 7650 4550
Wire Wire Line
	7650 4000 6800 4000
Connection ~ 6850 3900
Connection ~ 6850 4000
Connection ~ 6850 4450
Connection ~ 6850 4550
$Comp
L Anderson_3 C21
U 1 1 5AD3F677
P 7550 1500
F 0 "C21" H 7600 1450 60  0000 C CNN
F 1 "Anderson_3" H 7700 2250 60  0000 C CNN
F 2 "MRDT_Connectors:Anderson_3_Horisontal_Side_by_Side" H 7600 950 60  0001 C CNN
F 3 "" H 7600 950 60  0001 C CNN
	1    7550 1500
	-1   0    0    -1  
$EndComp
Connection ~ 8500 900 
Wire Wire Line
	8550 1150 7650 1150
Connection ~ 8500 1400
Connection ~ 8500 1150
Text GLabel 8800 900  1    60   UnSpc ~ 0
GND
$EndSCHEMATC
