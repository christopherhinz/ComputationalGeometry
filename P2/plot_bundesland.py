
import matplotlib.pyplot as plt
import numpy as np

with open("koords_to_test.txt", "r") as file:
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

for poly in bundesland_dict['Brandenburg']:
    print(poly)

koords = []
for bund in bundesland_dict.keys():
    for poly in bundesland_dict[bund]:
        koords += poly

xs, ys = zip(*koords)
ys = [-y for y in ys]
plt.figure()
plt.plot(xs, ys, ".") 
plt.plot([366.968], [-700], 'x', 'r')
plt.show() 


