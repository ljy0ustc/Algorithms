#include<iostream>
#include<cstdio>
#include<fstream>
#include<windows.h>
#include<unordered_set>
using namespace std;
#define INF  1000000000
int pi[800];
int d[800];
int N[5]={0,27,81,243,729};
int path[800];
ifstream infile;
ofstream resfile;
ofstream timefile;
clock_t start_clk,end_clk;
LARGE_INTEGER  large_interger;  
double dff;  
__int64  c1, c2;
class Edge
{
    public:
        int u,v,weight;
};
std::unordered_set<Edge*> edge_set;
bool BellmanFord(int N)
{
    for(int i=0;i<=N-1;i++)
        pi[i]=-1;
    for(int i=1;i<=N-1;i++)
    {
        for(auto edge:edge_set)
        {
            if(d[edge->v]>d[edge->u]+edge->weight)
            {
                d[edge->v]=d[edge->u]+edge->weight;
                pi[edge->v]=edge->u;
            }
        }
    }
    for(auto edge:edge_set)
    {
        if(d[edge->v]>d[edge->u]+edge->weight)
        {
            return false;
        }
    }
    return true;
}
int ShortestPATH(int path_k)
{
    int node=path[path_k];
    if(node==0)
    {
        return path_k;
    }
    if(pi[node]==-1)
    {
        return 0;
    }
    else
    {
        path_k--;
        path[path_k]=pi[node];
        return ShortestPATH(path_k);
    }
}
int main()
{
    string infile_path_base=".//ex1//input//input";
    string resfile_path_base=".//ex1//output//result";
    timefile.open(".//ex1//output//time.txt", ios::out);
    for(int T=1;T<=4;T++)
    {
        for(int TT=1;TT<=2;TT++)
        {
            string infile_path=infile_path_base+to_string(T)+to_string(TT)+".txt";
            string resfile_path=resfile_path_base+to_string(T)+to_string(TT)+".txt";
            infile.open(infile_path, ios::in);
            resfile.open(resfile_path, ios::out);
            int weight;char sep;
            for(int i=0;i<N[T];i++)
            {
                for(int j=0;j<N[T];j++)
                {
                    infile>>weight;
                    infile>>sep;
                    if(weight)
                    {
                        Edge* new_edge=new Edge;
                        new_edge->u=i;
                        new_edge->v=j;
                        new_edge->weight=weight;
                        edge_set.insert(new_edge);
                    }
                    if(i==0)
                        d[j]=weight;
                    else
                        d[j]=INF;
                }
            }
            d[0]=0;

            QueryPerformanceFrequency(&large_interger);  
            dff = large_interger.QuadPart;  
            QueryPerformanceCounter(&large_interger);  
            c1 = large_interger.QuadPart;  

            BellmanFord(N[T]);

            QueryPerformanceCounter(&large_interger);  
            c2 = large_interger.QuadPart; 
            timefile<<(c2-c1)*1000000/dff<<"us"<<endl;

            int i=0;
            for(int j=1;j<N[T];j++)
            {
                int w=d[j];
                path[N[T]]=j;
                int path_start=ShortestPATH(N[T]);
                if(path_start)
                {
                    resfile<<i<<sep<<j<<sep<<w<<";"<<0;
                    for(int k=path_start+1;k<=N[T];k++)
                    {
                        resfile<<sep<<path[k];
                    }
                    resfile<<endl;
                }
            }
            edge_set.clear();
            infile.close();
            resfile.close();
        }   
    }   
    timefile.close();
    return 0;
}