#include "avl.hh" 
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

void process_operation(AVLTree &avl, const string &operation, int value, ofstream &output_file)
{
    if (operation == "insert")
    {
        avl.insert(value);
        output_file << "insert," << value << endl;
    }
    else if (operation == "search")
    {
        bool found = avl.search(value);
        output_file << "search," << value << "," << (found ? "true" : "false") << endl;
    }
    else if (operation == "delete")
    {
        bool found = avl.search(value);
        avl.remove(value);
        output_file << "delete," << value << (found ? "" : ",null") << endl;
    }
    else if (operation == "findmin")
    {
        AVLNode *min_node = avl.findMin();
        if (min_node)
        {
            output_file << "findmin," << min_node->data << endl;
        }
        else
        {
            output_file << "findmin,null" << endl;
        }
    }
    else if (operation == "findmax")
    {
        AVLNode *max_node = avl.findMax();
        if (max_node)
        {
            output_file << "findmax," << max_node->data << endl;
        }
        else
        {
            output_file << "findmax,null" << endl;
        }
    }
    else
    {
        cerr << "Warning: Unknown operation: " << operation << endl;
    }
}

void execute_operations(const vector<Operation> &operations, const string &output_filename)
{
    ofstream output_file(output_filename);
    if (!output_file.is_open())
    {
        cerr << "Error opening output file: " << output_filename << endl;
        return;
    }

    AVLTree avl;

    for (const auto &op : operations)
    {
        process_operation(avl, op.operation, op.value, output_file);
    }

    output_file.close();
}

int main()
{
    string input_filename = "../../../benchmark/benchmark_operations.csv";
    string output_filename = "correctness.csv";

    std::vector<Operation> operations;
    int count = load_operations(input_filename, operations);
    if (count < 0)
    {
        return 1;
    }

    execute_operations(operations, output_filename);

    return 0;
}