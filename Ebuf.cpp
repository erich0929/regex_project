#include "Ebuf.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>



Ebuf::Ebuf (unsigned char* source) {
	unsigned int length = strlen ((char*)source);
	this -> m_length = length;
	this -> m_buf = (unsigned char*) malloc (sizeof (unsigned char) * (this -> m_length + 1));
	strncpy ((char*)this -> m_buf, (char*)source, this -> m_length + 1);
	
	this -> m_offset = 0;
}

Ebuf::Ebuf (const Ebuf& src_ebuf) {
	this -> m_offset = src_ebuf.getOffset ();
	this -> m_length = src_ebuf.getLength ();
	this -> m_buf = src_ebuf.getBuffer ();
}

Ebuf& Ebuf::operator= (const Ebuf& src_ebuf) {
	if (this == &src_ebuf) return *this;
	
	free (this -> m_buf);
	
	this -> m_offset = src_ebuf.getOffset ();
	this -> m_length = src_ebuf.getLength ();
	this -> m_buf = src_ebuf.getBuffer ();
	
	return *this;
}

unsigned int Ebuf::getOffset () const {
	return this -> m_offset;
}

unsigned int Ebuf::getLength () const {
	return this -> m_length;
}

unsigned char* Ebuf::getBuffer () const {
	unsigned char* res;
	res = (unsigned char*) malloc (sizeof (unsigned char) * (this -> m_length + 1));
	strncpy ((char*)res, (char*) (this -> m_buf), this -> m_length + 1);
	return res;
}

unsigned char Ebuf::getNext (unsigned int offset) const{
	if ((this -> m_offset + offset) > this -> m_length) {
		return '\0';
	} else {
		return this -> m_buf [this -> m_offset + offset];
	}
}

void Ebuf::advance (unsigned int offset) {
	this -> m_offset += offset;
	if (this -> m_offset > this -> m_length) this -> m_offset = this -> m_length;
	return;
}

Ebuf::~Ebuf () {
	free (this -> m_buf);
}
















