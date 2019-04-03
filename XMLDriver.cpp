#include<iostream>
#include "XMLNode.h"

using namespace std;

int main () {

	XMLNode test1;
	XMLNode test2("test2.xml");
	test1.ParseFile("test1.xml");

	test1.WriteFile("test3.xml");
	XMLNode test3("test3.xml");

	test1.PrettyPrintDocument();
	test2.PrettyPrintDocument();
	test3.PrettyPrintDocument();

	return 0;
}
