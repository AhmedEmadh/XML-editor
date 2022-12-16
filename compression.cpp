#define _CRT_SECURE_NO_WARNINGS
#include "Compression.h"


Hash_Map codes = Hash_Map();

vector<char> chars;

void printCodes(struct Huffman_node* root, string str)
{
    if (!root)
        return;

    if (root->data != '&')
        cout << root->data << ": " << str << "\n";

    printCodes(root->left, str + "0");
    printCodes(root->right, str + "1");
}
void preOrder(Huffman_node* root, string s, vector<string>& ans) {
    if (!root) {
        return;
    }

    if (!root->left && !root->right) {
        ans.push_back(s);
    }

    preOrder(root->left, s + "0", ans);
    preOrder(root->right, s + "1", ans);
}

// utility function to store map each character with its
// frequency in input string

vector<int> calcFreq(string str)
{
    int size = str.length();
    vector<int> freqs(256,0);
    for (int i = 0; i < str.size(); i++)
        freqs[str[i]]++;
    return freqs;

}
//takes root and an empty string and char array each character is indexed in array and places at each index the array the code of each char
void Coding(struct Huffman_node* root,string s,string chars[]) {

    if (root->data != '&') {
        chars[root->data] = s;

    }
    else {
        Coding(root->left, s + '0', chars);
        Coding(root->right, s + '1', chars);
    }
}
Huffman_node* encoding(string s,vector<int> freq,int size)
{
    struct Huffman_node* left, * right, * top;
    // Create a min heap & inserts all characters of data[]
    priority_queue<Huffman_node*, vector<Huffman_node*>, compare>* minHeap = new priority_queue<Huffman_node*, vector<Huffman_node*>, compare>;
    string characters;
    for (int i = 0; i < size; ++i) {
        characters = s.substr(0, i);
        if(characters.find(s[i]) == -1)
        minHeap->push(new Huffman_node(s[i], freq[s[i]]));
    }
    // Iterate while size of heap doesn't become 1
    while (minHeap->size() != 1) {

        // Extract the two minimum
        // freq items from min heap
        left = minHeap->top();
        minHeap->pop();

        right = minHeap->top();
        minHeap->pop();

        // Create a new internal node with
        // frequency equal to the sum of the
        // two nodes frequencies. Make the
        // two extracted node as left and right children
        // of this new node. Add this node
        // to the min heap '&' is a special value
        // for internal nodes, not used
        top = new Huffman_node('&', left->freq + right->freq);

        top->left = left;
        top->right = right;

        minHeap->push(top);
    }
    Huffman_node* root = minHeap->top();
    return root;
    //from 114 to 124 takes root of tree fills an array with codes of each char
}
string encode(struct Huffman_node* root , string s , int size)
{
string arr[256];
for (int i = 0; i < 256; i++)
    cout << arr[i];
Coding(root, "", arr);
string temp = "";
for (int i = 0; i < size; i++)
{
    temp.append(arr[s[i]]);
}
/*cout << root->freq<<endl;*///testing
return temp;
}

// function iterates through the encoded string s
// if s[i]=='1' then move to node->right
// if s[i]=='0' then move to node->left
// if leaf node append the node->data to our output string
string decode_file(struct Huffman_node* root, string s)
{
    string ans = "";
    struct Huffman_node* curr = root;
    for (int i = 0; i < s.size(); i++)
    {
        if (s[i] == '0')
            curr = curr->left;
        else
            curr = curr->right;

        // reached leaf node
        if (curr->left == NULL && curr->right == NULL)
        {
            ans += curr->data;
            curr = root;
        }
    }
    // cout<<ans<<endl;
    return ans + '\0';
}
bool checkbyeight(string str)
{
    int n = str.length();

    // Empty string
    if (n == 0)
        return false;

    // If there is single digit
    if (n == 1)
        return ((str[0] - '0') % 8 == 0);

    // If there is double digit
    if (n == 2)
        return (((str[n - 2] - '0') * 10 + (str[n - 1] - '0')) % 8 == 0);

    // If number formed by last three digits is
    // divisible by 8.
    int last = str[n - 1] - '0';
    int second_last = str[n - 2] - '0';
    int third_last = str[n - 3] - '0';

    return ((third_last * 100 + second_last * 10 + last) % 8 == 0);
}





void WriteBit(string bits,string* package,FILE* f)
{

    int current_bit = 0;
    char bit_buffer=0;
    for (int i = 0; i < bits.length(); i++) {
        if (bits[i] == '1')
            bit_buffer |= (1 << current_bit);
        else
            bit_buffer |= (0 << current_bit);
        if (current_bit == 7) {
            package->push_back(bit_buffer);
            fwrite(&bit_buffer, 1, 1, f);
            current_bit = 0;
            bit_buffer = 0;
        }
        current_bit++;
    }

}
string ReadFile(ifstream* f) {

    char read;
    string buffer="";
    while (f->get(read)) {
        buffer.push_back(read);
    }
    return buffer;

}
vector<unsigned char> bitstring_to_bytes(string s)
{
    long long size = s.length();
    vector<unsigned char> arrayOfByte(size / 8);
    long long index = 0;
    //cout<<"size:  "<<size<<"\n";
    int rem = size % 8;
    //cout<<"rem:  "<<rem<<"\n";
    for (long long i = 0; i < size - rem; i = i + 8)
    {
        //string one_byte = s.substr(i,i+8);
        string one_byte = "";
        for (int bit = i; bit < i + 8; bit++)
        {
            if (s[bit] == '\0')
            {
                break;
            }
            one_byte = one_byte + s[bit];
        }
        //cout<<one_byte<<"\n";
        unsigned int integer = stoi(one_byte, 0, 2);
        unsigned char c = static_cast<unsigned char>(integer);
        arrayOfByte[index] = c;
        //cout<<arrayOfByte[index];
        index++;
    }
    return arrayOfByte;
}
//params:
//b: 1 byte integer
//Returns a string of 8 bits
string one_byte_to_bitstring(unsigned char byte)
{
    string binary = bitset<8>(byte).to_string();
    return binary;
}
