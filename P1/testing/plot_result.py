

import matplotlib.pyplot as plt


print("hallo")

with open("intersections.csv", "r") as csv_file:
    lines = csv_file.readlines()
    result_list = []
    tmp_dict = {}
    counter = 0
    for line in lines:
        if line != "\n":
            if counter == 0:
                counter = counter + 1
                tmp_dict["line1"] = [i.replace("\n", "") for i in line.split(";")]
            elif counter == 1:
                counter = counter + 1
                tmp_dict["line2"] = [i.replace("\n", "") for i in line.split(";")]
                result_list.append(tmp_dict)
        else: 
            tmp_dict = {}
            counter = 0


for i in range(len(result_list)):
    print(result_list[i])


print(f"{len(result_list)} Schnittpunkte gefunden!\nWie viele sollen geplottet werden?\n")
count = int(input("Anzahl plots: "))


for i in range(1, min(count, len(result_list))):
    x1, y1 = [result_list[i]["line1"][0], result_list[i]["line1"][2]] , [result_list[i]["line1"][1], result_list[i]["line1"][3]]
    x2, y2 = [result_list[i]["line2"][0], result_list[i]["line2"][2]] , [result_list[i]["line2"][1], result_list[i]["line2"][3]]
    print(x1, y1, x2, y2)
    plt.plot(x1, y1, marker = 'o', linestyle="-.")
    plt.plot(x2, y2, marker = 'x', linestyle="--")
    plt.show()

