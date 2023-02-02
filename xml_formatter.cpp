#include "xml_formatter.h"
#include <iostream>
#include <fstream>



void getChildren(string Xml,queue <string>& children)
{
    int openIndex;
    int closeIndex;
    string tagName;
    int i=0,j=0;
    int tagIndex=0;

    openIndex=Xml.find_first_of('<');
    //enhanced functionality better for big o but still not working there is an infite loop
/*
    while(Xml.find_first_of('<',tagIndex)<Xml.length()){
        closeIndex=Xml.find_first_of('>',tagIndex);
        cout<<"stuck"<<endl;
        tagName=Xml.substr(openIndex,closeIndex-openIndex-1);
        children.push(tagName);
        tagIndex=Xml.find("</"+tagName+">",tagIndex);
        openIndex=Xml.find_first_of('<',tagIndex);
    }
    */

   //working but bad for Big O
    while(i<=Xml.length()){

       if(Xml[i]=='<'){
            j=i;

           while(Xml[j]!='>'){
                j++;
            }
            tagName=Xml.substr(i+1,j-i-1);

            (children).push(tagName);
            closeIndex=Xml.find("</"+tagName+">",i);
            i=closeIndex+tagName.length();

        }
        else{

            i++;
        }
    }

}

string Formatter(string XMLStr,int level){
    string outputXml="";
    int indexOfFirstOpen=XMLStr.find_first_of("<");
    //Base Case
    if(indexOfFirstOpen==-1){
        int firstChar=XMLStr.find_first_not_of(' ');
        outputXml.append(level,'\t');
        if(firstChar==-1)
        {
            return " ";
        }
        else
        {
            return outputXml+=XMLStr.substr(firstChar)+'\n';
        }

    }
    else{
        queue <string> children;
        //get The Name of the Tag
        int indexOfFirstOpen=XMLStr.find_first_of("<");
        int indexOfFirstClose=XMLStr.find_first_of(">");
        string tagname = XMLStr.substr(indexOfFirstOpen+1,indexOfFirstClose-indexOfFirstOpen-1);
        int closeTag=XMLStr.find("</"+tagname+">");
        //create a string for the inner Children of said string
        string tagString=XMLStr.substr(indexOfFirstClose+1,closeTag-indexOfFirstClose-1);
        //traverse the string looking for first degree children of said string
        getChildren(tagString,children);

        outputXml.append(level,'\t');
        outputXml+="<"+tagname+">\n";


        if(!children.empty()){
            int childCounter=0;
            int looper=children.size();//we store the size in a variable because everytime we pop the size will decrease
                for(int i=0;i<looper;i++){
                //get the Child Tag name from the Queue then get its string including its tagname and put it in variable inner Xml
                string childTag=children.front();
                int childOpenTag=tagString.find("<"+childTag+">",childCounter);
                int childCloseTag=tagString.find("</"+childTag+">",childCounter)+childTag.length()+3;//+3 for the </> so that we have the entire child
                string innerXML=tagString.substr(childOpenTag,childCloseTag-childOpenTag);//getting the inner Substring
                outputXml+=Formatter(innerXML,level+1);//calling the function recursively on the child
                children.pop();

            //    outputXml.append(level,'\t');
                outputXml.append(level+1,'\t');
                outputXml.append("</"+childTag+">\n");

                childCounter=childCloseTag;

            }
        }
        //if there are no children then call the function on the inner string and the base case will be returned
        else{
            outputXml+=Formatter(tagString,level+1);
        }
        if(level==0){
            outputXml.append("<"+tagname+">");
        }
    }
    return outputXml;

}

int main() { 

    ifstream input_file("sample1.xml");
    string xmlfile = string((std::istreambuf_iterator<char>(input_file)), std::istreambuf_iterator<char>());
    cout << Formatter( xmlfile , 0 );
 }
