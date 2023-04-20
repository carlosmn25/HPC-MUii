import matplotlib.pyplot as plt
import pandas as pd

df = pd.read_csv('lab4/data.csv')
# Take the mean of time and loop of df with the same number of threads but dont index it
df = df.groupby(['nthreads', 'np']).mean().reset_index()

years = df['years']
time = df['time']
num = df['nthreads'].unique()
time_loop = df['loop']
numNodes = df['np'].unique()

# Add two columns "efficiency" and "efficiency_loop"
df['efficiency'] = 0
df['efficiency_loop'] = 0

fig = plt.plot(num, df[df['np']==1]['time'])
plt.plot(num, df[df['np']==2]['time'])
plt.plot(num, df[df['np']==4]['time'])
plt.plot(num, df[df['np']==8]['time'])
plt.xlabel('Number of threads')
plt.ylabel('Time in seconds')
plt.title('Time in seconds vs Number of threads')
plt.legend(['1 node', '2 nodes', '4 nodes', '8 nodes'])

for np in numNodes:
    for nt in num:
        y = df[(df['nthreads']==nt) & (df['np']==np)]['time']
        tag = round(df[(df['nthreads']==1) & (df['np']==np)]['time']/y.values[0], 2)
        plt.text(nt, y, str(tag.values[0]) + 'x', color='blue', fontweight='bold', position=(nt, df[df['nthreads']==nt][df['np']==np]['time']+0.5))

for np in numNodes:
    for nt in num:
        y = df[(df['nthreads']==nt) & (df['np']==np)]['time']
        tag = round(df[(df['nthreads']==1) & (df['np']==np)]['time']/y.values[0]/nt, 2)
        # Append the efficiency to the data frame
        df.loc[(df['nthreads']==nt) & (df['np']==np), 'efficiency'] = tag.values[0]
        plt.text(nt, y, str(tag.values[0]) + 'x', color='red', fontweight='bold', position=(nt, df[df['nthreads']==nt][df['np']==np]['time']-1))

plt.savefig('lab4/figTotal.png')

plt.clf()

fig = plt.plot(num, df[df['np']==1]['loop'])
plt.plot(num, df[df['np']==2]['loop'])
plt.plot(num, df[df['np']==4]['loop'])
plt.plot(num, df[df['np']==8]['loop'])
plt.xlabel('Number of threads')
plt.ylabel('Time in seconds')
plt.title('Time in seconds LOOP vs Number of threads')
plt.legend(['1 node', '2 nodes', '4 nodes', '8 nodes'])

# Show the speedup of each xticks
for np in numNodes:
    for nt in num:
        y = df[(df['nthreads']==nt) & (df['np']==np)]['loop']
        tag = round(df[(df['nthreads']==1) & (df['np']==np)]['loop']/y.values[0], 2)
        plt.text(nt, y, str(tag.values[0]) + 'x', color='blue', fontweight='bold', position=(nt, df[df['nthreads']==nt][df['np']==np]['loop']+0.5))

for np in numNodes:
    for nt in num:
        y = df[(df['nthreads']==nt) & (df['np']==np)]['loop']
        tag = round(df[(df['nthreads']==1) & (df['np']==np)]['loop']/y.values[0]/nt, 2)
        # Append the efficiency to the data frame
        df.loc[(df['nthreads']==nt) & (df['np']==np), 'efficiency_loop'] = tag.values[0]
        plt.text(nt, y, str(tag.values[0]) + 'x', color='red', fontweight='bold', position=(nt, df[df['nthreads']==nt][df['np']==np]['loop']-1))


plt.savefig('lab4/figLoop.png')

plt.clf()

# Plot efficiency list
fig = plt.plot(num, df[df['np']==1]['efficiency'])
plt.plot(num, df[df['np']==2]['efficiency'])
plt.plot(num, df[df['np']==4]['efficiency'])
plt.plot(num, df[df['np']==8]['efficiency'])
plt.xlabel('Number of threads')
plt.ylabel('Efficiency')
plt.title('Efficiency vs Number of threads')
plt.legend(['1 node', '2 nodes', '4 nodes', '8 nodes'])

plt.savefig('lab4/figEfficiency.png')

plt.clf()

# Plot efficiency list
fig = plt.plot(num, df[df['np']==1]['efficiency_loop'])
plt.plot(num, df[df['np']==2]['efficiency_loop'])
plt.plot(num, df[df['np']==4]['efficiency_loop'])
plt.plot(num, df[df['np']==8]['efficiency_loop'])
plt.xlabel('Number of threads')
plt.ylabel('Efficiency')
plt.title('Efficiency LOOP vs Number of threads')
plt.legend(['1 node', '2 nodes', '4 nodes', '8 nodes'])

plt.savefig('lab4/figEfficiencyLoop.png')