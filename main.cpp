#include <stdio.h>
#include <iostream>
#include "Ebuf.h"
#include "linked_list.h"

using namespace std;

int main(int argc, const char *argv[])
{
	char buf [] = "Hello world 헬로 월드\n";
	Ebuf ebuf0 (buf);
	Ebuf ebuf1 (ebuf0);
	Ebuf ebuf2 = ebuf1;
	char ch;
	int i = 0;
	ebuf0.advance (3);
	while (ch = ebuf0.getNext (i)) {
		printf ("%c", ch);
		i++;
	}
	
	
	linked_list <int> list;
	linked_node <int> node2 (2);
	linked_node <int>* node1  = new linked_node<int> (1);
	
	cout << (void*) &node1 << endl;
	list.insert (node1);
	list.insert (&node2);
	list.toString ();
	Iterator<int>& iter = list;
	while (iter.hasNext ()) {
		cout << "iterator's data : " << iter.next () << endl;
	}
	
	list.setNewIterator ();
	while (iter.hasNext ()) {
		cout << "iterator's data : " << iter.next () << endl;
	}
	
	return 0;
}
