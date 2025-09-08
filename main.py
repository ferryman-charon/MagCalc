import numpy as np
import numpy.random as rnd
import matplotlib.pyplot as plt

#These vals, will be replaced with the real values of the magnetic field
x=rnd.rand(100)
x=np.where(x<0.5,-1,1)
x=np.reshape(x,[10,10])
r,c=np.shape(x)

for i in range (r):
    for k in range (c):
        plt.quiver(i,k,0,x[i,k],scale=100)
plt.show()
print (x)
