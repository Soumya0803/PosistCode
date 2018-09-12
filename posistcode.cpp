#include <bits/stdc++.h>
#include <time.h>
#define pb push_back
 
using namespace std;


map<string,string> my_map;

int globalNO=0;
int globalownerNo=0;
 
string Utc()
{
	time_t now = time(0);
	tm *gmtm = gmtime(&now);
	string dt = asctime(gmtm);
	
	return dt;
} 

string getID(int nodeNumber)
{
	string str="";
	
	//as utc time will always be different we will always have different Id'str 
	str=str+Utc()+to_string(nodeNumber);
	
	return str;
}
 
 
string getOwnerId()
{
	string str="";
	
	//as utc time will always be different we will always have different Id'str 
	str=str+Utc()+to_string(globalownerNo);
	globalNO++;
	
	return str;
	
} 

string Hash(string str)
{
	long long HashNo=0;
	
	for(int i=0;i<str.length();i++)
	{
		HashNo+=(int)str[i];
	}
	
	HashNo%=10;
	
	return to_string(HashNo);
}

class Node
{
	
	
	public:
	
		string timestamp;
		string data;
		int nodeNumber;
		string nodeId;
		string referenceNodeId;
		vector<string> childReferenceNodeId;
		string genesisReferenceNodeId;
		string HashValue;
		
	
		Node()
		{
			timestamp=Utc();
			
			nodeNumber=globalNO++;
			nodeId=getID(nodeNumber);
			
			childReferenceNodeId.clear();
			childReferenceNodeId.resize(0);
			
		}
	
	
	
	
};


string encrypt(string str, string key)
{
	int keyint=0;
	
	for(int i=0;i<key.length();i++)
	{
		keyint+=(int)key[i];
	}
	
	keyint%=10;
	
	char keychar= (char)keyint;
	
	for(int i=0;i<str.length();i++)
	{
		str[i]= str[i] ^ keychar;
	}
	
	return str;
}


string decrypt(string str, string key)
{
	int keyint=0;
	
	for(int i=0;i<key.length();i++)
	{
		keyint+=(int)key[i];
	}
	
	keyint%=10;
	
	char keychar= (char)keyint;
	
	for(int i=0;i<str.length();i++)
	{
		str[i]= str[i] ^ keychar;
	}
	
	return str;
}

void addChild(Node *node, Node *par)
{
	par->childReferenceNodeId.pb(to_string(node));
}


void filldata(Node *node)
{
	cout<<"Enter your name\n";
	string ownername;
	cin>>ownername;
	
	cout<<"Provide your value\n";
	int value;
	cin>>value;
	
	cout<<"Enter your encryption key as a sequence of integers and/or characters\n";
	string key;
	cin>>key;
	
	string ownerid=getOwnerId();
	cout<<"Your owner id is "<<ownerid<<"\n";
	
	
	//first Hash the original data and create a Hash string
	string Hashstring=Hash(ownerid+value+ownername);
	
	node->data=encrypt(ownerid+value+ownername+Hashstring,key);
	
}


string gethashvalue(Node *node)
{
	string str=node->timestamp + node->data + to_string(node->nodeNumber) + node->nodeId + node->referenceNodeId + node->genesisReferenceNodeId;
	for(auto it: node->childReferenceNodeId)
	{
		str= str+ it;
	}
	
	return Hash(str);
}

void fillnode(Node *node, Node *par)
{
	node->referenceNodeId=to_string(par);
	
	
	addChild(node,par);
	
	node->genesisReferenceNodeId=par->genesisReferenceNodeId;
	
	
	
	filldata(node);
	
	
	stringstream ss;
	ss << node;
	string address=ss.str();
	
	my_map.insert( pair<string,string>(nodeId,address);
	
}


void creategenesisnode()
{
	Node node;
	Node *nodepointer=&node;
	
	string nulls="":
	nulls=nulls+'\0';
	
	nodepointer->referenceNodeId=nulls;
	nodepointer->genesisReferenceNodeId=nodepointer; 
	
	
	filldata(nodepointer);
	
	nodepointer->HashValue=gethashvalue(nodepointer);
	
}


void createchildnodes()
{
	cout<<"give us the nodeid of which you want this node to be a child\n";
}



int main()
{
	
	cout<<"Choose your task number, your first task has to be the task 1.\n";
	cout<<"1. create genessis node\n";
	
	
	
	
	int taskno;
	
	
	
	creategenesisnode();
	createchildnodes();
	task4();
	
	

	return 0;
}