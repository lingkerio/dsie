#include "bst.h" 
#include <ctime>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

struct Operation {
    string operation;
    int value;
};

int load_operations(std::string_view filename, vector<Operation>& operations)
{
    ifstream file((string)filename);
    if (!file.is_open()) {
        cerr << "Error opening file: " << filename << endl;
        return -1;
    }

    string line;
    while (getline(file, line)) {
        istringstream iss(line);
        string op;
        int value;

        if (getline(iss, op, ',') && iss >> value) {
            operations.push_back({ op, value });
        } else {
            cerr << "Warning: Malformed line: " << line << endl;
        }
    }

    file.close();
    return operations.size();
}

void process_operation(BST& bst, const string& operation, int value)
{
  if (operation == "insert") {
      bst.insert(value);
  } else if (operation == "search") {
      bool found = bst.search(value);
      // cout << "Search " << value << ": " << (found ? "Found" : "NotFound") << endl;
  } else if (operation == "delete") {
      bst.remove(value);
  } else if (operation == "findmin") {
      bst.findMin();
  } else if (operation == "findmax") {
      bst.findMax();
  }

}

double time_execution(BST& bst, const vector<Operation>& operations)
{
    clock_t start = clock();

    for (const auto& op : operations) {
        process_operation(bst, op.operation, op.value);
    }

    clock_t end = clock();
    return static_cast<double>(end - start) / CLOCKS_PER_SEC;
}

int main()
{
    BST bst;
#ifdef RELEASE_MODE
    string filename = "../../../benchmark/benchmark_operations.csv";

    vector<Operation> operations;
    int count = load_operations(filename, operations);
    if (count < 0) {
        return 1;
    }

    double elapsed_time = time_execution(bst, operations);
    cout << "Total time to execute all BST operations (excluding I/O): "
         << elapsed_time << " seconds" << endl;
#elif defined(DEBUG_MODE)
    bst.insert(123);
    cout << "insert" << "\n";
    bst.search(123);
    cout << "search" << "\n";
    bst.remove(123);
    cout << "remove" << "\n";
#else
    std::cout << "Unknown mode" << std::endl;
#endif
    return 0;
}
