/* 
 * File:   linked_list.h
 * Author: erich0929
 *
 * Created on 2014년 10월 11일 (토), 오후 3:49
 */

#ifndef LINKED_LIST_H
#define	LINKED_LIST_H
/* 
 * Warning !!
 * linked_node 의 defualt 복사생성자를 이용해도 좋도록 
 * linekd_node 의 멤버변수 data의 type인 class DfaNode의 대입연사자를
 * 잘 대비해 놓아야 한다.
 */
#include "Dfa.h"

class DfaNode;

class linked_node {
    public :
        linked_node (DfaNode* data);
        //linked_node (linked_node& node);
        ~linked_node ();
        DfaNode* getData () const;
        void append (linked_node* next);
        linked_node* next;
    private :
        DfaNode* data;
       
};



class Iterator {
    
public :
    virtual bool hasNext () const = 0;
    virtual linked_node* next () = 0;
};





class linked_list : public Iterator  {
    
public :
    linked_list ();
    linked_list (linked_list& source);
    ~linked_list ();
    
    /* 
	 * Warning !!
	 * linked_node 의 defualt 복사생성자를 이용해도 좋도록 
	 * linekd_node 의 멤버변수 data의 type인 class DfaNode의 대입연사자를
	 * 잘 대비해 놓아야 한다.
	 */
    void insert (linked_node* node);
    void insert (DfaNode* data);
    void toString ();

	/* implement Iterator Interface 
	 * linked_list를 Iterator 로 참조해서 사용할 때
	 * 복사생성자를 사용하지 말라. 복사생성자는 내부적으로 
	 * setNewIterator를 사용해 current 값을 초기화시킨다
	 */
    bool hasNext () const;
    linked_node* next ();
    void setNewIterator ();
    
private :
    linked_node* head;
    linked_node* current;
};

/*
template class linked_list <int>;
template class linked_node <int>;
*/

//linked_list <int> list;
//linked_node <int> node;


#endif	/* LINKED_LIST_H */

