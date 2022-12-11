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

//Ahmed Emad's includes
#include <fstream>
#include <sstream>
#include <string>

using namespace std;
//using namespace System::Xml;

/*
XMLReadFile is written by Ahmed Emad
please read carfully to understand the operation of the class:
-the constructor takes relative path of the file
-the content of the file is readed and encapsulated in the class
-the method is_balanced returnes balance state (first stage to check correctness) and state takes values = {true, false}
-the method is_correct returns the final state of the file (check that all stages returns true) and state takes values = {true, false }

example of using the class:

int main(){

    XmlReadFile myfile("file.xml");
    cout << myfile.is_correct() << endl;
    return 0;
}

here:
the program prints 1: if the file is balenced
the program prints 0: if the file is not balenced
*/

class XmlReadFile{
 private:
    string content;
    string readFileIntoString(const string& path) {
    ifstream input_file(path);
    if (!input_file.is_open()) {
        cerr << "Could not open the file - '"
             << path << "'" << endl;
        exit(EXIT_FAILURE);
    }
    return string((std::istreambuf_iterator<char>(input_file)), std::istreambuf_iterator<char>());
    }
    string get_content(){
        return this->content;
    }
    bool is_balenced(){
        stack<char> stk;
        for(int i=0;i<content.length();i++){
            if(content[i] == '<'){
                stk.push(content[i]);
            } else if(content[i] == '>'){
                if(!stk.empty()){
                    stk.pop();
                } else {
                    return false;
                }
            }
        }
        if(stk.empty()){
            return true;
        } else {
            return false;
        }
        
    }
    bool is_valid(){
        return true;
    }
    string to_json(){
        return "not now";
    }
 public:
    XmlReadFile (const string& path){
        content = this->readFileIntoString(path);
    }
    
    int sizeOfContent(){
        return this->content.size();
    }
    bool is_correct(){
        if((this->is_balenced()) && (this->is_valid())){
            return true;
        } else {
            return false;
        }
    }
};




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