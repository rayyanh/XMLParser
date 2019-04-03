#ifndef _PARSETOOLS_H_
#define _PARSETOOLS_H_

#include<string>
#include<map>
#include<vector>

using namespace std;

struct Node {
	string name;   // name of the node
	map<string, string> properties;  // any properties found in the node start tag
	string content; // if the node has content between the start and end tag, put it here
	vector<Node*> children;  // if the node has children, create new Nodes and store their pointers here

};

Node parseline (string);
vector<string> split (string, char);



#endif
