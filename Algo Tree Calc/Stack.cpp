#include <iostream>

using namespace std;

//below is a Stack Implemntaion we used to build the Calulator

template <class T>
struct stackNode{
	T data;
	stackNode <T> *next;
};

struct EmptyStackException: public std::exception{
    const char * what () {
        return "Popping an empty stack!";
    }
};

template <class T>
class Stack{
    public:
        Stack();
        virtual ~Stack();
        void push(T data);
        T pop();
        T peek();
        bool isEmpty(){return top==NULL;}
        int getCount(){return count;}
        void empty();
	private:
        stackNode<T> * top;
        int count;
};


template <class T> 
Stack<T>::Stack() {
	top = NULL;
	count=0;
}

template <class T> 
void Stack<T>::empty() {
	while(!isEmpty()){
		pop();
	}
}


template <class T> 
Stack<T>::~Stack() {
	empty();
}

template <class T>
void Stack<T>:: push(T item){
	stackNode<T>  * p=new stackNode<T>;
	p->data = item;
	p->next = top;
	top = p;	
	count++;
}

template <class T>
T Stack<T>::pop() { 	
	stackNode<T> * p;
 	if (isEmpty() ) throw EmptyStackException();
	T item = top->data;
	p = top;
	top = top->next;
	count--;
	delete p;
	return item;
}


template <class T>
T Stack<T>::peek() { 	
	if (isEmpty() ) throw EmptyStackException();
	return top->data;
}



