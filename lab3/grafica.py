import matplotlib.pyplot as plt
import pandas as pd

df = pd.read_csv('lab3/data.csv')
# Take the mean of time and loop of df with the same number of threads but dont index it
df = df.groupby('nthreads').mean().reset_index()

years = df['years']
time = df['time']
num = df['nthreads']
time_loop = df['loop']

efficiency = []
efficiency_loop = []

fig = plt.plot(num, time)
plt.xlabel('Number of threads')
plt.ylabel('Time in seconds')
plt.title('Time in seconds vs Number of threads')
plt.xticks(num)

# Show the speedup of each xticks
for i, v in enumerate(time):
    # If i is power of 2
    if i in {0,1,3,7,15}:
        plt.text(num[i], v, str(round(time[0]/v, 2)) + 'x', color='blue', fontweight='bold', position=(num[i]-2, v))

# Show the efficiency of each xticks
for i, v in enumerate(time):
    efficiency.append(time[0]/(v*num[i]))
    # If i is power of 2
    if i in {0,1,3,7,15}:
        plt.text(num[i], v, str(round(time[0]/(v*num[i]), 2)) + 'x', color='red', fontweight='bold')


plt.savefig('lab3/figTotal.png')

plt.clf()

fig = plt.plot(num, time_loop)
plt.xlabel('Number of threads')
plt.ylabel('Time in seconds')
plt.title('Time in seconds LOOP vs Number of threads')
plt.xticks(num)

# Show the speedup of each xticks
for i, v in enumerate(time_loop):
    # If i is power of 2
    if i in {0,1,3,7,15}:
        plt.text(num[i], v, str(round(time_loop[0]/v, 2)) + 'x', color='blue', fontweight='bold', position=(num[i]-2, v))

# Show the efficiency of each xticks
for i, v in enumerate(time_loop):
    efficiency_loop.append(time_loop[0]/(v*num[i]))
    # If i is power of 2
    if i in {0,1,3,7,15}:
        plt.text(num[i], v, str(round(time_loop[0]/(v*num[i]), 2)) + 'x', color='red', fontweight='bold')

plt.savefig('lab3/figLoop.png')

plt.clf()

# Plot efficiency list
fig = plt.plot(num, efficiency)
plt.xlabel('Number of threads')
plt.ylabel('Efficiency')
plt.title('Efficiency vs Number of threads')
plt.xticks(num)

plt.savefig('lab3/figEfficiency.png')

plt.clf()

# Plot efficiency list
fig = plt.plot(num, efficiency_loop)
plt.xlabel('Number of threads')
plt.ylabel('Efficiency')
plt.title('Efficiency LOOP vs Number of threads')
plt.xticks(num)

plt.savefig('lab3/figEfficiencyLoop.png')