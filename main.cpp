#include <stdio.h>
#include <iostream>
#include <string.h>
#include "Ebuf.h"
#include "linked_list.h"
#include "Dfa.h"

using namespace std;

int main(int argc, const char *argv[])
{
	unsigned char buf [] = "<ab>b<a>";
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
	printf ("\n");
	linked_list* token_list = new linked_list ();
	DfaNode* atoken = new SingleWordNode ((UCHAR*)"a", (UCHAR*)"a", false, false);
	DfaNode* btoken = new SingleWordNode ((UCHAR*)"b", (UCHAR*) "b", false, false);
	DfaNode* arrowR = new SingleWordNode ((UCHAR*) "<", (UCHAR*) "<", false, false);
	DfaNode* arrowL = new SingleWordNode ((UCHAR*) ">", (UCHAR*) ">", false, false);
	//linked_node<SingleWordNode>* token2 = new linked_node<SingleWordNode> ((SingleWordNode*)singleDigit);
	
	//token_list -> insert (singleDigit);
	//token_list -> insert (singleDigit);
	//token_list -> insert (singleDigit);
	
	token_list -> insert (atoken);
	token_list -> insert (btoken);
	token_list -> insert (arrowR);
	token_list -> insert (arrowL);
	//token_list -> toString ();
	//Iterator& iter = *token_list;
	//linked_node* node;
	//i = 0;
	//while (iter.hasNext ()) {
	//	node = iter.next ();
	//	printf ("%d", i++);
	//}
	printf ("\n");
	//token_list -> insert (hanSingle);
	
	AlterNode alter (token_list, false);
	Ebuf lazyBuf ((unsigned char*)">");
	//cout << "match : " << concat -> match (ebuf0, 0, nullBuf) << endl;
	
	//alter.match(ebuf0, 0, &lazyBuf);
	
	DfaNode* digitStar = new PlusNode (&alter, &lazyBuf);
	//StarNode real (*digitStar);
	cout << "regex : [ab<>]*?>, input : " << buf << "result : " << 
	digitStar -> match (ebuf0, 0, NULL) << endl;

	
	
	
	return 0;
}
