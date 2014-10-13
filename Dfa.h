#ifndef _DFA_H_
#define _DFA_H_
#include "Ebuf.h"
#include "linked_list.h"

typedef bool UPPER;
class linked_list;

class DfaNode {
public:
	virtual int match(Ebuf& ebuf, unsigned int startOffset) const = 0;
	virtual DfaNode* clone () = 0;
};

class SingleWordNode : public DfaNode {
public:
	SingleWordNode(unsigned char from, unsigned char to, bool IsNotExp);
	
	/* implement DfaNode */
	int match(Ebuf& ebuf, unsigned int startOffset) const;
	DfaNode* clone ();
	
	static DfaNode* getDotNode();
	/* 
	 * SingleWordNode 를 ConcatNode 로 연결해야 할 듯.
	 * SingleWordNode getAlphaNumber_Node (const UPPER IsUpper) const;
	 * SingleWordNode getWhiteSpaceNode (const UPPER IsUpper) const;
	 */
	static DfaNode* getDigitNode(const UPPER IsUpper);
	static SingleWordNode* getBoundaryNode(const UPPER IsUpper);

private:
	const unsigned char from;
	const unsigned char to;
	const bool IsNotExp;
};


class ConcatNode : public DfaNode {
public:
	ConcatNode(linked_list* token_list);
	~ConcatNode();
	
	int match(Ebuf& ebuf, unsigned int startOffset) const;
	DfaNode* clone ();
	
private:
	linked_list* token_list;

};

/*
class StarNode : public DfaNode {
public:
	StarNode (DfaNode* token);
	~StarNode ();
	int match (Ebuf& buf, unsigned int startOffset);
	DfaNode* clone ();
private:
	DfaNode* token;
};
*/
#endif /* _DFA_H_ */
