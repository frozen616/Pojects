
# Plot 2 signals

import serial
import numpy as np
from time import sleep 
from matplotlib import pyplot as plt
from matplotlib import animation


def serialConnect(portName, baudRate):
    try: 
        ser = serial.Serial(portName, baudRate)
        print("opened port " + ser.name + '\n')
        # give Arduino time to reset
        sleep(2)
        # flush input buffer, discarding all contents
        ser.reset_input_buffer()
        return ser 
    except serial.SerialException:
        raise IOError("problem connecting to " + portName)


def init():
    graph_temp.set_data([], [])
    graph_hum.set_data([], [])

 
    return graph_temp, graph_hum

def animate(i):
    global t, temp, hum

    while (ser.inWaiting() == 0):
        pass

    arduinoString = ser.readline().decode("utf-8")
    dataArray = arduinoString.split(':')

    temp.append(float(dataArray[0]))    
    hum.append(float(dataArray[1]))    



    temp.pop(0)
    hum.pop(0)




    graph_temp.set_data(t, temp)
    graph_hum.set_data(t, hum)




    return graph_temp, graph_hum

   

if __name__ == '__main__':

    portName = "/dev/ttyUSB0"
    ser = serialConnect(portName,115200)
    sleep(2)                                        # give Arduino time to reset

    # flush input buffer, discarding all contents
    ser.reset_input_buffer()

    numPoints = 201                                 # number of data points
    fig = plt.figure(figsize=(4, 5))               # create figure window
    ax = plt.axes(xlim=(0,numPoints-1), ylim=(30, 100))    # specify axis limits

    plt.title('Real-time Temperature')
    plt.xlabel('Data points over 7 min')
    plt.ylabel('Temp [Degrees F]')
    ax.grid(True)

    graph_temp, = ax.plot([], [], 'b', label = 'Temperature')


    ax.legend(loc='upper right')

    
    fig1 = plt.figure(figsize=(4,4))
    ax = plt.axes(xlim=(0,numPoints-1), ylim=(0, 100))    # specify axis limits

    plt.title('Real-time Humidity')
    plt.xlabel('Data points over 7 min')
    plt.ylabel('Humidity [%]')
    ax.grid(True)

    graph_hum, = ax.plot([], [], 'b', label = 'Humidity')
    ax.legend(loc='upper right')




    t = list(range(0, numPoints))
    temp = []
    hum = []




    for i in range(0, numPoints):
        temp.append(0)
        hum.append(0)



    delay = 20
    anim = animation.FuncAnimation(fig, animate, init_func=init,
                               interval=delay, blit=True)

    anim = animation.FuncAnimation(fig1, animate, init_func=init,
                               interval=delay, blit=True)
    plt.show() 
    
		




