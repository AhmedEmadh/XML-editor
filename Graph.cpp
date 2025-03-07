#include <iostream>
#include <map>
#include <fstream>
#include <istream>
#include <cstdlib>
#include <bits/stdc++.h>
#include <list>
#include <string>
#include <algorithm>
#include <functional>
#include <queue>
#include <vector>
#include <stdio.h>
using namespace std;

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

void add_edge(int u, int v) {       //function to add edge into the matrix
   vertArr[u][v] = 1;
   vertArr[v][u] = 1;
}

string RepresentData( ) {

    ifstream input_file("XML2.xml");
    string xmlfile = string((std::istreambuf_iterator<char>(input_file)), std::istreambuf_iterator<char>()); 
       
       int no_users = 0 ;
       string users[100] ;
    int vertices = 0 ;
    string userdata  ;
    string AdjacentList = "Adjacent List of id : \n";
    Graph M; 
        
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
                    M.add_edge( userid , follow[k] );
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




string PostSearch ( string word )  {

         ifstream input_file("XML2.xml");
         string xmlfile = string((std::istreambuf_iterator<char>(input_file)), std::istreambuf_iterator<char>()); 
       
         string output = "" ;                 bool found = false ;
    
       for ( int i=0 ; i < xmlfile.length() ; i++ ) {
          
        if( xmlfile.substr( i , 6 ) == "<user>"  ) {
             
             string posts = "" ;
             i+=6 ;
             int userid = 0 ;        string temp = ""  , name = ""  ;
             int start = 0  ; 

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
                        output += "The word is found in the posts whose user name is " 
                                     + name + "\n" + "The posts are : \n" + posts ;
                       }
                    }
                           
                 i+=7 ; 
                         
             }            
       }  
                    if ( found ) { return output ; } 
                    else  return "The word not found \n" ;
         
}

};

int main(  ){

    Graph g ;
    //g.printlist();
    cout << g.RepresentData();
  
    // cout << g.PostSearch( "yarab" ); 
  
    
}
