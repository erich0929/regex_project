#include "Dfa.h"
#include "linked_list.h"
#include <stdio.h>

SingleWordNode::SingleWordNode (unsigned char from, unsigned char to, bool IsNotExp)
	: from (from), to (to), IsNotExp (IsNotExp) {
	
}

int SingleWordNode::match (Ebuf& ebuf, unsigned int startOffset) const {
	unsigned char current = ebuf.getNext (startOffset);
	bool IsAccept = false;
	
	if (current >=from && current <= to) IsAccept = true;
	IsNotExp ? IsAccept = !IsAccept : IsAccept;
	
	return IsAccept ? 1 : -1;
}

SingleWordNode* SingleWordNode::getDotNode () {
	return new SingleWordNode ('\0', '\0', true);
}

SingleWordNode* SingleWordNode::getDigitNode (const UPPER IsUpper) {
	return new SingleWordNode ('0', '9', IsUpper);
}

SingleWordNode* SingleWordNode::getBoundaryNode (const UPPER IsUpper)  {
	return new SingleWordNode (' ', ' ', IsUpper);
}

/* implement ConcatNode */
/* 
 * Warning !!
 * linked_list의 복사생성자를 이용하기 위해 
 * linked_list의 복사생성자가 잘 정의되어 있어야 한다.
 */
 
template <class T>
ConcatNode<T>::ConcatNode (linked_list<T>* token_list) : token_list (NULL) {
	this -> token_list = new linked_list<T> (*token_list); /* 복사생성자의 이용 */
}

template <class T>
ConcatNode<T>::~ConcatNode () {
	delete this -> token_list;
}

template <class T>
int ConcatNode<T>::match (Ebuf& ebuf, unsigned int startOffset) const {
	this -> token_list -> setNewIterator ();
	Iterator<T>& iter = *(this -> token_list);
	unsigned int acceptedOffset = 0;
	unsigned int offset = 0;
	linked_node<T>* temp;
	T* token;
	while (iter.hasNext ()) {
		temp = iter.next ();
		token = temp -> getData ();
		if ((offset = token -> match (ebuf, acceptedOffset)) == -1) return -1;
		acceptedOffset += offset;
	}
	return acceptedOffset;
}

template class ConcatNode<SingleWordNode>;












