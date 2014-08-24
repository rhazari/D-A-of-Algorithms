#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <cmath>
#include <vector>
#include <map>

#define MAX 1000000.0

using namespace std;

//Gosper's Hack for generating all possible subsets 
//of a subproblem
vector<int> gosper(int k, int n)
{
    vector<int> vec;
    int set = (1 << k) - 1;
    int limit = (1 << n);
    while (set < limit) 
    {
        vec.push_back(set);
        int c = set & -set;
        int r = set + c;
        set = (((r^set) >> 2) / c) | r;
    }
    return vec;
}

//Find the indices of the set bits
vector<int> func(int val)
{
    vector<int> vec;
    int rd, idx = 0; 
    while(val)
    {
        rd = (val) & 1;
        if(rd == 1)
        {
            vec.push_back(idx);
        }
        idx++;        
        val = val>>1;
    }
    return vec;
}

int main(int argc, char* argv[])
{
    if(argc != 2)
    {
        cout<<"Enter text file..."<<endl;
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
    
    int num_city;
    fscanf(file,"%d",&num_city);
    cout <<"\nNumber of Cities: "<<num_city<<endl;
    cout<< endl;
    
    //Reading the X and Y co-ordinates from the file for the TSP travel
    float x_cor, y_cor; 
    int index = 0, read = 1;
    float *arr = (float*)malloc(sizeof(int)*num_city*2);
    while(read)
    {
        if(fscanf(file,"%f %f",&x_cor, &y_cor)!= 2)
        {
            read = 0;
            fclose(file);
            break;
        }
        arr[index++] = x_cor;
        arr[index++] = y_cor;
    }
    
    int k, j;
    /*for(k = 0; k < num_city; k++)
    {
        cout<<arr[2*k]<<" "<<arr[2*k+1]<<endl;
    }*/
    
    //Adjacency Matrix of distances between the points of the TSP travel
    float *adjMat = (float*)malloc((num_city)*(num_city)*sizeof(float));
    for(k = 0; k <num_city; k++)
    {
        for(j = 0; j<num_city; j++)
        {
            if(k == j)
            {
                *(adjMat+k*(num_city)+j) = 0;
            }
            else
            {
                *(adjMat+k*(num_city)+j) = sqrt(pow(arr[2*k]-arr[2*j],2.0)+pow(arr[2*k+1]-arr[2*j+1],2.0));  
                
            }                  
        }
    }
    
    //Dynamic Programming Solution to the TSP problem
    int m, S, a;
    double min;
    map<int,double> tsp_map;
    vector<int> vc;
    vector<int> idx;
    vector<int> pk;
    tsp_map[0] = 0.0;
    for(m = 1; m <= num_city; m++)
    {
		cout<<"Sub-Problem Size: "<<m<<endl;
        vc = gosper(m,num_city-1);
        for (vector<int>:: iterator it = vc.begin(); it != vc.end(); ++it)
        {
            idx = func((*it));
            for (vector<int>:: iterator itr = idx.begin(); itr != idx.end(); ++itr)
            {
                j = (*itr);    
                k = (*it)^(1<<j);
                //S = (*it) | (1<<(num_city+j));
			    S = (*it) | (j+1)<<(num_city-1);
                //cout<<k<<"\t";
                if(k == 0)
                {
                    tsp_map[S] = tsp_map.find(k)->second + *(adjMat+k*num_city+j+1);     
                }
                else
                {
                    pk = func(k);
                    min = MAX;
                    for(vector<int>::iterator itr2 = pk.begin(); itr2 != pk.end(); ++itr2)
                    {
                        a = k | ((*itr2)+1)<<(num_city-1);
                        //cout<<a<<"\t";
                        if(min > tsp_map.find(a)->second + *(adjMat+(*itr2+1)*num_city+j+1))
                        {
                            min = tsp_map.find(a)->second + *(adjMat+(*itr2+1)*num_city+j+1);
                        }
                    }
                    tsp_map[S] = min;
                }                 
            }   
        }
        //Deleting data from subproblems of size (m-2) and less 
		if (m >= 3)
		{
		    vc = gosper(m-2,num_city-1);
			for(vector<int>:: iterator it = vc.begin(); it != vc.end(); ++it)
			{
			    idx = func((*it));
				for (vector<int>:: iterator itr = idx.begin(); itr != idx.end(); ++itr)
				{
					S = (*it) | ((*itr)+1)<<(num_city-1);
					tsp_map.erase(S);
				}
			}
		 }	
    }
    
    //The Final Step: Completing the tour (& heading to the origin)
    int ty = (1<<num_city-1)-1;
    pk = func(ty);
    min = MAX;
    for(vector<int>::iterator itr = pk.begin(); itr != pk.end(); ++itr)
    {
		S = ty|((*itr)+1)<<(num_city-1);
        if(min > tsp_map.find(S)->second + *(adjMat+(*itr+1)*num_city))
        {
            min = tsp_map.find(S)->second + *(adjMat+(*itr+1)*num_city);
        }   
    }
    
    cout <<"\nThe minimum cost path travel: "<<min <<endl;    
       
    return 0;
}
