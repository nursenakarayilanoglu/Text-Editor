#include <iostream>
#include "linkedlist.cpp"
#include <vector>
#include <stdlib.h> 
#include <string.h>
#include <sstream>
#include <algorithm>
#include <iterator>

using namespace std;


int main(){
	SingleLinkedList texteditor;
	string input;
	string instr;
	bool flag=false;
	cout<<"Command List:\n(1)open filename\n(2)delete linenumber\n(3)move 1stlinenumber 2ndlinenumber\n(4)replace linenumber text\n(5)next\n(6)prev\n(7)undo\n"<<endl;
	while(input!="Exit" || input!="exit"){
		cout<<"Enter A Command: "<<endl;
		getline(cin,input);
		int pos=input.find(' ');
		instr=input.substr(0,pos);
		if(instr=="open"){
			input.erase(0,pos+1);
			texteditor.openFile(input);
			flag=true;
		}
		else if(instr=="save" && flag){
			input.erase(0,pos+1);
			texteditor.saveFile(input);
			flag=false;
			continue;
		}
		else if(instr=="insert" && flag){
			int number;
			input.erase(0,input.find(' ')+1);
			string lineN=input.substr(0,pos);
			istringstream(lineN)>>number;
			input.erase(0,input.find(' ')+1);
			texteditor.insert(input,number,true);
		}
		else if(instr=="delete" && flag){
			int number;
			input.erase(0,input.find(' ')+1);
			istringstream(input)>>number;
			texteditor.deleteLine(number,true);
		}
		else if(instr=="move" && flag){
			int number1;
			input.erase(0,input.find(' ')+1);
			string lineN=input.substr(0,pos);
			istringstream(lineN)>>number1;
			int number2;
			input.erase(0,input.find(' ')+1);
			string lineN2=input.substr(0,pos);
			istringstream(lineN2)>>number2;
			texteditor.move(number1,number2);
		}
		else if(instr=="replace" && flag){
			int number;
			input.erase(0,input.find(' ')+1);
			string lineN=input.substr(0,pos);
			istringstream(lineN)>>number;
			input.erase(0,input.find(' ')+1);
			texteditor.replace(input,number);
		}
		else if(instr=="next" && flag){
			texteditor.next();
		}
		else if(instr=="prev" && flag){
			texteditor.prev();
		}
		else if(instr=="undo" && flag){
			texteditor.undo();
		}
		else if(instr=="exit"){
			break;
		}
		else{
			if(flag)
				cout<<"Wrong Command! Try Again"<<endl;
		}
		if(flag)
			cout<<"\nText contains "<<texteditor.get_size()<<" lines."<<endl;
		if(instr!="next" && instr!="prev" && flag){
			cout<<endl;
			texteditor.print(texteditor.pageNum);
		}
		
		if(!flag)
			cout<<"\nPlease Open a file before editing!"<<endl;
	}
}
