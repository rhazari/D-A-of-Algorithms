#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <vector>
#include <map>

using namespace std;

typedef map<int,vector<int> > graph;
typedef map<int, int> vf;

graph fwd_graph;
graph rev_graph;

vf fwd_visit;
vf rev_visit;
vf finish_time;
vf leader;

//Value of the leader in the SCC
int S;

//Completion time in the reverese graph
int T = 0;
void rev_dfs(int key)
{
	rev_visit[key] = 1;
	
	for(vector<int>::iterator it = rev_graph[key].begin(); it != rev_graph[key].end(); ++it)
	{
		if(rev_visit[(*it)] == 0)
		{
			rev_dfs((*it));
		}
	}
	finish_time[++T] = key;	
}

void fwd_dfs(int key)
{
	fwd_visit[key] = 1;
	leader[key] = S;

	for(vector<int>:: iterator it = fwd_graph[key].begin(); it != fwd_graph[key].end(); ++it)
	{
		if(fwd_visit[(*it)] == 0)
		{
			fwd_dfs((*it));
		}
	}
}

int main(int agc, char* argv[])
{
    if(agc != 2)
    {
        cout<<"Enter the text file...!!!\n";
        return 2;
    }
    
    char* infile = argv[1];
    
    //Open the input file
    FILE* file = fopen(infile,"r");
    if(file == NULL)
    {
        printf("Cannot open file. Exiting...\n");
        return 2;
    }
    
    int num_vars;
    fscanf(file,"%d",&num_vars);
    cout <<"Number of variables & clauses: "<<num_vars <<endl;
   
    int read = 1;
    int x, y;
    
    //Reading from the file
    //Generating the forward and the reverse graphs
    while(read)
    {
        if(fscanf(file,"%d %d",&x, &y)!= 2)
        {
            read = 0;
            fclose(file);
            break;
        }
        
        //Forward Graph
        fwd_graph[-x].push_back(y);
        fwd_visit[y] = 0;
        fwd_graph[-y].push_back(x);
        fwd_visit[x] = 0;

        //Reverse Graph
        rev_graph[y].push_back(-x);
        rev_visit[-x] = 0;
        rev_graph[x].push_back(-y);
        rev_visit[-y] = 0;
                
    }
    
    /*for(map<int,vector<int> >:: iterator itr = fwd_graph.begin(); itr != fwd_graph.end(); itr++)
    {
        cout<< itr->first<<": ";
        for(vector<int> :: iterator it = itr->second.begin(); it != itr->second.end(); it++)
        {
            cout << (*it)<<" ";
        }
        cout << endl;
    }*/
 	//cout<<endl; 

	/*for(map<int,vector<int> >:: iterator itr = rev_graph.begin(); itr != rev_graph.end(); itr++)
    {
        cout<< itr->first<<": ";
        for(vector<int> :: iterator it = itr->second.begin(); it != itr->second.end(); it++)
        {
            cout << (*it)<<" ";
        }
        cout << endl;
    }*/

    //Depth first search on the reverse graph
    //Finding the completion times at the vertices
	for(map<int,vector<int> >:: reverse_iterator itr = rev_graph.rbegin(); itr != rev_graph.rend(); ++itr)
	{
		if(rev_visit[itr->first] == 0)
		{
			rev_dfs(itr->first);
		}
	}
	
	//Depth first search on the forward graph
	//Finding the leader vertex on each SCC
	for(map<int,int>::reverse_iterator it = finish_time.rbegin(); it != finish_time.rend(); ++it)
	{
		if(fwd_visit[it->second] == 0)
		{
			S = it->second;  
			fwd_dfs(it->second);			
		}
	}
	
	int index, flag = 0;
	//If v & ~v have the same leader vertex then they lie on the same SCC, hence not satisfiable
	//Else ...
	for(map<int,int>:: iterator it = leader.begin(); it != leader.end(); ++it)
	{
		index = it->first;
		if((leader.count(index)==leader.count(-index)) &&(leader[index] == leader[-index]))
		{	
			flag = 1;
			break;
		}
	}

	if(flag)
	{
		cout<<"\nNot Satisfiable\n";	
	}
	else
	{
		cout<<"\nSatisfiable\n";
	}   
    return 0;
}
