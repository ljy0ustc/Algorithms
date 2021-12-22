#include<iostream>
#include<cstdio>
#include<fstream>
#include<windows.h>
#include<unordered_set>
#include<queue>
#include<utility>
#include<map>
using namespace std;
#define INF 1000000000
typedef pair<int,int> pii;
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
class NodeEdge
{
    public:
        int adj,weight;
};
typedef struct Node
{
    std::unordered_set<NodeEdge*> adj_set;
}Node;
Node node[800];
int N[5]={0,27,81,243,729};
int h[800];
int dis[800];
std::unordered_set<Edge*> edge_set;
bool BellmanFord(int N)
{
    for(int i=1;i<=N-1;i++)
    {
        for(auto edge:edge_set)
        {
            if(h[edge->v]>h[edge->u]+edge->weight)
            {
                h[edge->v]=h[edge->u]+edge->weight;
            }
        }
    }
    for(auto edge:edge_set)
    {
        if(h[edge->v]>h[edge->u]+edge->weight)
        {
            return false;
        }
    }
    return true;
}
void Dijkstra(int k,int N)
{
    priority_queue<pii,vector<pii>,greater<pii>> q;
    bool done[800];
    for(int i=0;i<N;i++)
    {
        dis[i]=INF;
        done[i]=false;
    }
    dis[k]=0;
    q.push(make_pair(dis[k],k));
    while(!q.empty())
    {
        auto item=q.top();
        q.pop();
        int u=item.second;
        if(done[u])continue;
        done[u]=true;
        for(auto edge:node[u].adj_set)
        {
            int v=edge->adj;
            if(done[v]==false&&dis[v]>dis[u]+edge->weight)
            {
                dis[v]=dis[u]+edge->weight;
                q.push(make_pair(dis[v],v));
            }
        }
    }
}
int main()
{
    string infile_path_base=".//ex2//input//input";
    string resfile_path_base=".//ex2//output//result";
    timefile.open(".//ex2//output//time.txt", ios::out);
    for(int T=1;T<=4;T++)
    {
        for(int TT=1;TT<=2;TT++)
        {
            string infile_path=infile_path_base+to_string(T)+to_string(TT)+".txt";
            string resfile_path=resfile_path_base+to_string(T)+to_string(TT)+".txt";
            infile.open(infile_path, ios::in);
            resfile.open(resfile_path, ios::out);
            int weight;char sep;
            for(int i=0;i<=N[T];i++)
            {
                node[i].adj_set.clear();
            }
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
                }
            }
            for(int i=0;i<N[T];i++)
            {
                Edge* new_edge=new Edge;
                new_edge->u=N[T];
                new_edge->v=i;
                new_edge->weight=0;
                edge_set.insert(new_edge);
                h[i]=0;
            }
            h[N[T]]=0;

            QueryPerformanceFrequency(&large_interger);  
            dff = large_interger.QuadPart;  
            QueryPerformanceCounter(&large_interger);  
            c1 = large_interger.QuadPart; 

            BellmanFord(N[T]+1);
            
            for(auto edge:edge_set)
            {
                NodeEdge* node_edge=new NodeEdge;
                node_edge->adj=edge->v;
                node_edge->weight=edge->weight+h[edge->u]-h[edge->v];
                node[edge->u].adj_set.insert(node_edge);
            }
            for(int i=0;i<N[T];i++)
            {
                Dijkstra(i,N[T]);
                for(int j=0;j<N[T];j++)
                {
                    int D=dis[j]+h[j]-h[i];
                    if(dis[j]<INF)
                    {
                        resfile<<D<<" ";
                    }
                    else
                    {
                        resfile<<"X ";
                    }
                }
                resfile<<endl;
            }

            QueryPerformanceCounter(&large_interger);  
            c2 = large_interger.QuadPart; 
            timefile<<(c2-c1)*1000000/dff<<"us"<<endl;

            edge_set.clear();
            infile.close();
            resfile.close();
        }   
    }   
    timefile.close();
    return 0;
}