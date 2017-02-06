//Samantha Lee 

#include <set>
#include <cstdlib>
#include "paths.h"
#include <utility>
#include <algorithm>
#include <iostream>
#include <string>
#include <queue>


// Preconditions: distances and paths vectors are large
// enough to contain g.size() elements, and start is less
// than g.size().
// Postconditions: distances filled with shortest distances
// from start vertex of g to all other vertices. If no path
// exists to vertex i, then distances[i] is set to INF. Also
// paths[i] is a list of vertex numbers showing the path
// from start  to vertex i (empty list means no path exists).


void shortest(wtdgraph<string> &g, size_t start, vector<size_t> &distances, vector<list<size_t>> &paths) {
	for(size_t i = 0; i < distances.size(); ++i) {
        distances[i] = INF;
    }
    
    distances[start] = 0;
    std::set<size_t> allowed_vertices;
    size_t next = start;
    allowed_vertices.insert(start);
    //size_t predecessors[g.size()];

    for(size_t allowed_size = 1; allowed_size <= g.size(); ++allowed_size) {
        paths[next].push_back(next);
        
        for(size_t v = 0; v < g.size(); ++v)
        {
            if(g.is_edge(next, v))
            {  
                size_t sum = distances[next] + g.edge_weight(next, v);
                if(sum < distances[v])
                {
                    distances[v] = sum;
                    paths[v] = paths[next];
                    
                }
            }
        }


        //step3a: find next closest vertex
        size_t min = INF;
        for(size_t i = 0; i < distances.size(); ++i)
        {
            if(allowed_vertices.find(i) == allowed_vertices.end())
            {
                if(distances[i] < min)
                {
                    min = distances[i];
                    next = i;
                    //paths[i] = paths[next];
                }
            }
        }


        //step3b: add next closest to set of allowed vertices
        allowed_vertices.insert(next);


    }

    for(size_t i = 0; i < paths.size(); ++i)
    {
        paths[i].unique();
    }

}

//(1) distances[start] should be 0; 
//(2) if vertex v is reachable from the start vertex, then distances[v] should be the shortest distance from start to v; 
//(3) if there is no path from start to v, then distances[v] should be set to INF (the constant defined in paths.h to represent infinity).

//Finish implementing function shortest to fill the vector named paths with lists of vertex numbers representing paths from the start vertex to other vertices.
// If there is no path from vertex start to vertex v, then paths[v] is an empty list. 
//Otherwise, paths[v] is a list of vertex numbers ordered to show the path from start to v, inclusive.
