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
		
		/* form  
		length = strlen ((char*)from);
		this -> from = (UCHAR*) malloc (sizeof (UCHAR) * (length + 1));
		strncpy ((char*)this -> from, (char*)from, length + 1);
		 */
		this -> from = new Ebuf (from);
		/* to 
		length = strlen ((char*)to);
		this -> to = (UCHAR*) malloc (sizeof (UCHAR) * (length + 1));
		strncpy ((char*)this -> to, (char*)to, length + 1);
		*/
		this -> to = new Ebuf (to);
		/* m_length */
		//this -> m_length = length;
		/* IsNotExp */
		this -> IsNotExp = IsNotExp;
		/* IsUTF8 */
		std::cout << this -> from -> getLength () << std::endl;
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
		
		//unsigned int length = 0;
		/* form 
		length = strlen ((char*)source.from);
		this -> from = (UCHAR*) malloc (sizeof (UCHAR) * (length + 1));
		strncpy ((char*)this -> from, (char*)source.from, length + 1);
		 */
		/* 
		 * to 
		length = strlen ((char*)source.to);
		this -> to = (UCHAR*) malloc (sizeof (UCHAR) * (length + 1));
		strncpy ((char*)this -> to, (char*)source.to, length + 1);
		 */
		/* m_length */
		//this -> m_length = source.m_length;
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

int SingleWordNode::match(Ebuf& ebuf, OFFSET startOffset, Ebuf& lazyChar) const
{
		UCHAR current = ebuf.getNext(startOffset);
		bool IsAccept = true;
		
		/* ASCII Range Mode */
		/*
		if (!(this -> IsUTF8)) {
				std::cout << "Not UTF8" << std::endl;
				if (current >= from -> getNext (0) && current <= to -> getNext (0)) IsAccept = true;
				IsNotExp ? IsAccept = !IsAccept : IsAccept;
				
				// if IsAccept and IsLazyChar , then return 0 
				if (IsAccept && current == lazyChar.getNext(0)) {
						std::cout << "lazyChar accepted" << std::endl;
						return 0;
				}
				return IsAccept ? 1 : -1;
		} else {
		*/
				/* case : Mutibytes and just 'from' char (string) to be used. */
				int i = 0;
				OFFSET acceptedOffset = 0;
				bool IsLazyAccepted = true;
				unsigned int lazyCount = 0;
				unsigned int charSize = 0;
				/**
				if (from -> getNext (0) == '\0' && IsNotExp == true && current <= 128) {
					charSize = 1; /* ASCII MODE 
				} else {
					charSize = from -> getLength ();
				} /* Mutibytes Mode 
				**/
				
				if (IsNotExp) {
					/* criterion to buffer */
					(current < 128) ? charSize = 1 : charSize = 3;
				} else {
					/* criterion to from */
					charSize = from -> getLength ();
					
				}
				std::cout << "charsize :" << charSize << std::endl;
				for (i = 0; /*i < this -> from -> getLength ()*/(i < charSize) && (IsAccept) ; i++) {
						current = ebuf.getNext (startOffset + i);
						
						if (this -> IsRange) {
							printf ("from : %d, to : %d, current : %d\n", from -> getNext (0), to -> getNext (0), current);
							(current >= from -> getNext (0) && current <= to -> getNext (0)) ? IsAccept = true : IsAccept = false;
						} else {
							(current == from -> getNext (i)) ? IsAccept = true : IsAccept = false; 
						}
						
						if ((current == lazyChar.getNext(lazyCount)) && IsLazyAccepted
								/*&& IsAccept*/) {
									lazyCount ++;
						} else {
								IsLazyAccepted = false;
						}
				}
				
				IsNotExp ? IsAccept = !IsAccept : IsAccept;
						std::cout << "let's determine. : " << IsAccept << std::endl;
						if (IsAccept) {
								acceptedOffset += charSize;
						} else {
								std::cout << IsAccept << std::endl;
								return -1;
						}
				/* if IsAccept and IsLazyChar , then return 0 */
				if (IsLazyAccepted && IsAccept) {
						std::cout << "is lazy" << std::endl;
						return 0;
				} else {
						std::cout << "is not lazy" << std::endl;
						return acceptedOffset;
				}
				/*
		}*/
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


int ConcatNode::match(Ebuf& ebuf, OFFSET startOffset, Ebuf& lazyChar) const
{
		this -> token_list -> setNewIterator();
		Iterator& iter = *(this -> token_list);
		OFFSET acceptedOffset = 0;
		OFFSET offset = 0;
		linked_node* temp;
		DfaNode* token;
		
		/* The first token's considerred as lazyChar. */
		if (iter.hasNext()) {
				token = iter.next() -> getData ();
				if ((offset = token -> match (ebuf, startOffset, lazyChar)) == 0) {
						return 0;
				} else {
						acceptedOffset += offset;
				}
		}
		
		Ebuf* nullBuf = new Ebuf ((UCHAR*)"");
		while (iter.hasNext()) {
				temp = iter.next();
				token = temp -> getData();
				if ((offset = token -> match(ebuf, startOffset + acceptedOffset, *nullBuf)) == -1) {
						delete nullBuf;
						return -1;
				}
				acceptedOffset += offset;
		}
		delete nullBuf;
		return acceptedOffset;
}


DfaNode* ConcatNode::clone () {
		return new ConcatNode (*this);
}

/* implement StarNode */

StarNode::StarNode(DfaNode* token) {
		this -> token = token -> clone ();
}

StarNode::~StarNode () {
		delete this -> token;
}

int StarNode::match (Ebuf& ebuf, OFFSET startOffset, Ebuf& lazyChar) const {
		OFFSET acceptedOffset = 0;
		int offset = 0;
		UCHAR current;
		while ((offset = this -> token -> 
				match (ebuf, startOffset + acceptedOffset, lazyChar)) > 0) {
				printf ("StarNode loop ; offset : %d\n", offset);
				acceptedOffset += offset;
		}
		/* Don't care if lazyChar == NULL. */
		OFFSET lazyOffset = 0;
		OFFSET lazyAccepted = 0;
		UCHAR lazyCurrent;
		
		/*
		while ((lazyCurrent = lazyChar.getNext(lazyOffset)) != '\0') {
				current = ebuf.getNext (startOffset + acceptedOffset + lazyOffset);
				if (current == lazyCurrent) {
						lazyAccepted += 1;
				} else {
						return -1;
				}
				lazyOffset ++;
		}
		*/
		SingleWordNode lazyToken (&lazyChar, &lazyChar, false, false);
		Ebuf nullToken ((UCHAR*) "");
		if ((lazyAccepted = lazyToken.match (ebuf, startOffset + acceptedOffset, nullToken)) < 0) return -1;
		
		return acceptedOffset + lazyAccepted;
}

DfaNode* StarNode::clone () {
		return new StarNode (*this);
}

//template class ConcatNode ;
//template class StarNode ;
//template class StarNode <SingleWordNode>;
//template class StarNode <ConcatNode>;












