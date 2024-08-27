#include "bst.h" // Assuming the C++ BST implementation is in bst.h
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

int load_operations(std::string_view filename, vector<Operation> &operations) {
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
      operations.push_back({op, value});
    } else {
      cerr << "Warning: Malformed line: " << line << endl;
    }
  }

  file.close();
  return operations.size();
}

void process_operation(BST &bst, const string &operation, int value,
                       ofstream &output_file) {
  if (operation == "insert") {
    bst.insert(value);
    output_file << "insert," << value << endl;
  } else if (operation == "search") {
      bool found = bst.search(value);
      output_file << "search," << value << "," << (found ? "true" : "false")
                  << endl;
  } else if (operation == "delete") {
    bool found = bst.search(value);
    bst.remove(value);
    output_file << "delete," << value << (found ? "" : ",null") << endl;
  } else if (operation == "findmin") {
    BSTNode *min_node = bst.findMin();
    if (min_node) {
      output_file << "findmin," << min_node->data << endl;
    } else {
      output_file << "findmin,null" << endl;
    }
  } else if (operation == "findmax") {
    BSTNode *max_node = bst.findMax();
    if (max_node) {
      output_file << "findmax," << max_node->data << endl;
    } else {
      output_file << "findmax,null" << endl;
    }
  } else {
    cerr << "Warning: Unknown operation: " << operation << endl;
  }
}

void execute_operations(const vector<Operation> &operations,
                        const string &output_filename) {
  ofstream output_file(output_filename);
  if (!output_file.is_open()) {
    cerr << "Error opening output file: " << output_filename << endl;
    return;
  }

  BST bst;

  for (const auto &op : operations) {
    process_operation(bst, op.operation, op.value, output_file);
  }

  output_file.close();
}

int main() {
  string input_filename = "../../../benchmark/benchmark_operations.csv";
  string output_filename = "correctness.csv";

  std::vector<Operation> operations;
  int count = load_operations(input_filename, operations);
  if (count < 0) {
    return 1;
  }

  execute_operations(operations, output_filename);

  return 0;
}