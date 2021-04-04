import math
import time
import csv

from itertools import count

from matplotlib import pyplot as plt
from matplotlib.animation import FuncAnimation

x = [ ] 
ysin = [ ]
ycos = [ ]

plt.style.use('seaborn')
#plt.style.use('fivethirtyeight')

fig, (sin,cos) = plt.subplots(nrows=2,ncols=1)
#sin.set_ylim(-1,1)
   
index = count(step=0.1)

def animate(i):
    x.append(next(index))

    ysin.append(math.sin(x[-1]))
    ycos.append(math.cos(x[-1]))

    sin.cla()
    cos.cla()

    sin.set_xlim(max(0,x[-1]-10),x[-1]+5)
    cos.set_xlim(max(0,x[-1]-10),x[-1]+5)

    sin.plot(x,ysin)
    cos.plot(x,ycos)

    if len(x) == 100:
        x.pop(0)
        ysin.pop(0)
        ycos.pop(0)



ani = FuncAnimation(fig, animate, interval=10)
plt.tight_layout()
plt.show()