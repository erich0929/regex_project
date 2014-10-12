#ifndef _DFA_H_
#define _DFA_H_
#include "Ebuf.h"

typedef bool UPPER;

class Dfa_node {
	public : 
		virtual int match (Ebuf& ebuf) const = 0;
};

class SingleWordNode : Dfa_node {
	public :
		SingleWordNode (unsigned char from, unsigned char to, bool IsNotExp);
		int match (Ebuf& ebuf) const;
		
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

#endif /* _DFA_H_ */
