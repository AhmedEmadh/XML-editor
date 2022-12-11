#include"xml2json.h"



void getChildrenjson(string Xml,queue <string>& children)
{
    int openIndex;
    int closeIndex;
    string tagName;
    int i=0,j=0;
    int tagIndex=0;

    openIndex=Xml.find_first_of('<');


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



bool isArray(queue <string> children){
    if(children.empty()){
        return false;
    }
    string temp=children.front();
    children.pop();
    if((!children.empty())&&temp==children.front()){
        return true;
    }
    else return false;
}

string x2json(string XMLStr,int level){
    string outputJson = "";
    int indexOfFirstOpen=XMLStr.find_first_of("<");
    //Base Case
    if(indexOfFirstOpen==-1){
        return outputJson+=("\""+XMLStr+"\"");
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
        getChildrenjson(tagString,children);

      //if we are in the first level i.e beginning the file we add a {
        if(level==0){
            outputJson+="{\n";
        }
        //insert indentation less than the current level then the tag name
        for(int i=0;i<level;i++){
            outputJson+="\t";
        }
        outputJson+="\""+tagname+"\": ";

        // if the string is an array enter a '['
        bool isArr=isArray(children);
        if(isArr){
            outputJson+="[\n";
        }
       //else if there are children then insert a '{'
        else if(!children.empty()){
            outputJson+="{\n";
        }
        if(!children.empty()){
            int childCounter=0;
            int looper=children.size();//we store the size in a variable because everytime we pop the size will decrease
                for(int i=0;i<looper;i++){
                //get the Child Tag name from the Queue then get its string including its tagname and put it in variable inner Xml
                string childTag=children.front();
                int childOpenTag=tagString.find("<"+childTag+">",childCounter);
                int childCloseTag=tagString.find("</"+childTag+">",childCounter)+childTag.length()+3;//+3 for the </> so that we have the entire child
                string innerXML=tagString.substr(childOpenTag,childCloseTag-childOpenTag);//getting the inner Substring
                outputJson+=x2json(innerXML,level+1);//calling the function recursively on the child
                //poping the queue for the next child
                children.pop();
                //if there are no more children left inser the indentation for closer then add } or ] depending on if its an array or not
                if(children.empty()){
                    for(int i=0;i<level;i++){
                        outputJson+="\t";
                    }
                    if(isArr){
                        outputJson.append("]");
                    }
                    else{
                        outputJson.append("}");
                    }
                }

                if(isArr){
                   //if there is an array shift the start for the find functions as to avoid a infinite recursive calls
                    childCounter=childCloseTag;
                }

            }
        }
        //if there are no children then call the function on the inner string and the base case will be returned
        else{
            outputJson+=x2json(tagString,level+1);
        }

        //insert tab spaces corrosponding with the level
       for(int i=0;i<level;i++){
            outputJson+="\t";
       }
        outputJson+='\n';
        //add the closing tag in level 0
        if(level==0){
            outputJson+="}\n";
        }
        return outputJson;
    }
}
