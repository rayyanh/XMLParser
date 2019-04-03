#include <utility>

/**
 * @author Rayyan Hussain
 *
 * This program is essentially an XML parser for a very basic XML file. It contains methods that allow it to parse
 * through the file, read it in, print it, as well as print it properly formatted to an XML file.
 */
#include <iostream>
#include <string>
#include <vector>       //include statements used for this code
#include <map>
#include <fstream>
#include "XMLNode.h"

using namespace std;

/**
 * This is the default constructor, it is used for allocating memory
 */
XMLNode::XMLNode() = default;

/**
 * This is the constructor used to initialize parsefile with the inputted filename from the user or driver file
 * @param filename
 */
XMLNode::XMLNode(string filename) {
    ParseFile(move(filename));
}

/**
 * This method splits code based on a given line, and a charecter delimeter, which is what is cut out. It goes line
 * by line.
 *
 * Method provided by Professor Brent Lagesse.
 *
 * @param delimiter, line
 * @return splitStrings
 */
vector<string> XMLNode::split(string line, char delimiter) {
    vector<string> splitStrings;
    int start = 0;
    int end = line.find(delimiter);
    while (end != string::npos) {
        string subs = line.substr(static_cast<unsigned int>(start), static_cast<unsigned int>(end - start));
        start = end + 1;
        end = line.find(delimiter, static_cast<unsigned int>(start));
        splitStrings.push_back(subs);
    }
    string subs = line.substr(static_cast<unsigned int>(start), line.length() - start);
    splitStrings.push_back(subs);
    return splitStrings;
}

/**
 * This method parses through the file. It does so by opening the file and continuing to go through until the file is
 * reaching its end. It uses a recursive call to a different method with the 'line' the parser is based on.
 *
 * ParseFile method
 * @param filename
 */
void XMLNode::ParseFile(string filename) {
    ifstream openFile;
    openFile.open(filename);
    while (!openFile.eof()) { // while not at end of
        string line;
        getline(openFile, line);
        if (line.length() == 0) {  // skip empty liness
            continue;
        }
        ParseLine(line);   // turns a line into a node
    }
    openFile.close();
}

/**
 * This method parses through each line and is essentially a helper function for ParseLine. It does so by checking for
 * values and splitting them based on the = sign. It uses that to get content and store it in the form of 'name'
 * The method also gets content from each node by checking in with the characters used to enclose each of the content.
 *
 *
 * @param line
 */
void XMLNode::ParseLine(string line) {
    int startOfTag = 1;
    int endOfTag = line.find('>');
    string tagString = line.substr(static_cast<unsigned int>(startOfTag),
                                   static_cast<unsigned int>(endOfTag - startOfTag));
    vector<string> properties2 = split(tagString, ' ');
    for (const auto &val: properties2) {
        vector<string> props = split(val, '='); // Brent's code
        if (props.size() != 2) {
            name = props[0];
        } else {
            properties.insert(pair<string, string>(props[0], props[1]));
        }
    }
    // gets the content from the node
    // the contents could be more nodes, so it is up to you to parse the contents for more nodes (think, recursion!)
    int startOfContent = endOfTag + 1;
    string endNode = "</" + name + ">";
    int endOfContent = line.rfind(endNode);
    string substr = line.substr(static_cast<unsigned int>(startOfContent),
                                static_cast<unsigned int>(endOfContent - startOfContent));
    int last = substr.find("</" + name + ">");
    int first = substr.find("<" + name);
    if (substr.find('<') == -1) { //if there is no <
        content = substr;
    } else {
        if (last < first) { //tries to check for children inside a single line
            vector<string> splitAgain;
            splitAgain = mySplit(line, endNode);
            for (const string &splitter : splitAgain) {
                auto *myNode2 = new XMLNode();
                myNode2->ParseLine(splitter);
                children.push_back(myNode2);
            }
        } else {
            auto *myNode3 = new XMLNode();
            myNode3->ParseLine(substr);
            children.push_back(myNode3);
        }
    }
}

/**
 * This method is my helper function to be able to catch other cases that the other split function could not achieve.
 * This is used to try to split children based on delimeter and line they are on.
 * @param line, delimiter
 * @return splitter
 */
vector<string> XMLNode::mySplit(string line, string delimiter) {
    vector<string> splitter;
    int first = 0;
    int last;
    last = line.find(delimiter) + delimiter.length();
    string breakHere;
    breakHere = line.substr(static_cast<unsigned int>(first), static_cast<unsigned int>(last - first));
    first = last;
    splitter.push_back(breakHere);
    breakHere = line.substr(static_cast<unsigned int>(first), line.length() - first);
    splitter.push_back(breakHere);
    return splitter;
}

/**
 * This method is the helper method for printing. It uses the concept of levels to achieve its task. The method
 * basically is set to print level by level so that proper indentation can occur. All indentation is calculated based
 * on the 'level' or floor the code is on. Some of the code is shared with Professor Brents code.
 *
 * It is also recursive
 *
 * @param level
 * @return resultFinal
 */
string XMLNode::PrettyHelper(int level) {
    string result;
    string space;
    for (int i = 0; i < level; i++) {
        space += "\t";
    }
    result = space + "Node: " + name + "\n" + space;
    for (const auto &kv : properties) { //Brents code
        result += ("\t" + kv.first + ": " + kv.second + "\n");
    }
    if (!content.empty()) {
        result += space + "\t\tContent: " + content + "\n";
    }
    string child;
    string spacing;
    spacing = result;
    level++;
    for (XMLNode *allChildren : children) {
        string child2;
        child2 = allChildren->PrettyHelper(level); //recursive call
        child += child2;
    }
    string resultFinal;
    resultFinal = spacing + child;
    return resultFinal;
}

/**
 * Simple print function, prints nicely to the console and is based on the PrettyHelper function. Calls it with a start
 * level of 0 and goes from there.
 */
void XMLNode::PrettyPrintDocument() {
    cout << "XML File Printed to Console: " << endl;
    cout << "--------------------------------------------------------------" << endl;
    cout << PrettyHelper(0);
    cout << "--------------------------------------------------------------" << endl;
}

/**
 * very similar to PrettyHelper function and uses similar functionality. Instead of using spacing, it uses the actual
 * proper syntax for an XML file.
 *
 * @return resultFinal
 */
string XMLNode::PrintHelper() {
    string result;
    result = "<" + name;
    for (const auto &kv : properties) {
        result += " " + kv.first + "=" + kv.second;
    }
    result += ">";
    if (!content.empty()) {
        result += content + "</" + name + ">";
    }
    string childPrint;
    string printer = result;
    for (XMLNode *childPrinter : children) {
        string str;
        str = childPrinter->PrintHelper(); //recursive call
        childPrint += str;
    }
    string resultFinal;
    resultFinal = printer + childPrint;
    return resultFinal;
}

/**
 * Simple print function, prints in a formatted XML file. Is similar to the print function as it uses and does most work
 * in the helper function.
 */
void XMLNode::WriteFile(string filename) {
    ofstream newFile(filename);
    cout << "--------------------------------------------------------------" << endl;
    cout << "Writing to File..." << endl;
    newFile << PrintHelper();
    cout << "Success! Saved as " << filename << endl;
    cout << "--------------------------------------------------------------" << endl;
}