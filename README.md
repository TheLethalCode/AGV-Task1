# AGV-Task1

This is the repository for all the codes related to AGV Task - 1 (Path Finder)

## Subtask-1

In this subtask we are required to find the shortest path between the starting\
point and the ending point with obstacles in between them, considering the bot has\
a point object

The image is given to us. I detected the starting point and the ending point and\
found the path as close to the shortest path as possible using A* algorithm. Here, I\
considered the diagonal movement to cost the same as a straight movement.

The path is printed along with the path length as well as shown in the image.

I created a structure "tryst" to store the details of each pixel

Then I created a matrix of tryst storing the details of each pixel and implemented the algorithm\
with set data type of tryst ordered by the f-cost as open list. The closed list is\
incorporated in the matrix.

To use this program\
Clone the repo
`git clone https://www.github.com/thelethalcode/AGV-Task1.git`\
Cd into the directory
`cd AGV-Task1`\
Make the file
`make Subtask1`\
Execute the file with the image name as the argument
`.\Subtask1 a.png`

You need to have opencv2 to be able to execute the file.
