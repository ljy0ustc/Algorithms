#include<iostream>
#include<cstdio>
#include<cstring>
#include<fstream>
#include<windows.h>
using namespace std;
ifstream infile;
ofstream resfile;
ofstream timefile;
clock_t start_clk,end_clk;
LARGE_INTEGER  large_interger;  
double dff;  
__int64  c1, c2;
int pi[5000];
int s[5000];
void Compute_Prefix(const string& P)
{
    int m=P.length();
    pi[0]=-1;
    int k=-1;
    for(int q=1;q<m;q++)
    {
        while(k>-1 && P[k+1]!=P[q])
            k=pi[k];
        if(P[k+1]==P[q])
            k++;
        pi[q]=k;
    }
}
int KMP_Matcher(const string& P,const string& T)
{
    int n=T.length();
    int m=P.length();
    Compute_Prefix(P);
    int q=-1,cnt=0;
    for(int i=0;i<n;i++)
    {
        while(q>-1 && P[q+1]!=T[i])
            q=pi[q];
        if(P[q+1]==T[i])
            q++;
        if(q==m-1)
        {
            cnt++;
            s[cnt]=i-m+1;
            q=pi[q];
        }
    }
    return cnt;
}
int main()
{
    infile.open(".//ex1//input//4_1_input.txt",ios::in);
    resfile.open(".//ex1//output//result.txt",ios::out);
    timefile.open(".//ex1//output//time.txt", ios::out);
    for(int K=0;K<=4;K++)
    {
        string P,T;
        infile>>P>>T;

        QueryPerformanceFrequency(&large_interger);  
        dff = large_interger.QuadPart;  
        QueryPerformanceCounter(&large_interger);  
        c1 = large_interger.QuadPart;  

        int cnt=KMP_Matcher(P,T);

        QueryPerformanceCounter(&large_interger);  
        c2 = large_interger.QuadPart; 
        timefile<<(c2-c1)*1000000/dff<<"us"<<endl;

        resfile<<cnt<<endl;
        for(int i=0;i<P.length();i++)
            resfile<<pi[i]+1<<" ";
        resfile<<endl;
        for(int i=1;i<=cnt;i++)
            resfile<<s[i]<<" ";
        resfile<<endl<<endl;
    }
    infile.close();
    resfile.close();
    timefile.close();
    return 0;
}