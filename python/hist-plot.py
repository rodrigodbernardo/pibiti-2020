import glob
import time
import numpy as np
import pandas as pd
#import seaborn as sn
from datetime import datetime as dt
from matplotlib import pyplot as plt

#path = './python/file.txt'
folder = input('Choose the frequency[Hz]: ')
size = int(input('Set the size: '))

iteration = 0
for path in glob.glob('./python/capture/3230_VAZIO/*.txt'.format(folder)):
    iteration += 1

    plt.style.use('seaborn')
    raw = pd.read_csv(path)
    header = raw.keys()

    x = np.arange(size)

    fig, ((acx,acy),(acz,gyx),(gyy,gyz)) = plt.subplots(nrows=3,ncols=2,sharex=False,sharey=True)
    #fig, acy = plt.subplots(sharey=True)

    axes = np.array([acx,acy,acz,gyx,gyy,gyz])
    #axes = np.array([acy])

    fig.suptitle('{} Hz'.format(folder))

    for i in range(6):
        
        axes[i].plot(x,raw.iloc[:size,i])
        axes[i].set_title(header[i])
        axes[i].set_ylim([-32768,32767])

    #axes[0].set_xlabel('Eixo X')
    #axes[0].set_ylabel('Eixo Y')

    plt.tight_layout()
    #plt.show()

    try:
        fig.savefig('./python/image/{}_{}_{}_{}.png'.format(dt.now().strftime("%Y%m%d_%H-%M-%S"),folder,size,iteration))
        print('Capture saved.')
    except:
        print('Failed to save image.')