#include <iostream>
#include <string>
#include <stack>
#include <stdlib.h>
using namespace std;

string MORSE;
//Message class.
class Message {
protected:
	string x;
public:
	virtual void print( );
	void getMessage();
	Message( );
	Message( string m );
	~Message( );
};
//default constructor
Message::Message( )
{
	x = "";
}

Message::Message( string m )
{
	x = m ;
}
//destructor
Message::~Message()
{
}
//print information
void Message::print( )
{
	cout <<"Message is :  "<<x << endl;
	cout <<"Morse code is:  "<<MORSE << endl;
}
//update information
void Message::getMessage(){
	cout<<"Please enter message!"<<endl;
	getline(cin, x);
}

//MorsecodeMessage class
class MorseCodeMessage : public Message {
private:
	string result;
public:
	void translate( );
	MorseCodeMessage(string m );
	~MorseCodeMessage( );
	void Mprint( );
};

//translate function
void MorseCodeMessage::translate( )
{
	string MS_C[]= {"-----", ".----", "..---", "...--", "....-",".....", "-....", "--...", "---..", "----.",
					"---...","", "", "-...-","", "..--..",".--.-.",".-", "-...",	"-.-.",
					"-..", ".", "..-.",  "--.",   "....", "..",    ".---",  "-.-",   ".-..",  "--",
					"-.", "---",   ".--.",  "--.-",  ".-.", "...",   "-",     "..-",   "...-",  ".--",
					"-..-", "-.--",  "--..",  "-.--.-","-..-.", "-.--.-","", "",   "",  ".-",
					"-...", "-.-.",  "-..",   ".", "..-.","--.", "....",  "..", ".---",  "-.-",
					".-..", "--", "-.", "---", ".--.", "--.-", ".-.", "...", "-", "..-",
					"...-", ".--", "-..-", "-.--", "--..","-.--.-","", "-.--.-" };
	//for loop to find the correct position
	for( int i = 0; i < x.length( ); i++ )
	{
		//set the range and replace character
		if( '0' <= x.at( i ) && x.at( i ) <= '}' )
			result += MS_C[ x[ i ] - 48 ] + " ";
		else if( x.at( i ) == ' ' )
			result += "\t";
		else
			result += "";
	}
	MORSE=result;
}

MorseCodeMessage::MorseCodeMessage(string m) : Message(m)
{
	result = "";
	translate();
}
//destructor
MorseCodeMessage::~MorseCodeMessage()
{
}
//print the information
void MorseCodeMessage::Mprint()
{
	cout <<"Message is :  "<< x << endl;
	cout <<"Morse code is :  "<< result << endl;
}
//MessageStack class
class MessageStack {
private:
	stack<MorseCodeMessage*> top;
public:
	MessageStack( MorseCodeMessage* m );
	~MessageStack();
	void push( MorseCodeMessage* m );
	void pop();
	virtual void printSTC();
};

MessageStack::MessageStack( MorseCodeMessage* m )
{
	top.push(m);
}
//destructor, free the stack.
MessageStack::~MessageStack()
{
	while( !top.empty() )
		top.pop();
}
//push new message into stack.
void MessageStack::push( MorseCodeMessage* m )
{
	top.push(m);
}
//pop out message.
void MessageStack::pop()
{
	//check if it is empty stack
	if(top.empty()){
		cout<<"The stack is empty!"<<endl;
		exit (-1);
	}
	//pop out.
	top.pop();
}
//print out information
void MessageStack::printSTC()
{
	stack<MorseCodeMessage*> temp;
	//check if it is empty.
	if(top.empty()){
		cout<<"The stack is empty!"<<endl;
	}
	//save the original stack into temp, and print the stack.
	while( !top.empty())
	{
		top.top() -> Mprint();
		temp.push(top.top());
		top.pop();
	}
	//reload the original stack.
	while(!temp.empty())
	{
		top.push(temp.top());
		temp.pop();
	}
}

int main( void )
{

	string MES;
	cout<<"Please enter what you want to convert!"<<endl;
	getline(cin, MES);
	//initialize and input the first message
	MorseCodeMessage MCM(MES);
	MessageStack S1(&MCM);
	int opt;
	//looping to do the menu.
	do{
		cout<<"Please enter the options!"<<endl;
		cout<<"1.Enter new message"<<endl;
		cout<<"2.Print Result"<<endl;
		cout<<"3.Pop"<<endl;
		cout<<"4.Quit"<<endl;
		cin>>opt;
		switch(opt){
			//add new message
			case 1:{
				MorseCodeMessage MCM("");
				cin.ignore();
				MCM.getMessage();
				MCM.translate();
				S1.push(&MCM);
				break;
			}
			//pop
			case 3:{
				S1.pop();
				break;
			}
			//print out
			case 2:{
				S1.printSTC();
				break;
			}
			//quit
			case 4:{
				cout<<"End"<<endl;
				break;
			}
			default:{
				cout<<"ERROR!"<<endl;
				exit(-1);
				break;
			}
		}
	}while (opt!=4);

	return 0;
}
















