#include "lltg.h"
#include "Userfunctions/user_function.h"
#include "valuegenerators.h"
#include "llmutator.h"
#include <sstream>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <regex>
#include <fstream>
#include <jsoncpp/json/json.h>
#include <filesystem>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <exception>
#include <ctime>

using namespace std;
using namespace testgenerator;

// Coverage tracking variables for Lltg
namespace
{
    std::set<int> last_accepted_lines;
    std::set<int> cumulative_covered_lines;
    const float COVERAGE_THRESHOLD = 95.0f;
}

// Helper to parse gcov output and get covered line numbers
std::set<int> Lltg::getCoveredLinesFromGcov()
{
    std::set<int> covered_lines;
    FILE *pipe = popen("gcov -b user_function.cpp", "r");
    if (!pipe)
        return covered_lines;
    char buffer[256];
    std::string result = "";
    while (fgets(buffer, sizeof(buffer), pipe) != nullptr)
    {
        result += buffer;
    }
    pclose(pipe);
    std::regex re("(\d+):\s*([0-9]+|#####)");
    std::smatch match;
    std::istringstream iss(result);
    std::string line;
    while (std::getline(iss, line))
    {
        if (std::regex_search(line, match, re))
        {
            int line_num = std::stoi(match[1]);
            std::string count = match[2];
            if (count != "#####" && std::stoi(count) > 0)
            {
                covered_lines.insert(line_num);
            }
        }
    }
    return covered_lines;
}

// Returns number of new lines covered by current testcase compared to last accepted testcase
float Lltg::getIndividualCoverage()
{
    std::set<int> current_lines = getCoveredLinesFromGcov();
    std::set<int> new_lines;
    std::set_difference(current_lines.begin(), current_lines.end(),
                        last_accepted_lines.begin(), last_accepted_lines.end(),
                        std::inserter(new_lines, new_lines.begin()));
    return static_cast<float>(new_lines.size());
}

// Returns cumulative coverage percentage
float Lltg::getTotalCoverage()
{
    int total_lines = 0;
    FILE *pipe = popen("gcov -b user_function.cpp", "r");
    if (!pipe)
        return 0.0f;
    char buffer[256];
    std::string result = "";
    while (fgets(buffer, sizeof(buffer), pipe) != nullptr)
    {
        result += buffer;
    }
    pclose(pipe);
    std::regex re("(\d+):\s*([0-9]+|#####)");
    std::smatch match;
    std::set<int> all_lines;
    std::istringstream iss(result);
    std::string line;
    while (std::getline(iss, line))
    {
        if (std::regex_search(line, match, re))
        {
            int line_num = std::stoi(match[1]);
            all_lines.insert(line_num);
        }
    }
    total_lines = static_cast<int>(all_lines.size());
    if (total_lines == 0)
        return 0.0f;
    float percent = (static_cast<float>(cumulative_covered_lines.size()) / total_lines) * 100.0f;
    return percent;
}

const unsigned int Lltg::MAXTESTCOUNT = 20;

Lltg::Lltg()
{
    setMutator(new LLMutator());
}

Lltg::~Lltg()
{
    for (auto &t : testcases)
    {
        delete t;
    }
}

LinkedList *Lltg::generateRandomTest()
{
    LinkedList *ll = new LinkedList();
    StringGenerator sg;

    // Generate random number of nodes (between 1 and 10)
    int numNodes = (rand() % 10) + 1;
    for (int i = 0; i < numNodes; i++)
    {
        string data = sg.generateValue();
        ll->append(data);
    }

    return ll;
}

vector<LinkedList *> Lltg::generateTest(LinkedList *base)
{
    vector<LinkedList *> result;
    if (!mutator)
        return result;
    auto mutations = mutator->getMutations(base);
    for (auto &mutation : mutations)
    {
        try
        {
            LinkedList *mutated = mutation(deepCopy(base));
            result.push_back(mutated);
        }
        catch (...)
        {
            // If mutation fails, skip this mutation
        }
    }
    return result;
}

void Lltg::deleteTest(LinkedList *ll)
{
    delete ll;
}

extern "C" void __gcov_dump(void);

float Lltg::getCoverage()
{
    struct stat st;
    if (stat("user_function.gcda", &st) != 0)
    {
        return 0.0;
    }
    FILE *pipe = popen("gcov -b user_function.cpp", "r");
    if (!pipe)
        return 0.0;
    char buffer[128];
    string result = "";
    while (fgets(buffer, sizeof(buffer), pipe) != nullptr)
    {
        result += buffer;
    }
    pclose(pipe);
    regex re("Lines executed:\\s*(\\d+\\.\\d+)%");
    smatch match;
    if (regex_search(result, match, re))
    {
        float coverage = stof(match[1]);
        return coverage;
    }
    return 0.0;
}

bool Lltg::toContinue()
{
    if (count >= MAXTESTCOUNT)
    {
        return false;
    }
    float coverage = getCoverage();
    cout << "Current gcov coverage for user_function.cpp: " << coverage << "%" << endl;
    if (coverage == 100.0)
    {
        return false;
    }
    count++;
    return true;
}

string Lltg::toString(LinkedList *ll)
{
    Node *temp = ll->head;
    string s = "";
    while (temp != nullptr)
    {
        s += temp->data + " -> ";
        temp = temp->next;
    }
    s += "nullptr\n";
    return s;
}

string Lltg::toJSON(LinkedList *ll)
{
    Node *temp = ll->head;
    string s = "{ \"list\" : [";
    unsigned int count = 0;
    while (temp != nullptr)
    {
        s += "{\"" + to_string(count) + "\" : \"" + temp->data + "\"}";
        temp = temp->next;
        if (temp != nullptr)
        {
            s += ',';
        }
        count++;
    }
    s += "]}";
    return s;
}

LinkedList *Lltg::readFromJSONFile(string fileName)
{
    ifstream test_file(fileName, ifstream::binary);
    Json::Value t1;
    test_file >> t1;

    LinkedList *list = new LinkedList();
    StringGenerator sg;
    // Adding some items
    for (unsigned int count = 0; count < t1["list"].size(); count++)
    {
        cout << "data = " << t1["list"][count][to_string(count)] << endl;
        string s = (t1["list"][count][to_string(count)]).asString();
        list->append(s);
    }

    return list;
}

void Lltg::writeToFile(string s, string fname)
{
    ofstream outfile(fname);
    outfile << s;
    outfile.close();
}

void Lltg::deleteDirectoryContents(const std::filesystem::path &dir)
{
    if (!std::filesystem::exists(dir))
        return;
    for (const auto &entry : std::filesystem::directory_iterator(dir))
    {
        std::filesystem::remove_all(entry.path());
    }
}

void Lltg::writeAllTestsToFile()
{
    std::filesystem::path test_dir("test_cases");
    deleteDirectoryContents(test_dir);
    std::filesystem::create_directories(test_dir);

    int count = 0;
    for (const auto &test : testcases)
    {
        string filename = "test_cases/test_" + to_string(count) + ".json";
        writeToFile(toJSON(test), filename);
        count++;
    }
}

LinkedList *Lltg::deepCopy(LinkedList *ll)
{
    if (!ll)
        return nullptr;

    LinkedList *copy = new LinkedList();
    Node *current = ll->head;
    while (current != nullptr)
    {
        copy->append(current->data);
        current = current->next;
    }
    return copy;
}

void Lltg::callPUT(LinkedList *ll)
{
    try
    {
        user_function(ll);
        __gcov_dump();
    }
    catch (const std::exception &e)
    {
        cerr << "Exception in user_function: " << e.what() << endl;
        throw;
    }
    catch (...)
    {
        cerr << "Unknown exception in user_function." << endl;
        throw;
    }
}
