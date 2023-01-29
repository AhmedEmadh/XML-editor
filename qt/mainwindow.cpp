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
   text2= Formating(text2);
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

