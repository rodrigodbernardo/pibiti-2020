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
for path in glob.glob('./python/capture/{}/*.txt'.format(folder)):
    iteration += 1

    plt.style.use('seaborn')
    raw = pd.read_csv(path)
    header = raw.keys()
    #print(raw)

    x = np.arange(size)

    fig, ((acx,gyx),(acy,gyy),(acz,gyz)) = plt.subplots(figsize=(6,5),sharey=False,nrows=3,ncols=2)
    #fig, (acx) = plt.subplots(sharey=False)
    axes = np.array([acx,acy,acz,gyx,gyy,gyz])
    #axes = np.array([acy])

    fig.suptitle('{} Hz'.format(folder[-2:]),size=20.0)

    for g in range(3):
        axes[g].plot(x,raw.iloc[:size,g])
        axes[g].set_title(header[g], size=20.0)
        axes[g].set_ylim([-20000,20000])
        axes[g].set_xlim([0,size])

        axes[g+3].plot(x,raw.iloc[:size,g+3])
        axes[g+3].set_title(header[g+3], size=20.0)
        axes[g+3].set_ylim([-5000,5000])
        axes[g+3].set_xlim([0,size])

    #axes[0].set_xlabel('Eixo X')
    #axes[0].set_ylabel('Eixo Y')

    plt.tight_layout()
    #plt.show()

    try:
        fig.savefig('./python/image/{}/{}_{}_{}_{}.png'.format(folder,dt.now().strftime("%Y%m%d_%H-%M-%S"),folder,size,iteration),dpi=500)
        print('Capture saved.')
    except:
        print('Failed to save image.')