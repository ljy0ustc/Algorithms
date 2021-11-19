#include<iostream>
#include<fstream>
#include<cstdio>
#include<cstring>
#include<windows.h>
using namespace std;
char s1[35];
char s2[35];
int b[35][35];
int c[35][35];
char res[50000][35];
char res_str[35];
int res_len=0; 
ifstream infile; 
ofstream resfile;
ofstream timefile;
clock_t start_clk,end_clk;
LARGE_INTEGER  large_interger;  
double dff;  
__int64  c1, c2;
int cnt=0; 
void Print_LCS(int i,int j,int cur_len,int max_len)
{
    if(i==0||j==0)
    {
        res_len=max_len;
        for(int k=1;k<=res_len;k++)
            res[cnt][k]=res_str[k];
        cnt++;
        return;
    } 
    if(b[i][j]==1)
    {
        res_str[cur_len]=s1[i];
        Print_LCS(i-1,j-1,cur_len-1,max_len);
        return;
    }
    else if(b[i][j]==2)
    {
        Print_LCS(i-1,j,cur_len,max_len);
        return;
    }
    else if(b[i][j]==3)
    {
        Print_LCS(i,j-1,cur_len,max_len);
        return;
    }
    else if(b[i][j]==5)
    {
        Print_LCS(i,j-1,cur_len,max_len);
        Print_LCS(i-1,j,cur_len,max_len);
        return;
    }
}
int LCS_Length(int n)
{
    for(int i=0;i<=n;i++)
    {
        c[i][0]=0;
        c[0][i]=0;
    }
    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=n;j++)
        {
            if(s1[i]==s2[j])
            {
                c[i][j]=c[i-1][j-1]+1;
                b[i][j]=1;
            }
            else if(c[i-1][j]>c[i][j-1])
            {
                c[i][j]=c[i-1][j];
                b[i][j]=2;
            }
            else if(c[i-1][j]<c[i][j-1])
            {
                c[i][j]=c[i][j-1];
                b[i][j]=3;
            }
            else if(c[i-1][j]==c[i][j-1])
            {
                c[i][j]=c[i][j-1];
                b[i][j]=5;
            }
        }
    }
    return c[n][n];
}
int main()
{
    infile.open(".\\exp2\\input\\1_2_input.txt", ios::in);
    timefile.open(".\\exp2\\output\\time.txt",ios::out);
    string file_path_base=".\\exp2\\output\\result_";
    if(!infile.is_open())
        cout<<"Open file failure"<<endl;
    int T=0;
    while(!infile.eof())
    {
        int n;
        infile>>n;
        T++;
        string file_path=file_path_base+to_string(T)+".txt";
        
        resfile.open(file_path,ios::out);
        string string1,string2;
        infile>>string1>>string2;
        for(int i=0;i<n;i++)
        {
            s1[i+1]=string1[i];
            s2[i+1]=string2[i];
        }

        QueryPerformanceFrequency(&large_interger);  
        dff = large_interger.QuadPart;  
        QueryPerformanceCounter(&large_interger);  
        c1 = large_interger.QuadPart;  

        int max_len=LCS_Length(n);
        
        QueryPerformanceCounter(&large_interger);  
        c2 = large_interger.QuadPart; 
        timefile<<(c2-c1)*1000000/dff<<"us"<<endl;

        cnt=0;
        Print_LCS(n,n,max_len,max_len);
        resfile<<cnt<<endl;
        for(int i=0;i<cnt;i++)
        {
            for(int j=1;j<=res_len;j++)
                resfile<<res[i][j];
            resfile<<endl;
        }

        resfile.close();
    }
    infile.close();
    timefile.close();
    return 0;
}