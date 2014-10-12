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
	linked_node<SingleWordNode>* token1 = new linked_node<SingleWordNode> ((SingleWordNode*)allSingle);
	DfaNode* singleDigit = SingleWordNode::getDigitNode (false);
	linked_node<SingleWordNode>* token2 = new linked_node<SingleWordNode> ((SingleWordNode*)singleDigit);
	
	token_list -> insert (token2);
	token_list -> insert (token2);
	token_list -> insert (token2);
	token_list -> insert (token1);
	
	DfaNode* concat = new ConcatNode<SingleWordNode> (token_list);
	cout << "match : " << concat -> match (ebuf0, 0) << endl;
	delete allSingle;
	delete singleDigit;
	delete token1;
	delete token2;
	delete token_list;
	
	return 0;
}
