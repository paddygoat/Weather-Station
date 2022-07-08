#!/usr/bin/env python
# cd /home/paddy/Desktop/RoboController/Test_Pyserial/ && python3 test_pyserial_3.py

import warnings
warnings.filterwarnings("ignore")
warnings.filterwarnings( "ignore", module = "matplotlib\..*" )

import matplotlib.pyplot as plt
import matplotlib.animation as animation
from matplotlib import style
import numpy as np
import random
import serial
import sys
import math

end = "\n"
RED = "\x1b[1;31m"
BLUE="\e[44m"
F_LightGreen = "\x1b[92m"
F_Green = "\x1b[32m"
F_LightBlue = "\x1b[94m"
B_White = "\x1b[107m"
NC = "\x1b[0m" # No Color
Blink = "\x1b[5m"

sys.stderr.write("\x1b[94m" + "Start: " + '\x1b[0m' + end) 

#initialize serial port
ser = serial.Serial()
# ser.set_buffer_size(rx_size = 100000, tx_size = 12800)
ser.port = '/dev/ttyUSB0' #Arduino serial port
ser.baudrate = 115200
ser.timeout = 10 #specify timeout when using readline()
ser.open()
if ser.is_open==True:
        print("\nSerial port now open.\n")
        ser.write(b'Serial port is open.\n')
	# print(ser, "\n") # print serial parameters

# Create figure for plotting
fig = plt.figure(figsize=(10,5))
ax = fig.add_subplot(1, 1, 1)
xs = [] # time index
yt = [] # temperature values
ym = [] # moisture values
yc = [] # detection confidence values
ycar = []
yPerson = []
threeDArray = np.zeros((2, 8, 10), dtype='object')       # fill array with zeros.
# threeDArray = np.select([threeDArray == 0], [""], threeDArray)   # get rid of the zeros.
counter =[10]
counter[0] = 0

# This function is called periodically from FuncAnimation
def animate(i, xs, yt, ym, yc, ycar, yPerson, threeDArray, counter):
    # Make a call back:
    # ser.write(b'S\n')

    arrayExists = False
    try:
        threeDArray
    except NameError:
        arrayExists = False
        # print("well, threeDArray WASN'T defined after all!")
    else:
        arrayExists = True
        # print("sure, threeDArray was defined.")

    #Aquire and parse data from serial port
    char_data=ser.readline()      # ascii
    char_data = char_data.decode("utf-8")
    # char_data = char_data[0:-2]
    len_char_data = len(char_data)

    # threeDArray = np.zeros((4, 8, 10), dtype='object')       # fill array with zeros.
    # print("threeDArray: ")
    # print(threeDArray)
    # threeDArray = np.select([threeDArray == 0], [""], threeDArray)   # get rid of the zeros.
    # print("threeDArray: ")
    # print(threeDArray)
    # threeDArray[threeDArray] = ""    # replace zeros with nulls.
    # arr[arr > 255] = x
    # s = numpy.array(['a', 'b', 'dude'], dtype='object')

    # print("threeDArray: ",threeDArray)
    detectionHeader = "@>#"
    testGlassHeader = ""
    testDetectHeader = ""
    desiredHeader = "#<~"
    headerGlassTest = False
    headerDetectTest = False
    detectLabel = ""
    detectConf = ""
    label_car = 0
    label_person = 0

    if len_char_data >2:
        for i in range(3):
            testGlassHeader = "" + testGlassHeader + str(char_data[i])
            testDetectHeader = "" + testDetectHeader + str(char_data[i])
        # print("testGlassHeader: ",testGlassHeader)
        # print("testDetectHeader: ",testDetectHeader)

    if testDetectHeader == detectionHeader:
        headerDetectTest = True

    if testGlassHeader == desiredHeader:
        headerGlassTest = True

    if len_char_data >2 and len_char_data <50:
        # Make a call back:
        ser.write(b'C\n')

        # print("threeDArray 1: ")
        # print(threeDArray)

        # print("threeDArray[0][5][0]: ",threeDArray[0][5][0]) 
        if str(threeDArray[0][5][0]) == "c":
            label_car = 10
            print("car was detected!") 
        if str(threeDArray[0][5][0]) == "p":
            label_person = 10
            print("PERSON was detected!") 

        for i in range(6):
            # temp = "" + temp + str(threeDArray[1][1][i])
            # mois = "" + mois + str(threeDArray[1][2][i])
            detectLabel = "" + detectLabel + str(threeDArray[0][5][i])
            detectConf = "" + detectConf + str(threeDArray[1][5][i])
        # print("detectLabel: ",detectLabel)
        # print("detectConf: ",detectConf)

        # Empty the array:
        for k in range(2):
            for j in range(8):
                for i in range(10):
                    threeDArray[k][j][i] = ""

        # print("threeDArray 2: ")
        # print(threeDArray)

        digit = 0
        space = 0
        period = 0
        brackets = 0
        colons = 0
        underScore = 0

        i = 0
        j = 0
        k = 0
        jAdjust = 0
        iAdjust = 0
        underScoreCount = 0

        if headerDetectTest == True:
            jAdjust = 4
        for i in range(len_char_data):

            period = 0
            brackets = 0
            colons = 0
            underScore = 0
            digit = char_data[i].isdigit()

            # s.find("r")
            if char_data[i]=='.':period = 1
            if char_data[i]=='_':underScore = 1

            if underScore == 1:
                # print("underScore_i: ",i)
                underScoreCount = underScoreCount +1
                iAdjust = i+1

            if (digit == 0)and(period == 0):
                if underScoreCount == 0:j=0+jAdjust
                if underScoreCount == 1:j=1+jAdjust
                if underScoreCount == 3:j=2+jAdjust
                if underScoreCount == 5:j=3+jAdjust
                if underScore == 0:
                    threeDArray[k][j][i-iAdjust] = char_data[i]

            if (digit == 1)or(period == 1):
                if underScoreCount == 1:j=0+jAdjust
                if underScoreCount == 3:j=1+jAdjust
                if underScoreCount == 5:j=2+jAdjust
                if underScore == 0:
                    threeDArray[k+1][j][i-iAdjust] = char_data[i]

        print("threeDArray 3: ")
        print(threeDArray)
        temp = ""
        mois = ""
        # detectLabel = ""
        # detectConf = ""

        for i in range(6):
            temp = "" + temp + str(threeDArray[1][1][i])
            mois = "" + mois + str(threeDArray[1][2][i])
            # detectLabel = "" + detectLabel + str(threeDArray[0][5][i])
            # detectConf = "" + detectConf + str(threeDArray[1][5][i])
        print("temp: ",temp) 
        print("mois: ",mois)
        print("detectLabel: ",detectLabel)
        print("detectConf: ",detectConf)

        print("") 
        if headerGlassTest == True:
            data_y_temp = float(temp)
            data_y_mois = float(mois)
            data_y_mois = abs(data_y_mois - 4094)
            data_y_mois = math.log(data_y_mois)*2
            data_y_mois = 20 - round(data_y_mois,2)

            if len(detectConf)>0:
                data_y_Conf = float(detectConf)*10
            else:
                data_y_Conf = 0
            # try:
                # detectConf
            # except NameError:
                # data_y_Conf = 0
                # print("No value for detectConf.")
            # else:
                # data_y_Conf = float(detectConf)*10

            yt.append(data_y_temp)
            ym.append(data_y_mois)
            yc.append(data_y_Conf)
            ycar.append(label_car)
            yPerson.append(label_person)
        xs = range(len(yt))
        # data_y_mois = 20 - round((math.log(abs(data_y_mois) - 4095)) *2,2)
    	
        # print("len_char_data:",len_char_data)
        print("char_data:",char_data)

        # data_y_mois = float(char_data_truncated_mois) - 4095 + 20
        # data_y_mois = 20 - round((math.log(abs(float(char_data_truncated_mois) - 4095))) *2,2)
        # Add x and y to lists
        # xs.append(i)

        # print("xs: ",xs)
        # print("yt: ",yt)
        # print("ym: ",ym)

        # Limit x and y lists to 2000 items
        xs = xs[-2000:]
        yt = yt[-2000:]
        ym = ym[-2000:]
        yc = yc[-2000:]

        # Draw x and y lists
        ax.clear()
        ax.plot(xs, yt, label="Temperature")
        ax.plot(xs, ym, label="Moisture")
        ax.plot(xs, yc, label="Confidence")
        ax.plot(xs, ycar, label="Car detect")
        ax.plot(xs, yPerson, label="Person detect")
        # ax.plot(xs, rs, label="Theoretical Probability")

        # Format plot
        plt.xticks(rotation=45, ha='right')
        plt.subplots_adjust(bottom=0.30)
        plt.title('Glasshouse Environmentals')
        plt.ylabel('Temperature')
        plt.legend()
        # plt.axis([1, None, 0, 50]) # Use for arbitrary number of trials
        plt.axis() # Use for arbitrary number of trials
        # plt.axis([1, 100, 0, 1.1]) # Use for 100 trial demo

    # Make a call back:
    ser.write(b'D\n')

    counter[0] = counter[0] + 1
    print("Counter[0]:  ",counter[0])

# Set up plot to call animate() function periodically
ani = animation.FuncAnimation(fig, animate, fargs=(xs, yt, ym, yc, ycar, yPerson, threeDArray, counter), interval=50)
plt.show()



