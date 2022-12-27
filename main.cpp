#include <iostream>
#include <tchar.h>
#include <string>
#include <stack>
//Ahmed Emad's includes
#include <fstream>
#include <sstream>
#include <string>

using namespace std;


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
    int error_index;
    string readFileIntoString(const string& path) {
    ifstream input_file(path);
    if (!input_file.is_open()) {
        cerr << "Could not open the file - '"
             << path << "'" << endl;
        exit(EXIT_FAILURE);
    }
    return string((std::istreambuf_iterator<char>(input_file)), std::istreambuf_iterator<char>());
    }
    string readFileIntoString(string& path) {
    ifstream input_file(path);
    if (!input_file.is_open()) {
        cerr << "Could not open the file - '"
             << path << "'" << endl;
        exit(EXIT_FAILURE);
    }
    return string((std::istreambuf_iterator<char>(input_file)), std::istreambuf_iterator<char>());
    }
    bool is_stack_contains(stack<string> strStk,string word){
        
        cout<<"searching for "<<word<<" in stack"<<endl;
        while(!strStk.empty()){
            cout<<"comparing "<<strStk.top()<<" with "<<word<<endl;
            if(strStk.top() == word){
                cout<<"comparing is true"<<endl;
                return true;
            }else{
                cout<<"comparing is false poping"<<endl;
                strStk.pop();
                }
        }
        return false;
    }
    
    //added is_tags_balwnced private method that check whether the tags are balenced or not

     
    string to_json(){
        return "not now";
    }
 public:
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
 bool is_tags_balenced(){
        int last_opening;
        int last_closing;

        stack<int> stk_last_opening;
        stack<int> stk_last_closing;
        
        if(!this->is_balenced()) return false;
        stack<string> stk;
        string tag;
        //int end;
        for(int i=0;i<content.size();i++){
            
            //case 1
            if ((content[i]=='<') && (content[i+1]!='/')&&(content[i+1]!='?'))//case 1: opening tag handling
            {
                /*last_opening=i;*/
                stk_last_opening.push(i);

                //cout << "opening tag found"<<endl;
                i++;
                tag = "";
                
                //end = i;
                while(content[i] == ' ') i++;
                while((content[i] != ' ')&&(content[i] != '>')) {tag = tag+content[i];i++;}
                /**///cout<<tag<<" opening is at "<</*last_opening*/stk_last_opening.top()<<endl;
                //cout << tag << "  is pushing"<<endl;
                stk.push(tag);
                while(content[i] != '>') i++;
                
            }//opening tag handled and pushed to stack and exited

            //case 2
            if((content[i]=='<')&&(content[i+1] == '/')){//case 2: closing tag handling
                last_closing = i;
                //cout << "closing tag found"<<endl;
                i++;i++;
                /*last if stk empty before cutting*/
                tag = "";
                while(content[i]==' ')i++;
                while((content[i]!=' ')&&(content[i] != '>')){tag = tag+content[i];i++;}
                if(stk.empty()){error_index=last_closing;cout<<"closing tag found "<< tag <<" and stack is empty (failed) and error is at:"<<error_index<<endl;return false;}
                //cout << "comparing tag: "<< tag<<" and stack top: "<<stk.top()<<endl;
                /**///cout<<tag<<" closing is at "<<last_closing<<endl;
                if (stk.top() == tag){
                    //cout<< "compare is true "<<stk.top()<<" is poping"<<endl;
                    stk.pop();
                    stk_last_opening.pop();
                }else{//closing with no near opening
                    
                    //cout <<"compare is false (error)"<<endl;
                    //error_index=last_closing;
                    if(is_stack_contains(stk,tag)){
                        error_index = /*last_opening*/stk_last_opening.top();
                        //cout <<"compare is false (error) and the error at last opening "<< error_index <<endl;
                        return false;
                    }else{
                        error_index = last_closing;
                        //cout <<"compare is false (error) and the error at last closing: "<< error_index <<endl;
                        return false;
                    }
                }
                while(content[i] != '>') i++;
                
                
            }
          
        }//end for
        
        if(stk.empty()){//problem is stack is not empty at the end of a correct file
            //cout<<"stack is empty at the end (succedded)"<<endl;
            return true;
        } else {
            error_index = /*last_opening*/stk_last_opening.top();
            //cout <<"stack is not empty at the end (failed) and error is at: "<< error_index <<endl;
            
            return false;
            
        }
    }
    void correct(){
        int end;
        int length=0;
        //if(!is_tags_balenced()){
        while(!is_tags_balenced()){
            end=error_index;
            while(content[end] != '>'){
                end++;
            }
            end++;
            //cout<<"error between "<<error_index<<" and "<<end<<endl;
            length = end-error_index;
             content.erase(error_index,length);
        }
    //}
	}
    XmlReadFile() {
        this->content = "";
    }

    XmlReadFile (const string& path){
        content = this->readFileIntoString(path);
    }

    string get_content() {
        return this->content;
    }

    void set_content(const string& data) {
        this->content = data;
        
    }
    void set_content(string& data) {
        this->content = data;
        
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
    void Format() {
        
        std::string names[100] ;  // Array of words between <  > 
        std::string content = readFileIntoString("XML4.xml");
        
        int index = 0;
        int nameslength = 0 ;  
        // Store the words between < > in Array
        for ( int i=0 ; i<content.length() ; i++  ) {
            
            if ( content[i] == '<' && content[i+1] != '/' )  {
                 int sub = i ;
                 while( content[i] != '>'  ) { i++ ; }
                 for( int z = sub+1 ; z<=i ; z++ ) {
                      
                     names[index]+=content[z]; }
                     index++ ; nameslength ++ ; 
            }   
        } 
              std::string c = content ;
               int r = 4 ; 
               int index2 = 0 ; 
                 while ((index2 = c.find(names[1], index2)) != string::npos ) {
                    
                     c.insert( index2-1 , 2 , ' ')  ;   index2+= 2 ;  
                     index2 += names[1].length();  
                 }
              for ( int i=2 ; i<nameslength ; i++ ) {     // Find the words between < > and Insert spaces before < 
                  int index2 = 0 ; 
                 while ((index2 = c.find(names[i], index2)) != string::npos ) {
                    
                     c.insert( index2-1 , r , ' ')  ;   index2+= r ;  
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
             int f=0 ;
            for( int k=0 ; k < c.length() ; k++ ) {      // Remove unwanted spacse
                        
                        bool space = false ;
                 if( c[k] == '<' ) { 

                       while( c[k+1] != '\n' ) {
                        if ( c[k+1] == '<' )  { f = k ; space = true ; } 
                         k++ ; } 
                         int back = f ;
                         while ( c[back] == ' ' ) { back -- ; }
                         if( space ) { c.erase( back+1 , f-back );  }             
                 }         
              } 
                    cout << c ;
                
    }
};

int main() {
    cout << "hello"<<endl;
    XmlReadFile file("books.xml");
    file.correct();
    file.Format();
    cout<<file.get_content();
    return 0;
}
