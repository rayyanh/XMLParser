#include "parsetool.h"
#include <string>
#include <vector>
#include <iostream>
#include <map>

using namespace std;


/*********************************************************
 * Input: 2 Strings - First is the string to split, second is the delimiter
 * Output:  A vector of the split string components
 * Purpose:  splits a string into parts based on a delimiter
 * ******************************************************/

vector<string> split (string line, char delimiter) {

	vector<string> splitStrings;
	int start = 0;
	int end = line.find(delimiter);
	//cout << start << ", " << end << endl;
	while (end != string::npos ) {
		string subs = line.substr(start, end-start);
		//cout << subs << endl;
		start = end+1;
		end = line.find(delimiter, start);
		//cout << "start: " << start << endl;
		//cout << "end: " << end << endl << endl;
		splitStrings.push_back(subs);
	} 
		string subs = line.substr(start, line.length()-start);
		//cout << subs << endl;
		splitStrings.push_back(subs);
		
	return splitStrings;

}


/*************************************************
 * Input:  String -- single line from an XML file in the form
 * 		<name [properties]>contents</name>
 * Output:  Node - contents of a node
 * Purpose:  Converts a single line into a node for processing
 **************************************************/



Node parseline (string line) {

	Node newNode;

	// identifies the start of a node
	int startOfTag = 1;
	int endOfTag = line.find(">");
	string tagString = line.substr(startOfTag, endOfTag - startOfTag);
	//cout << "endOfTag: " << endOfTag << endl;
	//cout << tagString << endl;
	// pulls the name and properties out of the node
	vector<string> properties;
	properties = split(tagString, ' ');
	for (auto val: properties) {
		//cout << "val: " << val << endl;
		vector<string> props = split(val, '=');
		if (props.size() !=  2) {    // we know this is the name of the node
			cout << "node named: " << props[0] << endl;;
			newNode.name = props[0];
		}
		else {   	// got an actual property
			newNode.properties.insert(pair<string,string>(props[0], props[1]));
		}

	}

	// gets the content from the node
	// the contents could be more nodes, so it is up to you to parse the contents for more nodes (think, recursion!)
	int startOfContent = endOfTag+1;
	string endNode = "</" + newNode.name + ">";
	int endOfContent = line.rfind(endNode);
	//cout << "start: " << startOfContent << " end: " << endOfContent << endl;
	newNode.content = line.substr(startOfContent, endOfContent - startOfContent);

	return newNode;




}
