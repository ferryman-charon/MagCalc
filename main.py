import numpy as np
import numpy.random as rnd
import matplotlib.pyplot as plt

#These vals, will be replaced with the real values of the magnetic field

#Create random Vectorfield
x=rnd.rand(100)
x=np.where(x<0.5,-1,1)
x=np.reshape(x,[10,10])
r,c=np.shape(x)
print (x)

#Plot Vectorfield
for i in range (r):
    for k in range (c):
        plt.quiver(i,k,0,x[i,k],scale=100)
plt.show()

#Model for Energy calc
    #Check for surrounding Vals
en=np.zeros_like(x)
#Model Calculates edges and corners correctly but not the middle Terms may come back later
for i in range (r):
    for k in range(c):
        #Calculating upper corner Vals
        if i==0:
            if k==0:
                en[i,k]+=x[i,k]+x[i+1,k]+x[i,k+1]
            if k==c-1:
                en[i,k]+=x[i,k]+x[i+1,k]+x[i,k-1]
        #Calculating first and last col Vals
        if k==0 and 0<i<r-1:
            en[i,k]+=x[i,k]+x[i-1,k]+x[i+1,k]+x[i,k+1]
        if k==c-1 and 0<i<r-1:
            en[i,k]+=x[i,k]+x[i-1,k]+x[i+1,k]+x[i,k-1]
        #Calculating lower corner Vals
        if i==r-1:
            if k==0:
                en[i,k]+=x[i,k]+x[i-1,k]+x[i,k+1]
            if k==c-1:
                en[i,k]+=x[i,k]+x[i-1,k]+x[i,k-1]
        #Calculating first and last row Vals
        if i==0 and 0<k<c-1:
            en[i,k]+=x[i,k]+x[i+1,k]+x[i,k-1]+x[i,k+1]
        if i==r-1 and 0<k<c-1:
            en[i,k]+=x[i,k]+x[i-1,k]+x[i,k+1]+x[i,k-1]
        #Calculating all in between Vals
        if 0<i<r-1 and 0<k<c-1:
            en[i,k]+=x[i,k]+x[i-1,k]+x[i+1,k]+x[i,k-1]+x[i,k+1]
print(en)
