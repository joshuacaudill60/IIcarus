#!/usr/bin/env python3
import serial
import matplotlib.pyplot as plt
import numpy as np
import sys
from time import sleep
plt.style.use('ggplot')

if len(sys.argv) == 1:
    feather_port = "COM13"
else:
    feather_port = sys.argv[1]
baud = 9600

ser = serial.Serial(feather_port, baud)
print("Connected to Arduino port: " + feather_port)

channels = 288
sleep(1)  # Pause 1 second for suspense
line_1 = 0
# Create a numpy array to store the spectrometer data and the integral result
spec_data_1 = np.zeros([channels]) # used to be 1000,
# Create an array for all the wavelengths
points = np.linspace(340, 850, num=channels-2)

# line_2 = 0
# # Create a numpy array to store the spectrometer data and the integral result
# spec_data_2 = np.zeros([1000, channels+2])
fig, spec1 = plt.subplots(1)
fig.suptitle('Spectrometer Data')
spec1.set_ylabel("Spectrometer 1")
print(spec_data_1)
spec1.plot(points, spec_data_1[1:-1]) #used to be [0: -2]
# spec2.set_ylabel("Spectrometer 2")
# spec2.plot(points, spec_data_2[0, :-2])
fig.show()
spec_data_1 = str(ser.readline()).split(',')
sleep(1) # another dramatic pause
while 1:
    spec_data_1 = str(ser.readline()).split(',')[1:-1]
    spec_data_1 = [int(i) for i in spec_data_1]
    print(len(spec_data_1))
    print(spec_data_1)
    spec1.plot(points, spec_data_1)
    
    plt.pause(0.05)
    spec1.cla()
    # old stuff
    # getData = str(ser.readline())
    # print(getData[2:5])
    # pr = getData.split(',')
    # newstr = pr[0:][1:-3]
    # newstr = [int(i) for i in newstr]
    # spec_line_str = getData[0:][2:-4]
    # spec1.cla()
    # spec1.plot(points, newstr)
    # plt.pause(0.05)




    # if pr[0] == "b'257":    # or pr[0] == "b'258":
    #     newstr = pr[0:][1:-3]
    #     newstr = [int(i) for i in newstr]
    #     spec_line_str = getData[0:][2:-4]
    #     # Update lines
    #     if pr[0] == "b'257":
    #         spec1.cla()
    #         spec1.plot(points, newstr)

        # if pr[0] == "b'258":
        #     spec2.cla()
        #     spec2.plot(points, newstr)
        # plt.tight_layout()
        # plt.pause(0.05)
