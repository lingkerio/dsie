#include "bst.h" // Assuming the C++ BST implementation is in bst.h
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

struct Operation
{
    string operation;
    int value;
};

struct Result
{
    string output;
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

void process_operation(BST &bst, const string &operation, int value, vector<Result> &results)
{
    if (operation == "insert")
    {
        bst.insert(value);
        results.push_back({"insert," + to_string(value)});
    }
    else if (operation == "search")
    {
        bool found = bst.search(value);
        results.push_back({"search," + to_string(value) + "," + (found ? "true" : "false")});
    }
    else if (operation == "delete")
    {
        bool found = bst.search(value);
        bst.remove(value);
        results.push_back({"delete," + to_string(value) + (found ? "" : ",null")});
    }
    else if (operation == "findmin")
    {
        BSTNode *min_node = bst.findMin();
        if (min_node)
        {
            results.push_back({"findmin," + to_string(min_node->data)});
        }
        else
        {
            results.push_back({"findmin,null"});
        }
    }
    else if (operation == "findmax")
    {
        BSTNode *max_node = bst.findMax();
        if (max_node)
        {
            results.push_back({"findmax," + to_string(max_node->data)});
        }
        else
        {
            results.push_back({"findmax,null"});
        }
    }
    else
    {
        cerr << "Warning: Unknown operation: " << operation << endl;
    }
}

void execute_operations(const vector<Operation> &operations, const string &output_filename)
{
    vector<Result> results;
    BST bst;

    for (const auto &op : operations)
    {
        process_operation(bst, op.operation, op.value, results);
    }

    ofstream output_file(output_filename);
    if (!output_file.is_open())
    {
        cerr << "Error opening output file: " << output_filename << endl;
        return;
    }

    for (const auto &result : results)
    {
        output_file << result.output << endl;
    }

    output_file.close();
}

int main()
{
    string input_filename = "../../../benchmark/benchmark_operations.csv";
    string output_filename = "correctness.csv";

    vector<Operation> operations;
    int count = load_operations(input_filename, operations);
    if (count < 0)
    {
        return 1;
    }

    execute_operations(operations, output_filename);

    return 0;
}
