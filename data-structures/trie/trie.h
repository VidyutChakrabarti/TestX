#ifndef TRIE
#define TRIE
#include <string>
#include<vector>
using namespace std;


class TrieNode {
public:
    TrieNode *child[26];
    bool wordEnd;

    TrieNode();
    ~TrieNode();
};


class Trie {
public:
    TrieNode* root;

    Trie();
    ~Trie();
    
    void insert_string(string &str);
    void dfs(TrieNode *node, string &current, vector<string> &result); //both of these
    vector<string> getAllStrings(TrieNode* root);// functions are used for extracting all the strings stored in trie in one go. 
    void printTrie(TrieNode* root);
    string gen_random_string(const int len);

};

void search_key(Trie &t, string& key);
#endif
