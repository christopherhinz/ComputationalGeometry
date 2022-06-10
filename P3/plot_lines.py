
import matplotlib.pyplot as plt
import numpy as np

mode = 2

text_flag = str(input("Text zu jeder Strecke plotten?"))

if mode == 0:
    with open("strecken/s_1000_10_reduced.dat", "r") as dat_file:
            lines = dat_file.readlines()
            lines = [line.strip() for line in lines]
            clean_lines = list()
            for line in lines:
                if line == "x":
                    break
                clean_lines.append(line)

            for line in clean_lines: 
                x, y = [float(line.split(" ")[0]), float(line.split(" ")[2])], [float(line.split(" ")[1]), float(line.split(" ")[3])]
                if text_flag == "y":
                    plt.text(x[0], y[0], f"({x[0]},{y[0]})")
                plt.plot(x, y, linestyle="solid")
    
    with open("intersects_found2.txt", "r") as dat_file:
        lines = dat_file.readlines()
        lines = [line.strip() for line in lines]
        clean_lines = list()
        for line in lines:
            if line == "x":
                break
            clean_lines.append(line)

        for line in clean_lines: 
            x, y = float(line.split(" ")[0]), float(line.split(" ")[1])
            plt.plot(x, y, marker='o')
    plt.show()


elif mode == 1:
    filenames = ["strecken/s_1000_1.dat", "strecken/s_1000_10.dat"]

    for filename in filenames:
        with open(filename, "r") as dat_file:
            lines = dat_file.readlines()
            lines = [line.strip() for line in lines]
            clean_lines = list()
            for line in lines:
                if line == "x":
                    break
                clean_lines.append(line)

            for line in clean_lines: 
                x, y = [float(line.split(" ")[0]), float(line.split(" ")[2])], [float(line.split(" ")[1]), float(line.split(" ")[3])]
                plt.plot(x, y, linestyle="solid")
            plt.title(filename)
            plt.show()

elif mode == 2:

    with open("strecken/s_1000_10.dat", "r") as dat_file:
        lines = dat_file.readlines()
        lines = [line.strip() for line in lines]
        clean_lines = list()
        for line in lines:
            if line == "x":
                break
            clean_lines.append(line)

        counter = 1
        for line in clean_lines: 
            x, y = [float(line.split(" ")[0]), float(line.split(" ")[2])], [float(line.split(" ")[1]), float(line.split(" ")[3])]
            plt.plot(x, y, linestyle="solid")
            if text_flag == "y":
                plt.text(x[0], y[0], f"({x[0]},{y[0]})")
            counter = counter + 1


    with open("intersects_found.txt", "r") as dat_file:
        lines = dat_file.readlines()
        lines = [line.strip() for line in lines]
        clean_lines = list()
        for line in lines:
            if line == "x":
                break
            clean_lines.append(line)

        for line in clean_lines: 
            x, y = float(line.split(" ")[0]), float(line.split(" ")[1])
            plt.plot(x, y, marker='o')


    plt.show()


