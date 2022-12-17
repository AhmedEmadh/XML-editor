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
    //added is_tags_balwnced private method that check whether the tags are balenced or not
    bool is_tags_balenced(){
        
        if(!this->is_balenced()) return false;
        stack<string> stk;
        string tag;
        //int end;
        for(int i=0;i<content.size();i++){
            
            //case 1
            if ((content[i]=='<') && (content[i+1]!='/')&&(content[i+1]!='?'))//case 1: opening tag handling
            {
                cout << "opening tag found"<<endl;
                i++;
                tag = "";
                
                //end = i;
                while(content[i] == ' ') i++;
                while((content[i] != ' ')&&(content[i] != '>')) {tag = tag+content[i];i++;}
                cout << tag << "  is pushing"<<endl;
                stk.push(tag);
                while(content[i] != '>') i++;
                
            }//opening tag handled and pushed to stack and exited

            //case 2
            if((content[i]=='<')&&(content[i+1] == '/')){//case 2: closing tag handling
                cout << "closing tag found"<<endl;
                i++;i++;
                if(stk.empty()){cout<<"closing tag found and stack is empty (failed)"<<endl; return false;}
                tag = "";
                while(content[i]==' ')i++;
                while((content[i]!=' ')&&(content[i] != '>')){tag = tag+content[i];i++;}
                cout << "comparing tag: "<< tag<<" and stack top: "<<stk.top()<<endl;
                if (stk.top() == tag){
                    cout<< "compare is true "<<stk.top()<<" is poping"<<endl;
                    stk.pop();
                }else{cout<<"compare is false"<<endl;}
                while(content[i] != '>') i++;
                
                 
            }
          
        }//end for
        
        if(stk.empty()){//problem is stack is not empty at the end of a correct file
            cout<<"stack is empty at the end (succedded)"<<endl;
            return true;
        } else {
            cout <<"stack is not empty at the end (failed)"<<endl;
            return false;
            
        }
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
        if((this->is_balenced())&&(this->is_tags_balenced())){
            return true;
        } else {
            return false;
        }
    }
    string minify(string xml)
    {
        for (int i = 0; i < xml.length(); i++)
        {
            if ((xml[i] == ' ') || (xml[i] == '\n') || (xml[i] == '\t'))
            {
                xml.erase(xml.begin() + i);
                i--;
            }
        }
        return xml;
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
 void Format() {
        
        string pathfile ;
        std::string names[100] ;  // Array of words between <  > 
        cout << "Enter the XML path file to format \n" ;
        cin >> pathfile ;
        std::string content = readFileIntoString( pathfile );

        int index = 0;
        int nameslength =0 ;  
        // Store the words between < > in Array
        for ( int i=0 ; i<content.length() ; i++  ) {
            
            if ( content[i] == '<' && content[i+1] != '/' )  {
                 int sub = i ;
                 while( content[i] != '>'  ) { i++ ; }
                 for( int z = sub+1 ; z<=i-1 ; z++ ) {
                      
                     names[index]+=content[z]; }
                     index++ ; nameslength ++ ; 
            }      
        } 
              std::string c = content ;
              int r = 3 ;       // Identaion
              for ( int i=1 ; i<nameslength ;i++ ) {     // Insert spaces before < 
                 int index2 = 1; 
                 while ((index2 = c.find(names[i], index2)) != string::npos ) {

                     c.insert( index2-1 , r , ' ')  ;   index2+=r ; 
                     index2 += names[i].length();  
                 }
              }
              for( int j=0 ; j<c.length() ; j++ ) {      // Make < before / exatlly 

                if( c[j] == '<' && c[j+1] == ' '){
                     int e = j ;
                    while( c[e+1] != '/' ) e++ ;
                    swap( c[j] , c[e] );
                }
              } 
                        cout << c ;             
    }

int main() {



    return 0;
}
