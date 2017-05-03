
/*****************************************
 * Instructions
 *  - Replace 'uwuserid' with your uWaterloo User ID
 *  - Select the current calendar term and enter the year
 *  - List students with whom you had discussions and who helped you
 *
 * uWaterloo User ID:  uwuserid @uwaterloo.ca
 * Submitted for ECE 250
 * Department of Electrical and Computer Engineering
 * University of Waterloo
 * Calender Term of Submission:  (Winter|Spring|Fall) 201N
 *
 * By submitting this file, I affirm that
 * I am the author of all modifications to
 * the provided code.
 *
 * The following is a list of uWaterloo User IDs of those students
 * I had discussions with in preparing this project:
 *    -
 *
 * The following is a list of uWaterloo User IDs of those students
 * who helped me with this project (describe their help; e.g., debugging):
 *    -
 *****************************************/

#ifndef WEIGHTED_GRAPH_H
#define WEIGHTED_GRAPH_H

#ifndef nullptr
#define nullptr 0
#endif

#include <iostream>
#include <limits>
#include <utility>
#include "Exception.h"
#include "Disjoint_sets.h"

using namespace std;

class Weighted_graph {
private:
    static const double INF;
    double** graph;
    int num_nodes;
    int num_edges;
    
    
    // Do not implement these functions!
    // By making these private and not implementing them, any attempt
    // to make copies or assignments will result in errors
    Weighted_graph( Weighted_graph const & );
    Weighted_graph &operator=( Weighted_graph );
    
    // your choice
    
public:
    Weighted_graph( int = 10 );
    ~Weighted_graph();
    
    int degree( int ) const;
    int edge_count() const;
    std::pair<double, int> minimum_spanning_tree() const;
    
    bool insert_edge( int, int, double );
    bool erase_edge( int, int );
    void clear_edges();
    
    // Friends
    
    friend std::ostream &operator<<( std::ostream &, Weighted_graph const & );
};

const double Weighted_graph::INF = std::numeric_limits<double>::infinity();

Weighted_graph::Weighted_graph(int n ) {
    num_nodes = n;
    num_edges = 0;
    if (n <= 0) {
        throw illegal_argument();
    }
    graph = new double *[n];
    for (int i = 0; i < n; i++) {
        graph[i] = new double[n];
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            graph[i][j] = INF;
        }
    }
    for (int i = 0; i < n; i++) {
        graph[i][i] = 0;
    }
    
    



    
}

Weighted_graph::~Weighted_graph() {
    for (int i = 0; i < num_nodes; i++) {
        delete [] graph[i];
    }
    delete [] graph;
}

int Weighted_graph::degree(int u) const {
    if (u < 0 || u >= num_nodes) {
        throw illegal_argument();
    }
    int degree_num = 0;
    for (int i = 0; i < num_nodes; i++){
        if (graph[u][i] != INF){
            degree_num++;
        }
    }
    
    return degree_num -1;
    
}

int Weighted_graph::edge_count() const {
    return num_edges;
}

bool Weighted_graph::erase_edge(int i, int j) {
    if (i < 0 || i > num_nodes || j < 0 || j > num_nodes) {
        throw illegal_argument();
    }
    if (i == j) {
        return true;
    } else if (graph[i][j] != INF) {
        graph[i][j] = INF;
        graph[j][i] = INF;
        num_edges--;
        return true;
    }
    return false;
}

void Weighted_graph::clear_edges() {
    for (int i = 0; i < num_nodes; i++) {
        for (int j = 0; j < num_nodes; j++) {
            graph[i][j] = INF;
        }
    }
    for (int i = 0; i < num_nodes; i++) {
        graph[i][i] = 0;
    }
    num_edges = 0;
    return;
}

bool Weighted_graph::insert_edge( int i, int j, double d ) {
    if (i < 0 || i >= num_nodes || j < 0 || j >= num_nodes || d <= 0) {
        throw illegal_argument();
    }
    if (i == j){
        return false;
    } else {
        if (graph[i][j] == INF) {
            num_edges++;
        }
        graph[i][j] = d;
        graph[j][i] = d;
        
        return true;
    }
    
}

std::pair<double, int> Weighted_graph::minimum_spanning_tree() const {
    int pair_size = num_nodes*(num_nodes-1)/2;
    int count = 0;
    int pos_min;
    double total_weight = 0;
    int total_edges = 0;
    std::pair<int,int> temp;
    std::pair<int,int> *edges;
    edges = new std::pair<int, int> [pair_size];
    for (int i = 0; i < num_nodes-1; i++) {
        for (int j =  i+1; j < num_nodes; j++){
            edges[count] = make_pair(i,j);
            count++;
        }
    }
    for (int i = 0; i < pair_size; i++){
        for (int j = i+1; j < pair_size; j++){
            if (graph[edges[i].first][edges[i].second] > graph[edges[j].first][edges[j].second]){
                temp = edges[i];
                edges[i] = edges[j];
                edges[j] = temp;
            }
        }
        
    }
    //for (int i = 0; i < pair_size; i++){
    //    std::cout << edges[i].first<< " " << edges[i].second <<" "<< graph[edges[i].first][edges[i].second]<< endl;
    //}
    Disjoint_set *set = new Disjoint_set(num_nodes);
    std::pair<int,int> cur;
    for (int i = 0; i < pair_size; i++) {
        if ((set->find_set(edges[i].first) != set->find_set(edges[i].second))&&(graph[edges[i].first][edges[i].second]!= INF)){
            set->union_sets(edges[i].first, edges[i].second);
            total_weight += graph[edges[i].first][edges[i].second];
            cur = edges[i];
        }
    }
    int new_count = 0;
    while (edges[new_count] != cur){
        total_edges++;
        new_count++;
    }
    delete set;
    delete [] edges;
    
    
    return std::pair<double, int>( total_weight, total_edges+1 );
}

std::ostream &operator<<( std::ostream &out, Weighted_graph const &graph ) {
    
    
    return out;
}


#endif