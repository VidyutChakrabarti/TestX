#include <cstdint>
#include <jsoncpp/json/json.h>

#include "valuegenerators.h"
#include "lltg.h"

// using namespace testgenerator;
// Keep adding new nodes based on a random choice.
// The string content of the node is also randomly generated.

using namespace testgenerator;

const unsigned int Lltg::MAXTESTCOUNT = 20;
Lltg::~Lltg() {
    for(auto& t : testcases) {
        delete(t);
    }
}

LinkedList * Lltg::generateTest() {
    LinkedList *list = new LinkedList();
    StringGenerator sg;
    // Adding some items
    for(unsigned int count = 0; count < 10 && rand() % 2 == 1; count++) {
        string s = sg.generateValue();
        list->append(s);
    }
    return list;
}

void Lltg::deleteTest(LinkedList *list) {
    delete(list);
}

bool Lltg::toContinue() {
    set<unsigned int> covered = CoverageLogger::getInstance()->getCoverage();
    set<unsigned int> target = CoverageLogger::getInstance()->getTargets();
    if(covered == target || count >= MAXTESTCOUNT) {
        return false;
    }
    count++;
    return true; //rand() % 2 == 1;
}

string Lltg::toString(LinkedList * ll) {
    Node* temp = ll->head;
    string s = "";
    while (temp != nullptr) {
        s += temp->data + " -> ";
        temp = temp->next;
    }
    s += "nullptr" + '\n';
    return s;
}

string Lltg::toJSON(LinkedList * ll) {
    Node* temp = ll->head;
    string s = "{ \"list\" : [";
    unsigned int count = 0;
    while (temp != nullptr) {
        s += "{\"" + to_string(count) + "\" : \"" + temp->data + "\"}";
        temp = temp->next;
        if(temp != nullptr) {
            s += ',';
        }
        count++;
    }
    s += "]}";
    return s;
}

LinkedList * Lltg::readFromJSONFile(string fileName) {
    ifstream test_file(fileName, ifstream::binary);
    Json::Value t1;
    test_file >> t1;

    LinkedList *list = new LinkedList();
    StringGenerator sg;
    // Adding some tasks
    for(unsigned int count = 0; count < t1["list"].size(); count++) {   
        cout << "data = " << t1["list"][count][to_string(count)] << endl;
        string s = (t1["list"][count][to_string(count)]).asString();
        list->append(s);
    }

    return list;
}

void Lltg_reverseLinkedList::callPUT(LinkedList *list) {
    reverseLinkedList(*list);
}

