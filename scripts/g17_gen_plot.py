import matplotlib.pyplot as plt
import re

def average(data1, data2, step, iterations):
    ans = [ [], [] ]
    for count in range(iterations):
        ans[0].append(count + 1)
        ans[1].append(0.0)
    for count in range(len(data1)):
        ans[1][data1[count] - 1] = ans[1][data1[count] -1] + data2[count]
    for count in range(iterations):
        ans[1][count] = ans[1][count] / step
    return ans

def errorlist(data, iterations):
    ans = []
    for count in range(iterations):
        square = 0.0
        total = 0.0
        for count2 in range(iterations):
            square = square + (data[iterations*count + count2]**2)
            total = total + data[iterations*count + count2]
        ans.append((square - (iterations * ((total/float(iterations))**2)))/float(iterations))
    
    return ans

def cumulative(data, intervals):
    maximum = max(data)
    minimum = min(data)
    diff = maximum - minimum
    ans = list()
    for i in range(30):
        ans.append(0)
    for element in data:
        index = int(((element - minimum) / diff) * intervals)
        if index == intervals:
            index = index - 1
        ans[index] = ans[index] + 1
    for element in range(1, intervals):
        ans[element] = ans[element] + ans[element - 1]
    return ans

def dist(low, high, intervals):
    ans = list()
    for i in range(intervals):
        ans.append(float(low + (i*(high - low)) / intervals))
    return ans

filein = open('./data/lab09_g17_data.csv' , 'r')

linelist = filein.readlines()
datalist = list()
datalist = [ [], [], [], [], [], [], [] ]
for line in linelist:
    inpstr = re.findall(r'[0-9]+(?:\.[0-9]+)?', line)
    datalist[0].append(int(inpstr[0]))
    datalist[1].append(int(inpstr[1]))
    datalist[2].append(float(inpstr[2]))
    datalist[3].append(float(inpstr[3]))
    datalist[4].append(float(inpstr[4]))
    datalist[5].append(float(inpstr[5]))
    datalist[6].append(float(inpstr[6]))

avgstep = average(datalist[1], datalist[2], 100, 100)
avgloop = average(datalist[1], datalist[6], 100, 100)
avgcollision = average(datalist[1], datalist[3], 100, 100)
avgvelocity = average(datalist[1], datalist[4], 100, 100)
avgposition = average(datalist[1], datalist[5], 100, 100)
p1, = plt.plot(avgstep[0], avgstep[1],'.')
p2, = plt.plot(avgloop[0], avgloop[1], '-')
plt.ylabel('Values of step time and loop time')
plt.xlabel('Iteration Values')
plt.title('First Plot: Step and Loop time v/s iteration values')
l1 = plt.legend([p1, p2], ["Step Time", "Total Loop Time"], loc = 2)
plt.savefig('./plots/g17_lab09_plot01.png')
#plt.show()
plt.clf()
p3, = plt.plot(avgstep[0], avgstep[1], '.')
p4, = plt.plot(avgcollision[0], avgcollision[1], '-')
p5, = plt.plot(avgvelocity[0], avgvelocity[1], '--')
p6, = plt.plot(avgposition[0], avgposition[1], 'y--')
plt.ylabel('Various Timing Values')
plt.xlabel('Iteration Values')
plt.title('Second Plot: Step, collision, velocity and position time v/s iteration values')
l2 = plt.legend([p3,p4,p5,p6], ["Step Time", "Collision Time", "Velocity Time", "Position Time"], loc = 1)
plt.savefig('./plots/g17_lab09_plot02.png')
#plt.show()
plt.clf()
avgstepr = average(datalist[0], datalist[2], 100, 100)
avgloopr = average(datalist[0], datalist[6], 100, 100)
avgcollisionr = average(datalist[0], datalist[3], 100, 100)
avgvelocityr = average(datalist[0], datalist[4], 100, 100)
avgpositionr = average(datalist[0], datalist[5], 100, 100)
p7, = plt.plot(avgstepr[0], avgstepr[1],'.')
p8, = plt.plot(avgloopr[0], avgloopr[1], '-')
plt.ylabel('Values of step time and loop time')
plt.xlabel('Rerun Values')
plt.title('Third Plot: Step and Loop time v/s rerun values')
l3 = plt.legend([p7, p8], ["Step Time", "Total Loop Time"], loc = 10)
plt.savefig('./plots/g17_lab09_plot03.png')
#plt.show()
plt.clf()
p9, = plt.plot(avgstepr[0], avgstepr[1], '.')
p10, = plt.plot(avgcollisionr[0], avgcollisionr[1], '-')
p11, = plt.plot(avgvelocityr[0], avgvelocityr[1], '--')
p12, = plt.plot(avgpositionr[0], avgpositionr[1], 'y--')
plt.ylabel('Various Timing Values')
plt.xlabel('Rerun Values')
plt.title('Fourth Plot: Step, collision, velocity and position time v/s rerun values')
l4 = plt.legend([p9,p10,p11,p12], ["Step Time", "Collision Time", "Velocity Time", "Position Time"], loc = 10)
plt.savefig('./plots/g17_lab09_plot04.png')
#plt.show()
plt.clf()

errorans = errorlist(datalist[2], 100)
p13 = plt.errorbar(avgstep[0], avgstep[1], yerr=errorans)
l5 = plt.legend([p13], ["Step Time averaged over reruns with error bars"], loc = 1)
plt.xlabel('Iteration Values')
plt.ylabel('Step Time with error bars')
plt.title('Fifth plot: Step time with error bars v/s iteration values')
plt.savefig('./plots/g17_lab09_plot05.png')
#plt.show()
plt.clf()

intervals = 30
cumdata = cumulative(datalist[2][2400:4500], intervals)
distlist = dist(min(datalist[2][2400:4500]), max(datalist[2][2400:4500]), intervals)
p15, = plt.plot(distlist, cumdata, '--')
l6 = plt.legend([p15], ["Cumulative Frequency Curve"], loc = 7)
p14 = plt.hist(datalist[2][2400:4500], bins = 50)
plt.title("Frequency and cumulative distributions for step times v/s 45 iterations")
plt.xlabel('Step Time')
plt.ylabel('Reruns')
plt.savefig('./plots/g17_lab09_plot06.png')
#plt.show()
plt.clf()
