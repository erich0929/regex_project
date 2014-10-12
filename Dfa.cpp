#include "Dfa.h"

SingleWordNode::SingleWordNode (unsigned char from, unsigned char to, bool IsNotExp)
	: from (from), to (to), IsNotExp (IsNotExp) {
	
}

int SingleWordNode::match (Ebuf& ebuf) const {
	unsigned char current = ebuf.getNext (0);
	bool IsAccept = false;
	
	if (current >=from && current <= to) IsAccept = true;
	IsNotExp ? IsAccept = !IsAccept : IsAccept;
	
	return IsAccept ? 1 : -1;
}

SingleWordNode* SingleWordNode::getDotNode () const {
	return new SingleWordNode ('\0', '\0', true);
}

SingleWordNode* SingleWordNode::getDigitNode (const UPPER IsUpper) const {
	return new SingleWordNode ('0', '9', IsUpper);
}

SingleWordNode* SingleWordNode::getBoundaryNode (const UPPER IsUpper) const {
	return new SingleWordNode (' ', ' ', IsUpper);
}














