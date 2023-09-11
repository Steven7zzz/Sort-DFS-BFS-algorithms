#include <iostream>
#include <vector>
#include <list>


// DFS
using std::vector;
using std::list;

// visted is 1, unvisted is 0

void DFS( const vector< list<int> >& graph, int curr, vector<int>& visited, int& step){ // if need to update values in function pass by &
    std::cout << "Step " << step << " : vsisting " << curr << std::endl;
    step++;

    visited.at(curr) = 1;

    // iterate the adjacency list at current vetex !!!
    for (auto& v : graph.at(curr)){

        // if not visited, run dfs in it
        if ( !visited.at(v) ){
            DFS(graph, v, visited, step);
        } 
    } 

    std::cout << "Step " << step << " : " << curr << " is finished" << std::endl;    
    step++;
}

void printDFS( const vector< list<int> >& graph, int start ){

    // vector with all vectices default to 0
    vector<int> visited(graph.size());
    int step = 0;

    DFS(graph, start, visited, step);

    // need this if the grapg is disconnected
    // check if there is any unvisted vertex
    for (int v = 0 ; v < graph.size(); v++){

        // run dfs on those
        if(!visited.at(v)){
            std::cout << "found disconnected vertex"<< std::endl;
            DFS(graph, v, visited, step);
        }
    }

}

#include <queue> // for BFS

void BFS( const vector< list<int> >& graph, int start, vector<int>& visited, int& step){ // if need to update values in function pass by &

    // use queue to visit closest first
    std::queue<int> q;

    q.push(start);
    visited.at(start)=1;

    // run untill no connected
    while(!q.empty()){

        // check adj vertex
        int curr = q.front();
        std::cout << "Step " << step << " : vsisting " << curr << std::endl;
        step++;
        q.pop(); // visited

        for (auto & v : graph.at(curr)){

            // if not visited, add to queue
            if(!visited.at(v)){
                q.push(v);
                visited.at(v) = 1;
            }
        }
    }
}



void printBFS( const vector< list<int> >& graph, int start ){
    int step = 0;

    vector<int> visited(graph.size());

    BFS(graph, start, visited, step);

    for (int v = 0 ; v < graph.size(); v++){

        if(!visited.at(v)){
            std::cout << "found disconnected vertex?"<< std::endl;
            BFS(graph, v, visited, step);
        }
    }

}


// toplogical
#include <stack>

void sortTill(int v, vector<int>& visited, std::stack<int>& s, const vector< list<int> >& graph){
    visited.at(v) = 1;

    for(auto i : graph.at(v)) {
        if (!visited.at(i)){
            sortTill(i, visited, s, graph);
        }
    }

    s.push(v);
}

void topS( const vector< list<int> >& graph){
    std::stack<int> s;

    vector<int> visited(graph.size());

    for (int i = 0; i < graph.size(); i++){
        if (!visited.at(i)){
            sortTill(i, visited, s, graph);
        }
    }

    while (!s.empty()){ // print 
        std::cout << s.top() << std::endl;
        s.pop();
    }

}




int main(){

    std::cout << "DFS on graph1 " << std::endl;
    vector<list<int>> graph1 = {
        {1},    // adj to 0
        {2},    // adj to 1
        {4},    // adj to 2
        {0,4},  // adj to 3
        {1},     // adj to 4
    };

    printDFS(graph1, 0);
    std::cout << std::endl;

    std::cout << "BFS on graph2 " << std::endl;
    vector<list<int>> graph2 = {
        {1, 4}, {0, 2, 5}, {1, 3, 6}, {2, 7},
        {0, 5, 8}, {1,4,6,9}, {2,5,7,10}, {3,6,11},
        {4,9,12}, {5,8,10,13}, {6,9,11,14}, {7,10,15},
        {8,13}, {9,12,14}, {10,13,15}, {11,14}
    };

    printDFS(graph2, 0);
    std::cout << std::endl;


    std::cout << "topological on graph3 " << std::endl;
    vector<list<int>> graph3 = {
        {},    // adj to 0
        {},    // adj to 1
        {3},    // adj to 2
        {1},  // adj to 3
        {0,1},     // adj to 4
        {2,0}
    };

    topS(graph3);
    std::cout << std::endl;

    printDFS(graph2, 0);
    return 0;
}