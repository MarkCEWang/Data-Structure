
#ifndef DISJOINT_SET_H
#define DISJOINT_SET_H

#ifndef nullptr
#define nullptr 0
#endif


#include <limits>
#include "Exception.h"

using namespace std;

struct ll_entry; // represents each element of the linked list
struct set_info; // keeps track of the information (pointers to head and tail and the size of the set) of each set
//could we delete the above two lines?


struct ll_entry{
    int content;
    set_info* ptr_to_info; // ptr to the info entry of the corresponding set
    ll_entry* next;
    
};

struct set_info {
    ll_entry* head;
    ll_entry* tail;
    int size;
};

class Disjoint_set {
    
private:
    ll_entry** nodes;
    set_info** sets;
    int set_counter;
    int initial_num_sets;
public:
    Disjoint_set(int);
    ~Disjoint_set();
    int find_set(int) const;
    int num_sets() const;
    void union_sets(int, int);
};

Disjoint_set::Disjoint_set(int n) : nodes(new ll_entry*[n]),
sets (new set_info*[n]),
set_counter(n),
initial_num_sets(n) {
    for (int i = 0; i < n; i++) {
        nodes[i] = new ll_entry;
        sets[i] = new set_info;
        nodes[i]->content = i;
        nodes[i]->ptr_to_info = sets[i];
        nodes[i]->next = nullptr;
        sets[i]->head = nodes[i];
        sets[i]->tail = nodes[i];
        sets[i]->size = 1;
    }
    // initialize the sets
}

Disjoint_set::~Disjoint_set() {
    for (int i = 0; i < initial_num_sets; i++){
        delete  nodes[i];
        delete  sets[i];
    }
    delete [] nodes;
    delete [] sets;
    set_counter = 0;
    
}
int Disjoint_set::find_set(int item) const{
    // should it be? return nodes[item]->ptr_to_info->head->content
    if (item < 0 || item > initial_num_sets) {
        throw illegal_argument();
    }
    return nodes[item]->ptr_to_info->head->content;
}

int Disjoint_set::num_sets() const {
    return set_counter;
}

void Disjoint_set::union_sets(int node_index1, int node_index2) {
    
    if (node_index1 == node_index2)
        return;
    
    set_info* si1 = nodes[node_index1]->ptr_to_info;
    set_info* si2 = nodes[node_index2]->ptr_to_info;
    
    // ni1: the index of the larger set, ni2: the index of the smaller index
    int ni1 = si1->size >= si2->size ? node_index1 : node_index2;
    int ni2 = si1->size < si2->size ? node_index1 : node_index2;
    /*
    while (nodes[ni2]) {
        nodes[ni2]->ptr_to_info = si1;
        nodes[ni2] = nodes[ni2]->next;
    }
    nodes[ni2]->ptr_to_info = si1;
    si1->size += si2->size;
    si1->tail->next = si2->head;
    si1->tail = si2->tail;
    
    set_counter--;*/
    nodes[ni1] -> ptr_to_info -> tail -> next = nodes[ni2] -> ptr_to_info -> head;
    nodes[ni1] -> ptr_to_info -> tail = nodes[ni2] -> ptr_to_info -> tail;
    nodes[ni1] -> ptr_to_info ->  size = nodes[ni1] -> ptr_to_info ->  size + nodes[ni2] -> ptr_to_info ->  size;
    ll_entry *cur = nodes[ni2]->ptr_to_info->head;
    while (cur != nullptr) {
        cur->ptr_to_info = nodes[ni1]->ptr_to_info;
        cur = cur->next;
    }
    set_counter--;
    //delete [] si2;
    
    
    /* iterate through the shorter list and modify the pointers
     while (has not reached the end of set) {
     
     }*/
    
    // do we need to modify anything else?
    
    
    // delete the set_info entry that no longer exists
    
    
}


#endif