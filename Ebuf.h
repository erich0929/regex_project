#ifndef _E_BUF_H_
#define _E_BUF_H_

class Ebuf {
	public :
		Ebuf (unsigned char* source);
		Ebuf (const Ebuf& src_buf); /* 복사생성자 */
		Ebuf& operator= (const Ebuf& src_ebuf); /* 대입연산자 */
		~Ebuf ();
		
		unsigned int getOffset () const;
		unsigned int getLength () const;
		unsigned char* getBuffer () const;
		
		unsigned char getNext (unsigned int offset) const;
		void advance (unsigned int offset);
		
	private :
		unsigned char* m_buf;
		unsigned int m_offset;
		unsigned int m_length;
};

#endif /* _E_BUF_H_ */
