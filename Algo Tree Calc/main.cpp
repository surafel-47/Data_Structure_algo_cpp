/********************************************************************
  Batch:Drb2002

  Surafel Zewdu  - GC5332
  
  Yodahe Zerihun - AJ6475 

********************************************************************/
#include <cstdlib>
#include <string>
#include <sstream>
#include <iostream>
#include <cmath>
#include "Stack.cpp"
#include "Tree.cpp"
using namespace std;

//Note: we didn't use Union, but rather numeric value to rep the value of the internal node(the Operator)

template <class T>
bool inputStringToPostFixStackExpr(string input, Stack<T> &postFixStackExpr); //to convert an infix stack experssion into a postFix stack expression
bool isNumeric(char x); // to check if a give character is Numeric by using ascii 
bool isWhiteSpace(char x); //to check white spaces in exprssion entered too remove them
bool isCurrentOpertorHigherPrecdanceThanLast(string curr, string last);	//compare precedance of current operator and what was last in the Operators stack
nodeTree* postFixStackExprToTreeExpr(Stack<string>postFixStackExpr);//////////////////////////////////////////////////////////////////
double stringToDouble(string str);//coverts String to double
string doubleToString(double val);//coverts double to string

void evaluateLeafs(nodeTree *root);
double solveBinaryTreeExperssion(nodeTree *root);

string getUserInput();
int main(){	
/********************************************************************
  Batch:Drb2002

  Surafel Zewdu  - GC5332
  
  Yodahe Zerihun - AJ6475 

********************************************************************/


	restart:
	try{
		string input="";//.........................................To Hold User Input String Expression
		Stack <string>postFixStackExpr;//...........................To Hold the PostFix Form of the Stack From Expression	

		input=getUserInput();	//...................................Getting experssion
		inputStringToPostFixStackExpr(input,postFixStackExpr);//..................Converting String experssion to PostFix Stack of String experssion			
		
		
		//coverting from stack of postfix to binary tree
		Stack <nodeTree*> numbersStack; // this is a Stack of NodeTreePointers
		nodeTree *token;
		while(!postFixStackExpr.isEmpty()){		//while the postFixStack is not empty
			token=new nodeTree();		//preparing a new nodeTree
			if(isNumeric(postFixStackExpr.peek()[0])){	//if next thing is double number
				token->data=stringToDouble(postFixStackExpr.pop());	//put data into the prepared node
				numbersStack.push(token);	//push the node onto the NodeTree Pointer stack
			}else{			//else if it is a charcher
				token->data=(int) postFixStackExpr.pop()[0]; //prepare a node and get the operator
				token->left=numbersStack.pop();	//	insert into node left what was top of the stack
				token->right=numbersStack.pop();//	insert into node right what was second top of the stack
				numbersStack.push(token);	//push the node onto the NodeTree Pointer stack
			}
		}
		
		
		//when loop is completed, the last elem to be poped will be the root of the binary tree
		Tree treeExpr;
		treeExpr.root=numbersStack.pop();//getting the root of the binary tree
			
		double result=solveBinaryTreeExperssion(treeExpr.root);//calling the function to solve a binary tree expr
		cout<<"Result : "<<result<<"\n";
		
		
	}catch(...){
		cout<<"Error! Invalid Input \n\n";
	}
	system("pause"); system("cls");
	goto restart;
}

double solveBinaryTreeExperssion(nodeTree *root){//computes final value of the binarry expr tree
		
		// a binary expr tree is solved when left and right of the top root is NULL, this while loop specficys that condion
		while(root->left!=NULL && root->right!=NULL){
			//for every call of recurive evaluateLeafs, every tree leaf is evaluated and the tree shrinks down 
			evaluateLeafs(root);
		}
		return root->data; //returning final value
}

void evaluateLeafs(nodeTree *root){//recurively computes each silbiling leafs by using their parent as Opertor, then placeing the reault is that operator

	if(!root){
		return ;  // recurion stop when a leaf is reached
	}else if(!root->left || !root->right ){ // when a parent with either no left or right child is found
			return ;
	}else if( (root)    &&	 (!root->left->left && !root->left->right)    && 	(!root->right->left && !root->right->right) 	){ // a leaf has been found
		char Opertor = (int)root->data;
			 if(Opertor=='^') 
			 	root->data=pow((int)root->left->data,(int)root->right->data); //if operand is ^
		else if(Opertor=='/') 
				root->data= root->left->data / root->right->data;	//if operand is /
		else if(Opertor=='+') 
				root->data= root->left->data + root->right->data;	//if operand is +
		else if(Opertor=='-') 
				root->data= root->left->data - root->right->data;	//if operand is -
		else if(Opertor=='%')	
				root->data= (int)root->left->data % (int)root->right->data;	//if operand is %
		else if(Opertor=='*') 
				root->data= root->left->data * root->right->data;	//if operand is *
		
		root->left=root->right=NULL; //shrinking the tree by making left and right childs null since they are no longer needed
	}
		evaluateLeafs(root->left);
		evaluateLeafs(root->right);

}




string getUserInput(){
	string input="";
	cout<<"             Welcome! \n";
	cout<<"Notice! Please use '*' Operator for Multiplication! \n\n\n";
	cout<<"Enter Experssion : ";
	getline(cin,input);	
	return input;
}



bool isNumeric(char x){  // to check if a give character is Numeric by using ascii 
	return (x>=48 && x<=57); //return true if it's a number
}

bool isWhiteSpace(char x){ //to check white spaces in exprssion entered too remove them
	return x==32; //returns true if it's whiteSpace
}


template <class T>
bool inputStringToPostFixStackExpr(string input, Stack<T> &postFixStackExpr){ //to convert an infix stack experssion into a postFix stack expression

	Stack <T>stackExpr;
	double operand; //to hold each operand found in string temporarly for pushing on to the stack
	
	istringstream strm(input);
	
	//below code will load each opertor or operand into the stack from the string
	while(!strm.eof()){
		stringstream temp;
		if(isNumeric(strm.peek())){	//if an operand is found
			strm>>operand;
			temp<<operand;
		}else if(isWhiteSpace(strm.peek())){ //if a white space is found, skip it
			strm.get();
			continue;
		}else{		//if an opertor is found
			char Opr=strm.get();
			temp<<Opr;
		}
		stackExpr.push(temp.str()); //pushing the operand or operator found on to the stack
	}
	
	
	//Now to reversing the stack so that it is in proper order
	Stack<T>temp1,temp2;
	while(!stackExpr.isEmpty())
		temp1.push(stackExpr.pop());
	while(!temp1.isEmpty())
		temp2.push(temp1.pop());
	while(!temp2.isEmpty())
		stackExpr.push(temp2.pop());  
	
	
	
	Stack<string> Opertors;	//to hold the Operators while scanning the Stack Experssion
	
	//below is while loop taht scans the stack Expression and puts elems in there proper place in the postFix stack
	while(!stackExpr.isEmpty()){
		if(isNumeric(stackExpr.peek()[0])){	
		
			postFixStackExpr.push(stackExpr.pop()); //if numeric just push it onto the postFix stack
		
		}else if(stackExpr.peek()=="("){
		
			Opertors.push(stackExpr.pop());	//if Open Brace, push it on to the Opertors stack since it has higher precdance than all
		
		}else if(stackExpr.peek()==")"){
			
			//if a close brace is reached
			
			stackExpr.pop();  //skipping the close brace from the stackExprsion Stack-
			
			//push from Operators to PostFix stack until a closed Brace is found
			while(!Opertors.isEmpty() ){ 
				if(Opertors.peek()=="("){
					Opertors.pop();	//skipping the open brace from the Opertors Stack
					break;
				}else{
					postFixStackExpr.push(Opertors.pop());		
				}
			}
		}else if(stackExpr.peek()=="^"){
		
			Opertors.push(stackExpr.pop()); //if power, the push it on the stack since it has higher precedance than other all opertors 
		
		}else if(!Opertors.isEmpty() && isCurrentOpertorHigherPrecdanceThanLast(stackExpr.peek(),Opertors.peek())){
		
				Opertors.push(stackExpr.pop());  //if higher precdance then push to onto the top of the Operators stack
		
		}else{  //if Current if Lower than Last Opertor
			
			string curr=stackExpr.pop();
			//do this will end of stack not reached, and until u find a numeric Value and, a last operator lower precadnce of current
			while(!Opertors.isEmpty() && !isCurrentOpertorHigherPrecdanceThanLast(curr,Opertors.peek())){
				postFixStackExpr.push(Opertors.pop()); //pushing onto the Post Fix Expr stack the higher precdance operatorssss
			}
			
			Opertors.push(curr);
			//pusing onto the Operator stack the lower precdance operator
		}
	}
	
	while(!Opertors.isEmpty()){	//adding to the postfix stack what remains in the operator stack
		if(Opertors.peek()=="/" || Opertors.peek()=="%" || Opertors.peek()=="*" || Opertors.peek()=="^" || Opertors.peek()=="+" || Opertors.peek()=="-")
			postFixStackExpr.push(Opertors.pop()); 
		else
			Opertors.pop();
	}	
	
	//	Now to reversing the stack so that it is in proper order
	Stack<T>temp3,temp4;
	while(!postFixStackExpr.isEmpty())
		temp3.push(postFixStackExpr.pop());
	while(!temp3.isEmpty())
		temp4.push(temp3.pop());
	while(!temp4.isEmpty())
			postFixStackExpr.push(temp4.pop());  
}


bool isCurrentOpertorHigherPrecdanceThanLast(string curr, string last){ //compare precedance of current operator and what was last in the Operators stack
	if( (curr=="^" || curr=="*" || curr== "/" || curr=="%") && (last=="-" || last=="+") )
		return true;
	else if(  (curr=="+" || curr=="-") && (last=="*" || last=="/" || last=="^" || last=="%")  ) 
		return false;
	else if( (curr=="^") && (last=="*" || last=="/" || last=="^" || last=="%" || last=="+" || last=="-") )
		return true;
	else if((curr=="^" || curr=="*" || curr== "/" || curr=="%" || curr=="-" || curr=="+") && (last=="(") )
		return true;
	else 
		return false; //the rest cases are all false since the remaing are left to right assoitative
}


double stringToDouble(string str){
	stringstream tempStrm;
	tempStrm<<str;
	double tempVal;
	tempStrm>>tempVal;
	return tempVal;
}

string doubleToString(double val){
	stringstream tempStrm;
	tempStrm<<val;
	string tempVal;
	tempStrm>>tempVal;
	return tempVal;
}



