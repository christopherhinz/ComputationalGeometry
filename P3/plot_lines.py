
import matplotlib.pyplot as plt
import numpy as np

mode = 1

##############################################
# P3: plot s_1000_10.dat and found intersects
##############################################
if mode == 1:
    with open("strecken/s_1000_10.dat", "r") as dat_file:
            lines = dat_file.readlines()
            lines = [line.strip() for line in lines]
            clean_lines = list()
            for line in lines:
                if line == "x":
                    break
                clean_lines.append(line)
            lineID = 0
            for line in clean_lines: 
                x, y = [float(line.split(" ")[0]), float(line.split(" ")[2])], [float(line.split(" ")[1]), float(line.split(" ")[3])]
                #plt.text(x[0], y[0], f"({x[0]},{y[0]})")
                #plt.text(x[1], y[1], f"({x[1]},{y[1]})")
                plt.text(x[0], y[0], f"{lineID}")
                plt.plot(x, y, linestyle="solid")
                lineID += 1 

    with open("s_1000_10_intersects.txt", "r") as dat_file:
        lines = dat_file.readlines()
        lines = [line.strip() for line in lines]
        clean_lines = list()
        for line in lines:
            if line == "x":
                break
            clean_lines.append(line)

        for line in clean_lines: 
            x, y = float(line.split(" ")[0]), float(line.split(" ")[1])
            plt.plot(x, y, 'bo')

    
    with open("s_1000_10_intersects_bruteforce.txt", "r") as dat_file:
        lines = dat_file.readlines()
        lines = [line.strip() for line in lines]
        clean_lines = list()
        for line in lines:
            if line == "x":
                break
            clean_lines.append(line)

        for line in clean_lines: 
            x, y = float(line.split(" ")[0]), float(line.split(" ")[1])
            plt.plot(x, y, 'yx')

    plt.title("P3: s_1000_10.dat")
    plt.show()





##############################################
# P1: plot s_1000_1.dat and found intersects
##############################################
elif mode == 2:

    with open("strecken/s_1000_1_reduced.dat", "r") as dat_file:
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

    with open("s_1000_1_reduced_intersects.txt", "r") as dat_file:
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
    plt.title("P1: s_1000_1_reduced.dat")
    plt.show()



##############################################
#  Plot Testdata
##############################################

elif mode == 3:

    with open("strecken/test.dat", "r") as dat_file:
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

    with open("test.txt", "r") as dat_file:
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
    plt.title("test.dat")
    plt.show()

