#include<bits/stdc++.h>
#include<opencv2/opencv.hpp>
using namespace std;
using namespace cv;

#define fi first
#define se second
#define ma make_pair

//Structure to hold the details of the grid
struct tryst
{
  int i,j,f,g,h,parenti,parentj;
  bool wall,closed;
  // Comparison operator for the set
  bool operator <(const tryst& judo) const
  {
    return f < judo.f;
  }
};

Mat A;
int Ar, Ac, n;
tryst start_point,end_point;

// Function to draw and print the path
void draw(tryst grid[][150])
{
  int i = end_point.i, j = end_point.j;
  vector< pair<int,int> > path;
  while(i!=start_point.i || j!=start_point.j)
  {
    int te1,te2;
    path.push_back(ma(i,j));
    for(int k=0;k<n;k++)
    {
      for(int l=0;l<n;l++)
      {
        A.at<Vec3b>(i*n+k,j*n+l)[0] = 255;
        A.at<Vec3b>(i*n+k,j*n+l)[1] = 0;
        A.at<Vec3b>(i*n+k,j*n+l)[2] = 0;
      }
    }
    te1 = grid[i][j].parenti;
    te2 = grid[i][j].parentj;
    i = te1;
    j = te2;
  }
  cout<<"The path followed is"<<endl;
  for(vector< pair<int,int> >::reverse_iterator it =  path.rbegin();it!=path.rend();it++)
  {
    cout<<it->fi<<" "<<it->se<<endl;
  }
}

//Checks for a valid cell or not
bool Check(tryst grid[][150],int i, int j)
{
  if(grid[i][j].wall)
  return false;
  if(i<0 || i>= Ar/n)
  return false;
  if(j<0 || j>= Ac/n)
  return false;
  if(grid[i][j].closed)
  return false;
  return true;
}

//Finds all the successors and checks for their validity and returns 1 if it is the detination
int successor(tryst grid[][150], set<tryst> &open, int r, int s)
{
  //Up
  int i = r, j=s+1;
  if(i==end_point.i && j==end_point.j)
  {
    grid[i][j].parenti = r;
    grid[i][j].parentj = s;
    grid[i][j].closed = true;
    return 1;
  }
  if(Check(grid,i,j))
  {
    int te1,te2,te;
    te1 = grid[r][s].g + 1;
    te2 = abs(end_point.i - i) + abs(end_point.j - j);
    te = te1 + te2;
    if(te <= grid[i][j].f)
    {
      grid[i][j].g = te1;
      grid[i][j].h = te2;
      grid[i][j].f = te;
      grid[i][j].parenti = r;
      grid[i][j].parentj = s;
      open.insert(grid[i][j]);
    }
  }

  //Down
  i = r, j=s-1;
  if(i==end_point.i && j==end_point.j)
  {
    grid[i][j].parenti = r;
    grid[i][j].parentj = s;
    grid[i][j].closed = true;
    return 1;
  }
  if(Check(grid,i,j))
  {
    int te1,te2,te;
    te1 = grid[r][s].g + 1;
    te2 = abs(end_point.i - i) + abs(end_point.j - j);
    te = te1 + te2;
    if(te <= grid[i][j].f)
    {
      grid[i][j].g = te1;
      grid[i][j].h = te2;
      grid[i][j].f = te;
      grid[i][j].parenti = r;
      grid[i][j].parentj = s;
      open.insert(grid[i][j]);
    }
  }

  //Left
  i = r-1, j=s;
  if(i==end_point.i && j==end_point.j)
  {
    grid[i][j].parenti = r;
    grid[i][j].parentj = s;
    grid[i][j].closed = true;
    return 1;
  }
  if(Check(grid,i,j))
  {
    int te1,te2,te;
    te1 = grid[r][s].g + 1;
    te2 = abs(end_point.i - i) + abs(end_point.j - j);
    te = te1 + te2;
    if(te <= grid[i][j].f)
    {
      grid[i][j].g = te1;
      grid[i][j].h = te2;
      grid[i][j].f = te;
      grid[i][j].parenti = r;
      grid[i][j].parentj = s;
      open.insert(grid[i][j]);
    }
  }

  //Right
  i = r+1, j=s;
  if(i==end_point.i && j==end_point.j)
  {
    grid[i][j].parenti = r;
    grid[i][j].parentj = s;
    grid[i][j].closed = true;
    return 1;
  }
  if(Check(grid,i,j))
  {
    int te1,te2,te;
    te1 = grid[r][s].g + 1;
    te2 = abs(end_point.i - i) + abs(end_point.j - j);
    te = te1 + te2;
    if(te <= grid[i][j].f)
    {
      grid[i][j].g = te1;
      grid[i][j].h = te2;
      grid[i][j].f = te;
      grid[i][j].parenti = r;
      grid[i][j].parentj = s;
      open.insert(grid[i][j]);
    }
  }

  //top-right
  i = r+1, j=s+1;
  if(i==end_point.i && j==end_point.j)
  {
    grid[i][j].parenti = r;
    grid[i][j].parentj = s;
    grid[i][j].closed = true;
    return 1;
  }
  if(Check(grid,i,j))
  {
    int te1,te2,te;
    te1 = grid[r][s].g + 1;
    te2 = abs(end_point.i - i) + abs(end_point.j - j);
    te = te1 + te2;
    if(te <= grid[i][j].f)
    {
      grid[i][j].g = te1;
      grid[i][j].h = te2;
      grid[i][j].f = te;
      grid[i][j].parenti = r;
      grid[i][j].parentj = s;
      open.insert(grid[i][j]);
    }
  }

  //Top-left
  i = r-1, j=s+1;
  if(i==end_point.i && j==end_point.j)
  {
    grid[i][j].parenti = r;
    grid[i][j].parentj = s;
    grid[i][j].closed = true;
    return 1;
  }
  if(Check(grid,i,j))
  {
    int te1,te2,te;
    te1 = grid[r][s].g + 1;
    te2 = abs(end_point.i - i) + abs(end_point.j - j);
    te = te1 + te2;
    if(te <= grid[i][j].f)
    {
      grid[i][j].g = te1;
      grid[i][j].h = te2;
      grid[i][j].f = te;
      grid[i][j].parenti = r;
      grid[i][j].parentj = s;
      open.insert(grid[i][j]);
    }
  }

  //Bottom right
  i = r+1, j=s-1;
  if(i==end_point.i && j==end_point.j)
  {
    grid[i][j].parenti = r;
    grid[i][j].parentj = s;
    grid[i][j].closed = true;
    return 1;
  }
  if(Check(grid,i,j))
  {
    int te1,te2,te;
    te1 = grid[r][s].g + 1;
    te2 = abs(end_point.i - i) + abs(end_point.j - j);
    te = te1 + te2;
    if(te <= grid[i][j].f)
    {
      grid[i][j].g = te1;
      grid[i][j].h = te2;
      grid[i][j].f = te;
      grid[i][j].parenti = r;
      grid[i][j].parentj = s;
      open.insert(grid[i][j]);
    }
  }

  //Bottom Left
  i = r-1, j=s-1;
  if(i==end_point.i && j==end_point.j)
  {
    grid[i][j].parenti = r;
    grid[i][j].parentj = s;
    grid[i][j].closed = true;
    return 1;
  }
  if(Check(grid,i,j))
  {
    int te1,te2,te;
    te1 = grid[r][s].g + 1;
    te2 = abs(end_point.i - i) + abs(end_point.j - j);
    te = te1 + te2;
    if(te <= grid[i][j].f)
    {
      grid[i][j].g = te1;
      grid[i][j].h = te2;
      grid[i][j].f = te;
      grid[i][j].parenti = r;
      grid[i][j].parentj = s;
      open.insert(grid[i][j]);
    }
  }
  return 0;
}

//Finds all the obstacles and initializes the grid with their initial values
void Trust(tryst grid[][150])
{
 for(int i=0;i < Ar/n;i++)
  {
    for(int j =0;j< Ac/n;j++)
    {
        int flag=0;
        for(int k=0;k<n;k++)
        {
          for(int l=0;l<n;l++)
          {
            if(A.at<Vec3b>(i*n+k,j*n+l)[0] > 0 && A.at<Vec3b>(i*n+k,j*n+l)[1] > 0)
            {
              flag = 1;
              break;
            }
          }
          if(flag==1)
          break;
        }
        if((i!=end_point.i || j != end_point.j) && (i!=start_point.i || j!=start_point.j))
        {
          if(i==76 && j==3)
          cout<<"fsdb"<<endl;
          if(!flag)
          {
            grid[i][j].i=i;
            grid[i][j].j=j;
            grid[i][j].g=1e9;
            grid[i][j].h=1e9;
            grid[i][j].f=1e9;
            grid[i][j].wall=false;
            grid[i][j].closed = false;
          }
          if(flag)
          {
            grid[i][j].i=i;
            grid[i][j].j=j;
            grid[i][j].g=1e9;
            grid[i][j].h=1e9;
            grid[i][j].f=1e9;
            grid[i][j].wall=true;
            grid[i][j].closed = false;
          }
        }
        flag=0;
      }
  }
}

//Finds the starting point
void Start(tryst grid[][150])
{
  int gr_imin=1000, gr_imax=0, gr_jmin=1000, gr_jmax=0;
  for(int i=0;i<A.rows;i++)
  {
    for(int j=0;j<A.cols;j++)
    {
      if(A.at<Vec3b>(i,j)[1] > 0 && A.at<Vec3b>(i,j)[0]==0)
      {
        if(gr_imax < i)
        gr_imax=i;
        if(gr_jmax < j)
        gr_jmax=j;
        if(gr_imin > i)
        gr_imin=i;
        if(gr_jmin > j)
        gr_jmin=j;
      }
    }
  }

  start_point.i = (gr_imin + gr_imax)/(2*n);
  start_point.j = (gr_jmin + gr_jmax)/(2*n);
  int a= start_point.i, b=start_point.j;
  grid[a][b].i=a;grid[a][b].j=b;
  start_point.f = 0;grid[a][b].f=0;
  start_point.g = 0;grid[a][b].g=0;
  start_point.h = 0;grid[a][b].h=0;
  start_point.wall = false;grid[a][b].wall=false;
  start_point.closed = false;grid[a][b].closed=false;
}

//Finds the ending point
void End()
{
  int r_imin=1000, r_imax=0, r_jmin=1000, r_jmax=0;
  for(int i=0;i<A.rows;i++)
  {
    for(int j=0;j<A.cols;j++)
    {
      if(A.at<Vec3b>(i,j)[2] > 0 && A.at<Vec3b>(i,j)[0]==0)
      {
        if(r_imax < i)
        r_imax=i;
        if(r_jmax < j)
        r_jmax=j;
        if(r_imin > i)
        r_imin=i;
        if(r_jmin > j)
        r_jmin=j;
      }
    }
  }
  end_point.i = (r_imin + r_imax)/(2*n);
  end_point.j = (r_jmin + r_jmax)/(2*n);
}

//Function to implement the A-star algorithm
int Astar(tryst grid[][150], set<tryst> &open)
{
  while(!open.empty())
  {
    tryst test = *open.begin();
    open.erase(open.begin());
    int i = test.i, j=test.j;
    grid[i][j].closed = true;
    if(successor(grid,open,i,j))
    return 1;
  }
  return 0;
}

int main(int argc, char * argv[])
{
  A= imread(argv[1]);
  Ar = A.rows, Ac = A.cols, n = 5;
  tryst grid[150][150];
  set<tryst> open;
  Start(grid);
  End();
  Trust(grid);
  cout<<"The Co-ordinates of the starting point is "<<start_point.i<<" "<<start_point.j<<endl;
  cout<<"The Co-ordinates of the destination point is "<<end_point.i<<" "<<end_point.j<<endl;
  open.insert(start_point);
  if(Astar(grid,open))
  cout<<"The Destination is Found"<<endl;
  else
  cout<<"Either destination is not reachable or somethin wrong with the algorithm"<<endl;
  draw(grid);
  namedWindow("Window",WINDOW_NORMAL);
  imshow("Window",A);
  waitKey(0);
  return 0;
}
