#ifndef _DFA_H_
#define _DFA_H_
#include "Ebuf.h"
#include "linked_list.h"

typedef bool UPPER;
typedef unsigned int OFFSET;
typedef unsigned char UCHAR;
class linked_list;

class DfaNode {
public:
	virtual int match(Ebuf& ebuf, OFFSET startOffset, Ebuf* lazyChar) const = 0;
	virtual DfaNode* clone () = 0;
};

class SingleWordNode : public DfaNode {
public:
	SingleWordNode(UCHAR* from, UCHAR* to, bool IsNotExp, bool IsRange);
	SingleWordNode (Ebuf* from, Ebuf* to, bool IsNotExp, bool IsRange);
	SingleWordNode (SingleWordNode& source);
	~SingleWordNode ();
	/* implement DfaNode */
	int match(Ebuf& ebuf, OFFSET startOffset, Ebuf* lazyChar) const;
	
	DfaNode* clone ();
	
	static DfaNode* getDotNode();
	/* 
	 * SingleWordNode 를 ConcatNode 로 연결해야 할 듯.
	 * SingleWordNode getAlphaNumber_Node (const UPPER IsUpper) const;
	 * SingleWordNode getWhiteSpaceNode (const UPPER IsUpper) const;
	 */
	static DfaNode* getDigitNode(const UPPER IsUpper);
	static SingleWordNode* getBoundaryNode(const UPPER IsUpper);


	Ebuf* from;
	Ebuf* to;
	//unsigned int m_length;
	bool IsNotExp;
	bool IsUTF8;
	bool IsRange;
};


class ConcatNode : public DfaNode {
public:
	ConcatNode(linked_list* token_list);
	virtual ~ConcatNode();
	
	virtual int match (Ebuf& ebuf, OFFSET startOffset, Ebuf* lazyChar) const;
	virtual DfaNode* clone ();
	
protected:
	linked_list* token_list;

};

class AlterNode : public ConcatNode {
public :
	AlterNode (linked_list* token_list, bool IsNotExp);
	AlterNode (AlterNode& source);
	~AlterNode ();
	int match (Ebuf& ebuf, OFFSET startOffset, Ebuf* lazyChar) const;
	DfaNode* clone ();
	bool IsNotExp;
};

class StarNode : public DfaNode {
public:
	StarNode (DfaNode* token, Ebuf* pLazyChar);
	~StarNode ();
	virtual int match (Ebuf& ebuf, OFFSET startOffset, Ebuf* lazyChar) const;
	virtual DfaNode* clone ();
	
	Ebuf* pLazyChar;
protected:
	DfaNode* token;
};

class PlusNode : public StarNode {
public :
	PlusNode (DfaNode* token, Ebuf* pLazyChar);
	~PlusNode ();
	//PlusNode (Ebuf);
	int match (Ebuf& ebuf, OFFSET startOffset, Ebuf* lazyChar) const;
	DfaNode* clone ();
};

#endif /* _DFA_H_ */
