
import matplotlib.pyplot as plt
import numpy as np

with open("/Users/Chrisi/SynologyDrive/Studium/Master/1.Semester/GoGe/Praktikum/P2/bundeslaender.txt", "r") as file:
    lines = [line.replace("\n", "") for line in file.readlines() if line]
    bundesland_dict = {}
    koords_list = []
    bund = ""
    for line in lines:
        if not line.startswith("\t"):
            if "Bundesland:" in line:
                bund = line.replace("Bundesland: ", "")
                bundesland_dict[bund] = []
            elif "Polygonnetz" in line:
                if koords_list:
                    bundesland_dict[bund].append(koords_list)
                koords_list = []
        elif line == "\n":
            bundesland_dict[bund].append(koords_list)
            bund = ""
            break
        else:
            line = line.replace("\t", "")
            koords_list.append([float(line.replace("\n", "").split(" ")[0]), float(line.replace("\n", "").split(" ")[1])])

with open("/Users/Chrisi/SynologyDrive/Studium/Master/1.Semester/GoGe/Praktikum/P2/staedte.txt", "r") as file:
    lines = file.readlines()
    koords_staedte = []
    for line in lines:
        koords_staedte.append([float(line.split(": ")[1].split(" ")[0]), float(line.split(": ")[1].split(" ")[1])])

print(koords_staedte)

koords_bund = []
for bund in bundesland_dict.keys():
    for poly in bundesland_dict[bund]:
        koords_bund += poly

xs_bund, ys_bund = zip(*koords_bund)
ys_bund = [-y for y in ys_bund]

xs_stadt, ys_stadt = zip(*koords_staedte)
ys_stadt = [-y for y in ys_stadt]

plt.figure()
plt.plot(xs_bund, ys_bund, ".")
plt.plot(xs_stadt, ys_stadt, 'x', color='r')
for i in range(len(xs_bund)):
    if (i > 5900) and (i < 6100):
        plt.annotate(i, (xs_bund[i], ys_bund[i]))
plt.show()
