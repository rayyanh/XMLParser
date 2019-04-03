//
// Created by Rayyan on 1/27/2019.
//

/**
 * @author Rayyan Hussain
 * This program is a simple XML Parser that has functionality such as reading in a file, printing contents in a clear
 * manner to the console, as well as printing with XML format to a file.
 */
#include <string>
#include <vector>
#include <iostream>
#include <map>
#include <fstream>

#ifndef ASSIGNMENTTWO_XMLNODE_H
#define ASSIGNMENTTWO_XMLNODE_H
using namespace std;

class XMLNode {
public:
    XMLNode(); //default

    XMLNode(string filename); //most used constructor

    void ParseFile(string filename); //used to go through files

    void ParseLine(string line); //line by line, ties into parsefile

    void WriteFile(string filename); //writes to actual file

    void PrettyPrintDocument(); //prints to console

    string name;   // name of the node
    map<string, string> properties;  // any properties found in the node start tag
    string content; // if the node has content between the start and end tag, put it here
    vector<XMLNode *> children;  // if the node has children, create new Nodes and store their pointers here
    vector<string> split(string line, char delimiter);

private:
    string PrettyHelper(int level); //PrettyPrintDoc helper

    string PrintHelper(); //WriteFile helper

    vector<string> mySplit(string line, string delimiter); //split function helper

};


#endif //ASSIGNMENTTWO_XMLNODE_H