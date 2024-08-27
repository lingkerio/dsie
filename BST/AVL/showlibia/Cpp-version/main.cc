#include "avl.hh"
#include <ctime>
#include <fstream>
#include <iostream>
#include <iterator>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

struct Operation
{
    string operation;
    int value;
};

int load_operations(std::string_view filename, vector<Operation> &operations)
{
    ifstream file((string)filename);
    if (!file.is_open())
    {
        cerr << "Error opening file: " << filename << endl;
        return -1;
    }

    string line;
    while (getline(file, line))
    {
        istringstream iss(line);
        string op;
        int value;

        if (getline(iss, op, ',') && iss >> value)
        {
            operations.push_back({op, value});
        }
        else
        {
            cerr << "Warning: Malformed line: " << line << endl;
        }
    }

    file.close();
    return operations.size();
}

void process_operation(AVLTree &avl, const string &operation, int value)
{
    if (operation == "insert")
    {
        avl.insert(value);
    }
    else if (operation == "search")
    {
        avl.search(value);
    }
    else if (operation == "delete")
    {
        avl.remove(value);
    }
    else if (operation == "findmin")
    {
        avl.findMin();
    }
    else if (operation == "findmax")
    {
        avl.findMax();
    }
}

double time_execution(AVLTree &avl, const vector<Operation> &operations)
{
    clock_t start = clock();
#ifdef DEBUG_MODE
    int count = 1;
#endif
    for (const auto &op : operations)
    {
#ifdef DEBUG_MODE
        cout << count << ":" << op.operation << "," << op.value << endl;
        count++;
#endif
        process_operation(avl, op.operation, op.value);
    }

    clock_t end = clock();
    return static_cast<double>(end - start) / CLOCKS_PER_SEC;
}

int main()
{
    AVLTree avl;
#ifdef RELEASE_MODE
    string filename = "../../../benchmark/benchmark_operations.csv";

    vector<Operation> operations;
    int count = load_operations(filename, operations);
    if (count < 0)
    {
        return 1;
    }

    double elapsed_time = time_execution(avl, operations);
    cout << "Total time to execute all AVLTree operations (excluding I/O): " << elapsed_time << " seconds" << endl;
#elif defined(DEBUG_MODE)
    string filename = "../../../benchmark/benchmark_operations.csv";

    vector<Operation> operations;
    int count = load_operations(filename, operations);
    if (count < 0)
    {
        return 1;
    }

    double elapsed_time = time_execution(avl, operations);
    cout << "Total time to execute all AVLTree operations (excluding I/O): " << elapsed_time << " seconds" << endl;
#else
    std::cout << "Unknown mode" << std::endl;
#endif
    return 0;
}