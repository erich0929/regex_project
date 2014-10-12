#ifndef _DFA_H_
#define _DFA_H_
#include "Ebuf.h"
#include "linked_list.h"

typedef bool UPPER;

class DfaNode {
	public : 
		virtual int match (Ebuf& ebuf, unsigned int startOffset) const = 0;
};

class SingleWordNode : public DfaNode {
	public :
		SingleWordNode (unsigned char from, unsigned char to, bool IsNotExp);
		int match (Ebuf& ebuf, unsigned int startOffset) const;
		
		SingleWordNode* getDotNode () const;
		/* 
		 * SingleWordNode 를 ConcatNode 로 연결해야 할 듯.
		 * SingleWordNode getAlphaNumber_Node (const UPPER IsUpper) const;
		 * SingleWordNode getWhiteSpaceNode (const UPPER IsUpper) const;
		 */
		SingleWordNode* getDigitNode (const UPPER IsUpper) const;
		SingleWordNode* getBoundaryNode (const UPPER IsUpper) const;
	
	private :
		const unsigned char from;
		const unsigned char to;
		const bool IsNotExp;
};

template <class T>
class ConcatNode : public DfaNode {
public :
	ConcatNode (linked_list<T>* token_list);
	~ConcatNode ();
	int match (Ebuf& ebuf, unsigned int startOffset) const;
	
private :
	const linked_list<T>* token_list;
	
};

#endif /* _DFA_H_ */
