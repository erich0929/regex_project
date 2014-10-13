#include "linked_list.h"
#include "Dfa.h"
#include <stdio.h>
#include <stdlib.h>
#include <iostream>

using namespace std;

template <class T>
linked_node<T>::linked_node (T* data) : next (NULL) {
	this -> data = data -> clone ();
}


template <class T>
linked_node<T>::~linked_node () {
	delete data;
}

template <class T>
T* linked_node<T>::getData () const {
    return (this -> data);    
}

template <class T>
void linked_node<T>::append (linked_node<T>* next) {
    this -> next = next;
}

template <class T>
linked_list<T>::linked_list () : head (NULL), current (NULL) {}

template <class T>
linked_list<T>::linked_list (linked_list<T>& source) {
	/* const 변수는 const 변수에만 대입가능 */
	source.setNewIterator ();
	Iterator<T>& iter = source;
	linked_node<T>* temp = NULL;
	if (iter.hasNext ()) {
		this -> head = new linked_node<T> (*iter.next ());
		temp = this -> head;
	}
	
	while (iter.hasNext ()) {
		temp -> next = new linked_node<T> (*iter.next ());
		temp = temp -> next;
	}
}

template <class T>
linked_list<T>::~linked_list () {
	linked_node <T>* iter = this -> head;
	linked_node <T>* temp;
	if (iter != NULL) {
		while (iter != NULL) {
			temp = iter -> next;
			delete iter;
			iter = temp;
		}
	} 
}

template <class T>
void linked_list<T>::insert (linked_node<T>* node) {
	
	/* 
	 * Warning !!
	 * linked_node 의 defualt 복사생성자를 이용해도 좋도록 
	 * linekd_node 의 멤버변수 data의 type인 class T의 대입연사자를
	 * 잘 대비해 놓아야 한다.
	 */
	 
	linked_node <T>* newNode = new linked_node<T> (*node);
    if (this -> head == NULL) {
        this -> head = newNode;
        this -> current = this -> head;
    } else {
        linked_node<T>* iter = this -> head;
        while (iter -> next != NULL) {
        	iter = iter -> next;
        }
        iter -> next = newNode;
    }
}

template <class T>
void linked_list<T>::insert (T* data) {
	
	/* 
	 * Warning !!
	 * linked_node 의 defualt 복사생성자를 이용해도 좋도록 
	 * linekd_node 의 멤버변수 data의 type인 class T의 대입연사자를
	 * 잘 대비해 놓아야 한다.
	 */
	 
	linked_node <T>* newNode = new linked_node<T> (data);
    if (this -> head == NULL) {
        this -> head = newNode;
        this -> current = this -> head;
    } else {
        linked_node<T>* iter = this -> head;
        while (iter -> next != NULL) {
        	iter = iter -> next;
        }
        iter -> next = newNode;
    }
}

template <class T>
void linked_list<T>::toString () {
	linked_node <T>* iter = this -> head;
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
template <class T>
bool linked_list<T>::hasNext () const {
	return (this -> current == NULL) ? false : true;
}

template <class T>
linked_node<T>* linked_list<T>::next () {
	linked_node<T>* res = this -> current;
	this -> current = this -> current -> next;
	return res;
}

template <class T>
void linked_list<T>::setNewIterator () {
	this -> current = this -> head;
}

/* 명시적 인스턴스화를 소스 구현 밑에 해야만 한다 */

template class linked_list <DfaNode>;
template class linked_node <DfaNode>;
template class Iterator <DfaNode>;

