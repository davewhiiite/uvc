EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title ""
Date ""
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L Device:Fuse F?
U 1 1 5F29AE34
P 1150 900
F 0 "F?" H 1210 946 50  0000 L CNN
F 1 "Fuse" H 1210 855 50  0000 L CNN
F 2 "" V 1080 900 50  0001 C CNN
F 3 "~" H 1150 900 50  0001 C CNN
	1    1150 900 
	0    -1   -1   0   
$EndComp
$Comp
L power:+3.3V #PWR?
U 1 1 5F2A5172
P 4100 850
F 0 "#PWR?" H 4100 700 50  0001 C CNN
F 1 "+3.3V" H 4115 1023 50  0000 C CNN
F 2 "" H 4100 850 50  0001 C CNN
F 3 "" H 4100 850 50  0001 C CNN
	1    4100 850 
	1    0    0    -1  
$EndComp
$Comp
L Regulator_Linear:L7812 U?
U 1 1 5F2A7324
P 2200 900
F 0 "U?" H 2200 1142 50  0000 C CNN
F 1 "L7812" H 2200 1051 50  0000 C CNN
F 2 "" H 2225 750 50  0001 L CIN
F 3 "http://www.st.com/content/ccc/resource/technical/document/datasheet/41/4f/b3/b0/12/d4/47/88/CD00000444.pdf/files/CD00000444.pdf/jcr:content/translations/en.CD00000444.pdf" H 2200 850 50  0001 C CNN
	1    2200 900 
	1    0    0    -1  
$EndComp
$Comp
L Switch:SW_DIP_x08 SW?
U 1 1 5F2AA059
P 9700 2500
F 0 "SW?" V 9746 2070 50  0000 R CNN
F 1 "SW_DIP_x08" V 9655 2070 50  0000 R CNN
F 2 "" H 9700 2500 50  0001 C CNN
F 3 "~" H 9700 2500 50  0001 C CNN
	1    9700 2500
	0    -1   -1   0   
$EndComp
$Comp
L Regulator_Linear:AP1117-33 U?
U 1 1 5F2B408A
P 3450 900
F 0 "U?" H 3450 1142 50  0000 C CNN
F 1 "AP1117-33" H 3450 1051 50  0000 C CNN
F 2 "Package_TO_SOT_SMD:SOT-223-3_TabPin2" H 3450 1100 50  0001 C CNN
F 3 "http://www.diodes.com/datasheets/AP1117.pdf" H 3550 650 50  0001 C CNN
	1    3450 900 
	1    0    0    -1  
$EndComp
Wire Wire Line
	2200 1400 2200 1200
Wire Wire Line
	2200 1400 1750 1400
Connection ~ 2200 1400
Wire Wire Line
	1900 900  1750 900 
Wire Wire Line
	2500 900  2600 900 
Wire Wire Line
	3750 900  4100 900 
Wire Wire Line
	4100 900  4100 850 
$Comp
L power:+12V #PWR?
U 1 1 5F2BBA38
P 2800 800
F 0 "#PWR?" H 2800 650 50  0001 C CNN
F 1 "+12V" H 2815 973 50  0000 C CNN
F 2 "" H 2800 800 50  0001 C CNN
F 3 "" H 2800 800 50  0001 C CNN
	1    2800 800 
	1    0    0    -1  
$EndComp
Wire Wire Line
	2800 800  2800 900 
Connection ~ 2800 900 
Wire Wire Line
	2800 900  3050 900 
$Comp
L Device:C C?
U 1 1 5F2BCA0E
P 1750 1150
F 0 "C?" H 1865 1196 50  0000 L CNN
F 1 "C" H 1865 1105 50  0000 L CNN
F 2 "" H 1788 1000 50  0001 C CNN
F 3 "~" H 1750 1150 50  0001 C CNN
	1    1750 1150
	1    0    0    -1  
$EndComp
$Comp
L Device:C C?
U 1 1 5F2BDA91
P 2600 1150
F 0 "C?" H 2715 1196 50  0000 L CNN
F 1 "C" H 2715 1105 50  0000 L CNN
F 2 "" H 2638 1000 50  0001 C CNN
F 3 "~" H 2600 1150 50  0001 C CNN
	1    2600 1150
	1    0    0    -1  
$EndComp
$Comp
L Device:C C?
U 1 1 5F2C0478
P 3050 1150
F 0 "C?" H 3165 1196 50  0000 L CNN
F 1 "C" H 3165 1105 50  0000 L CNN
F 2 "" H 3088 1000 50  0001 C CNN
F 3 "~" H 3050 1150 50  0001 C CNN
	1    3050 1150
	1    0    0    -1  
$EndComp
Wire Wire Line
	3050 1000 3050 900 
Connection ~ 3050 900 
Wire Wire Line
	3050 900  3150 900 
Wire Wire Line
	2600 1000 2600 900 
Connection ~ 2600 900 
Wire Wire Line
	2600 900  2800 900 
Wire Wire Line
	2600 1300 2600 1400
Connection ~ 2600 1400
Wire Wire Line
	2600 1400 2200 1400
Wire Wire Line
	3050 1300 3050 1400
Wire Wire Line
	3050 1400 2600 1400
Wire Wire Line
	1750 1000 1750 900 
Connection ~ 1750 900 
Wire Wire Line
	1750 900  1300 900 
Wire Wire Line
	1750 1300 1750 1400
Connection ~ 1750 1400
Wire Wire Line
	1750 1400 1000 1400
$Comp
L Device:R_Network04 RN?
U 1 1 5F2C1A70
P 9500 1450
F 0 "RN?" H 9688 1496 50  0000 L CNN
F 1 "R_Network04" H 9688 1405 50  0000 L CNN
F 2 "Resistor_THT:R_Array_SIP5" V 9775 1450 50  0001 C CNN
F 3 "http://www.vishay.com/docs/31509/csc.pdf" H 9500 1450 50  0001 C CNN
	1    9500 1450
	1    0    0    -1  
$EndComp
$Comp
L Device:R_Network04 RN?
U 1 1 5F2C46D5
P 9900 1450
F 0 "RN?" H 10088 1496 50  0000 L CNN
F 1 "R_Network04" H 10088 1405 50  0000 L CNN
F 2 "Resistor_THT:R_Array_SIP5" V 10175 1450 50  0001 C CNN
F 3 "http://www.vishay.com/docs/31509/csc.pdf" H 9900 1450 50  0001 C CNN
	1    9900 1450
	1    0    0    -1  
$EndComp
Wire Wire Line
	9300 2200 9300 1800
Wire Wire Line
	9400 1650 9400 1900
Wire Wire Line
	9500 1650 9500 2000
Wire Wire Line
	9600 2200 9600 2100
Wire Wire Line
	9800 2200 9800 1900
Wire Wire Line
	9900 1650 9900 2000
Wire Wire Line
	10000 1650 10000 2100
Text GLabel 8900 1800 0    50   Output ~ 0
D0
Text GLabel 9000 1900 0    50   Output ~ 0
D1
Text GLabel 9100 2000 0    50   Output ~ 0
D3
Text GLabel 9200 2100 0    50   Output ~ 0
D3
Wire Wire Line
	8900 1800 9300 1800
Connection ~ 9300 1800
Wire Wire Line
	9300 1800 9300 1650
Wire Wire Line
	9000 1900 9400 1900
Connection ~ 9400 1900
Wire Wire Line
	9400 1900 9400 2200
Wire Wire Line
	9100 2000 9500 2000
Connection ~ 9500 2000
Wire Wire Line
	9500 2000 9500 2200
Wire Wire Line
	9700 1650 9700 1800
Wire Wire Line
	9200 2100 9600 2100
Connection ~ 9600 2100
Wire Wire Line
	9600 2100 9600 1650
Text GLabel 10300 1800 2    50   Output ~ 0
D4
Text GLabel 10400 1900 2    50   Output ~ 0
D5
Text GLabel 10500 2000 2    50   Output ~ 0
D6
Text GLabel 10600 2100 2    50   Output ~ 0
D7
Wire Wire Line
	10300 1800 9700 1800
Connection ~ 9700 1800
Wire Wire Line
	9700 1800 9700 2200
Wire Wire Line
	10400 1900 9800 1900
Connection ~ 9800 1900
Wire Wire Line
	9800 1900 9800 1650
Wire Wire Line
	10500 2000 9900 2000
Connection ~ 9900 2000
Wire Wire Line
	9900 2000 9900 2200
Wire Wire Line
	10600 2100 10000 2100
Connection ~ 10000 2100
Wire Wire Line
	10000 2100 10000 2200
$Comp
L power:GND #PWR?
U 1 1 5F2D7E36
P 2200 1600
F 0 "#PWR?" H 2200 1350 50  0001 C CNN
F 1 "GND" H 2205 1427 50  0000 C CNN
F 2 "" H 2200 1600 50  0001 C CNN
F 3 "" H 2200 1600 50  0001 C CNN
	1    2200 1600
	1    0    0    -1  
$EndComp
Wire Wire Line
	2200 1400 2200 1600
Wire Wire Line
	9300 2800 9400 2800
Connection ~ 9400 2800
Wire Wire Line
	9400 2800 9500 2800
Wire Wire Line
	10000 2800 9900 2800
Connection ~ 9900 2800
Wire Wire Line
	9700 2800 9600 2800
Wire Wire Line
	9500 2800 9600 2800
Connection ~ 9700 2800
Wire Wire Line
	9700 2800 9800 2800
Connection ~ 9500 2800
Connection ~ 9600 2800
Connection ~ 9800 2800
Wire Wire Line
	9800 2800 9900 2800
$Comp
L power:GND #PWR?
U 1 1 5F2DED72
P 9400 2950
F 0 "#PWR?" H 9400 2700 50  0001 C CNN
F 1 "GND" H 9405 2777 50  0000 C CNN
F 2 "" H 9400 2950 50  0001 C CNN
F 3 "" H 9400 2950 50  0001 C CNN
	1    9400 2950
	1    0    0    -1  
$EndComp
Wire Wire Line
	9400 2950 9400 2800
Wire Wire Line
	3450 1400 3050 1400
Wire Wire Line
	3450 1200 3450 1400
Connection ~ 3050 1400
$Comp
L power:+3.3V #PWR?
U 1 1 5F2ECDD6
P 9300 1000
F 0 "#PWR?" H 9300 850 50  0001 C CNN
F 1 "+3.3V" H 9315 1173 50  0000 C CNN
F 2 "" H 9300 1000 50  0001 C CNN
F 3 "" H 9300 1000 50  0001 C CNN
	1    9300 1000
	1    0    0    -1  
$EndComp
Wire Wire Line
	9300 1000 9300 1100
Wire Wire Line
	9300 1100 9700 1100
Wire Wire Line
	9700 1100 9700 1250
Connection ~ 9300 1100
Wire Wire Line
	9300 1100 9300 1250
$Comp
L Reference_Voltage:CJ432 U?
U 1 1 5F2F25D0
P 5150 1250
F 0 "U?" V 5196 1180 50  0000 R CNN
F 1 "NCP321AVSNT1GOSCT" V 5105 1180 50  0000 R CNN
F 2 "Package_TO_SOT_SMD:SOT-23" H 5150 1100 50  0001 C CIN
F 3 "http://www.cj-elec.com/txUpfile/20134181474991806.pdf" H 5150 1250 50  0001 C CIN
	1    5150 1250
	0    1    -1   0   
$EndComp
$Comp
L Device:R_Small 10k
U 1 1 5F2F59E9
P 5400 1100
F 0 "10k" H 5459 1146 50  0000 L CNN
F 1 "R_Small" H 5459 1055 50  0000 L CNN
F 2 "" H 5400 1100 50  0001 C CNN
F 3 "~" H 5400 1100 50  0001 C CNN
	1    5400 1100
	1    0    0    -1  
$EndComp
$Comp
L Device:R_Small 10k
U 1 1 5F2F8521
P 5400 1400
F 0 "10k" H 5459 1446 50  0000 L CNN
F 1 "R_Small" H 5459 1355 50  0000 L CNN
F 2 "" H 5400 1400 50  0001 C CNN
F 3 "~" H 5400 1400 50  0001 C CNN
	1    5400 1400
	1    0    0    -1  
$EndComp
Wire Wire Line
	5150 1150 5150 950 
Wire Wire Line
	5150 950  4900 950 
Wire Wire Line
	5150 950  5400 950 
Wire Wire Line
	5400 950  5400 1000
Connection ~ 5150 950 
Wire Wire Line
	5400 1200 5400 1250
Wire Wire Line
	5250 1250 5400 1250
Connection ~ 5400 1250
Wire Wire Line
	5400 1250 5400 1300
Wire Wire Line
	5400 1500 5400 1550
Wire Wire Line
	5400 1550 5150 1550
Wire Wire Line
	5150 1550 5150 1350
$Comp
L power:GND #PWR?
U 1 1 5F3007B5
P 5150 1600
F 0 "#PWR?" H 5150 1350 50  0001 C CNN
F 1 "GND" H 5155 1427 50  0000 C CNN
F 2 "" H 5150 1600 50  0001 C CNN
F 3 "" H 5150 1600 50  0001 C CNN
	1    5150 1600
	1    0    0    -1  
$EndComp
Wire Wire Line
	5150 1550 5150 1600
Connection ~ 5150 1550
$Comp
L power:+5V #PWR?
U 1 1 5F302E35
P 5700 850
F 0 "#PWR?" H 5700 700 50  0001 C CNN
F 1 "+5V" H 5715 1023 50  0000 C CNN
F 2 "" H 5700 850 50  0001 C CNN
F 3 "" H 5700 850 50  0001 C CNN
	1    5700 850 
	1    0    0    -1  
$EndComp
Wire Wire Line
	5400 950  5700 950 
Wire Wire Line
	5700 950  5700 850 
Connection ~ 5400 950 
$Comp
L power:+12V #PWR?
U 1 1 5F307271
P 4450 850
F 0 "#PWR?" H 4450 700 50  0001 C CNN
F 1 "+12V" H 4465 1023 50  0000 C CNN
F 2 "" H 4450 850 50  0001 C CNN
F 3 "" H 4450 850 50  0001 C CNN
	1    4450 850 
	1    0    0    -1  
$EndComp
Wire Wire Line
	4450 850  4450 950 
Wire Wire Line
	4450 950  4600 950 
$Comp
L Device:R R220
U 1 1 5F2F97E2
P 4750 950
F 0 "R220" V 4543 950 50  0000 C CNN
F 1 "R" V 4634 950 50  0000 C CNN
F 2 "" V 4680 950 50  0001 C CNN
F 3 "~" H 4750 950 50  0001 C CNN
	1    4750 950 
	0    1    1    0   
$EndComp
Text Notes 9250 4550 0    50   ~ 0
12-BIT ADC\nNEED TO MAKE MCP3221 MODEL\n
Wire Notes Line
	10700 4200 10700 4950
Wire Notes Line
	10700 4950 9050 4950
Wire Notes Line
	9050 4950 9050 4200
Wire Notes Line
	9050 4200 10700 4200
$Comp
L Transistor_FET:BSS138 Q?
U 1 1 5F32A009
P 7250 4050
F 0 "Q?" H 7454 4096 50  0000 L CNN
F 1 "BSS138" H 7454 4005 50  0000 L CNN
F 2 "Package_TO_SOT_SMD:SOT-23" H 7450 3975 50  0001 L CIN
F 3 "https://www.fairchildsemi.com/datasheets/BS/BSS138.pdf" H 7250 4050 50  0001 L CNN
	1    7250 4050
	0    1    1    0   
$EndComp
$Comp
L Device:R_Small R?
U 1 1 5F32C0DC
P 6900 3950
F 0 "R?" V 6704 3950 50  0000 C CNN
F 1 "R_Small" V 6795 3950 50  0000 C CNN
F 2 "" H 6900 3950 50  0001 C CNN
F 3 "~" H 6900 3950 50  0001 C CNN
	1    6900 3950
	1    0    0    -1  
$EndComp
$Comp
L Device:R_Small R?
U 1 1 5F33E538
P 7700 3950
F 0 "R?" V 7504 3950 50  0000 C CNN
F 1 "R_Small" V 7595 3950 50  0000 C CNN
F 2 "" H 7700 3950 50  0001 C CNN
F 3 "~" H 7700 3950 50  0001 C CNN
	1    7700 3950
	1    0    0    -1  
$EndComp
Wire Wire Line
	7250 3850 7250 3700
Wire Wire Line
	7250 3700 6900 3700
Wire Wire Line
	6900 3700 6900 3850
$Comp
L power:+3.3V #PWR?
U 1 1 5F34263C
P 6900 3600
F 0 "#PWR?" H 6900 3450 50  0001 C CNN
F 1 "+3.3V" H 6915 3773 50  0000 C CNN
F 2 "" H 6900 3600 50  0001 C CNN
F 3 "" H 6900 3600 50  0001 C CNN
	1    6900 3600
	1    0    0    -1  
$EndComp
Wire Wire Line
	6900 3600 6900 3700
Connection ~ 6900 3700
Wire Wire Line
	6900 4050 6900 4150
Wire Wire Line
	6900 4150 7050 4150
$Comp
L power:+5V #PWR?
U 1 1 5F3493D1
P 7700 3600
F 0 "#PWR?" H 7700 3450 50  0001 C CNN
F 1 "+5V" H 7715 3773 50  0000 C CNN
F 2 "" H 7700 3600 50  0001 C CNN
F 3 "" H 7700 3600 50  0001 C CNN
	1    7700 3600
	1    0    0    -1  
$EndComp
Wire Wire Line
	7700 3600 7700 3850
Wire Wire Line
	7450 4150 7700 4150
Wire Wire Line
	7700 4150 7700 4050
Text Notes 4650 1950 0    50   ~ 0
5V ADC REFERENCE\n
Text Notes 1500 1950 0    50   ~ 0
24V SUPPLY CIRCUIT / 12V, 3.3V REGULATORS
$Comp
L Transistor_FET:BSS138 Q?
U 1 1 5F35FF51
P 7250 4950
F 0 "Q?" H 7454 4996 50  0000 L CNN
F 1 "BSS138" H 7454 4905 50  0000 L CNN
F 2 "Package_TO_SOT_SMD:SOT-23" H 7450 4875 50  0001 L CIN
F 3 "https://www.fairchildsemi.com/datasheets/BS/BSS138.pdf" H 7250 4950 50  0001 L CNN
	1    7250 4950
	0    1    1    0   
$EndComp
$Comp
L Device:R_Small R?
U 1 1 5F35FF57
P 6900 4850
F 0 "R?" V 6704 4850 50  0000 C CNN
F 1 "R_Small" V 6795 4850 50  0000 C CNN
F 2 "" H 6900 4850 50  0001 C CNN
F 3 "~" H 6900 4850 50  0001 C CNN
	1    6900 4850
	1    0    0    -1  
$EndComp
$Comp
L Device:R_Small R?
U 1 1 5F35FF5D
P 7700 4850
F 0 "R?" V 7504 4850 50  0000 C CNN
F 1 "R_Small" V 7595 4850 50  0000 C CNN
F 2 "" H 7700 4850 50  0001 C CNN
F 3 "~" H 7700 4850 50  0001 C CNN
	1    7700 4850
	1    0    0    -1  
$EndComp
Wire Wire Line
	7250 4750 7250 4600
Wire Wire Line
	7250 4600 6900 4600
Wire Wire Line
	6900 4600 6900 4750
$Comp
L power:+3.3V #PWR?
U 1 1 5F35FF66
P 6900 4500
F 0 "#PWR?" H 6900 4350 50  0001 C CNN
F 1 "+3.3V" H 6915 4673 50  0000 C CNN
F 2 "" H 6900 4500 50  0001 C CNN
F 3 "" H 6900 4500 50  0001 C CNN
	1    6900 4500
	1    0    0    -1  
$EndComp
Wire Wire Line
	6900 4500 6900 4600
Connection ~ 6900 4600
Wire Wire Line
	6900 4950 6900 5050
Wire Wire Line
	6900 5050 7050 5050
$Comp
L power:+5V #PWR?
U 1 1 5F35FF70
P 7700 4500
F 0 "#PWR?" H 7700 4350 50  0001 C CNN
F 1 "+5V" H 7715 4673 50  0000 C CNN
F 2 "" H 7700 4500 50  0001 C CNN
F 3 "" H 7700 4500 50  0001 C CNN
	1    7700 4500
	1    0    0    -1  
$EndComp
Wire Wire Line
	7700 4500 7700 4750
Wire Wire Line
	7450 5050 7700 5050
Wire Wire Line
	7700 5050 7700 4950
Text GLabel 8350 4150 2    50   BiDi ~ 0
ADC_SDA
Wire Wire Line
	8350 4150 7700 4150
Connection ~ 7700 4150
Text GLabel 8350 5050 2    50   BiDi ~ 0
ADC_SCL
Wire Wire Line
	8350 5050 7700 5050
Connection ~ 7700 5050
Text GLabel 6500 4150 0    50   BiDi ~ 0
MCU_SDA
Wire Wire Line
	6500 4150 6900 4150
Connection ~ 6900 4150
Text GLabel 6500 5050 0    50   BiDi ~ 0
MCU_SCL
Wire Wire Line
	6500 5050 6900 5050
Text Notes 6800 5550 0    50   ~ 0
ADC I2C LEVEL-SHIFTER
$Comp
L Device:R_Small R10K
U 1 1 5F396267
P 2000 3050
F 0 "R10K" V 1804 3050 50  0000 C CNN
F 1 "R_Small" V 1895 3050 50  0000 C CNN
F 2 "" H 2000 3050 50  0001 C CNN
F 3 "~" H 2000 3050 50  0001 C CNN
	1    2000 3050
	0    1    1    0   
$EndComp
$Comp
L Device:CP1 C?
U 1 1 5F39C758
P 2250 3200
F 0 "C?" H 2365 3246 50  0000 L CNN
F 1 "CP1" H 2365 3155 50  0000 L CNN
F 2 "" H 2250 3200 50  0001 C CNN
F 3 "~" H 2250 3200 50  0001 C CNN
	1    2250 3200
	1    0    0    -1  
$EndComp
$Comp
L Device:D D?
U 1 1 5F39D991
P 2900 3200
F 0 "D?" V 2854 3280 50  0000 L CNN
F 1 "D" V 2945 3280 50  0000 L CNN
F 2 "" H 2900 3200 50  0001 C CNN
F 3 "~" H 2900 3200 50  0001 C CNN
	1    2900 3200
	0    1    1    0   
$EndComp
$Comp
L Device:D D?
U 1 1 5F39F00E
P 2900 2800
F 0 "D?" V 2854 2880 50  0000 L CNN
F 1 "D" V 2945 2880 50  0000 L CNN
F 2 "" H 2900 2800 50  0001 C CNN
F 3 "~" H 2900 2800 50  0001 C CNN
	1    2900 2800
	0    1    1    0   
$EndComp
Wire Wire Line
	2900 2950 2900 3050
Text GLabel 1250 3050 0    50   Input ~ 0
PB1_DIO-
Wire Wire Line
	2100 3050 2250 3050
Connection ~ 2250 3050
Connection ~ 2900 3050
Text GLabel 3300 3050 2    50   Output ~ 0
D8
Wire Wire Line
	3300 3050 2900 3050
$Comp
L power:+3.3V #PWR?
U 1 1 5F3CA6D5
P 2900 2550
F 0 "#PWR?" H 2900 2400 50  0001 C CNN
F 1 "+3.3V" H 2915 2723 50  0000 C CNN
F 2 "" H 2900 2550 50  0001 C CNN
F 3 "" H 2900 2550 50  0001 C CNN
	1    2900 2550
	1    0    0    -1  
$EndComp
Wire Wire Line
	2900 3350 2900 3450
Wire Wire Line
	2900 3450 2250 3450
Wire Wire Line
	2250 3450 2250 3350
$Comp
L power:GND #PWR?
U 1 1 5F3D230D
P 2250 3550
F 0 "#PWR?" H 2250 3300 50  0001 C CNN
F 1 "GND" H 2255 3377 50  0000 C CNN
F 2 "" H 2250 3550 50  0001 C CNN
F 3 "" H 2250 3550 50  0001 C CNN
	1    2250 3550
	1    0    0    -1  
$EndComp
Wire Wire Line
	2250 3550 2250 3450
Connection ~ 2250 3450
$Comp
L Device:LED D?
U 1 1 5F3E27DF
P 7500 1000
F 0 "D?" H 7493 745 50  0000 C CNN
F 1 "LED" H 7493 836 50  0000 C CNN
F 2 "" H 7500 1000 50  0001 C CNN
F 3 "~" H 7500 1000 50  0001 C CNN
	1    7500 1000
	-1   0    0    1   
$EndComp
$Comp
L Device:LED D?
U 1 1 5F3E3FB8
P 7500 1400
F 0 "D?" H 7493 1145 50  0000 C CNN
F 1 "LED" H 7493 1236 50  0000 C CNN
F 2 "" H 7500 1400 50  0001 C CNN
F 3 "~" H 7500 1400 50  0001 C CNN
	1    7500 1400
	-1   0    0    1   
$EndComp
$Comp
L Device:LED D?
U 1 1 5F3E7A06
P 7500 1750
F 0 "D?" H 7493 1495 50  0000 C CNN
F 1 "LED" H 7493 1586 50  0000 C CNN
F 2 "" H 7500 1750 50  0001 C CNN
F 3 "~" H 7500 1750 50  0001 C CNN
	1    7500 1750
	-1   0    0    1   
$EndComp
$Comp
L Device:LED D?
U 1 1 5F3EBCA3
P 7500 2050
F 0 "D?" H 7493 1795 50  0000 C CNN
F 1 "LED" H 7493 1886 50  0000 C CNN
F 2 "" H 7500 2050 50  0001 C CNN
F 3 "~" H 7500 2050 50  0001 C CNN
	1    7500 2050
	-1   0    0    1   
$EndComp
$Comp
L Device:R R470
U 1 1 5F3EF3DD
P 6950 1000
F 0 "R470" V 6743 1000 50  0000 C CNN
F 1 "R" V 6834 1000 50  0000 C CNN
F 2 "" V 6880 1000 50  0001 C CNN
F 3 "~" H 6950 1000 50  0001 C CNN
	1    6950 1000
	0    1    1    0   
$EndComp
$Comp
L Device:R R110
U 1 1 5F3F08E7
P 6950 1400
F 0 "R110" V 6743 1400 50  0000 C CNN
F 1 "R" V 6834 1400 50  0000 C CNN
F 2 "" V 6880 1400 50  0001 C CNN
F 3 "~" H 6950 1400 50  0001 C CNN
	1    6950 1400
	0    1    1    0   
$EndComp
$Comp
L Device:R R16
U 1 1 5F3F3FEC
P 6950 1750
F 0 "R16" V 6743 1750 50  0000 C CNN
F 1 "R" V 6834 1750 50  0000 C CNN
F 2 "" V 6880 1750 50  0001 C CNN
F 3 "~" H 6950 1750 50  0001 C CNN
	1    6950 1750
	0    1    1    0   
$EndComp
$Comp
L Device:R R24
U 1 1 5F3F7A23
P 6950 2050
F 0 "R24" V 6743 2050 50  0000 C CNN
F 1 "R" V 6834 2050 50  0000 C CNN
F 2 "" V 6880 2050 50  0001 C CNN
F 3 "~" H 6950 2050 50  0001 C CNN
	1    6950 2050
	0    1    1    0   
$EndComp
$Comp
L power:GND #PWR?
U 1 1 5F3FE6C8
P 8150 2650
F 0 "#PWR?" H 8150 2400 50  0001 C CNN
F 1 "GND" H 8155 2477 50  0000 C CNN
F 2 "" H 8150 2650 50  0001 C CNN
F 3 "" H 8150 2650 50  0001 C CNN
	1    8150 2650
	1    0    0    -1  
$EndComp
Wire Wire Line
	7650 2050 8150 2050
Connection ~ 8150 2050
Wire Wire Line
	7650 1750 8150 1750
Wire Wire Line
	8150 1000 8150 1400
Connection ~ 8150 1750
Wire Wire Line
	8150 1750 8150 2050
Wire Wire Line
	7650 1400 8150 1400
Connection ~ 8150 1400
Wire Wire Line
	8150 1400 8150 1750
Wire Wire Line
	7650 1000 8150 1000
Wire Wire Line
	7100 1000 7350 1000
Wire Wire Line
	7350 1400 7100 1400
Wire Wire Line
	7350 1750 7100 1750
Wire Wire Line
	7350 2050 7100 2050
$Comp
L Transistor_FET:BSS138 Q?
U 1 1 5F43C3B7
P 3150 5900
F 0 "Q?" H 3354 5946 50  0000 L CNN
F 1 "BSS138" H 3354 5855 50  0000 L CNN
F 2 "Package_TO_SOT_SMD:SOT-23" H 3350 5825 50  0001 L CIN
F 3 "https://www.fairchildsemi.com/datasheets/BS/BSS138.pdf" H 3150 5900 50  0001 L CNN
	1    3150 5900
	1    0    0    -1  
$EndComp
Wire Wire Line
	3250 5700 3250 5450
$Comp
L Device:R_Small R2.2K
U 1 1 5F440E52
P 3000 6150
F 0 "R2.2K" V 2804 6150 50  0000 C CNN
F 1 "R_Small" V 2895 6150 50  0000 C CNN
F 2 "" H 3000 6150 50  0001 C CNN
F 3 "~" H 3000 6150 50  0001 C CNN
	1    3000 6150
	0    1    1    0   
$EndComp
$Comp
L Device:R_Small R100
U 1 1 5F4427B6
P 2650 5900
F 0 "R100" V 2454 5900 50  0000 C CNN
F 1 "R_Small" V 2545 5900 50  0000 C CNN
F 2 "" H 2650 5900 50  0001 C CNN
F 3 "~" H 2650 5900 50  0001 C CNN
	1    2650 5900
	0    1    1    0   
$EndComp
Wire Wire Line
	2750 5900 2850 5900
Wire Wire Line
	2850 5900 2850 6150
Wire Wire Line
	2850 6150 2900 6150
Connection ~ 2850 5900
Wire Wire Line
	2850 5900 2950 5900
Wire Wire Line
	3100 6150 3250 6150
Connection ~ 3250 6150
Wire Wire Line
	3250 6150 3250 6100
$Comp
L power:GND #PWR?
U 1 1 5F457846
P 3250 6300
F 0 "#PWR?" H 3250 6050 50  0001 C CNN
F 1 "GND" H 3255 6127 50  0000 C CNN
F 2 "" H 3250 6300 50  0001 C CNN
F 3 "" H 3250 6300 50  0001 C CNN
	1    3250 6300
	1    0    0    -1  
$EndComp
Wire Wire Line
	3250 6150 3250 6300
Text GLabel 6300 1000 0    50   Input ~ 0
DX
Wire Wire Line
	6300 1000 6800 1000
Text GLabel 6300 1400 0    50   Input ~ 0
DX
Wire Wire Line
	6300 1400 6800 1400
Text GLabel 6300 1750 0    50   Input ~ 0
DX
Wire Wire Line
	6300 1750 6800 1750
Text GLabel 6300 2050 0    50   Input ~ 0
DX
Wire Wire Line
	6300 2050 6800 2050
Text Notes 6650 850  2    50   ~ 0
PWR_LED (RED)
Text Notes 6650 1300 2    50   ~ 0
LED2_RGB_RED
Text Notes 6650 1650 2    50   ~ 0
LED2_RBG_GREEN
Text Notes 6650 1950 2    50   ~ 0
LED2_RGB_BLUE
Wire Wire Line
	8150 2050 8150 2650
Wire Notes Line
	7300 1250 7800 1250
Wire Notes Line
	7800 1250 7800 2250
Wire Notes Line
	7800 2250 7300 2250
Wire Notes Line
	7300 2250 7300 1250
Text Notes 7850 2400 2    50   ~ 0
EVERLIGHT_19-337
Text GLabel 2350 5900 0    50   Input ~ 0
DX
Text Notes 2700 6150 2    50   ~ 0
24V_IO_DRIVER1
$Comp
L Transistor_FET:BSS138 Q?
U 1 1 5F4B8296
P 3700 7000
F 0 "Q?" H 3904 7046 50  0000 L CNN
F 1 "BSS138" H 3904 6955 50  0000 L CNN
F 2 "Package_TO_SOT_SMD:SOT-23" H 3900 6925 50  0001 L CIN
F 3 "https://www.fairchildsemi.com/datasheets/BS/BSS138.pdf" H 3700 7000 50  0001 L CNN
	1    3700 7000
	1    0    0    -1  
$EndComp
Wire Wire Line
	3800 6800 3800 6550
$Comp
L Device:R_Small R2.2K?
U 1 1 5F4B829D
P 3550 7250
F 0 "R2.2K?" V 3354 7250 50  0000 C CNN
F 1 "R_Small" V 3445 7250 50  0000 C CNN
F 2 "" H 3550 7250 50  0001 C CNN
F 3 "~" H 3550 7250 50  0001 C CNN
	1    3550 7250
	0    1    1    0   
$EndComp
$Comp
L Device:R_Small R?
U 1 1 5F4B82A3
P 3200 7000
F 0 "R?" V 3004 7000 50  0000 C CNN
F 1 "R_Small" V 3095 7000 50  0000 C CNN
F 2 "" H 3200 7000 50  0001 C CNN
F 3 "~" H 3200 7000 50  0001 C CNN
	1    3200 7000
	0    1    1    0   
$EndComp
Wire Wire Line
	3300 7000 3400 7000
Wire Wire Line
	3400 7000 3400 7250
Wire Wire Line
	3400 7250 3450 7250
Connection ~ 3400 7000
Wire Wire Line
	3400 7000 3500 7000
Wire Wire Line
	3650 7250 3800 7250
Connection ~ 3800 7250
Wire Wire Line
	3800 7250 3800 7200
$Comp
L power:GND #PWR?
U 1 1 5F4B82B1
P 3800 7400
F 0 "#PWR?" H 3800 7150 50  0001 C CNN
F 1 "GND" H 3805 7227 50  0000 C CNN
F 2 "" H 3800 7400 50  0001 C CNN
F 3 "" H 3800 7400 50  0001 C CNN
	1    3800 7400
	1    0    0    -1  
$EndComp
Wire Wire Line
	3800 7250 3800 7400
Text GLabel 2900 7000 0    50   Input ~ 0
DX
Text Notes 3300 7250 2    50   ~ 0
24V_IO_DRIVER2
Text GLabel 3250 5450 1    50   Output ~ 0
J2F-1
Text GLabel 3800 6550 1    50   Output ~ 0
J2F-2
Wire Wire Line
	2350 5900 2550 5900
Wire Wire Line
	2900 7000 3100 7000
$Comp
L Transistor_FET:BSS138 Q?
U 1 1 5F517BF0
P 5000 6000
F 0 "Q?" H 5204 6046 50  0000 L CNN
F 1 "BSS138" H 5204 5955 50  0000 L CNN
F 2 "Package_TO_SOT_SMD:SOT-23" H 5200 5925 50  0001 L CIN
F 3 "https://www.fairchildsemi.com/datasheets/BS/BSS138.pdf" H 5000 6000 50  0001 L CNN
	1    5000 6000
	1    0    0    -1  
$EndComp
Wire Wire Line
	5100 5800 5100 5550
$Comp
L Device:R_Small R2.2K?
U 1 1 5F517BF7
P 4850 6250
F 0 "R2.2K?" V 4654 6250 50  0000 C CNN
F 1 "R_Small" V 4745 6250 50  0000 C CNN
F 2 "" H 4850 6250 50  0001 C CNN
F 3 "~" H 4850 6250 50  0001 C CNN
	1    4850 6250
	0    1    1    0   
$EndComp
$Comp
L Device:R_Small R?
U 1 1 5F517BFD
P 4500 6000
F 0 "R?" V 4304 6000 50  0000 C CNN
F 1 "R_Small" V 4395 6000 50  0000 C CNN
F 2 "" H 4500 6000 50  0001 C CNN
F 3 "~" H 4500 6000 50  0001 C CNN
	1    4500 6000
	0    1    1    0   
$EndComp
Wire Wire Line
	4600 6000 4700 6000
Wire Wire Line
	4700 6000 4700 6250
Wire Wire Line
	4700 6250 4750 6250
Connection ~ 4700 6000
Wire Wire Line
	4700 6000 4800 6000
Wire Wire Line
	4950 6250 5100 6250
Connection ~ 5100 6250
Wire Wire Line
	5100 6250 5100 6200
$Comp
L power:GND #PWR?
U 1 1 5F517C0B
P 5100 6400
F 0 "#PWR?" H 5100 6150 50  0001 C CNN
F 1 "GND" H 5105 6227 50  0000 C CNN
F 2 "" H 5100 6400 50  0001 C CNN
F 3 "" H 5100 6400 50  0001 C CNN
	1    5100 6400
	1    0    0    -1  
$EndComp
Wire Wire Line
	5100 6250 5100 6400
Text GLabel 4200 6000 0    50   Input ~ 0
DX
Text Notes 4550 6250 2    50   ~ 0
24V_IO_DRIVER3
$Comp
L Transistor_FET:BSS138 Q?
U 1 1 5F517C14
P 5550 7100
F 0 "Q?" H 5754 7146 50  0000 L CNN
F 1 "BSS138" H 5754 7055 50  0000 L CNN
F 2 "Package_TO_SOT_SMD:SOT-23" H 5750 7025 50  0001 L CIN
F 3 "https://www.fairchildsemi.com/datasheets/BS/BSS138.pdf" H 5550 7100 50  0001 L CNN
	1    5550 7100
	1    0    0    -1  
$EndComp
Wire Wire Line
	5650 6900 5650 6650
$Comp
L Device:R_Small R2.2K?
U 1 1 5F517C1B
P 5400 7350
F 0 "R2.2K?" V 5204 7350 50  0000 C CNN
F 1 "R_Small" V 5295 7350 50  0000 C CNN
F 2 "" H 5400 7350 50  0001 C CNN
F 3 "~" H 5400 7350 50  0001 C CNN
	1    5400 7350
	0    1    1    0   
$EndComp
$Comp
L Device:R_Small R?
U 1 1 5F517C21
P 5050 7100
F 0 "R?" V 4854 7100 50  0000 C CNN
F 1 "R_Small" V 4945 7100 50  0000 C CNN
F 2 "" H 5050 7100 50  0001 C CNN
F 3 "~" H 5050 7100 50  0001 C CNN
	1    5050 7100
	0    1    1    0   
$EndComp
Wire Wire Line
	5150 7100 5250 7100
Wire Wire Line
	5250 7100 5250 7350
Wire Wire Line
	5250 7350 5300 7350
Connection ~ 5250 7100
Wire Wire Line
	5250 7100 5350 7100
Wire Wire Line
	5500 7350 5650 7350
Connection ~ 5650 7350
Wire Wire Line
	5650 7350 5650 7300
$Comp
L power:GND #PWR?
U 1 1 5F517C2F
P 5650 7500
F 0 "#PWR?" H 5650 7250 50  0001 C CNN
F 1 "GND" H 5655 7327 50  0000 C CNN
F 2 "" H 5650 7500 50  0001 C CNN
F 3 "" H 5650 7500 50  0001 C CNN
	1    5650 7500
	1    0    0    -1  
$EndComp
Wire Wire Line
	5650 7350 5650 7500
Text GLabel 4750 7100 0    50   Input ~ 0
DX
Text Notes 5150 7350 2    50   ~ 0
24V_IO_DRIVER4
Text GLabel 5100 5550 1    50   Output ~ 0
J2F-3
Text GLabel 5650 6650 1    50   Output ~ 0
J2F-4
Wire Wire Line
	4200 6000 4400 6000
Wire Wire Line
	4750 7100 4950 7100
Wire Wire Line
	2900 2550 2900 2650
Wire Wire Line
	2250 3050 2900 3050
Connection ~ 6900 5050
Text Notes 1150 3750 0    50   ~ 0
EXTERNAL \nPUSHBUTTON \nINPUTS
Text Notes 6750 2400 2    50   ~ 0
USER LED ARRAY
$Comp
L Device:R R4.7K
U 1 1 5F6665DB
P 2000 2650
F 0 "R4.7K" V 1793 2650 50  0000 C CNN
F 1 "R" V 1884 2650 50  0000 C CNN
F 2 "" V 1930 2650 50  0001 C CNN
F 3 "~" H 2000 2650 50  0001 C CNN
	1    2000 2650
	0    1    1    0   
$EndComp
Wire Wire Line
	2150 2650 2900 2650
Connection ~ 2900 2650
Text GLabel 1250 2650 0    50   Input ~ 0
PB1_DIO+
Wire Wire Line
	1700 2650 1700 3050
Connection ~ 1700 2650
Wire Wire Line
	1700 2650 1850 2650
Wire Wire Line
	1700 3050 1900 3050
Wire Wire Line
	1250 2650 1700 2650
$Comp
L power:GND #PWR?
U 1 1 5F6C7C11
P 1450 3250
F 0 "#PWR?" H 1450 3000 50  0001 C CNN
F 1 "GND" H 1455 3077 50  0000 C CNN
F 2 "" H 1450 3250 50  0001 C CNN
F 3 "" H 1450 3250 50  0001 C CNN
	1    1450 3250
	1    0    0    -1  
$EndComp
Wire Wire Line
	1250 3050 1450 3050
Wire Wire Line
	1450 3050 1450 3250
$Comp
L Device:R_Small R10K
U 1 1 5F6F6107
P 2150 4550
F 0 "R10K" V 1954 4550 50  0000 C CNN
F 1 "R_Small" V 2045 4550 50  0000 C CNN
F 2 "" H 2150 4550 50  0001 C CNN
F 3 "~" H 2150 4550 50  0001 C CNN
	1    2150 4550
	0    1    1    0   
$EndComp
$Comp
L Device:CP1 C?
U 1 1 5F6F610D
P 2400 4700
F 0 "C?" H 2515 4746 50  0000 L CNN
F 1 "CP1" H 2515 4655 50  0000 L CNN
F 2 "" H 2400 4700 50  0001 C CNN
F 3 "~" H 2400 4700 50  0001 C CNN
	1    2400 4700
	1    0    0    -1  
$EndComp
$Comp
L Device:D D?
U 1 1 5F6F6113
P 3050 4700
F 0 "D?" V 3004 4780 50  0000 L CNN
F 1 "D" V 3095 4780 50  0000 L CNN
F 2 "" H 3050 4700 50  0001 C CNN
F 3 "~" H 3050 4700 50  0001 C CNN
	1    3050 4700
	0    1    1    0   
$EndComp
$Comp
L Device:D D?
U 1 1 5F6F6119
P 3050 4300
F 0 "D?" V 3004 4380 50  0000 L CNN
F 1 "D" V 3095 4380 50  0000 L CNN
F 2 "" H 3050 4300 50  0001 C CNN
F 3 "~" H 3050 4300 50  0001 C CNN
	1    3050 4300
	0    1    1    0   
$EndComp
Wire Wire Line
	3050 4450 3050 4550
Text GLabel 1400 4550 0    50   Input ~ 0
PB2_DIO-
Wire Wire Line
	2250 4550 2400 4550
Connection ~ 2400 4550
Connection ~ 3050 4550
Text GLabel 3450 4550 2    50   Output ~ 0
D8
Wire Wire Line
	3450 4550 3050 4550
$Comp
L power:+3.3V #PWR?
U 1 1 5F6F6126
P 3050 4050
F 0 "#PWR?" H 3050 3900 50  0001 C CNN
F 1 "+3.3V" H 3065 4223 50  0000 C CNN
F 2 "" H 3050 4050 50  0001 C CNN
F 3 "" H 3050 4050 50  0001 C CNN
	1    3050 4050
	1    0    0    -1  
$EndComp
Wire Wire Line
	3050 4850 3050 4950
Wire Wire Line
	3050 4950 2400 4950
Wire Wire Line
	2400 4950 2400 4850
$Comp
L power:GND #PWR?
U 1 1 5F6F612F
P 2400 5050
F 0 "#PWR?" H 2400 4800 50  0001 C CNN
F 1 "GND" H 2405 4877 50  0000 C CNN
F 2 "" H 2400 5050 50  0001 C CNN
F 3 "" H 2400 5050 50  0001 C CNN
	1    2400 5050
	1    0    0    -1  
$EndComp
Wire Wire Line
	2400 5050 2400 4950
Connection ~ 2400 4950
Wire Wire Line
	3050 4050 3050 4150
Wire Wire Line
	2400 4550 3050 4550
$Comp
L Device:R R4.7K
U 1 1 5F6F613A
P 2150 4150
F 0 "R4.7K" V 1943 4150 50  0000 C CNN
F 1 "R" V 2034 4150 50  0000 C CNN
F 2 "" V 2080 4150 50  0001 C CNN
F 3 "~" H 2150 4150 50  0001 C CNN
	1    2150 4150
	0    1    1    0   
$EndComp
Wire Wire Line
	2300 4150 3050 4150
Connection ~ 3050 4150
Text GLabel 1400 4150 0    50   Input ~ 0
PB2_DIO+
Wire Wire Line
	1850 4150 1850 4550
Connection ~ 1850 4150
Wire Wire Line
	1850 4150 2000 4150
Wire Wire Line
	1850 4550 2050 4550
Wire Wire Line
	1400 4150 1850 4150
$Comp
L power:GND #PWR?
U 1 1 5F6F6148
P 1600 4750
F 0 "#PWR?" H 1600 4500 50  0001 C CNN
F 1 "GND" H 1605 4577 50  0000 C CNN
F 2 "" H 1600 4750 50  0001 C CNN
F 3 "" H 1600 4750 50  0001 C CNN
	1    1600 4750
	1    0    0    -1  
$EndComp
Wire Wire Line
	1400 4550 1600 4550
Wire Wire Line
	1600 4550 1600 4750
$EndSCHEMATC
