import math
import time
import csv

from itertools import count
import paho.mqtt.client as mqtt

from matplotlib import pyplot as plt
from matplotlib.animation import FuncAnimation

x = [ ] 
acx_dt = [ ]
ycos = [ ]
data = [ ]
data_ = 1
axis_data = [[],[],[],[],[],[]]
plots = [0,0,0,0,0,0]

plt.style.use('seaborn')
#plt.style.use('fivethirtyeight')

fig, ((plots[0],plots[1]),(plots[2],plots[3]),(plots[4],plots[5])) = plt.subplots(nrows=3,ncols=2)
    
index = count(step=1)

def animate(i):
    global data
    global plots

    #if(len(acx_dt) > 0):
    x.append(next(index))

    print(data)
    #print(axis_data)

    for axis in range (2,3):
        axis_data[axis].append(data[axis])

        plots[axis].cla()
        plots[axis].set_ylim(-15,15)
        plots[axis].plot(x,axis_data[axis])

    print(axis_data)
    
    if len(x) == 50:
        x.pop(0)
        axis_data[0].pop(0)

def on_message(client, userdata, message):
    global data

    data = message.payload.decode("utf-8").split(";")
    data.pop(-1)
    data = [float(i) for i in data]

def on_connect (client, userdata, flags, rc):
    if rc == 0:
        print("Connected!")
    else:
        print("Bad connection. Return code = ", rc)

    client.subscribe(outTopic)



def on_subscribe(client, userdata, mid, granted_qos): 
   print("Subscribed:" + str(mid) + str(granted_qos))

def on_unsubscribe(client, userdata, mid): 
   print("Unsubscribed:" + str(mid))

def on_disconnect(client, userdata, rc): 
   if rc != 0: 
       print("Unexpected disconnection.") 

def on_log(client,userdata,level,buf):
    print("log: " + buf)

broker_addr = "broker.hivemq.com"
broker_port = 1883

client = mqtt.Client("rdba_pyclient001") 
client.on_subscribe = on_subscribe 
client.on_unsubscribe = on_unsubscribe 
client.on_connect = on_connect 
client.on_message = on_message 
#client.on_log = on_log
time.sleep(1) # Sleep for a beat to ensure things occur in order 
client.connect(broker_addr) 

'''
outTopic --> Do sensor para o computador
inTopic  --> Do computador para o sensor
'''

outTopic = "rdba/outTopic"
inTopic  = "rdba/inTopic"

client.loop_start()
time.sleep(3)
ani = FuncAnimation(fig, animate, interval=100)
plt.tight_layout()
plt.show()

client.disconnect() 
client.loop_stop() 