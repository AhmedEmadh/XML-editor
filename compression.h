#ifndef COMPRESSION_H
#define COMPRESSION_H
// C++(STL) program for Huffman Coding with STL
#include <iostream>
#include <queue>
#include "Hash_Map.h"
#include "Minifying.h"
#include <fstream>
#include <string>
#include <bitset>

using namespace std;


//Huffman tree node
struct Huffman_node {

    // Input character key value to be coded
    char data;

    // Frequency of input character to be stored in node for filling the tree
    int freq;

    // Left and right child
    Huffman_node* left, * right;
    //Huffman_node constructor
    Huffman_node(char data, unsigned freq)
    {
        left = right = NULL;
        this->data = data;
        this->freq = freq;
    }
};
// Compares two nodes to reach if left node bigger than right node
struct compare {

    bool operator()(Huffman_node* l, Huffman_node* r)
    {
        return (l->freq > r->freq);
    }
};
void printCodes(struct Huffman_node* root, string str);
void preOrder(Huffman_node* root, string s, vector<string>& ans);
vector<int> calcFreq(string str);
void Coding(struct Huffman_node* root, string s, string chars[]);
Huffman_node* encoding(string s, vector<int> freq, int size);
string encode(struct Huffman_node* root, string s, int size);
string decode_file(struct Huffman_node* root, string s);
bool checkbyeight(string str);
void WriteBit(string bits, string* package, FILE* f);
string ReadFile(ifstream* f);
vector<unsigned char> bitstring_to_bytes(string s);
string one_byte_to_bitstring(unsigned char byte);
#endif // COMPRESSION_H
