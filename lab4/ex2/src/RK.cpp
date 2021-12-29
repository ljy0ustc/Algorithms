#include<iostream>
#include<cstdio>
#include<cstring>
#include<fstream>
#include<windows.h>
#include<cmath>
using namespace std;
ifstream infile;
ofstream resfile;
ofstream timefile;
clock_t start_clk,end_clk;
LARGE_INTEGER  large_interger;  
double dff;  
__int64  c1, c2;
int base_d[]={2,2,10,10};
int prime_q[]={13,1009,13,1009};
int shift[5000];
int cnt=0,false_cnt=0;
int f_cnt[5];
int tt[5][5];
void RK_Matcher(const string& P,const string& T,int d,int q)
{
    int n=T.length(),m=P.length();
    int h=d%q;
    if(h<0)h+=q;
    for(int i=1;i<=m-2;i++)
    {
        h=(h*d)%q;
        if(h<0)h+=q;
    }
    int p=0,t=0;
    cnt=0,false_cnt=0;
    for(int i=0;i<m;i++)
    {
        p=(d*p+P[i])%q;
        if(p<0)p+=q;
        t=(d*t+T[i])%q;
        if(t<0)t+=q;
    }
    for(int s=0;s<=n-m;s++)
    {
        if(p==t)
        {
            false_cnt++;
            bool matched=true;
            for(int i=0;i<m;i++)
            { 
                if(P[i]!=T[s+i])
                {
                    matched=false;
                    break;
                }
            }
            if(matched)
            {
                cnt++;
                shift[cnt]=s+1;
            }
        }
        if(s<n-m)
        {
            t=(d*(t-T[s]*h)+T[s+m])%q;
            if(t<0)t+=q;
        }
    }
}
int main()
{
    infile.open(".//ex2//input//4_2_input.txt",ios::in);
    resfile.open(".//ex2//output//result.txt",ios::out);
    timefile.open(".//ex2//output//time.txt", ios::out);
    for(int K=0;K<=4;K++)
    {
        string P,T;
        infile>>P>>T;
        for(int i=0;i<4;i++)
        {
            QueryPerformanceFrequency(&large_interger);  
            dff = large_interger.QuadPart;  
            QueryPerformanceCounter(&large_interger);  
            c1 = large_interger.QuadPart; 
             

            RK_Matcher(P,T,base_d[i],prime_q[i]);

            QueryPerformanceCounter(&large_interger);  
            c2 = large_interger.QuadPart; 
            tt[K][i]=(c2-c1)*1000000/dff;
            f_cnt[i]=false_cnt-cnt;
        }
        resfile<<cnt<<endl;
        for(int i=0;i<4;i++)
            resfile<<f_cnt[i]<<" ";
        resfile<<endl; 
        for(int i=1;i<=cnt;i++)
            resfile<<shift[i]<<" ";
        resfile<<endl<<endl;
    }
    for(int i=0;i<4;i++)
    {
        timefile<<"("<<base_d[i]<<","<<prime_q[i]<<")"<<endl;
        for(int K=0;K<=4;K++)
        {
            timefile<<tt[K][i]<<"us"<<" ";
        }
        timefile<<endl;
    }
        
    infile.close();
    resfile.close();
    timefile.close();
    return 0;
}