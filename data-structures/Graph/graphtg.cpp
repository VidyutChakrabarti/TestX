#include "graphtg.h"
#include "user_function.h"
#include "valuegenerators.h"
#include "graphmutator.h"
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

using namespace std;
using namespace testgenerator;
// Coverage tracking variables for Graphtg
namespace
{
    std::set<int> last_accepted_lines;
    std::set<int> cumulative_covered_lines;
    const float COVERAGE_THRESHOLD = 95.0f;
}

// Helper to parse gcov output and get covered line numbers
std::set<int> Graphtg::getCoveredLinesFromGcov()
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
float Graphtg::getIndividualCoverage()
{
    std::set<int> current_lines = getCoveredLinesFromGcov();
    std::set<int> new_lines;
    std::set_difference(current_lines.begin(), current_lines.end(),
                        last_accepted_lines.begin(), last_accepted_lines.end(),
                        std::inserter(new_lines, new_lines.begin()));
    return static_cast<float>(new_lines.size());
}

// Returns cumulative coverage percentage
float Graphtg::getTotalCoverage()
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

bool Graphtg::toContinue()
{
    float total_coverage = getTotalCoverage();
    std::cout << "Current cumulative coverage: " << total_coverage << "%" << std::endl;
    if (total_coverage >= COVERAGE_THRESHOLD || count >= MAXTESTCOUNT)
    {
        return false;
    }
    return true;
}

const unsigned int Graphtg::MAXTESTCOUNT = 20;

Graphtg::Graphtg()
{
    setMutator(new GraphMutator());
}

Graphtg::~Graphtg()
{
    for (auto &t : testcases)
    {
        delete t;
    }
}

Graph *Graphtg::generateRandomTest()
{
    Graph *g = new Graph();
    FloatGenerator fg;
    IntGenerator ig;
    StringGenerator sg;

    g->n = (ig.generate() % 10) + 2;
    g->graph.resize(g->n, vector<int>(g->n, 0));
    g->weights.resize(g->n, vector<float>(g->n, numeric_limits<float>::infinity()));
    g->nodes.resize(g->n, nullptr);

    auto sanitizeString = [](const string &str) -> string
    {
        string sanitized;
        for (char c : str)
        {
            if (isalnum(c) || c == ' ' || c == '_' || c == '-')
            {
                sanitized += c;
            }
        }
        return sanitized;
    };

    for (int i = 0; i < g->n; i++)
    {
        string rawString = sg.generate();
        string sanitizedString = sanitizeString(rawString);
        g->nodes[i] = new Graphnode(sanitizedString.empty() ? "Node" + to_string(i) : sanitizedString);
    }

    for (int i = 0; i < g->n; ++i)
    {
        for (int j = 0; j < g->n; ++j)
        {
            if (i == j)
            {
                g->graph[i][j] = 0;
                g->weights[i][j] = numeric_limits<float>::infinity();
            }
            else if (j > i)
            {
                g->graph[i][j] = ig.generate() % 2;
                if (g->graph[i][j] == 0)
                    g->weights[i][j] = numeric_limits<float>::infinity();
                else
                    g->weights[i][j] = static_cast<float>((ig.generate() % 100) + 1);
            }
            else
            {
                g->graph[i][j] = g->graph[j][i];
                g->weights[i][j] = g->weights[j][i];
            }
        }
    }

    vector<set<int>> connected_sets = g->connected_components(g->graph);
    while (connected_sets.size() > 1)
    {
        int parent_set_index = ig.generate() % connected_sets.size();
        auto parent_set = connected_sets[parent_set_index];
        connected_sets.erase(connected_sets.begin() + parent_set_index);
        int merging_set_index = ig.generate() % connected_sets.size();
        auto merging_set = connected_sets[merging_set_index];
        connected_sets.erase(connected_sets.begin() + merging_set_index);
        int parent_node = *next(parent_set.begin(), ig.generate() % parent_set.size());
        int merging_node = *next(merging_set.begin(), ig.generate() % merging_set.size());
        g->graph[parent_node][merging_node] = 1;
        g->graph[merging_node][parent_node] = 1;
        g->weights[parent_node][merging_node] = static_cast<float>((ig.generate() % 100) + 1);
        g->weights[merging_node][parent_node] = g->weights[parent_node][merging_node];
        parent_set.insert(merging_set.begin(), merging_set.end());
        connected_sets.push_back(parent_set);
    }

    return g;
}

vector<Graph *> Graphtg::generateTest(Graph *base)
{
    vector<Graph *> result;
    if (!mutator)
        return result;
    auto mutations = mutator->getMutations(base);
    for (auto &mutation : mutations)
    {
        try
        {
            Graph *mutated = mutation(deepCopy(base));
            result.push_back(mutated);
        }
        catch (...)
        {
            // If mutation fails, skip this mutation
        }
    }
    return result;
}

void Graphtg::deleteTest(Graph *g)
{
    delete g;
}

extern "C" void __gcov_dump(void);

float Graphtg::getCoverage()
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

bool Graphtg::toContinue()
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

string Graphtg::toString(Graph *g)
{
    int n = g->n;
    string s = "Node data: ";
    for (auto node : g->nodes)
    {
        s += node->data + " ";
    }
    s += "\nWeights:\n";
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            s += to_string(g->weights[i][j]) + " ";
        }
        s += "\n";
    }
    return s;
}

string Graphtg::toJSON(Graph *g)
{
    int n = g->n;
    string s = "{ \"Nodedata\" : [";
    string edges = "\"Graph\" : [";
    string w = "\"Weights\" : [";
    for (unsigned int c = 0; c < n; c++)
    {
        string nodeData = g->nodes[c]->data;
        replace(nodeData.begin(), nodeData.end(), '"', '\'');
        s += "{\"" + to_string(c) + "\" : \"" + nodeData + "\"}";
        if (c != n - 1)
            s += ",";
    }
    s += "],";
    for (int i = 0; i < n; ++i)
    {
        edges += "{\"" + to_string(i) + "\" : [";
        w += "{\"" + to_string(i) + "\" : [";
        for (int j = 0; j < n; ++j)
        {
            edges += "{\"" + to_string(j) + "\" : \"" + to_string(g->graph[i][j]) + "\"}";
            w += "{\"" + to_string(j) + "\" : \"" + to_string(g->weights[i][j]) + "\"}";
            if (j != n - 1)
            {
                edges += ", ";
                w += ", ";
            }
        }
        if (i != n - 1)
        {
            edges += "]}, ";
            w += "]}, ";
        }
        else
        {
            edges += "]}";
            w += "]}";
        }
    }
    edges += "], ";
    w += "]}";
    s += edges + w;
    return s;
}

Graph *Graphtg::readFromJSONFile(string fileName)
{
    ifstream test_file(fileName, ifstream::binary);
    Json::Value t1;
    test_file >> t1;
    Graph *g = new Graph();
    g->n = t1["Nodedata"].size();
    for (unsigned int c = 0; c < g->n; c++)
    {
        g->nodes.push_back(new Graphnode(t1["Nodedata"][c][to_string(c)].asString()));
    }
    for (unsigned int c = 0; c < g->n; c++)
    {
        vector<int> v;
        for (unsigned int idx = 0; idx < g->n; idx++)
        {
            v.push_back(stoi(t1["Graph"][c][to_string(c)][idx][to_string(idx)].asString()));
        }
        g->graph.push_back(v);
    }
    for (unsigned int c = 0; c < g->n; c++)
    {
        vector<float> v2;
        for (unsigned int idx = 0; idx < g->n; idx++)
        {
            v2.push_back(stof(t1["Weights"][c][to_string(c)][idx][to_string(idx)].asString()));
        }
        g->weights.push_back(v2);
    }
    return g;
}

void Graphtg::writeToFile(string s, string fname)
{
    ofstream fout(fname);
    fout << s;
    fout.close();
}

void Graphtg::deleteDirectoryContents(const std::filesystem::path &dir)
{
    for (const auto &entry : std::filesystem::directory_iterator(dir))
        std::filesystem::remove_all(entry.path());
}

void Graphtg::writeAllTestsToFile()
{
    string dirName = "test/testcases/";
    std::filesystem::create_directories(dirName);
    Graphtg::deleteDirectoryContents(dirName);
    unsigned int i = 1;
    for (const auto &t : testcases)
    {
        string json = toJSON(t);
        string fileName = "t" + to_string(i) + ".json";
        string path = dirName + fileName;
        cout << "Writing test file: " << path << endl;
        writeToFile(json, path);
        i++;
    }
}

Graph *Graphtg::deepCopy(Graph *g)
{
    Graph *copy = new Graph();
    copy->n = g->n;
    copy->graph = g->graph;
    copy->weights = g->weights;
    for (auto node : g->nodes)
    {
        copy->nodes.push_back(new Graphnode(node->data));
    }
    return copy;
}

void Graphtg::callPUT(Graph *g)
{
    try
    {
        user_function(g);
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
