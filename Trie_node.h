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

#ifndef SINGLE_NODE_H
#define SINGLE_NODE_H

#ifndef nullptr
#define nullptr 0
#endif

#include <string>
#include <cctype>
#include "ece250.h"

class Trie;

class Trie_node {
private:
    Trie_node **children;
    bool is_terminal;
    static int const CHARACTERS = 26;
    
    
public:
    Trie_node();
    Trie_node *child( int ) const;
    
    bool member( std::string const &, int ) const;
    //string convertLowerCase(std:: string const &str);
    bool insert( std::string const &, int );
    bool erase( std::string const &, int, Trie_node *& );
    void clear();
    
    friend class Trie;
    
    // if ptr is a pointer to a Trie_node object
    // in one of the friendly classes, you should:
    //    use   ptr->next_   to modify it
    //    use   ptr->next()      to access it
};

Trie_node::Trie_node():
children( nullptr ),
is_terminal( false ) {
    // empty constructor
}

Trie_node *Trie_node::child( int n ) const {
    if ( children == nullptr ) {
        return nullptr;
    } else {
        if (n > 0 && n < CHARACTERS) {
            return children[n];
        }
    }
}

//std::string Trie_node::convertLowerCase( std:: string const &str) const{
 //   for (int i = 0; i < str.length(); i++) {
   //     str[i] = std::tolower(str[i]);
//    }
 //  return str;
//}


bool Trie_node::member( std::string const &str, int depth ) const {
    char letter = str[depth];
    int cur = letter;
    if (cur >= 'A' && cur <= 'Z'){
        cur +=32;
    }
    cur -= 97;
    //std::cout <<"cur: " << cur << std::endl;
    if (depth == str.length()){
        return this->is_terminal;
    }
    if (this->children == nullptr){
        return false;
    }
    else if (this->children[cur] == nullptr){
        return false;
    }
    return this->children[cur]->member(str,depth+1);
    
}

bool Trie_node::insert( std::string const &str, int depth ) {
    if (depth == str.length()) {
		this->is_terminal = true;
		return true;
    }
    char letter = str[depth];
    int cur = letter;
    if (cur >= 'A' && cur <= 'Z'){
        cur +=32;
    }
    cur -= 97;
	if (this->children == nullptr) {
		children = new Trie_node*[CHARACTERS];
        for (int i = 0; i < CHARACTERS; i++){
            this->children[i] = nullptr;
        }
	}
    if (this->children[cur] == nullptr) {
		this->children[cur] = new Trie_node();
     }
	
    return this->children[cur]->insert(str,depth+1);
        

}

bool Trie_node::erase(std::string const &str, int depth, Trie_node *&ptr_to_this) {
	char letter = str[depth];
    int cur = letter;
    if (cur >= 'A' && cur <= 'Z'){
        cur +=32;
    }
    cur -= 97;
	bool flag = false;
    bool val = true;
		if (depth == str.length()) {
			
			if (children != nullptr) {
				this->is_terminal = false;
			}
			else {
                //delete [] this->children;
                //this->children = nullptr;
                delete this;
                ptr_to_this = nullptr;
			}
            return true;
		}
		else {
			//ptr_to_this = this->children[cur];
            children[cur]->erase(str, depth+1, children[cur]);
            flag = false;
            for (int i = 0; i < CHARACTERS; i++) {
                if (this->children[i] != nullptr) {
                    flag = true;
                }
            }
            if ((!flag) && (!this->is_terminal)){
                delete [] this->children;
                this->children = nullptr;
                delete this;
                ptr_to_this = nullptr;
            }
            return true;
		}
}


void Trie_node::clear() {
	if (this->children != nullptr) {
	 for(int i = 0; i < CHARACTERS; i++){
			if (this->children[i] != nullptr){
				this->children[i]->clear();
                delete this->children[i];
                this->children[i] = nullptr;
			}
		}
        delete [] this->children;
        this->children = nullptr;
	} 
}


// Is an error showing up in ece250.h or elsewhere?
// Did you forget a closing '}' ?

#endif