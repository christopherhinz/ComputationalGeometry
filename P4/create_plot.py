
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
            koords.append([float(i.strip()) for i in line.split(" ") if i != ""])

    with open(result_path, "r") as hull_file:
        lines     = hull_file.readlines()
        dimension = int(lines[0])
        vert_count  = int(lines[1].split(" ")[0]) 
        face_count    = int(lines[1].split(" ")[1]) 
        vertices = list()
        facets = list()
        for vert in lines[2:2+vert_count]:
            vertices.append([float(i) for i in vert.strip().split(" ") if i != ""])
        for face in lines[2+vert_count:2+vert_count+face_count]:
            facets.append([int(i) for i in face.strip().split(" ")[1:] if i != ""])


    if(dimension == 2):
        for i in range(len(koords)):
            plt.plot(koords[i][0], koords[i][1], 'bo')
        if hyperplane: 
            for face in facets:
                x_vals = [vertices[face[0]][0], vertices[face[1]][0]] 
                y_vals = [vertices[face[0]][1], vertices[face[1]][1]] 
                plt.plot(x_vals,y_vals, linestyle="solid")
        plt.xlabel("x")
        plt.ylabel("y")
        plt.show()
    
    elif(dimension == 3):
        ax = plt.axes(projection='3d')
        for i in range(len(koords)):
            ax.plot(koords[i][0], koords[i][1], koords[i][2], 'bo')
        if hyperplane: 
            for face in facets:
                x_vals = [vertices[face[0]][0], vertices[face[1]][0], vertices[face[2]][0]] 
                y_vals = [vertices[face[0]][1], vertices[face[1]][1], vertices[face[2]][1]] 
                z_vals = [vertices[face[0]][2], vertices[face[1]][2], vertices[face[2]][2]] 
                ax.plot([vertices[face[0]][0], vertices[face[1]][0]], 
                        [vertices[face[0]][1], vertices[face[1]][1]],
                        [vertices[face[0]][2], vertices[face[1]][2]], linestyle="solid")
                ax.plot([vertices[face[1]][0], vertices[face[2]][0]], 
                        [vertices[face[1]][1], vertices[face[2]][1]],
                        [vertices[face[1]][2], vertices[face[2]][2]], linestyle="solid")
                ax.plot([vertices[face[2]][0], vertices[face[0]][0]], 
                        [vertices[face[2]][1], vertices[face[0]][1]],
                        [vertices[face[2]][2], vertices[face[0]][2]], linestyle="solid")
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
    cmd_create_data = "rbox 5 D2 > " + data_file
    cmd_calc_hull   = "qconvex s o Qt < " + data_file + " > " + hull_file

    cmd_additional = "qconvex f < " + data_file + " > output.txt"

    to_terminal(cmd_create_data)
    to_terminal(cmd_calc_hull)
    to_terminal(cmd_additional)

        
    plot_data_and_normals(data_file, hull_file, hyperplane = True)


''''

rbox 4 D2 > data.txt && qconvex f < data.txt > result.txt


'''
