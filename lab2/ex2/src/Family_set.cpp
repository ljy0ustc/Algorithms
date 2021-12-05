#include<iostream>
#include<cstdio>
#include<fstream>
#include<windows.h>
using namespace std;
LARGE_INTEGER  large_interger;  
double dff;  
__int64  c1, c2;
int p[35];
int r[35];
void MAKE_SET(int x)
{
    p[x]=x;
    r[x]=0;
}
void LINK(int x,int y)
{
    if(r[x]>r[y])
        p[y]=x;
    else
    {
        p[x]=y;
        if(r[x]==r[y])
            r[y]++;
    }
}
int FIND_SET(int x)
{
    if(x!=p[x])
    {
        p[x]=FIND_SET(p[x]);
        return p[x];
    }
}
void UNION(int x,int y)
{
    LINK(FIND_SET(x),FIND_SET(y));
}
int main()
{
    ifstream infile;
    ofstream resfile;
    ofstream timefile;
    infile.open(".//ex2//input//2_2_input.txt", ios::in);
    resfile.open(".//ex2//output//result.txt", ios::out);
    timefile.open(".//ex2//output//time.txt", ios::out);
    for(int N=10;N<=30;N+=5)
    {
        QueryPerformanceFrequency(&large_interger);  
        dff = large_interger.QuadPart;  
        QueryPerformanceCounter(&large_interger);  
        c1 = large_interger.QuadPart;

        int cnt=0;
        for(int i=0;i<N;i++)
        {
            MAKE_SET(i);
        }
        for(int i=0;i<N;i++)
        {
            for(int j=0;j<N;j++)
            {  
                int m;
                infile>>m;
                if(i<j && m)
                {
                    UNION(i,j);
                }
            }
        }
        for(int i=0;i<N;i++)
        {
            if(FIND_SET(i)==i)
            {
                cnt++;
            }
        }

        QueryPerformanceCounter(&large_interger);  
        c2 = large_interger.QuadPart; 
        timefile<<"n="<<N<<" "<<(c2-c1)*1000000/dff<<"us"<<endl;

        resfile<<"n="<<N<<" "<<cnt<<endl;
    }
    infile.close();
    resfile.close();
    timefile.close();
    return 0;
}