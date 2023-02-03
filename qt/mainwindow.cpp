#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <iostream>
#include <tchar.h>
#include <string>
#include <stack>
//Ahmed Emad's includes
#include <fstream>
#include <sstream>
#include <string>
#include <queue>
#include <unordered_map>

using namespace std;
#define EMPTY_STRING ""


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setCentralWidget(ui->textEdit);
}

MainWindow::~MainWindow()
{
    delete ui;
}
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

string MainWindow:: Formatter(string XMLStr,int level){
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

string MainWindow:: PostSearch ( string word )  {

    QString text = ui->textEdit->toPlainText();
    string text2=text.toStdString();


         string xmlfile = text2;

         string output = "" ;                 bool found = false ;

       for ( int i=0 ; i < xmlfile.length() ; i++ ) {

        if( xmlfile.substr( i , 6 ) == "<user>"  ) {

             string posts = "" ;
             i+=6 ;
             int userid = 0 ;        string temp = ""  , name = ""  ;
             int start = 0  ;

             //cout << "new user \n" ;
             while ( xmlfile.substr( i , 7 ) != "</user>" )
             {

                  if ( xmlfile.substr( i , 6 ) == "<name>" ) {

                    i+=6;
                    while ( xmlfile[i] != '<' ) {  name +=xmlfile[i] ; i++ ; }

                 }
                 else if ( xmlfile.substr( i , 7 ) == "<posts>" ) {
                         start = i ;
                         i+=7;
                    while ( xmlfile.substr( i , 8 ) != "</posts>" ) { posts += xmlfile[i]; i++ ;  }

                 }
                    i++ ;
             }
                    for ( int k = start ; k < i ; k++ ) {

                        if ( xmlfile.substr( k , word.length() ) == word ) {
                        found = true ;
                        output += "The word is found in the posts whose name is "
                                     + name + "\n" + "The posts are : \n" + posts ;
                       }
                    }

                 i+=7 ;

             }
       }
                    if ( found ) { return output ; }
                    else  return "The word not found \n" ;

}
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

string MainWindow:: x2json(string XMLStr,int level){
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
struct Node
{
    char ch;
    int freq;
    Node *left, *right;
};

// Function to allocate a new tree node
Node* getNode(char ch, int freq, Node* left, Node* right)
{
    Node* node = new Node();

    node->ch = ch;
    node->freq = freq;
    node->left = left;
    node->right = right;

    return node;
}

// Comparison object to be used to order the heap
struct comp
{
    bool operator()(const Node* l, const Node* r) const
    {
        // the highest priority item has the lowest frequency
        return l->freq > r->freq;
    }
};

// Utility function to check if Huffman Tree contains only a single node
bool isLeaf(Node* root) {
    return root->left == nullptr && root->right == nullptr;
}

// Traverse the Huffman Tree and store Huffman Codes in a map.
void encode(Node* root, string str, unordered_map<char, string> &huffmanCode)
{
    if (root == nullptr) {
        return;
    }

    // found a leaf node
    if (isLeaf(root)) {
        huffmanCode[root->ch] = (str != EMPTY_STRING) ? str : "1";
    }


    encode(root->left, str + "0", huffmanCode);
    encode(root->right, str + "1", huffmanCode);
}

// Traverse the Huffman Tree and decode the encoded string
string decoded ;
void decode(Node* root, int &index, string str)
{
    if (root == nullptr) {
        return ;
    }

    // found a leaf node
    if (isLeaf(root))
    {
          decoded +=  root->ch;
          return ;

    }

    index++;

    if (str[index] == '0') {
        decode(root->left, index, str);
    }
    else {
        decode(root->right, index, str);
    }
}

// Builds Huffman Tree and decodes the given input text
string MainWindow:: buildHuffmanTree( string text ){

    // base case: empty string
    if (text == EMPTY_STRING) {
        return "empty string \n";
    }

    // count the frequency of appearance of each character and store it in a map
    unordered_map<char, int> freq;
    for (char ch: text) {
        freq[ch]++;
    }

    // Create a priority queue to store live nodes of the Huffman tree
    priority_queue<Node*, vector<Node*>, comp> pq;

    // Create a leaf node for each character and add it to the priority queue.
    for (auto pair: freq) {
        pq.push(getNode(pair.first, pair.second, nullptr, nullptr));
    }

    // do till there is more than one node in the queue
    while (pq.size() != 1)
    {
        // Remove the two nodes of the highest priority
        // (the lowest frequency) from the queue

        Node* left = pq.top(); pq.pop();
        Node* right = pq.top();    pq.pop();

        // create a new internal node with these two nodes as children and
        // with a frequency equal to the sum of the two nodes' frequencies.
        // Add the new node to the priority queue.

        int sum = left->freq + right->freq;
        pq.push(getNode('\0', sum, left, right));
    }

    // `root` stores pointer to the root of Huffman Tree
    Node* root = pq.top();

    // Traverse the Huffman Tree and store Huffman Codes
    // in a map. Also, print them
    unordered_map<char, string> huffmanCode;
    encode(root, EMPTY_STRING, huffmanCode);


    string HuffmanCodes ;
    for (auto pair: huffmanCode) {

       HuffmanCodes += pair.first ;
       HuffmanCodes += " " ;
       HuffmanCodes +=  pair.second;
       HuffmanCodes +=  "\n";
    }

    // Print encoded string
    string str;
    for (char ch: text) {
        str += huffmanCode[ch];
    }

    if (isLeaf(root))
    {
        // Special case: For input like a, aa, aaa, etc.
        while (root->freq--) {
            decoded += root->ch;
        }

    }
    else {
        // Traverse the Huffman Tree again and this time,
        // decode the encoded string
        int index = -1;
        while (index < (int)str.size() - 1) {
           decode(root, index, str);
        }
    }            string s="Huffman Codes are:\n";
    string output =s.append(HuffmanCodes ).append("\nThe original string is:\n").append(text).append(
    "\nThe encoded string is:\n").append(str).append("\nThe decoded string is:\n").append(decoded) ;
    //+ "\nThe encoded string is:\n" + str + "\nThe decoded string is:\n" + decodexml ;
    return output ;
}
string readFileIntoString(const string& path) {
    ifstream input_file(path);
    if (!input_file.is_open()) {
        cerr << "Could not open the file - '"
             << path << "'" << endl;
        exit(EXIT_FAILURE);
    }}
string MainWindow:: Formating(string xml) {

        string names[10000] ;  // Array of words between <  >

        string content =xml;

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
                    string c = content ;
                     int r = 6 ;
                     int index2 = 0 ;
                       while ((index2 = c.find(names[1], index2)) != string::npos ) {

                           c.insert( index2-1 , 2 , ' ')  ;   index2+= 2 ;
                           index2 += names[1].length();
                       }index2 = 0 ;
                       while ((index2 = c.find(names[2], index2)) != string::npos ) {

                           c.insert( index2-1 , 4 , ' ')  ;   index2+= 4;
                           index2 += names[2].length();
                       }
                    for ( int i=3 ; i<nameslength ; i++ ) {     // Find the words between < > and Insert spaces before <
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
                  for( int k=0 ; k <(c.length()-10); k++ ) {      // Remove unwanted spacse

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

           return c;
    }
string MainWindow:: minify(string xml)
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



void  MainWindow::on_actionNew_triggered()
{
    // Global referencing the current file that we are clearing
    currentFile.clear();

    // Clear the textEdit widget buffer
    ui->textEdit->setText(QString());
}

void MainWindow::on_actionOpen_triggered()
{
    // Opens a dialog that allows you to select a file to open
    QString fileName = QFileDialog::getOpenFileName(this, "Open the file");

    // An object for reading and writing files
    QFile file(fileName);

    // Store the currentFile name
    currentFile = fileName;

    // Try to open the file as a read only file if possible or display a
    // warning dialog box
    if (!file.open(QIODevice::ReadOnly | QFile::Text)) {
        QMessageBox::warning(this, "Warning", "Cannot open file: " + file.errorString());
        return;
    }

    // Set the title for the window to the file name
    setWindowTitle(fileName);

    // Interface for reading text
    QTextStream in(&file);

    // Copy text in the string
    QString text = in.readAll();
    string text2=text.toStdString();
   //text2= minify(text2);
    text=QString::fromStdString(text2);
    // Put the text in the textEdit widget
    ui->textEdit->setText(text);

    // Close the file
    file.close();
}



void MainWindow::on_actionSave_triggered()
{
    QString fileName = QFileDialog::getSaveFileName(this, "Save");
    QFile file(fileName);
    if (!file.open(QFile::WriteOnly | QFile::Text)) {
        QMessageBox::warning(this, "Warning", "Cannot save file: " + file.errorString());
        return;
    }
    currentFile = fileName;
    setWindowTitle(fileName);
    QTextStream out(&file);
    QString text = ui->textEdit->toPlainText();
    out << text;
    file.close();
}




void MainWindow::on_actionExit_triggered()
{
    QApplication::quit();
}


void MainWindow::on_actionCopy_triggered()
{
    ui->textEdit->copy();
}

void MainWindow::on_actionCut_triggered()
{
    ui->textEdit->cut();
}

void MainWindow::on_actionPaste_triggered()
{
    ui->textEdit->paste();
}

void MainWindow::on_actionUndo_triggered()
{
    ui->textEdit->undo();
}

void MainWindow::on_actionRedo_triggered()
{

}




void MainWindow::on_actionSave_as_triggered()
{
    QString fileName = QFileDialog::getSaveFileName(this, "Save as");

    // An object for reading and writing files
    QFile file(fileName);

    // Try to open a file with write only options
    if (!file.open(QFile::WriteOnly | QFile::Text)) {
        QMessageBox::warning(this, "Warning", "Cannot save file: " + file.errorString());
        return;
    }

    // Store the currentFile name
    currentFile = fileName;

    // Set the title for the window to the file name
    setWindowTitle(fileName);

    // Interface for writing text
    QTextStream out(&file);

    // Copy text in the textEdit widget and convert to plain text
    QString text = ui->textEdit->toPlainText();

    // Output to file
    out << text;

    // Close the file
    file.close();
}


void MainWindow::on_actionminify_triggered()
{
    QString text = ui->textEdit->toPlainText();
    string text2=text.toStdString();
   text2= minify(text2);
    text=QString::fromStdString(text2);
    // Put the text in the textEdit widget
    ui->textEdit->setText(text);

}





void MainWindow::on_actioncompression_triggered()
{
    QString text = ui->textEdit->toPlainText();
    string text2=text.toStdString();
   text2= buildHuffmanTree(text2);
    text=QString::fromStdString(text2);
    // Put the text in the textEdit widget
    ui->textEdit->setText(text);
}


void MainWindow::on_actionformat_triggered()
{
    QString text = ui->textEdit->toPlainText();
    string text2=text.toStdString();
   text2= Formatter(text2,0);
    text=QString::fromStdString(text2);
    // Put the text in the textEdit widget
    ui->textEdit->setText(text);
}


void MainWindow::on_actionXMLtoJSON_triggered()
{
    QString text = ui->textEdit->toPlainText();
    string text2=text.toStdString();
   text2= x2json(text2,1);
    text=QString::fromStdString(text2);
    // Put the text in the textEdit widget
    ui->textEdit->setText(text);
}


void MainWindow::on_actionMinify_triggered()
{
    QString text = ui->textEdit->toPlainText();
    string text2=text.toStdString();
   text2= minify(text2);
    text=QString::fromStdString(text2);
    // Put the text in the textEdit widget
    ui->textEdit->setText(text);
}


void MainWindow::on_actionpost_search_triggered()
{
    QString text = ui->textEdit->toPlainText();
    string text2=text.toStdString();
   text2= PostSearch("mido");
    text=QString::fromStdString(text2);
    // Put the text in the textEdit widget
    ui->textEdit->setText(text);
}
class Graph {

private:

        int nodes;
        list<int> *adjlist;
public:
     int vertArr[20][20]; //the adjacency matrix initially 0
     int count = 0;
    Graph() {
        }

        Graph (int nodes) { // Allocate resources
            adjlist = new list<int> [nodes];
            this->nodes = nodes;
           // cout<<"nodes";
        }

      ~Graph () { // Free allocated resources
            delete [] adjlist;
        }

        void AddEdge (int src, int dst) {
            adjlist[src].push_back({dst});
            adjlist[dst].push_back(src);
           // cout<<"IN AddEdge";
        }

        void Iterate (int src) {
            cout <<  src << " : ";
            for (auto& adj_node : adjlist[src]) {
                 cout << adj_node << " --> ";
            } cout << endl;
        }


void printlist() {

      Graph g(7);

    g.AddEdge(0,1);
    g.AddEdge(0,2);
    g.AddEdge(1,3);
    g.AddEdge(1,4);
    g.AddEdge(2,3);
    g.AddEdge(3,5);
    g.AddEdge(4,6);
    g.AddEdge(5,6);

    cout << "Adjacency list of id : \n" << endl;

    g.Iterate(0);
    g.Iterate(1);
    g.Iterate(4);
    g.Iterate(2);
    g.Iterate(3);
    g.Iterate(5);
    g.Iterate(6);
}
void displayMatrix(int v) {
   int i, j;
   for(i = 1 ; i <= v; i++) {
      for(j = 1 ; j <= v; j++) {
         cout << vertArr[i][j] << "  ";
      }
      cout << endl;
   }
}

void  add_edge(int u, int v) {       //function to add edge into the matrix
   vertArr[u][v] = 1;
   vertArr[v][u] = 1;
}};

string MainWindow:: RepresentData(string xml ) {



   ;
       string xmlfile =xml;

          int no_users = 0 ;
          string users[100] ;
       int vertices = 0 ;
       string userdata  ;
       string AdjacentList = "Adjacent List of id : \n";
       //Graph M;

          for ( int i=0 ; i < xmlfile.length() ; i++ ){

            if( xmlfile.substr( i , 6 ) == "<user>" ) { vertices++ ; i+=6 ; }

            }
                      //userdata += "No of users = " + to_string( vertices ) + "\n" ;
                          //Graph m( vertices +1 );
                     // graph = createGraph( vertices+1 );
                      int influencer[50] ; int inf = 0 ;
                      int  max = 1 ;
                      string mostactive , mostInfluencer ;
                      map<int, string> mapp;
          for ( int i=0 ; i < xmlfile.length() ; i++ ) {

           if( xmlfile.substr( i , 6 ) == "<user>"  ) {

                no_users ++ ;
                i+=6 ;
                int userid = 0 ;        string temp = "" , name = "" ;
                int no_follow = 0 ;     int follow[20] ;

                while ( xmlfile.substr( i , 7 ) != "</user>" )
                {
                   if( xmlfile.substr( i , 11 ) == "<followers>"  ){

                       i+=11 ;
                       while( xmlfile.substr( i , 12 ) != "</followers>" ) {

                            if ( xmlfile.substr( i , 4 ) == "<id>" ) {
                               no_follow ++ ;
                               users[ no_users ] += "follower = " ;
                                i+=4; temp = "" ;
                                while ( xmlfile[i] != '<' ) { users[ no_users ] += xmlfile[i] ; temp+=xmlfile[i] ;  i++ ; }
                                inf++ ; influencer[inf] = stoi ( temp ) ;
                                    follow[no_follow] = stoi ( temp );
                                    users[ no_users ] += "\n" ;
                           }
                            i++ ;
                            }
                            i+=12 ;
                   }
                    if ( xmlfile.substr( i , 4 ) == "<id>" ) {
                      // cout << "id = " ;
                      users[ no_users ] += "id = " ;
                       i+=4; temp = "" ;
                       while ( xmlfile[i] != '<' ) { users[ no_users ] += xmlfile[i] ; temp+=xmlfile[i] ; i++ ; }
                              userid = stoi(temp) ;
                              users[ no_users ] += "\n" ;
                    }
                    else if ( xmlfile.substr( i , 6 ) == "<name>" ) {
                        users[ no_users ] += "name = " ;
                       i+=6;
                       while ( xmlfile[i] != '<' ) { users[ no_users ] += xmlfile[i] ; name+= xmlfile[i] ;  i++ ; }
                             users[ no_users ] += "\n" ;
                    }
                    else if ( xmlfile.substr( i , 7 ) == "<topic>" ) {
                            users[ no_users ] +=  "topic = " ;
                       i+=7;
                       while ( xmlfile[i] != '<' ) { users[ no_users ] += xmlfile[i] ; i++ ; }
                             users[ no_users ] += "\n" ;
                    }
                    else if ( xmlfile.substr( i , 6 ) == "<body>" ) {
                            users[ no_users ] +=  "body = " ;
                       i+=7;
                       while ( xmlfile[i] != '<' ) { users[ no_users ] += xmlfile[i] ; i++ ; }
                             users[ no_users ] += "\n" ;
                    }
                    i++ ;
                }
                   AdjacentList += to_string(userid) + " : " ;
                   if ( no_follow >= max ){ max = no_follow ;  mostactive = to_string (userid) ; }

                   for ( int k=1 ; k <= no_follow ; k++ ) {

                       AdjacentList += to_string( follow[k] ) + " -- > " ;
                     //  M.add_edge( userid , follow[k] );
                       auto it = mapp.find(follow[k]);
                       if ( it == mapp.end() ) {
                           mapp[follow[k]]=name;
                       }else {
                           mapp[follow[k]]=mapp[follow[k]] + "," + name;
                       }

                    }

                    i+=7 ;
                              AdjacentList += "\n" ;
                }



          }
                   string Mutual = "" ;
                   map<int, string>::iterator itt;

                   for (itt = mapp.begin(); itt != mapp.end(); itt++)
                   {

                       if((itt->second).find(",") != std::string::npos)  {
                           Mutual += itt->second + "\n";
                           //cout<<endl;
                           }
                       /*std::cout << itt->first    // string (key)
                               << ':'
                               << itt->second   // string's value
                               << std::endl;*/
                   }

                        int max_count = 0;
                        int maxfreqelement;
                            for (int i = 1 ; i <= inf ; i++) {
                                   int count = 0;
                                   for (int j = 1 ; j <= inf ; j++) {
                                         if ( influencer[i] == influencer[j])
                                          count++;
                                  }
                                if (count > max_count) {
                                     max_count = count;
                                     maxfreqelement = influencer[i];
                                }
                            }

              //for ( int j = 1 ; j <= inf ; j++  ) { cout << influencer[j] << endl ;  }

            for ( int j = 1 ; j <= vertices ; j++ ) {
                       userdata += "\n============new user============= \n" ;
                      userdata+= users[j]  ;

             }

                    return   "Mutual Friends are : "+ Mutual + "The most active user its id = " + mostactive + "\n" +
                                "The most influencer user its id = "+ to_string( maxfreqelement ) +
                                "\n" + AdjacentList + userdata ;
}


void MainWindow::on_actionRepresentdata_triggered()
{
    QString text = ui->textEdit->toPlainText();
    string text2=text.toStdString();
   text2= RepresentData(text2);
    text=QString::fromStdString(text2);
    // Put the text in the textEdit widget
    ui->textEdit->setText(text);
}

