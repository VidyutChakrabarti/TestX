#include "testgenerator.h"
#include "lltg.h"
int main() {
    Lltg_reverseLinkedList testGenerator;
    vector<string> fileNames = testGenerator.getFileList("testcases");
    for(auto& fileName : fileNames) {
        cout << fileName << endl;
	LinkedList *list = testGenerator.readFromJSONFile(fileName);
	cout << "original list:" << endl;
	list->printList(); // not important
	reverseLinkedList(*list); // most important: call the function under test.
	cout << "reversed list:" << endl;
	list->printList();
    }
    return 0;
}
