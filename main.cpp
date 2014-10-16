#include <stdio.h>
#include <iostream>
#include <string.h>
#include "Ebuf.h"
#include "linked_list.h"
#include "Dfa.h"

using namespace std;

int main(int argc, const char *argv[])
{
	unsigned char buf [] = "11수김혜\n";
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
	DfaNode* allSingle = new SingleWordNode ((UCHAR*)"", (UCHAR*)"", true, false);
	DfaNode* hanSingle = new SingleWordNode ((UCHAR*)"강", (UCHAR*) "강", false, false);
	DfaNode* singleDigit = SingleWordNode::getDigitNode (false);
	//linked_node<SingleWordNode>* token2 = new linked_node<SingleWordNode> ((SingleWordNode*)singleDigit);
	
	//token_list -> insert (singleDigit);
	//token_list -> insert (singleDigit);
	//token_list -> insert (singleDigit);
	
	token_list -> insert (allSingle);
	//token_list -> insert (hanSingle);
	
	DfaNode* concat = new ConcatNode (token_list);
	Ebuf nullBuf ((unsigned char*)"김");
	//cout << "match : " << concat -> match (ebuf0, 0, nullBuf) << endl;
	
	StarNode digitStar (concat, &nullBuf);
	cout << "regex : .*?김, input : " << buf << "result : " << 
	digitStar.match (ebuf0, 0, *(digitStar.pLazyChar)) << endl;
	delete token_list;
	
	delete hanSingle;
	delete allSingle;
	delete singleDigit;
	
	
	
	return 0;
}
