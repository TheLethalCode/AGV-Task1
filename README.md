# AGV-Task1

This is the repository for all the codes related to AGV Task - 1 (Path Finder)

## Subtask-1

In this subtask we are required to find the shortest path between the starting\
point and the ending point with obstacles in between them.

The image is given to us.I detected the starting point and the ending point and\
found the path as close to the shortest path as possible using A* algorithm.

Initially the picture size on an average is 640x400, which is too much nodes for A*\
to handle efficiently. So, I divided the pixels into 5*5 grids, effectively reducing the\
no. of nodes to handle by 25. The grids with obstacles are marked as blocked.

Then I created a matrix storing the details of each grid and implemented the algorithm.

To use this program\
Clone the repo\
`git clone https://www.github.com/thelethalcode/AGV-Task1.git`\
Cd into the directory\
`cd AGV-Task1`\
Make the file\
`make Subtask1`\
Execute the file with the image name as the argument\
`.\Subtask1 a.png`\
