#include <stdio.h>
#include <iostream>
#include "Ebuf.h"
#include "linked_list.h"
#include "Dfa.h"

using namespace std;

int main(int argc, const char *argv[])
{
	char buf [] = "010*a\n";
	Ebuf ebuf0 (buf);
	Ebuf ebuf1 (ebuf0);
	Ebuf ebuf2 = ebuf1;
	char ch;
	int i = 0;
	ebuf0.advance (0);
	while (ch = ebuf0.getNext (i)) {
		printf ("%c", ch);
		i++;
	}
	
	linked_list<SingleWordNode>* token_list = new linked_list<SingleWordNode> ();
	DfaNode* allSingle = SingleWordNode::getDotNode ();
	DfaNode* singleDigit = SingleWordNode::getDigitNode (false);
	//linked_node<SingleWordNode>* token2 = new linked_node<SingleWordNode> ((SingleWordNode*)singleDigit);
	
	token_list -> insert ((SingleWordNode*) singleDigit);
	token_list -> insert ((SingleWordNode*) singleDigit);
	token_list -> insert ((SingleWordNode*) allSingle);
	token_list -> insert ((SingleWordNode*) allSingle);
	
	DfaNode* concat = new ConcatNode<SingleWordNode> (token_list);
	cout << "match : " << concat -> match (ebuf0, 0) << endl;
	delete token_list;
	
	delete allSingle;
	delete singleDigit;
	
	
	
	return 0;
}
