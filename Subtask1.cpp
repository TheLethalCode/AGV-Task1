#include<bits/stdc++.h>
#include<opencv2/opencv.hpp>
using namespace std;
using namespace cv;

#define fi first
#define se second
#define ma make_pair

// Structure to hold the details of the pixels
struct tryst
{
  int i,j,parenti,parentj;
  float f,g,h;
  bool wall,closed,open;
};

// A comparison for the ordering of the set
struct tryst_compare
{
  bool operator()(const tryst *lhs, const tryst *rhs) const
  {
    return lhs->f < rhs->f;
  }
};

// Class of the Bot
class Killer_Bot
{
  private:
    pair<int, int> start_point,end_point;
    Mat Cost_map;
    int Ar, Ac;
    vector< pair<int,int> > path;
    vector< vector<tryst> > grid;
    set<tryst *, tryst_compare> open;
    void draw();
    bool possCheck(int,int);
    void successor(int r, int s, set<tryst *, tryst_compare> &open);
    void successoradd(int r, int s, int i, int j, set<tryst *, tryst_compare> &open);
    void Trust();
    void Start();
    void End();
    int Astar(set<tryst *, tryst_compare> &open);

  public:
    Killer_Bot(Mat A, int x, int y);
    vector< pair<int,int> > getpath();
    int pathlength;
};

// Constructor initialising the cost map, no. of rows and columns
Killer_Bot :: Killer_Bot(Mat A, int x, int y)
{
  Cost_map=A;
  Ar=x;
  Ac=y;
  pathlength = 0;
  grid.resize(Ar,vector<tryst>(Ac));
}

// A function to find the path
vector<pair<int,int> > Killer_Bot :: getpath()
{
  Start();
  End();
  Trust();
  cout<<"The Co-ordinates of the starting point is "<<start_point.fi<<" "<<start_point.se<<endl;
  cout<<"The Co-ordinates of the destination point is "<<end_point.fi<<" "<<end_point.se<<endl;
  open.insert(&grid[start_point.fi][start_point.se]);
  if(Astar(open))
  cout<<"The Destination is Found"<<endl;
  else
  cout<<"Either destination is not reachable or somethin wrong with the algorithm"<<endl;
  namedWindow("Window",WINDOW_NORMAL);
  imshow("Window",Cost_map);
  return path;
}

// Function to draw the path
void Killer_Bot :: draw()
{
  int i = end_point.fi, j = end_point.se;
  while(i!=start_point.fi || j!=start_point.se)
  {
    int te1,te2;
    path.push_back(ma(i,j));
    Cost_map.at<Vec3b>(i,j)[0] = 255;
    Cost_map.at<Vec3b>(i,j)[1] = 0;
    Cost_map.at<Vec3b>(i,j)[2] = 0;
    te1 = grid[i][j].parenti;
    te2 = grid[i][j].parentj;
    i = te1;
    j = te2;
    pathlength++;
  }
  path.push_back(ma(i,j));
}

// Checks for a valid cell or not
bool Killer_Bot :: possCheck(int i, int j)
{
  if(i<0 || i>= Ar)
  return false;
  if(j<0 || j>= Ac)
  return false;
  if(grid[i][j].wall)
  return false;
  return true;
}

// Finds all the obstacles and initializes the pixels with their initial values
void Killer_Bot :: Trust()
{
 for(int i=0;i < Ar;i++)
  {
    for(int j =0;j< Ac;j++)
    {
      if(Cost_map.at<Vec3b>(i,j)[0] > 150 && Cost_map.at<Vec3b>(i,j)[1] > 150 && Cost_map.at<Vec3b>(i,j)[2] > 150)
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
      else if((i!=end_point.fi || j != end_point.se) && (i!=start_point.fi || j!=start_point.se))
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
    }
  }
}

// Finds the starting point
void Killer_Bot :: Start()
{
  for(int i=0;i<Ar;i++)
  {
    for(int j=0;j<Ac;j++)
    {
      if(Cost_map.at<Vec3b>(i,j)[1] > Cost_map.at<Vec3b>(i,j)[0] && Cost_map.at<Vec3b>(i,j)[1] > Cost_map.at<Vec3b>(i,j)[2])
      {
        int r = i + 10,s=j + 2;
        start_point.fi = r ;
        start_point.se = s;
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

// Finds the ending point
void Killer_Bot :: End()
{
  for(int i=0;i<Ar;i++)
  {
    for(int j=0;j<Ac;j++)
    {
      if(Cost_map.at<Vec3b>(i,j)[2] > Cost_map.at<Vec3b>(i,j)[0] && Cost_map.at<Vec3b>(i,j)[2] > Cost_map.at<Vec3b>(i,j)[1])
      {
        int r = i + 10,s=j+2;
        end_point.fi = r;
        end_point.se = s;
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

//Checks each successor whether it is valid or not and then adds it to the open list if necessary
void Killer_Bot :: successoradd(int r, int s, int i, int j, set<tryst *, tryst_compare> &open)
{
  if(possCheck(i,j) && !grid[i][j].closed)
  {
    float g = grid[r][s].g + 1;
    float h = sqrt((end_point.fi - i)*(end_point.fi - i) + (end_point.se - j)*(end_point.se - j));
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

// Calls all the 8 neighbours
void Killer_Bot :: successor(int r, int s, set<tryst *, tryst_compare> &open)
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

// Function to implement the A-star algorithm
int Killer_Bot :: Astar(set<tryst *, tryst_compare> &open)
{
  while(!open.empty())
  {
    tryst *test = *open.begin();
    open.erase(open.begin());
    (*test).open=false;
    (*test).closed = true;
    if(test->i == end_point.fi && test->j == end_point.se )
    {
      draw();
      return 1;
    }
    successor(test->i,test->j,open);
  }
  return 0;
}

// Main reads the file name as a command line argument and prints the path
int main(int argc, char * argv[])
{
  Mat A= imread(argv[1]);
  if(A.empty())
  {
    cout<<"The file can't be opened"<<endl;
    return -1;
  }
  int Ar = A.rows, Ac = A.cols;
  Killer_Bot KX1(A,Ar,Ac);
  vector<pair<int,int> > path = KX1.getpath();

  cout<<"The path followed is"<<endl;
  for(vector< pair<int,int> >::reverse_iterator it =  path.rbegin();it!=path.rend();it++)
  {
    cout<<it->fi<<" "<<it->se<<endl;
  }
  waitKey(0);
  cout<<"The length of the path is "<<KX1.pathlength<<endl;
  return 0;
}
