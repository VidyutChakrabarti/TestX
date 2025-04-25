#include <iostream>
#include <string>
#include "trie.h"
#include<vector>
#include "coveragelogger.h"
using namespace std;

// Node class representing a single node in the linked list

TrieNode::TrieNode() {
    wordEnd = false;
    for (int i = 0; i < 26; i++)
    {
      child[i] = NULL;
    }
}

TrieNode::~TrieNode() {
    for (int i = 0; i < 26; i++)
    {
      delete(child[i]);
    }
}

Trie::Trie() {
    root = new TrieNode();
}

Trie::~Trie() {
    delete(root);
}

void Trie::insert_string(string &str) {
    TrieNode *currentNode = root;
    for (auto character : str)
    {
      if (currentNode->child[character - 'a'] == NULL)
      {
        TrieNode *newNode = new TrieNode();
        currentNode->child[character - 'a'] = newNode;
      }
      currentNode = currentNode->child[character - 'a'];
    }

    currentNode->wordEnd = true;
}


//helper function for getAllStrings function. 
void Trie::dfs(TrieNode* node, string& current, vector<string>& result) {
    if (node->wordEnd) {
        result.push_back(current);
    }

    for (int i = 0; i < 26; ++i) {
        if (node->child[i]) {
            current.push_back('a' + i);
            dfs(node->child[i], current, result);
            current.pop_back();
        }
    }
}

//to get all the strings stored in trie in one go.
vector<string> Trie::getAllStrings(TrieNode* root) {
    vector<string> result;
    string current;
    dfs(root, current, result);
    return result;
}

void Trie::printTrie(TrieNode *root) {
    vector<string> allStrings = getAllStrings(root);
    for(auto str: allStrings){
    cout<<str<<"\n";
    }
}

//usual string generator doesn't integrate as only small alphabets allowed. 
string Trie::gen_random_string(const int len)
  {
    static const char alpha[] = "abcdefghijklmnopqrstuvwxyz"; // "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
    string tmp_s;
    tmp_s.reserve(len);

    for (int i = 0; i < len; ++i)
    {
      tmp_s += alpha[rand() % (sizeof(alpha) - 1)];
    }
    return tmp_s;
  }

void search_key(Trie &t, string& key)
{
    CoverageLogger::getInstance()->log(1u);
    bool flag = true;
    TrieNode* currentNode = t.root;

    // Iterate across the length of the string
    for (auto c : key) {
	CoverageLogger::getInstance()->log(2u);
        // Check if the node exist for the current
        // character in the Trie.
        if (currentNode->child[c - 'a'] == NULL) {
            //coverage skipped
            // Given word does not exist in Trie
            flag = false;
            break;
        }
        // Move the currentNode pointer to the already 
        // existing node for current character.
        currentNode = currentNode->child[c - 'a'];
    }
    if(flag == true){
    CoverageLogger::getInstance()->log(3u);
    }
}
