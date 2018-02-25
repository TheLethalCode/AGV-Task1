#include<bits/stdc++.h>
#include<opencv2/opencv.hpp>
using namespace std;
using namespace cv;

#define fi first
#define se second
#define ma make_pair

Mat A;
int Ar, Ac, n;

//Structure to hold the details of the grid
struct tryst
{
  int i,j,parenti,parentj;
  float f,g,h;
  bool wall,closed,open;
};

tryst grid[200][200];
tryst start_point,end_point;

struct tryst_compare
{
  bool operator()(const tryst *lhs, const tryst *rhs) const
  {
    return lhs->f < rhs->f;
  }
};

// Function to draw and print the path
void draw()
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
bool possCheck(int i, int j)
{
  if(grid[i][j].wall)
  return false;
  if(i<0 || i>= Ar/n)
  return false;
  if(j<0 || j>= Ac/n)
  return false;
  return true;
}

//Finds all the obstacles and initializes the grid with their initial values
void Trust()
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
            if(A.at<Vec3b>(i*n+k,j*n+l)[0] > 150 && A.at<Vec3b>(i*n+k,j*n+l)[1] > 150 && A.at<Vec3b>(i*n+k,j*n+l)[2] > 150 )
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
          if(!flag)
          {
            grid[i][j].i=i;
            grid[i][j].j=j;
            grid[i][j].g=1e9;
            grid[i][j].h=1e9;
            grid[i][j].f=1e9;
            grid[i][j].wall=false;
            grid[i][j].closed = false;
            grid[i][j].open = false;
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
            grid[i][j].open = false;
          }
        }
        flag=0;
      }
  }
}

//Finds the starting point
void Start()
{
  for(int i=0;i<A.rows;i++)
  {
    for(int j=0;j<A.cols;j++)
    {
      if(A.at<Vec3b>(i,j)[1] > A.at<Vec3b>(i,j)[0] && A.at<Vec3b>(i,j)[1] > A.at<Vec3b>(i,j)[2])
      {
        int r = i/n +2,s=j/n;
        start_point.i = r ;
        start_point.j = s;
        grid[r][s].i = r;
        grid[r][s].j = s;
        grid[r][s].f = 0;
        grid[r][s].g = 0;
        grid[r][s].h = 0;
        grid[r][s].wall = false;
        grid[r][s].closed = false;
        grid[r][s].open = true;
        return;
      }
    }
  }
}

//Finds the ending point
void End()
{
  for(int i=0;i<A.rows;i++)
  {
    for(int j=0;j<A.cols;j++)
    {
      if(A.at<Vec3b>(i,j)[2] > A.at<Vec3b>(i,j)[0] && A.at<Vec3b>(i,j)[2] > A.at<Vec3b>(i,j)[1])
      {
        int r = i/n + 2,s=j/n;
        end_point.i = r;
        end_point.j = s;
        grid[r][s].i = r;
        grid[r][s].j = s;
        grid[r][s].f = 0;
        grid[r][s].g = 0;
        grid[r][s].h = 0;
        grid[r][s].wall = false;
        grid[r][s].closed = false;
        grid[r][s].open = false;
        return;
      }
    }
  }
}

void successoradd(int r, int s, int i, int j, set<tryst *, tryst_compare> &open)
{
  if(possCheck(i,j) && !grid[i][j].closed)
  {
    float g = grid[r][s].g + 1;
    float h = sqrt((end_point.i - i)*(end_point.i - i) + (end_point.j - j)*(end_point.j - j));
    float f = g+h;
    if(!grid[i][j].open )
    {
      grid[i][j].g = g;
      grid[i][j].h = h;
      grid[i][j].f = f;
      grid[i][j].parenti = r;
      grid[i][j].parentj = s;
      open.insert(&grid[i][j]);
      grid[i][j].open = true;
    }
    else
    {
      if(g < grid[i][j].g )
      {
        grid[i][j].g = g;
        grid[i][j].h = h;
        grid[i][j].f = f;
        grid[i][j].parenti = r;
        grid[i][j].parentj = s;
      }
    }
  }
}

void successor(int r, int s, set<tryst *, tryst_compare> &open)
{
  successoradd(r,s,r+1,s,open);
  successoradd(r,s,r-1,s,open);
  successoradd(r,s,r,s+1,open);
  successoradd(r,s,r,s-1,open);
  successoradd(r,s,r+1,s-1,open);
  successoradd(r,s,r+1,s+1,open);
  successoradd(r,s,r-1,s-1,open);
  successoradd(r,s,r-1,s+1,open);
}

//Function to implement the A-star algorithm
int Astar(set<tryst *, tryst_compare> &open)
{
  while(!open.empty())
  {
    tryst *test = *open.begin();
    open.erase(open.begin());
    (*test).open=false;
    (*test).closed = true;
    if(test->i == end_point.i && test->j == end_point.j )
    {
      draw();
      return 1;
    }
    successor(test->i,test->j,open);
  }
  return 0;
}

int main(int argc, char * argv[])
{
  A= imread(argv[1]);
  Ar = A.rows, Ac = A.cols, n = 5;
  set<tryst *, tryst_compare> open;
  Start();
  End();
  Trust();
  cout<<"The Co-ordinates of the starting point is "<<start_point.i<<" "<<start_point.j<<endl;
  cout<<"The Co-ordinates of the destination point is "<<end_point.i<<" "<<end_point.j<<endl;
  open.insert(&grid[start_point.i][start_point.j]);
  if(Astar(open))
  cout<<"The Destination is Found"<<endl;
  else
  cout<<"Either destination is not reachable or somethin wrong with the algorithm"<<endl;
  namedWindow("Window",WINDOW_NORMAL);
  imshow("Window",A);
  waitKey(0);
  return 0;
}
