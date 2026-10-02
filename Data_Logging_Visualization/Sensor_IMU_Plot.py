import matplotlib.pyplot as plt
import csv
data="""Temperature: 25
X: 8
Y: 0
Z: 9
Temperature: 26
X: 7
Y: 1
Z: 9
Temperature: 27
X: 6
Y: 0
Z: 10"""
lines=data.splitlines()
temperature=[]
x=[]
y=[]
z=[]
for line in lines:
    parts=line.split(":")
    value=int(parts[1])
    if(parts[0]=="Temperature"):
        temperature.append(value)
    elif(parts[0]=="X"):
        x.append(value)
    elif(parts[0]=="Y"):
        y.append(value)
    elif(parts[0]=="Z"):
        z.append(value)
reading=[1,2,3]
plt.figure()
plt.plot(reading,temperature)
plt.xlabel("reading")
plt.ylabel("Temperature")
plt.title("Temperature Monitoring")
plt.show()
plt.figure()
plt.plot(reading,x,label="X")
plt.plot(reading,y,label="Y")
plt.plot(reading,z,label="Z")
plt.xlabel("reading")
plt.ylabel("Acceleration")
plt.title("IMU Monitoring")
plt.legend()
plt.show()
with open("Sensor_Data.csv","w",newline="") as file:
    writer=csv.writer(file)
    writer.writerow(["Reading","Temperature","X","Y","Z"])
    for i in range(len(temperature)):
        writer.writerow([
            i+1,
            temperature[i],
            x[i],
            y[i],
            z[i]
        ])