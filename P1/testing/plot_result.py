

import matplotlib.pyplot as plt
import numpy as np


with open("intersections.csv", "r") as csv_file:
    lines = csv_file.readlines()
    result_list = []
    tmp_dict = {}
    counter = 0
    for line in lines:
        if line != "\n":
            if counter == 0:
                counter = counter + 1
                tmp_dict["line1"] = [float(i.replace("\n", "")) for i in line.split(";")]
            elif counter == 1:
                counter = counter + 1
                tmp_dict["line2"] = [float(i.replace("\n", "")) for i in line.split(";")]
                result_list.append(tmp_dict)
        else: 
            tmp_dict = {}
            counter = 0


print(f"{len(result_list)} Schnittpunkte gefunden!\nWie viele sollen geplottet werden?\n")
lower = int(input("Startindex: "))
upper = int(input("Stoppindex: "))


for i in range(min(lower, upper), min(upper, len(result_list))):
    x1, y1 = [result_list[i]["line1"][0], result_list[i]["line1"][2]] , [result_list[i]["line1"][1], result_list[i]["line1"][3]]
    x2, y2 = [result_list[i]["line2"][0], result_list[i]["line2"][2]] , [result_list[i]["line2"][1], result_list[i]["line2"][3]]
    plt.plot(x1, y1, marker = 'o', linestyle="-.")
    plt.plot(x2, y2, marker = 'x', linestyle="--")
    plt.show()

