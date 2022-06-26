#!/usr/bin/env python
# cd /home/paddy/Desktop/RoboController/Test_Pyserial/ && python3 test_pyserial_2.py

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
ser.port = '/dev/ttyUSB0' #Arduino serial port
ser.baudrate = 57600
ser.timeout = 10 #specify timeout when using readline()
ser.open()
if ser.is_open==True:
	print("\nSerial port now open.\n")
	# print(ser, "\n") # print serial parameters

# Create figure for plotting
fig = plt.figure(figsize=(10,5))
ax = fig.add_subplot(1, 1, 1)
xs = [] # store trials here (n)
ys = [] # store relative frequency here
rs = [] # for theoretical probability

# This function is called periodically from FuncAnimation
def animate(i, xs, ys):

    #Aquire and parse data from serial port
    character_data=ser.readline()      # ascii
    character_data = character_data.decode("utf-8")
    character_data = character_data[0:-2]
    len_character_data = len(character_data)
    
    if len_character_data >2 and len_character_data <20:
    	
        print("len_character_data:",len_character_data)
        print("character_data:",character_data)
        character_data_truncated = character_data[11:len_character_data]
        print("character_data_truncated:",character_data_truncated)
        print("")
        data_y = float(character_data_truncated)
	
	    # Add x and y to lists
        # xs.append(i)
        ys.append(data_y)
        xs = range(len(ys))
        print("xs: ",xs)
        print("ys: ",ys)
        # rs.append(0.5)

        # Limit x and y lists to 2000 items
        xs = xs[-2000:]
        ys = ys[-2000:]

        # Draw x and y lists
        ax.clear()
        ax.plot(xs, ys, label="Temperature")
        # ax.plot(xs, rs, label="Theoretical Probability")

        # Format plot
        plt.xticks(rotation=45, ha='right')
        plt.subplots_adjust(bottom=0.30)
        plt.title('Glasshouse Enviromentals')
        plt.ylabel('Temperature')
        plt.legend()
        # plt.axis([1, None, 0, 50]) # Use for arbitrary number of trials
        plt.axis() # Use for arbitrary number of trials
        # plt.axis([1, 100, 0, 1.1]) # Use for 100 trial demo

# Set up plot to call animate() function periodically
ani = animation.FuncAnimation(fig, animate, fargs=(xs, ys), interval=1000)
plt.show()


