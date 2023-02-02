#ifndef XML_FORMATTER_H
#define XML_FORMATTER_H

#include <iostream>
#include <string>
#include <locale>
#include <algorithm>
#include <fstream>
#include <queue>

using namespace std;

void getChildren(string Xml,queue <string>& children);
string Formatter(string XMLStr,int level);

#endif // XML_FORMATTER_H
