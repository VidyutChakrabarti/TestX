#include "testgenerator.h"
#include "trietg.h"
#include<string>

int main()
{
    Trietg_search_key testGenerator;
    vector<string> fileNames = testGenerator.getFileList("testcases");
    for (auto &fileName : fileNames)
    {
        cout << fileName << endl;
        Trie *t = testGenerator.readFromJSONFile(fileName);
        cout << "original trie contains:" << endl;
        //t->printTrie(t->root);
        string sk = "vi";
        search_key(*t, sk);
    }
    return 0;
}
