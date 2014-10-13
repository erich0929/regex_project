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
	
	linked_list* token_list = new linked_list ();
	DfaNode* allSingle = SingleWordNode::getDotNode ();
	DfaNode* singleDigit = SingleWordNode::getDigitNode (false);
	//linked_node<SingleWordNode>* token2 = new linked_node<SingleWordNode> ((SingleWordNode*)singleDigit);
	
	token_list -> insert (singleDigit);
	token_list -> insert (singleDigit);
	token_list -> insert (allSingle);
	token_list -> insert (allSingle);
	
	DfaNode* concat = new ConcatNode (token_list);
	cout << "match : " << concat -> match (ebuf0, 0) << endl;
	delete token_list;
	
	delete allSingle;
	delete singleDigit;
	
	
	
	return 0;
}
