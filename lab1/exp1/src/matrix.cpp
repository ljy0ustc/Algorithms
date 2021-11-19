#include<iostream>
#include<cstdio>
#include<fstream>
#include<ctime>
#include<windows.h>
using namespace std;
int n;
long long m[30][30];
long long p[30];
int s[30][30];
ifstream infile; 
ofstream resfile;
ofstream timefile; 
clock_t start_clk,end_clk;
LARGE_INTEGER  large_interger;  
double dff;  
__int64  c1, c2;  
void Matrix_Chain_Order()
{
    for(int i=1;i<=n;i++)
        m[i][i]=0;
    for(int l=2;l<=n;l++)
    {
        for(int i=1;i<=n-l+1;i++)
        {
            int j=i+l-1;
            m[i][j]=9223372036854775807;
            for(int k=i;k<=j-1;k++)
            {
                long long q=m[i][k]+m[k+1][j]+p[i-1]*p[k]*p[j];
                if(q<m[i][j])
                {
                    m[i][j]=q;
                    s[i][j]=k;
                }
            }
        }
    }
}
void Print_Optimal_Parents(int i,int j)
{
    if(i==j)
    {
        resfile<<"A"<<i;
    }
    else
    {
        resfile<<"(";
        Print_Optimal_Parents(i,s[i][j]);
        Print_Optimal_Parents(s[i][j]+1,j);
        resfile<<")";
    }
}
int main()
{
    infile.open(".\\exp1\\input\\1_1_input.txt", ios::in);
    resfile.open(".\\exp1\\output\\result.txt",ios::out);
    timefile.open(".\\exp1\\output\\time.txt",ios::out);
    if(!infile.is_open())
        cout<<"Open file failure"<<endl;
    int T=0;
    while(!infile.eof())
    {
        T++;
        infile>>n;
        for(int i=0;i<=n;i++)
        {
            infile>>p[i];
        }
        
        QueryPerformanceFrequency(&large_interger);  
        dff = large_interger.QuadPart;  
        QueryPerformanceCounter(&large_interger);  
        c1 = large_interger.QuadPart;  
        
        Matrix_Chain_Order();
        
        QueryPerformanceCounter(&large_interger);  
        c2 = large_interger.QuadPart; 
        timefile<<(c2-c1)*1000000/dff<<"us"<<endl;

        resfile<<m[1][n]<<endl;
        Print_Optimal_Parents(1,n);
        resfile<<endl;

        
        
        if(n==5)
        {
            cout<<"m:"<<endl;
            cout<<"            ";
            for(int i=n;i>=1;i--)
                cout<<i<<"               ";
            cout<<endl;
            for(int i=1;i<=n;i++)
            {
                cout<<i<<" ";
                for(int j=n;j>=i;j--)
                {
                    cout<<m[i][j]<<" ";
                }
                cout<<endl;
            }
            cout<<"s:"<<endl;
            cout<<"  ";
            for(int i=n;i>=2;i--)
                cout<<i<<" ";
            cout<<endl;
            for(int i=1;i<=n-1;i++)
            {
                cout<<i<<" ";
                for(int j=n;j>=i+1;j--)
                {
                    cout<<s[i][j]<<" ";
                }
                cout<<endl;
            }
        }
    }
    while(1);
    infile.close();
    resfile.close();
    timefile.close();
    return 0;
}