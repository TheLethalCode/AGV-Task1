#include<bits/stdc++.h>
#include<opencv2/opencv.hpp>
using namespace std;
using namespace cv;

Mat A;
vector< pair<pair<int,int>,int> > v;
int Ar, Ac, n;
pair<int,int> start_point,end_point;

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
            if(A.at<Vec3b>(i*n+k,j*n+l)[0] > 0 && A.at<Vec3b>(i*n+k,j*n+l)[1] > 0)
            {
              flag = 1;
              break;
            }
          }
          if(flag==1)
          break;
        }
        if(!flag)
        {
          if( i != start_point.first || j != start_point.second)
          {
            if( i != end_point.first || j != end_point.second)
            {
              v.push_back(make_pair(make_pair(i,j),1));
            }
          }
        }
        if(flag)
        {
          if( i != start_point.first || j != start_point.second)
          {
            if( i != end_point.first || j != end_point.second)
            {
              v.push_back(make_pair(make_pair(i,j),0));
            }
          }
        }
        if(flag)
        {
          for(int k=0;k<n;k++)
          {
            for(int l=0;l<n;l++)
            {
              A.at<Vec3b>(i*n+k,j*n+l)[0] = 255;
              A.at<Vec3b>(i*n+k,j*n+l)[1] = 255;
              A.at<Vec3b>(i*n+k,j*n+l)[2] = 255;
            }
          }
          flag=0;
        }
    }
  }
}

void Start()
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
        A.at<Vec3b>(i,j)[1]=0;
      }
    }
  }
  start_point.first = (gr_imin + gr_imax)/(2*n);
  start_point.second = (gr_jmin + gr_jmax)/(2*n);
  for(int i=0;i<n;i++)
  {
    for(int j=0;j<n;j++)
    {
      A.at<Vec3b>(start_point.first*n+i,start_point.second*n+j)[1]=255;
      A.at<Vec3b>(start_point.first*n+i,start_point.second*n+j)[0]=0;
      A.at<Vec3b>(start_point.first*n+i,start_point.second*n+j)[2]=0;
    }
  }
}

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
        A.at<Vec3b>(i,j)[2]=0;
      }
    }
  }
  end_point.first = (r_imin + r_imax)/(2*n);
  end_point.second = (r_jmin + r_jmax)/(2*n);
  for(int i=0;i<n;i++)
  {
    for(int j=0;j<n;j++)
    {
      A.at<Vec3b>(end_point.first*n+i,end_point.second*n+j)[1]=0;
      A.at<Vec3b>(end_point.first*n+i,end_point.second*n+j)[0]=0;
      A.at<Vec3b>(end_point.first*n+i,end_point.second*n+j)[2]=255;
    }
  }
}

int main(int argc, char * argv[])
{
  A= imread(argv[1]);
  Mat B = A.clone();
  Ar = A.rows, Ac = A.cols, n = 5;
  cout<<A.rows<<endl;
  Start();
  End();
  Trust();
  cout<<"Start point "<<start_point.first<<" "<<start_point.second<<endl;
  cout<<"End point "<<end_point.first<<" "<<end_point.second<<endl;
  cout<<v.size()<<endl;
  namedWindow("Window",WINDOW_NORMAL);
  imshow("Window",A);
  waitKey(0);
  return 0;
}
