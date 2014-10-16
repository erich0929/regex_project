#include "Dfa.h"
#include "linked_list.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>

SingleWordNode::SingleWordNode(UCHAR* from, UCHAR* to, bool IsNotExp, bool IsRange)
/* : from(from), to(to), IsNotExp(IsNotExp) */
{
		unsigned int length = 0;
		
		this -> from = new Ebuf (from);
		
		this -> to = new Ebuf (to);
	
		/* IsNotExp */
		this -> IsNotExp = IsNotExp;
		/* IsUTF8 */
		this -> IsUTF8 = (((this -> from -> getLength ()) == 1) ? false : true) ; 
		
		this -> IsRange = IsRange;
		
}

SingleWordNode::SingleWordNode (Ebuf* from ,Ebuf* to, bool IsNotExp, bool IsRange) {
		this -> from = new Ebuf (*from);
		this -> to = new Ebuf (*to);
		this -> IsNotExp = IsNotExp;
		/* IsUTF8 */
		this -> IsUTF8 = (((this -> from -> getLength ()) == 1) ? false : true) ; 
		
		this -> IsRange = IsRange;
}

SingleWordNode::SingleWordNode(SingleWordNode& source) {
		this -> from = new Ebuf (*source.from);
		this -> to = new Ebuf (*source.to);
		/* IsNotExp */
		this -> IsNotExp = source.IsNotExp;
		/* IsUTF8 */
		this -> IsUTF8 = source.IsUTF8;
		this -> IsRange = source.IsRange;
}

SingleWordNode::~SingleWordNode () {
		delete this -> from;
		delete this -> to;
}

int SingleWordNode::match(Ebuf& ebuf, OFFSET startOffset, Ebuf* lazyChar) const
{
		UCHAR current = ebuf.getNext(startOffset);
		bool IsAccept = true;

		int i = 0;
		OFFSET acceptedOffset = 0;
		bool IsLazyAccepted = true;
		unsigned int lazyCount = 0;
		unsigned int charSize = 0;
		
		if (IsNotExp) {
				/* criterion to buffer */
				(current < 128) ? charSize = 1 : charSize = 3;
		} else {
				/* criterion to from */
				charSize = from -> getLength();

		}
		//std::cout << "charsize :" << charSize << std::endl;
		for (i = 0; (i < charSize) && (IsAccept); i++) {
				current = ebuf.getNext(startOffset + i);
				if (this -> IsRange) {
						(current >= from -> getNext(0) && current <= to -> getNext(0)) ? IsAccept = true : IsAccept = false;
				} else {
						(current == from -> getNext(i)) ? IsAccept = true : IsAccept = false;
				}
				printf ("from : %c, to : %c, current : %c\n", from -> getNext (0), to -> getNext (0), current);
				if ((current == lazyChar -> getNext(lazyCount)) && IsLazyAccepted) {
						lazyCount++;
				} else {
						IsLazyAccepted = false;
				}
		}

		IsNotExp ? IsAccept = !IsAccept : IsAccept;
		std::cout << "IsAccepted ? :" << IsAccept << std::endl;
		if (IsAccept) {
				acceptedOffset += charSize;
		} else {
				
				return -1;
		}
		if (IsLazyAccepted && IsAccept) {
				std::cout << "is lazy" << std::endl;
				return 0;
		} else {
				std::cout << "is not lazy" << std::endl;
				return acceptedOffset;
		}
}

DfaNode* SingleWordNode::clone () {
		return new SingleWordNode (*this);
}

DfaNode* SingleWordNode::getDotNode()
{
		return new SingleWordNode((UCHAR*)"", (UCHAR*)"", true, false);
}

DfaNode* SingleWordNode::getDigitNode(const UPPER IsUpper)
{
		return new SingleWordNode((UCHAR*)"0", (UCHAR*)"9", IsUpper, true);
}

SingleWordNode* SingleWordNode::getBoundaryNode(const UPPER IsUpper)
{
		return new SingleWordNode((UCHAR*)" ", (UCHAR*)" ", IsUpper, false);
}

/* implement ConcatNode */

/* 
 * Warning !!
 * linked_list의 복사생성자를 이용하기 위해 
 * linked_list의 복사생성자가 잘 정의되어 있어야 한다.
 */


ConcatNode::ConcatNode(linked_list* token_list) : token_list(NULL)
{
		this -> token_list = new linked_list (*token_list); /* 복사생성자의 이용 */
}

ConcatNode::~ConcatNode()
{
		delete this -> token_list;
}

int ConcatNode::match(Ebuf& ebuf, OFFSET startOffset, Ebuf* lazyChar) const {
		printf ("let's start concatnode match\n");
		this -> token_list -> setNewIterator();
		Iterator& iter = *(this -> token_list);
		OFFSET acceptedOffset = 0;
		int offset = 0;
		linked_node* temp;
		DfaNode* token;
		
		/* The first token's considerred as lazyChar. */
		if (iter.hasNext()) {
				token = iter.next() -> getData ();
				if ((offset = token -> match (ebuf, startOffset, lazyChar)) == 0) {
						return 0;
				} else if (offset == -1) {
						return -1;
				} else if (offset > 0) {
						acceptedOffset += offset;
				}
		}
		
		Ebuf nullBuf ((UCHAR*)"");
		while (iter.hasNext()) {
				temp = iter.next();
				token = temp -> getData();
				if ((offset = token -> match(ebuf, startOffset + acceptedOffset, &nullBuf)) == -1) {
						
						return -1;
				}
				acceptedOffset += offset;
		}
		
		return acceptedOffset;
}


DfaNode* ConcatNode::clone () {
		return new ConcatNode (*this);
}

/* implements AlterNode */
AlterNode::AlterNode(linked_list* token_list, bool IsNotExp) : ConcatNode (token_list) {
		this -> IsNotExp = IsNotExp;		
}

AlterNode::AlterNode (AlterNode& source) : ConcatNode (source) {
		this -> IsNotExp = source.IsNotExp;
}
AlterNode::~AlterNode () {
		/* nothing to do */
}

int AlterNode::match(Ebuf& ebuf, OFFSET startOffset, Ebuf* lazyChar) const {
		printf ("let's start alternode match\n");
		this -> token_list -> setNewIterator();
		Iterator& iter = *(this -> token_list);
		int acceptedOffset = 0;
		//OFFSET offset = 0;
		linked_node* temp;
		DfaNode* token;
		
		bool IsAccepted = false;
		//bool IsLazy = false;
		//Ebuf nullBuf ((UCHAR*)"");
		while (iter.hasNext() && !IsAccepted) {
				printf ("let's next\n");
				temp = iter.next();
				printf ("let's getData\n");
				token = temp -> getData();
				if ((acceptedOffset = token -> match(ebuf, startOffset, lazyChar)) >= 0) {
						printf ("found\n");
						IsAccepted = true;
						//if (acceptedOffset == 0) IsLazy = true;
				}
		}
		//IsNotExp ? IsAccepted = !IsAccepted : IsAccepted;
		printf ("AlterNode : IsAccepted : %d, acceptedOffset : %d\n", IsAccepted, acceptedOffset);
		if (IsAccepted) {
				return acceptedOffset;
		} else{
				return -1;
		}
}

DfaNode* AlterNode::clone() {
		return new AlterNode (*this);
}
/* implement StarNode */

StarNode::StarNode(DfaNode* token, Ebuf* pLazyChar) {
		this -> token = token -> clone ();
		this -> pLazyChar = new Ebuf (*pLazyChar);
}

StarNode::~StarNode () {
		delete this -> token;
		delete this -> pLazyChar;
}

int StarNode::match (Ebuf& ebuf, OFFSET startOffset, Ebuf* lazyChar) const {

		/* if lazyChar is null, then lazyChar is it's own lazyChar (this -> lazyChar) */
		if (lazyChar == NULL) lazyChar = this -> pLazyChar;
		
		int acceptedOffset = 0;
		int offset = 0;
		UCHAR current;
		while ((offset = this -> token -> 
				match (ebuf, startOffset + acceptedOffset, lazyChar)) > 0) {
				printf ("StarNode loop ; offset : %d\n", offset);
				acceptedOffset += offset;
		}
		printf ("end loop : acceptedOffset : %d\n", acceptedOffset);
		/* Don't care if lazyChar == NULL. */
		OFFSET lazyOffset = 0;
		OFFSET lazyAccepted = 0;
		UCHAR lazyCurrent;
	
		SingleWordNode lazyToken (lazyChar, lazyChar, false, false);
		Ebuf nullToken ((UCHAR*) "");
		if ((lazyAccepted = lazyToken.match (ebuf, startOffset + acceptedOffset, &nullToken)) < 0) return -1;
		
		return acceptedOffset + lazyAccepted;
}

DfaNode* StarNode::clone () {
		return new StarNode (*this);
}

	/* implements PlusNode */

PlusNode::PlusNode (DfaNode* token, Ebuf* pLazyChar) : StarNode (token , pLazyChar) {
	/* nothing to do */
}

PlusNode::~PlusNode () {
	/* nothing to do */
}
int PlusNode::match (Ebuf& ebuf, OFFSET startOffset, Ebuf* lazyChar) const {
		printf ("plusnode match start\n");
		/* if lazyChar is null, then lazyChar is it's own lazyChar (this -> lazyChar) */
		if (lazyChar == NULL) lazyChar = this -> pLazyChar;
		
		OFFSET acceptedOffset = 0;
		int offset = 0;
		UCHAR current;
		
		Ebuf nullBuf ((UCHAR*)"");
		if ((acceptedOffset = this -> token -> match (ebuf, startOffset, &nullBuf)) == -1) return -1;
		
		while ((offset = this -> token -> 
				match (ebuf, startOffset + acceptedOffset, lazyChar)) > 0) {
				printf ("StarNode loop ; offset : %d\n", offset);
				acceptedOffset += offset;
		}
		/* Don't care if lazyChar == NULL. */
		OFFSET lazyOffset = 0;
		OFFSET lazyAccepted = 0;
		UCHAR lazyCurrent;
	
		SingleWordNode lazyToken (lazyChar, lazyChar, false, false);
		Ebuf nullToken ((UCHAR*) "");
		if ((lazyAccepted = lazyToken.match (ebuf, startOffset + acceptedOffset, &nullToken)) < 0) return -1;
		
		return acceptedOffset + lazyAccepted;
}

DfaNode* PlusNode::clone() {
		return new PlusNode (*this);
}
//template class ConcatNode ;
//template class StarNode ;
//template class StarNode <SingleWordNode>;
//template class StarNode <ConcatNode>;












