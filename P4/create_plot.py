
import matplotlib.pyplot as plt
import numpy as np
import os


def to_terminal(cmd_string):
    os.system(cmd_string)

def plot_data_and_normals(data_path, result_path, hyperplane):
    koords = list()
    norms = list()
    with open(data_path, "r") as data_file:
        lines  = data_file.readlines()
        lines  = [line.strip() for line in lines[2:]]
        for line in lines:
            koords.append([float(i.strip()) for i in line.split(" ")])

    with open(result_path, "r") as hull_file:
        lines  = hull_file.readlines()
        lines  = [line.strip() for line in lines[2:]]
        for line in lines:
            line = [i for i in line.split(" ") if i != ""]
            norms.append([float(i.strip()) for i in line]) 


    if(len(koords[0]) == 2):
        for i in range(len(koords)):
            plt.plot(koords[i][0], koords[i][1], 'bo')
        if hyperplane: 
            for i in range(len(norms)):
                # a*x + b*y +c = 0
                max_val = 0.7
                if norms[i][1]:
                    x = np.linspace(-max_val, max_val, 100)
                    y = -1 * (norms[i][0] * x + norms[i][2])/norms[i][1]
                elif norms[i][0]:
                    y = np.linspace(-max_val, max_val, 100)
                    x = -1 * (norms[i][1] * y + norms[i][2])/norms[i][0]
                plt.plot(x,y)
        plt.xlabel("x")
        plt.ylabel("y")
        plt.show()

    elif(len(koords[0]) == 3):
        ax = plt.axes(projection='3d')
        for i in range(len(koords)):
            ax.plot(koords[i][0], koords[i][1], koords[i][2], 'bo')
        if hyperplane:
            for i in range(len(norms)):
                # a*x + b*y + c*z + d = 0
                max_val = 0.7
                if norms[i][2]:
                    xx, yy = np.meshgrid(np.linspace(-max_val, max_val, 10), np.linspace(-max_val, max_val, 10))
                    zz = (-norms[i][0] * xx - norms[i][1] * yy - norms[i][3])/norms[i][2]
                elif norms[i][1]: 
                    xx, zz = np.meshgrid(np.linspace(-max_val, max_val, 10), np.linspace(-max_val, max_val, 10))
                    yy = (-norms[i][0] * xx - norms[i][2] * zz - norms[i][3])/norms[i][1]
                elif norms[i][0]:
                    yy, zz = np.meshgrid(np.linspace(-max_val, max_val, 10), np.linspace(-max_val, max_val, 10))
                    xx = (-norms[i][1] * yy - norms[i][2] * zz - norms[i][3])/norms[i][0]
                ax.plot_surface(xx, yy, zz, alpha=0.2)
        ax.set_xlabel("x")
        ax.set_ylabel("y")
        plt.show()

    else: 
        print("ERROR: Only 2D and 3D plots/data as input!")



###################
# MAIN
###################

if __name__ == "__main__":
    
    data_file  = "data.txt"
    hull_file  = "result.txt"
    #cube_file  = "cube_data.txt"
    #square_file  = "square_data.txt"
    cmd_create_data = "rbox 10 D2 > " + data_file
    cmd_calc_hull   = "qconvex n < " + data_file + " > " + hull_file

    to_terminal(cmd_create_data)
    to_terminal(cmd_calc_hull)

    if "D2" in cmd_create_data or "D3" in cmd_create_data:
        plot_data_and_normals(data_file, hull_file, hyperplane = False)
