import math as m
import numpy as np
from matplotlib import pyplot as plt

SIZE = 100

def get_coordinates():

    while True:
        coords = input("insert x and y coordinates \n").split()
        for i in range(len(coords)):
            coords[i] = int(coords[i])
        if coords[1] and coords[0] < SIZE and coords[1] < SIZE: 
            break
        else: print("insert only two numbers separated by spaces and lower than", SIZE, "\n")
    
    print(coords)
    return coords

def raycast(x1, x2, y1, y2, matrix1, matrix2):
    mod = m.sqrt((x1 - x2)**2 + (y1 - y2)**2)
    dir = m.atan2((y1 - y2), (x1 - x2))
    d = 0
    if matrix1[x2, y2] == 0:
        matrix2[x2, y2] = 0

    while d < mod:
        d += 0.25
        x = x2 + d*m.cos(dir)
        y = y2 + d*m.sin(dir)
        if matrix1[round(x), round(y)] == 0:
            matrix2[x2, y2] = 0

        
#initialize dummy matrix
dummy_matrix = np.ones((SIZE,SIZE))
dummy_matrix[15, 18] = 0
dummy_matrix[23, 19] = 0
dummy_matrix[22, 8] = 0
dummy_matrix[15, 36] = 0
#initialize random matrix
initial_matrix = np.ones((SIZE, SIZE))
updated_matrix = np.ones_like(initial_matrix)

for row in range(len(initial_matrix)):
    for element in range(len(initial_matrix[row])):
        if np.random.rand() > 0.99:
            initial_matrix[row][element] = 0

lightSource = get_coordinates()

for x in range(SIZE):
    for y in range(SIZE):
        raycast(lightSource[0], x, lightSource[1], y, initial_matrix, updated_matrix)


print(initial_matrix)
print(updated_matrix)

    



plt.figure(figsize=(40,40))
plt.imshow(initial_matrix)
plt.savefig("matrix_plot.svg")
plt.figure(figsize=(40,40))
plt.scatter(lightSource[0], lightSource[1], color='red', s=500)
plt.imshow(updated_matrix)
plt.savefig("updated_plot.svg")