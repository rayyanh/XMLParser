#include<iostream>
#include "XMLNode.h"
#include<vector>
#include<map>
#include<fstream>

using namespace std;

int main() {

//    ifstream test;
//    test.open("test.xml");
//    while (!test.eof()) {
//        string line;
//        getline(test, line);
//        if (line.length() == 0) {  // skip empty liness
//            continue;
//        }
//        XMLNode myNode = myNode.ParseLine(line);   // turns a line into a node
//
//        // print out the Node info
//        cout << "***********************" << endl;
//        cout << "Node: " << myNode.name << endl;
//        for (const auto &kv : myNode.properties) {
//            cout << "\t" << kv.first << ": " << kv.second << endl;
//        }
//        cout << "Content: " << myNode.content << endl;
//        cout << "***********************" << endl;
//    }
//    test.close();
//    return 0;

    XMLNode test1("test.xml");
}
