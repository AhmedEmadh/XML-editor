#include <iostream>
#include "stdafx.h"
//#using <mscorlib.dll>
#include <tchar.h>
#include "rapidxml.hpp"
#include "rapidxml_iterators.hpp"
#include "rapidxml_print.hpp"
#include "rapidxml_utils.hpp"
#include <string>
#include <stack>


using namespace std;
//using namespace System::Xml;
bool balanced(const std::string& xml)
{
    std::stack<std::string> tags;

    auto from = 0u;
    while (from < xml.length()) {
        // check for tag
        const auto tag_open = xml.find('<', from);
        const auto tag_close = xml.find('>', tag_open);

        // no tag found
        if (tag_open == std::string::npos)
            break;

        // incomplete tag
        if (tag_close == std::string::npos)
            return false;

        // get tag
        auto tag = xml.substr(tag_open, tag_close + 1 - tag_open);
        from = tag_close + 1;

        // if its an opening tag, push the closing one
        if (tag[1] != '/') {
            tags.push(tag.insert(1, "/"));
        }
            // otherwise (if its a closing tag), check if it was expected
        else {
            if (tags.empty())
                return false;
            else if (tags.top() == tag)
                tags.pop();
            else
                return false;
        }
    }

    // all tags must have been closed
    return tags.empty();
}


int main() {



    return 0;
}