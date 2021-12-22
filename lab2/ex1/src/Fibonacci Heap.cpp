#include<iostream>
#include<cstdio>
#include<fstream>
#include<list>
#include<array>
#include<windows.h>
#include<unordered_map>
#include<unordered_set>
using namespace std;
const int max_D=500;
LARGE_INTEGER  large_interger;  
double dff;  
__int64  c1, c2;
class Node
{
    public:
        int key;
        int degree;
        Node* p;
        std::unordered_set<Node* > child;
        bool mark;
};
class Heap
{
    public:
        int n;
        Node* min;
        list<Node*> root_list;
};
Node* node_map[1001];
class Util
{
    public:
        Heap* Fib_Init_Heap();
        int Fib_Heap_Insert(Heap* ,int );
        Heap* Fib_Heap_Union(Heap* ,Heap* );
        int Fib_Heap_Decrease_Key(Heap*,Node*,int);
        int Fib_Heap_Min(Heap*);
        int Fib_Heap_Extract_Min(Heap*);
        int Fib_Heap_Delete(Heap*,Node*);
    private:
        void Consolidate(Heap* );
        void Cut(Heap*,Node*,Node*);
        void Cascading_Cut(Heap*,Node*);
        Node* Fib_Heap_Link(Heap*,Node* , Node*);
        Node* Fib_Make_Node(int);
};
Heap* Util::Fib_Init_Heap()
{
    Heap* heap=new Heap;
    heap->n=0;
    heap->min=NULL;
    return heap;
}
Node* Util::Fib_Make_Node(int val)
{
    Node* node=new Node;
    node->key=val;
    return node;
}
int Util::Fib_Heap_Insert(Heap* H,int val)
{
    Node* x=Util::Fib_Make_Node(val);
    node_map[val]=x;
    x->degree=0;
    x->p=NULL;
    x->mark=false;
    if(H->min==NULL)
    {
        H->root_list.push_back(x);
        H->min=x;
    }
    else
    {
        H->root_list.push_back(x);
        if(x->key < H->min->key)
            H->min=x;
    }
    H->n=H->n+1;
    return H->n;
}
int Util::Fib_Heap_Min(Heap* H)
{
    return H->min->key;
}
Heap* Util::Fib_Heap_Union(Heap* H1,Heap* H2)
{
    Heap* H = new Heap;
    H->min=H1->min;
    H->root_list.splice(H->root_list.end(),H1->root_list);
    H->root_list.splice(H->root_list.end(),H2->root_list);
    if(H1->min==NULL || H2->min!=NULL && H2->min->key < H1->min->key)
    {
        H->min=H2->min;
    }
    H->n=H1->n+H2->n;
    return H;
}
int Util::Fib_Heap_Extract_Min(Heap* H)
{
    Node* z=H->min;
    if(z)
    {
        for(auto x : z->child)
        {
            H->root_list.push_back(x);
            x->p=NULL;
        }
        H->root_list.remove(z);
        node_map[z->key]=NULL;
        if(H->root_list.size()==0)
        {
            H->min=NULL;
        }
        else
        {
            H->min=NULL;
            Util::Consolidate(H);
        }
        H->n=H->n-1;
    }
    return z->key;
}
Node* Util::Fib_Heap_Link(Heap* H,Node* y,Node* x)
{
    //H->root_list.remove(y);
    x->child.insert(y);
    x->degree++;
    y->mark=false;
    y->p=x;
    return y;
}
void Util::Consolidate(Heap* H)
{
    std::array<Node* , max_D> A;
    for(int i=0;i<max_D;i++)
    {
        A[i]=NULL;
    }
    std::unordered_set<Node* >remove_set;
    for(auto w : H->root_list)
    {
        Node* x=w;
        if(remove_set.find(x)!=remove_set.end())
            continue;//x已被移除
        int d=x->degree;
        while(A[d])
        {
            Node* y=A[d];
            if(x->key > y->key)
            {
                remove_set.insert(Fib_Heap_Link(H,x,y));
                x=y;
            }
            else
                remove_set.insert(Fib_Heap_Link(H,y,x));
            A[d]=NULL;
            d++;
        }
        A[d]=x;
    }
    H->min=NULL;
    H->root_list.clear();
    for(int i=0;i<max_D;i++)
    {
        if(A[i])
        {
            if(H->min==NULL)
            {
                H->root_list.push_back(A[i]);
                H->min=A[i];
            }
            else
            {
                H->root_list.push_back(A[i]);
                if(A[i]->key<H->min->key)
                {
                    H->min=A[i];
                }
            }
        }
    }
}
void Util::Cut(Heap* H,Node* x,Node* y)
{
    y->child.erase(x);
    y->degree--;
    H->root_list.push_back(x);
    x->p=NULL;
    x->mark=false;
}
void Util::Cascading_Cut(Heap* H,Node* y)
{
    Node* z=y->p;
    if(z)
    {
        if(y->mark==false)
        {
            y->mark=true;
        }
        else
        {
            Util::Cut(H,y,z);
            Util::Cascading_Cut(H,z);
        }
    }
}
int Util::Fib_Heap_Decrease_Key(Heap* H,Node* x,int k)
{
    if(k > x->key)
    {
        cout<<"new key is greater than current key"<<endl;
    }
    node_map[x->key]=NULL;
    node_map[k]=x;
    x->key=k;
    Node* y=x->p;
    if(y && x->key < y->key)
    {
        Util::Cut(H,x,y);
        Util::Cascading_Cut(H,y);
    }
    if(x->key < H->min->key)
    {
        H->min=x;
    }
    return H->min->key;
}
int Util::Fib_Heap_Delete(Heap* H,Node* x)
{
    Util::Fib_Heap_Decrease_Key(H,x,0);
    Util::Fib_Heap_Extract_Min(H);
    return H->n;
}
int main()
{
    ifstream infile;
    ofstream resfile;
    ofstream timefile;
    infile.open(".//ex1//input//2_1_input.txt", ios::in);
    resfile.open(".//ex1//output//result.txt", ios::out);
    timefile.open(".//ex1//output//time.txt", ios::out);
    int num;
    Util util;
    for(int i=0;i<=1000;i++)
        node_map[i]=NULL;
    Heap* H1=util.Fib_Init_Heap();
    Heap* H2=util.Fib_Init_Heap();
    Heap* H3=util.Fib_Init_Heap();
    Heap* H4=util.Fib_Init_Heap();
    Node* node;
    for(int i=1;i<=50;i++)
    {
        infile>>num;
        util.Fib_Heap_Insert(H1,num);
    }
    for(int i=1;i<=100;i++)
    {
        infile>>num;
        util.Fib_Heap_Insert(H2,num);
    }
    for(int i=1;i<=150;i++)
    {
        infile>>num;
        util.Fib_Heap_Insert(H3,num);
    }
    for(int i=1;i<=200;i++)
    {
        infile>>num;
        util.Fib_Heap_Insert(H4,num);
    }

    //step2:在H1下完成以下10个ops:
    resfile<<"H1"<<endl;

    QueryPerformanceFrequency(&large_interger);  
    dff = large_interger.QuadPart;  
    QueryPerformanceCounter(&large_interger);  
    c1 = large_interger.QuadPart;

    resfile<<util.Fib_Heap_Insert(H1,249)<<",";
    resfile<<util.Fib_Heap_Insert(H1,830)<<",";
    resfile<<util.Fib_Heap_Min(H1)<<",";
    resfile<<util.Fib_Heap_Delete(H1,node_map[127])<<",";
    resfile<<util.Fib_Heap_Delete(H1,node_map[141])<<","; 
    resfile<<util.Fib_Heap_Min(H1)<<",";
    resfile<<util.Fib_Heap_Decrease_Key(H1,node_map[75],61)<<",";
    resfile<<util.Fib_Heap_Decrease_Key(H1,node_map[198],169)<<","; 
    resfile<<util.Fib_Heap_Extract_Min(H1)<<",";
    resfile<<util.Fib_Heap_Extract_Min(H1)<<endl;

    QueryPerformanceCounter(&large_interger);  
    c2 = large_interger.QuadPart; 
    timefile<<"step2的运行时间"<<(c2-c1)*1000000/dff<<"us"<<endl;

    //Step3:在H2下完成以下10个ops:
    resfile<<"H2"<<endl;

    QueryPerformanceFrequency(&large_interger);  
    dff = large_interger.QuadPart;  
    QueryPerformanceCounter(&large_interger);  
    c1 = large_interger.QuadPart;

    resfile<<util.Fib_Heap_Insert(H2,816)<<","; 
    resfile<<util.Fib_Heap_Min(H2)<<","; 
    resfile<<util.Fib_Heap_Insert(H2,345)<<","; 
    resfile<<util.Fib_Heap_Extract_Min(H2)<<",";
    resfile<<util.Fib_Heap_Delete(H2,node_map[504])<<",";
    resfile<<util.Fib_Heap_Delete(H2,node_map[203])<<",";
    resfile<<util.Fib_Heap_Decrease_Key(H2,node_map[296],87)<<",";
    resfile<<util.Fib_Heap_Decrease_Key(H2,node_map[278],258)<<",";
    resfile<<util.Fib_Heap_Min(H2)<<",";
    resfile<<util.Fib_Heap_Extract_Min(H2)<<endl;

    QueryPerformanceCounter(&large_interger);  
    c2 = large_interger.QuadPart; 
    timefile<<"step3的运行时间"<<(c2-c1)*1000000/dff<<"us"<<endl;

    //Step4:在H3下完成以下10个ops：
    resfile<<"H3"<<endl;

    QueryPerformanceFrequency(&large_interger);  
    dff = large_interger.QuadPart;  
    QueryPerformanceCounter(&large_interger);  
    c1 = large_interger.QuadPart;

    resfile<<util.Fib_Heap_Extract_Min(H3)<<","; 
    resfile<<util.Fib_Heap_Min(H3)<<",";
    resfile<<util.Fib_Heap_Insert(H3,262)<<","; 
    resfile<<util.Fib_Heap_Extract_Min(H3)<<",";
    resfile<<util.Fib_Heap_Insert(H3,830)<<",";
    resfile<<util.Fib_Heap_Min(H3)<<",";
    resfile<<util.Fib_Heap_Delete(H3,node_map[134])<<",";
    resfile<<util.Fib_Heap_Delete(H3,node_map[177])<<",";
    resfile<<util.Fib_Heap_Decrease_Key(H3,node_map[617],360)<<",";
    resfile<<util.Fib_Heap_Decrease_Key(H3,node_map[889],353)<<endl; 

    QueryPerformanceCounter(&large_interger);  
    c2 = large_interger.QuadPart; 
    timefile<<"step4的运行时间"<<(c2-c1)*1000000/dff<<"us"<<endl;

    //Step5:在H4下完成以下10个ops：

    QueryPerformanceFrequency(&large_interger);  
    dff = large_interger.QuadPart;  
    QueryPerformanceCounter(&large_interger);  
    c1 = large_interger.QuadPart;

    resfile<<"H4"<<endl;
    resfile<<util.Fib_Heap_Min(H4)<<","; 
    resfile<<util.Fib_Heap_Delete(H4,node_map[708])<<","; 
    resfile<<util.Fib_Heap_Insert(H4,281)<<",";
    resfile<<util.Fib_Heap_Insert(H4,347)<<",";
    resfile<<util.Fib_Heap_Min(H4)<<",";
    resfile<<util.Fib_Heap_Delete(H4,node_map[415])<<","; 
    resfile<<util.Fib_Heap_Extract_Min(H4)<<","; 
    resfile<<util.Fib_Heap_Decrease_Key(H4,node_map[620],354)<<",";
    resfile<<util.Fib_Heap_Decrease_Key(H4,node_map[410],80)<<","; 
    resfile<<util.Fib_Heap_Extract_Min(H4)<<endl;

    QueryPerformanceCounter(&large_interger);  
    c2 = large_interger.QuadPart; 
    timefile<<"step5的运行时间"<<(c2-c1)*1000000/dff<<"us"<<endl;

    //Step6:将H1-H4进行UNION成H5
    Heap* heap12=util.Fib_Heap_Union(H1,H2);
    Heap* heap123=util.Fib_Heap_Union(heap12,H3);
    Heap* H5=util.Fib_Heap_Union(heap123,H4);

    //Step7:在H5完成如下10个ops：

    QueryPerformanceFrequency(&large_interger);  
    dff = large_interger.QuadPart;  
    QueryPerformanceCounter(&large_interger);  
    c1 = large_interger.QuadPart;

    resfile<<"H5"<<endl;
    resfile<<util.Fib_Heap_Extract_Min(H5)<<","; 
    resfile<<util.Fib_Heap_Min(H5)<<","; 
    resfile<<util.Fib_Heap_Delete(H5,node_map[800])<<","; 
    resfile<<util.Fib_Heap_Insert(H5,267)<<",";
    resfile<<util.Fib_Heap_Insert(H5,351)<<","; 
    resfile<<util.Fib_Heap_Extract_Min(H5)<<","; 
    resfile<<util.Fib_Heap_Decrease_Key(H5,node_map[478],444)<<",";
    resfile<<util.Fib_Heap_Decrease_Key(H5,node_map[559],456)<<",";
    resfile<<util.Fib_Heap_Min(H5)<<","; 
    resfile<<util.Fib_Heap_Delete(H5,node_map[929])<<endl;

    QueryPerformanceCounter(&large_interger);  
    c2 = large_interger.QuadPart; 
    timefile<<"step7的运行时间"<<(c2-c1)*1000000/dff<<"us"<<endl;

    infile.close();
    resfile.close();
    timefile.close();
    return 0;
}