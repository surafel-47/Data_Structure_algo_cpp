/********************************************************************
  	Batch:Drb2002

  	Surafel Zewdu  - GC5332
  

*********************************************************************/


#include <iostream>
using namespace std;

template <class T>
struct dnode{
		T data;
		dnode<T> * prev;
		dnode<T> * next;
		dnode(){
			prev=NULL;
			next=NULL;
		}
};

template <class T>
void DefaultDisplayer(T data){
	cout << data << " ";
}
template <class T>
class DList{
	public:
		DList(); //default constructor
		DList(bool sorted); //other constructor
		DList(const DList<T> &L); //copy constructor. it is used when you create a new object from existing DList object
		virtual ~DList(){ //destructor
			empty();
		}
		int isEmpty();
		void insertFirst(T data);// insert first
		void insertBack(T data); // insert last
		void insertBefore( T before); //insert before first occurance of some data
		void insertAfter( T after);//insert before last occurance of some data
		int insert(T data);//insert at last for unsorted, insert at appropriate position
		void insertRangeBefore(T before, DList<T> range);
		void insertRangeAfter(T after, DList<T> range);
		int removeFirst();//remove first
		int removeLast();//remove last
	 	int remove(T data);
		void removeRange(T target1, T target2);
		dnode<T>* find(T data); //search first occurance
		void empty(); //destroy the linked list
		DList<T> copy(); // copy and return linked list
		void DisplayForward();
		void DisplayBackward();
    
	protected:
        dnode<T> * head;
		dnode<T> * tail;
		int count;
    private:
		void insertNode(dnode<T> * p, dnode<T> * prev);
		void deleteNode(dnode<T> * p); // p is the node to be deleted
        dnode<T> * insertionSlot(T data);//finds insertion position
        bool sorted; //whether the list is sorted or not

};


template <class T>
DList<T>::DList(){
	this->sorted=false;
	count=0;
	head=tail=NULL;
}

template <class T>
DList<T>::DList(bool sorted){
	this->sorted=sorted;
	count=0;
	head=tail=NULL;

}

template <class T>
DList<T>::DList(const DList<T> &L){
	this->head=L->head;
	this->tail=L->tail;
}


template <class T>
int DList<T>::isEmpty(){
	if(head==NULL)
		return 1;
	else 
		return 0;
}


template <class T>
void DList<T>::insertNode(dnode<T> * p, dnode<T> * prev){
	//4 cases
	if(head==NULL){ //first elm
		head=p;
		p->prev=NULL;
		p->next=NULL;
		tail=p;
	}else if(prev==NULL){//insertion thorugh head
		head->prev=p;
		p->next=head;
		head=p;
		p->prev=NULL;
	}else{ //insert in the middle or end
		p->next=prev->next;
		p->prev=prev;
		if(prev->next!=NULL){
			prev->next->prev=p;	
		}
		prev->next=p;
		if(prev==tail)
			tail=p;		
	}
	count++;
}



template <class T>
void DList<T>::deleteNode(dnode<T> * p){
	
	dnode<T> *prev=p->prev;
	//4 cases
	if(head==tail){ //del the last remaining item
		head=tail=NULL;
	}else if(p->prev==NULL){//del first elem
		p->next->prev=NULL;
		head=p->next;
		p->next=p->prev=NULL;
	}else{ //del from the middle or end
	
		if(p->next==NULL){
			prev->next=NULL;
			tail=prev;
			return ;
		}
		prev->next=p->next;
		p->next->prev=prev;
	}
	count--;
	delete p; //removing p from Stack Memory
}




template <class T>
dnode<T> *  DList<T>::insertionSlot(T data){
	if(!sorted) return tail;

	bool found=false;
	dnode<T> *prev=NULL,*curr=head;

	while(curr!=NULL && !found){
		if(curr->data<data){
			prev=curr;
			curr=curr->next;
		}else{
			found=true;
		}
	}	
	return prev;
} 
 
 

template <class T>
int DList<T>::insert(T data){
	dnode<T> *p= new (nothrow) dnode<T>;
	p->data=data;
	dnode<T> *prev=insertionSlot(data);
	insertNode(p,prev);
	return 1;
}  
 

template <class T>
int DList<T>::remove(T data){
	dnode<T> *curr=head;
	while(curr!=NULL){
		if(curr->data==data){
			deleteNode(curr);
			return 1;
		}
		curr=curr->next;	
	}
	return 0; //no matching data found so no deleted
}   

template <class T>
void DList<T>::insertFirst(T data){
	sorted=false;
	dnode<T> *p= new (nothrow) dnode<T>;
	p->data=data;
	insertNode(p,NULL);
}

template <class T>
void DList<T>::insertBack(T data){
	sorted=false;
	dnode<T> *p= new (nothrow) dnode<T>;
	p->data=data;
	insertNode(p,tail);
}

template <class T>
int DList<T>::removeFirst(){
	if(head!=NULL)
		deleteNode(head);
}


template <class T>
int DList<T>::removeLast(){
	if(tail!=NULL)
		deleteNode(tail);
}
  
template <class T>
dnode<T> *DList<T>::find(T data){
	dnode<T> *curr=head;
	while(curr!=NULL){
		if(curr->data==data){
			return curr;
		}
		curr=curr->next;	
	}
	return NULL; //no matching data found 
}
  

template <class T>
void DList<T>::removeRange(T target1, T target2){
	dnode<T> *Target1=find(target1);
	dnode<T> *Target2=find(target2);
	dnode<T> *curr=Target1->next;
	dnode<T> *next=NULL;
	if(target1==NULL || target2==NULL) 
		return;
	
	while(curr!=NULL && curr!=Target2){
		next=curr->next;
		deleteNode(curr);
		curr=next;
	}
	return ;
}
    
template <class T>
void DList<T>::DisplayForward(){  
		dnode<T> *curr=head;
		if(curr!=NULL) cout<<"\n\nhead";
		while(curr!=NULL){
			cout<<"->"<<curr->data;
			curr=curr->next;
		}
		if(head!=NULL){
			cout<<"\n\nhead is: "<<head->data;
		}
		if(tail!=NULL){
			cout<<"\ntail is: "<<tail->data;
		}
		cout<<"\n\n\n";
}

template <class T>
void DList<T>::DisplayBackward(){  
		dnode<T> *curr=tail;
		if(curr!=NULL) cout<<"\n\ntail";
		while(curr!=NULL){
			cout<<"->"<<curr->data;
			curr=curr->prev;
		}
		if(head!=NULL){
			cout<<"\n\nhead is: "<<head->data;
		}
		if(tail!=NULL){
			cout<<"\n tail is: "<<tail->data;
		}
		cout<<"\n\n\n";
}


template <class T>
void DList<T>::empty(){  
		dnode<T> *curr=head,*next=NULL;
		while(curr!=NULL){
			next=curr->next;
			delete curr;
			curr=next;
		}
		head=tail=NULL;
}

	









int main(){
/********************************************************************
  	Batch:Drb2002

  	Surafel Zewdu  - GC5332
  
  	Yodahe Zerihun - AJ6475 

********************************************************/
	DList <float>dlist;
	cout<<"WellCome!\n Press 1: Create Unsorted List \n Press 2: Create Sorted List \n";
	int input;
	cin>>input;
	if(input=2){
		 dlist=new DList<float>(true);	//sorted
	}else{
	    dlist=new DList<float>(false);	//unsorted
	}
	system("cls");
	
	backToMainMenu:
	cout<<"Press 1:Insert \nPress 2:Remove  \nPress 3: DisplayForward \nPress 4: DisplayBackWard \nPress 5: RemoveFirst \nPress 6: RemoveLast \nPress 7: Exit \n";
	cin>>input;
	if(input==1){ //insert
		float data;
		cout<<"Insert Float Data to Be Inserted: "; 
		cin>>data;
		dlist.insert(data);
	}else if(input==2){
		float data;
		cout<<"Insert float Data To Be Removed: "; 
		cin>>data;
		dlist.remove(data);
	}else if(input==3){
		dlist.DisplayForward();
		system("pause");
	}else if(input==4){
		dlist.DisplayBackward();
		system("pause");
	}else if(input==5){
		dlist.removeFirst();
	}else if(input==6){
		dlist.removeLast();
	}else if(input==7){
		return 0;
	}
		system("cls");
		goto backToMainMenu;
};
