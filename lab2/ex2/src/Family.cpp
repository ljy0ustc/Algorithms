#include<iostream>
#include<cstdio>
#include<fstream>
#include<unordered_map>
using namespace std;
class family_set
{
    public:
        int rank;
        family_set* p;
}
class Family
{
    public:
        +
        void MAKE_SET(family_set* x)
        {
            x->p = x;
            x->rank = 0;
        }
        void UNION(family_set* x, family_set* y)
        {
            this->LINK(this->FIND_SET(x),this->FIND_SET(y));
        }
    private:
        void LINK(family_set* x, family_set* y)
        {
            if(x->rank > y->rank)
            {
                y->p = x;
            }
            else
            {
                x->p = y;
                if(x->rank == y->rank)
                {
                    y->rank++;
                }
            }
        }
        void FIND_SET(family_set* x)
        {
            if(x != x->p)
            {
                x->p=FIND_SET(x->p);
            }
            return x->p;
        }
}
int main()
{
    ifstream infile;
    ofstream resfile;
    ofstream timefile;
    infile.open(".//ex2//input//2_2_input.txt", ios::in);
    resfile.open(".//ex2//output//result.txt", ios::out);
    timefile.open(".//ex2//output//time.txt", ios::out);
    for(int N = 10; N <= 30; N += 5)
    {
        std::unordered_map<int, family_set* > family_set_map;
        Family util;
        for(int i = 0; i< N; i++)
        {
            
            util.MAKE_SET({i, new_family_set});
        }
        for(int i = 0; i < N; i++)
        {
            for(int j = 0; j < N; j++)
            {
                if(i < j)
                {
                    util.UNION(family_set_map[i],family_set_map[j]);
                }
            }
        }
    }
    
    infile.close();
    resfile.close();
    timefile.close();
    return 0;
}