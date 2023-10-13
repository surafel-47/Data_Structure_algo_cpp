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
using namespace std;

bool isNumeric(char x); // to check if a give character is Numeric by using ascii 
bool isWhiteSpace(char x); //to check white spaces in exprssion entered too remove them
template <class T>
bool stringExprToStack(string input, Stack<T>&stackExpr); //to convert a string input from the user into a stack form
template <class T>
string evalutePostFixStackExpr(Stack <T>expr);  //to evaluate a give postFix expression in stack form 
template <class T>
bool stackExprToPostFixStackExpr(Stack<T> stackExpr,Stack<T> &postFixStackExpr); //to convert an infix stack experssion into a postFix stack expression
bool isCurrentOpertorHigherPrecdanceThanLast(string curr, string last);	//compare precedance of current operator and what was last in the Operators stack
double stringToDouble(string str);//coverts String to double
string doubleToString(double val);//coverts double to string



int main(){	
/********************************************************************
  Batch:Drb2002

  Surafel Zewdu  - GC5332
  
  Yodahe Zerihun - AJ6475 

********************************************************************/

	restart:
	try{
	string input="";//.........................................To Hold User Input String Expression
	Stack <string>stackExpr;//.................................To hold the string expression converted into Stack of String Expression 
	Stack <string>postFixStackExpr;//...........................To Hold the PostFix Form of the Stack From Expression

		cout<<"             Welcome! \n";
		cout<<"Notice! Please use '*' Operator for Multiplication! \n\n\n";
		cout<<"Enter Experssion : ";
		getline(cin,input);						//...................................Getting experssion
		stringExprToStack(input,stackExpr);		//...................................Converting input from string experssion to Stack of String experssion  
		stackExprToPostFixStackExpr(stackExpr, postFixStackExpr);//..................Converting Stack of String experssion to PostFix Stack of String experssion			
		string result=evalutePostFixStackExpr(postFixStackExpr);//...................Evaluating what's in the PostFix Expression Stack
		if(isNumeric(result[0]))
			cout<<"Value is : "<<result<<" \n\n";//.......................................Displaying if it is a Numeric Value
		else
			cout<<"Error! Invalid Input \n\n";
	}catch(...){
		cout<<"Error! Invalid Input \n\n";
	}
	system("pause"); system("cls");
	goto restart;
}



bool isNumeric(char x){  // to check if a give character is Numeric by using ascii 
	return (x>=48 && x<=57); //return true if it's a number
}

bool isWhiteSpace(char x){ //to check white spaces in exprssion entered too remove them
	return x==32; //returns true if it's whiteSpace
}

template <class T>
bool stringExprToStack(string input, Stack<T>&stackExpr){  //to convert a string input from the user into a stack form
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
		
	return true; //done!
}

template <class T>
string evalutePostFixStackExpr(Stack <T>expr){ //to evaluate a give postFix expression in stack form 


	//while condition to iterate all elems of the stack
	while(!expr.isEmpty()){
		double arr[expr.getCount()]; //temp array to hold top of the stack elems until an operator is found
		
		//below while loop is used to add elems to a temp array until an operator(non-numeric) elems is found
		int count=0;
		while(!expr.isEmpty() && isNumeric(expr.peek()[0])){
			arr[count]=stringToDouble(expr.pop());
			count++;
		}
		
		// Below is code calulating top of the stack
		string Opertor=expr.pop();
		count--;
	
		if(Opertor=="^") 
			 	arr[count-1]= pow((int)arr[count-1],(int)arr[count]);
		else if(Opertor=="%")
				arr[count-1]= (int)arr[count-1]%(int)arr[count];
		else if(Opertor=="*") 
				arr[count-1]= arr[count-1]*arr[count];
		else if(Opertor=="/") 
				arr[count-1]= arr[count-1]/arr[count];
		else if(Opertor=="+") 
				arr[count-1]= arr[count-1]+arr[count];
		else if(Opertor=="-") 
				arr[count-1]= arr[count-1]-arr[count];
		count--;
		
		
		//below is code returning calualuted value from temp array to top of stack
		while(count>=0)
		   expr.push(doubleToString(arr[count--]));

		if(expr.getCount()==1)
				return expr.pop();
	}
	
}

template <class T>
bool stackExprToPostFixStackExpr(Stack<T> stackExpr,Stack<T> &postFixStackExpr){ //to convert an infix stack experssion into a postFix stack expression
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
	Stack<T>temp1,temp2;
	while(!postFixStackExpr.isEmpty())
		temp1.push(postFixStackExpr.pop());
	while(!temp1.isEmpty())
		temp2.push(temp1.pop());
	while(!temp2.isEmpty())
			postFixStackExpr.push(temp2.pop());  
	
	return true; //done!	
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


