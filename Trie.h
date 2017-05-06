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

#ifndef TRIE_H
#define TRIE_H

#ifndef nullptr
#define nullptr 0
#endif

#include "ece250.h"
#include "Trie_node.h"
#include "Exception.h"
#include <iostream>
#include <string>
#include <cctype>

class Trie {
	private:
		Trie_node *root_node;
		int trie_size;

	public:
		Trie();
		~Trie();

		// Accessors

		int size() const;
		bool empty() const;
		bool member( std::string const & ) const;
		Trie_node *root() const;
		// Mutators

		bool insert( std::string const & );
		bool erase( std::string const & );
		void clear();

	// Friends

	friend std::ostream &operator<<( std::ostream &, Trie const & );
};

Trie::Trie():
root_node( nullptr ),
trie_size( 0 ) {
	// empty constructor
}

Trie::~Trie() {
	clear();
	//if (root_node->children != nullptr) {
	//	root_node->children = nullptr;
	//}
	//delete root_node;
}

int Trie::size() const {
	return trie_size;
}

bool Trie::empty() const {
	return trie_size == 0;
}

Trie_node *Trie::root() const {
	return root_node;
}

bool Trie::member( std::string const &str ) const {
	if (empty()) {
		return false;
	}
	for (int i = 0; i < str.length(); i++) {
		if (!isalpha(str[i])) {
			throw illegal_argument();
		}
	}
	return root_node->member(str,0);
}

bool Trie::insert( std::string const &str ) {

	for (int i = 0; i < str.length(); i++) {
		if (!isalpha(str[i])) {
			throw illegal_argument();
		}
	}
    if (member(str)){
        return false;
    }
    if (root_node == nullptr){
    	root_node = new Trie_node();
    }
    trie_size++;
	return root_node->insert(str, 0);
	
}

bool Trie::erase( std::string const &str ) {
	for (int i = 0; i < str.length(); i++) {
		if (!isalpha(str[i])) {
			throw illegal_argument();
		}
	}
    if (!member(str)){
        return false;
    }
    char letter = str[0];
    int cur = letter;
    if (cur >= 'A' && cur <= 'Z'){
        cur +=32;
    }
    cur -= 97;
	if (root_node->erase(str, 0, root_node)) {
		//root_node->children[cur] = nullptr;
		trie_size--;
		return true;
	}
	return false;
}

void Trie::clear() {
	if (root_node == nullptr) {
		return;
	}
	trie_size = 0;
	root_node->clear();
		//delete [] root_node->children;
		//root_node->children = nullptr;

	delete root_node;
	
	root_node = nullptr;
}

// You can modify this function however you want:  it will not be tested

std::ostream &operator<<( std::ostream &out, Trie const &trie ) {

	return out;
}

// Is an error showing up in ece250.h or elsewhere?
// Did you forget a closing '}' ?

#endif
