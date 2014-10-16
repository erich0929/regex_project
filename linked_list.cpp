#include "linked_list.h"
#include "Dfa.h"
#include <stdio.h>
#include <stdlib.h>
#include <iostream>

using namespace std;


linked_node::linked_node (DfaNode* data) : next (NULL) {
	this -> data = data -> clone ();
}



linked_node::~linked_node () {
	delete data;
}


DfaNode* linked_node::getData () const {
    return (this -> data);    
}


void linked_node::append (linked_node* next) {
    this -> next = next;
}


linked_list::linked_list () : head (NULL), current (NULL) {}


linked_list::linked_list (linked_list& source) {
	/* const 변수는 const 변수에만 대입가능 */
	source.setNewIterator ();
	Iterator& iter = source;
	linked_node* temp = NULL;
	if (iter.hasNext ()) {
		this -> head = new linked_node (*iter.next ());
		temp = this -> head;
	}
	
	while (iter.hasNext ()) {
		temp -> next = new linked_node (*iter.next ());
		temp = temp -> next;
	}
}


linked_list::~linked_list () {
	linked_node* iter = this -> head;
	linked_node* temp;
	if (iter != NULL) {
		while (iter != NULL) {
			temp = iter -> next;
			delete iter;
			iter = temp;
		}
	} 
}


void linked_list::insert (linked_node* node) {
	
	/* 
	 * Warning !!
	 * linked_node 의 defualt 복사생성자를 이용해도 좋도록 
	 * linekd_node 의 멤버변수 data의 type인 class DfaNode의 대입연사자를
	 * 잘 대비해 놓아야 한다.
	 */
	 
	linked_node* newNode = new linked_node (*node);
    if (this -> head == NULL) {
        this -> head = newNode;
        this -> current = this -> head;
    } else {
        linked_node* iter = this -> head;
        while (iter -> next != NULL) {
        	iter = iter -> next;
        }
        iter -> next = newNode;
    }
}


void linked_list::insert (DfaNode* data) {
	
	/* 
	 * Warning !!
	 * linked_node 의 defualt 복사생성자를 이용해도 좋도록 
	 * linekd_node 의 멤버변수 data의 type인 class DfaNode의 대입연사자를
	 * 잘 대비해 놓아야 한다.
	 */
	 
	linked_node * newNode = new linked_node (data);
    if (this -> head == NULL) {
        this -> head = newNode;
        this -> current = this -> head;
    } else {
        linked_node* iter = this -> head;
        while (iter -> next != NULL) {
        	iter = iter -> next;
        }
        iter -> next = newNode;
    }
}


void linked_list::toString () {
	linked_node * iter = this -> head;
	unsigned int count = 1; 
	if (head != NULL) {
		cout << "Linked_list : {" << endl;
		while (iter != NULL) {
			cout << "\t" << count ++ << "th node : " << iter -> getData () << endl;
			iter = iter -> next;
		}
		cout << "}" << endl;
	}
}

/* implement Iterator Interface */

bool linked_list::hasNext () const {
	return (this -> current == NULL) ? false : true;
}


linked_node* linked_list::next () {
	linked_node* res = this -> current;
	this -> current = this -> current -> next;
	return res;
}


void linked_list::setNewIterator () {
	this -> current = this -> head;
}

/* 명시적 인스턴스화를 소스 구현 밑에 해야만 한다 */

//template class linked_list ;
//template class linked_node ;
//template class Iterator ;

