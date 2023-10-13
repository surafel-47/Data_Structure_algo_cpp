//
//Assignment 1
//Given the design of a double linked list, produce the full implementation. You are expected also to provide a menu driven driver program which has the following menu item:
//1.	Insert
//2.	Remove
//3.	Search
//4.	Display Forward
//5.	Display Backward
//6.	Exit
//The specification of the double linked list is attached together with this document
//Direction
//The assignment is going to be done by a group of two students.
//Assignment Submission Date: August 2, 2022
//While engaging in general discussion regarding the solution is encouraged, giving and receiving major sections of code will be considering cheating. All parties (giving or receiving) will be punished. This includes copping from Internet.
//Dead line to assignment should be respected. No justification will be accepted to reconsider 
//
//











template <class T>
struct dnode{
		T data;
		dnode<T> * prev;
		dnode<T> * next;
};
void DefaultDisplayer(T data){
	cout << data << " ";
}
template <class T>
class DList{
	public:
//		DList(); //default constructor
//		DList(bool sorted); //other constructor
//		DList(const DList<T> &L); //copy constructor. it is used when you create a new object from existing DList object
//		virtual ~DList(); //destructor
//		int isEmpty();
//		void insertFirst(T data);// insert first
//		void insertBack(T data); // insert last
		void insertBefore(T before); //insert before first occurance of some data
		void insertAfter(T after);//insert before last occurance of some data
//		int insert(T data);//insert at last for unsorted, insert at appropriate position
		void insertRangeBefore(T before, DList<T> range);
		void insertRangeAfter(T after, DList<T> range);
//		int removeFirst();//remove first
//		int removeLast();//remove last
//	 	int remove(T data);
//		void removeRange(T target1, T target2);
//		dnode<T>* find(T data); //search first occurance
//		void empty(); //destroy the linked list
		DList<T> copy(); // copy and return linked list
//		void DisplayForward(void (*displayer)(T data));
//		void DisplayBackward(void (*displayer)(T data));
    protected:
//        dnode<T> * head;
//	dnode<T> * tail;
//	int count;
    private:
//	void insertNode(dnode<T> * p, dnode<T> * prev);
//	void deleteNode(dnode<T> * p); // p is the node to be deleted
//        dnode<T> * insertionSlot(T data)//finds insertion position
//        bool sorted; //whether the list is sorted or not

};
