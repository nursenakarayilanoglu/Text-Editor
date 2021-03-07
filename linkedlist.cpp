#include <string>
#include <iostream>
#include <fstream>
#include <stack>
using namespace std;
class Node{
	public:
		Node(){
			next=0;
		}
		Node(string line,Node *ptr = 0){
			data=line;
			next=ptr;
		}
		string data;
		Node *next;
};

class SingleLinkedList{
	private:
		Node *head;
		int size;
		stack <pair<pair<int,int>,pair<string,string> > > buffer; // first pair is the line numbers, second pair is the text and the command
		pair <pair<int,int>,pair<string,string> > instructions;
	public:
		SingleLinkedList(){
			head = 0;
			size = 0;
		}
		int isEmpty() {
        	return head == 0;
    	}
    	
    	string eachline;
		int pageNum=1;
		
    	void openFile(string filename){
			ifstream file;
			file.open(filename.c_str());
			if(file.is_open() == false){
	            cout << "Couldn't open the file" << endl;
	            return;
			}
			else{
				int i=1;
				while(getline(file,eachline)){
					insert(eachline,i,false);
					i++;
				}
			}
		}
		void insert(string line, int lineNumber, bool flag){
			Node* tempLine=head;
			Node* prevTempLine=head;
			if(lineNumber==1){
				head=new Node(line,tempLine);
			}
			else{
				tempLine=head->next;
				int i=0;
				for(i=1;i<lineNumber-1 && tempLine!=NULL;i++){
					tempLine=tempLine->next;
					prevTempLine=prevTempLine->next;
				}
				if(prevTempLine->next==0){
					for(int j=1;j<lineNumber-i;j++){
						prevTempLine->next=new Node(" ",0);
						prevTempLine=prevTempLine->next;
						size++;
					}
				}
				/*if(tempLine!=NULL && (tempLine->data==" " || tempLine->data=="") && flag){ 
					tempLine->data=line;
				}
				else{*/
					prevTempLine->next=new Node(line,tempLine);
					prevTempLine->next->next=tempLine;
			//	}			
			}
			if(flag)
				buffer.push(make_pair(make_pair(lineNumber,-1),make_pair(line,"delete")));
			
			size++;
		}
		void deleteLine(int lineNumber,bool flag){
			if(lineNumber>size){
				cout<<"Out of Bound!"<<endl;
				return;
			}
			Node* tempLine=head;
			Node* prevTempLine=head;
			Node* temporaryNode;
			int temp_size=0;
			string tempData;
			if(lineNumber==1){
				head=prevTempLine->next;
				tempData=prevTempLine->data;
				prevTempLine=0;
			}
			else{
				tempLine=head->next;
				for(int i=1;i<lineNumber-1 && tempLine!=NULL;i++){
					if(tempLine->data!=" "){
						temporaryNode=tempLine;
						temp_size=i;
					}
					tempLine=tempLine->next;
					prevTempLine=prevTempLine->next;
				}
				prevTempLine->next=tempLine->next;
				tempData=tempLine->data;
				tempLine=0;
				if(prevTempLine->next==0){
					for(int i=1;i<(lineNumber-1)-temp_size;i++)
						size--;
					temporaryNode->next=prevTempLine->next;
				}
				
			}
			if(flag)
				buffer.push(make_pair(make_pair(lineNumber,-1),make_pair(tempData,"insert")));
			size--;
		}
		void print(int num){
			Node *tmp=head;
			for(int j=1;tmp!=NULL;j++){
				if(j>num*10-10 && j<=num*10)
					cout<<"("<<j<<")"<<tmp->data<<endl;
				tmp=tmp->next;
			}
			cout<<"---Page "<<num<<" ---\n"<<endl;
		}
		void move(int n, int m){
			if(n>size) return;
			Node *tmp=head;	
			string linedata;
			for(int i=1;i<n;i++){
				tmp=tmp->next;
			}
			linedata=tmp->data;
		
			deleteLine(n,false);
			insert(linedata,m,false);
			
			buffer.push(make_pair(make_pair(n,m),make_pair(linedata,"move")));
		}
		
		void replace(string line, int lineNumber){
			string tmpData;
			if(lineNumber>size){
				cout<<"Out of Bound!"<<endl;
				return;
			}
			Node *tmp=head;
			for(int i=1;i<lineNumber;i++){
				tmp=tmp->next;
			}
			tmpData=tmp->data;
			tmp->data=line;
			buffer.push(make_pair(make_pair(lineNumber,-1),make_pair(tmpData,"replace")));
		}
		
		void next(){
			pageNum++;
			print(pageNum);
		}
		
		void prev(){
			pageNum--;
			if(pageNum<1)
				pageNum=1;
			print(pageNum);
		}
		
		void undo(){
			if(!buffer.empty()){
				instructions = buffer.top();
				buffer.pop();
				if(instructions.second.second=="delete"){
					deleteLine(instructions.first.first,true);
				}
				else if(instructions.second.second=="insert"){
					insert(instructions.second.first,instructions.first.first,true);
				}
				else if(instructions.second.second=="move"){
					move(instructions.first.second,instructions.first.first);
				}
				else if(instructions.second.second=="replace"){
					replace(instructions.second.first,instructions.first.first);
				}
				else{
					//do nothing;
				}
				buffer.pop();
			}
		}
		
		void saveFile(string filename){
			Node *tmp=head;
			fstream my_file;
			my_file.open(filename.c_str());
			for(int j=1;tmp!=NULL;j++){
				my_file<<tmp->data<<endl;
				tmp=tmp->next;
			}
			my_file.close();
			
			while(!buffer.empty())
				buffer.pop();
		}
		
		int get_size(){
			return size;
		}
};
