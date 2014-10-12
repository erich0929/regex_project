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
 * linekd_node 의 멤버변수 data의 type인 class T의 대입연사자를
 * 잘 대비해 놓아야 한다.
 */
 
template <class T>
class linked_node {
    public :
        linked_node (const T* data);
        //linked_node (linked_node<T>& node);
        ~linked_node ();
        T* getData () const;
        void append (linked_node<T>* next);
        linked_node<T>* next;
    private :
        T* data;
       
};


template <class T>
class Iterator {
    
public :
    virtual bool hasNext () const = 0;
    virtual linked_node<T>* next () = 0;
};




template <class T>
class linked_list : public Iterator <T> {
    
public :
    linked_list ();
    linked_list (linked_list<T>& source);
    ~linked_list ();
    
    /* 
	 * Warning !!
	 * linked_node 의 defualt 복사생성자를 이용해도 좋도록 
	 * linekd_node 의 멤버변수 data의 type인 class T의 대입연사자를
	 * 잘 대비해 놓아야 한다.
	 */
    void insert (linked_node<T>* node);
    void toString ();

	/* implement Iterator Interface 
	 * linked_list를 Iterator 로 참조해서 사용할 때
	 * 복사생성자를 사용하지 말라. 복사생성자는 내부적으로 
	 * setNewIterator를 사용해 current 값을 초기화시킨다
	 */
    bool hasNext () const;
    linked_node<T>* next ();
    void setNewIterator ();
    
private :
    linked_node<T>* head;
    linked_node<T>* current;
};

/*
template class linked_list <int>;
template class linked_node <int>;
*/

//linked_list <int> list;
//linked_node <int> node;


#endif	/* LINKED_LIST_H */

