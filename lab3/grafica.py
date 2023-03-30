import matplotlib.pyplot as plt
import pandas as pd

df = pd.read_csv('lab3/data.csv')
years = df['years']
time = df['time']
num = df['nthreads']
time_loop = df['loop']

fig = plt.plot(num, time)
plt.xlabel('Number of threads')
plt.ylabel('Time in seconds')
plt.title('Time in seconds vs Number of threads')

plt.savefig('lab3/figTotal.png')

plt.clf()

fig = plt.plot(num, time_loop)
plt.xlabel('Number of threads')
plt.ylabel('Time in seconds')
plt.title('Time in seconds LOOP vs Number of threads')

plt.savefig('lab3/figLoop.png')
