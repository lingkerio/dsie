#include<iostream>
#include<fstream>
#include<sstream>
#include<string>
#include"avl.h"

using namespace std;

int main() {
    std::ifstream file("../../../../benchmark/benchmark_operations.csv");
    std::ofstream outfile("correctness.csv");
    std::string line;
    AVL avl;

    if (!file.is_open()) {
        std::cerr << "Error: can't open input file" << std::endl;
        return 1;
    }
    else {
        std::cout << "File opened successfully." << std::endl;
    }

    while (getline(file, line)) {
        std::istringstream ss(line);
        std::string operation;
        std::string value_str;
        int val = 0;

        if (getline(ss, operation, ',') && getline(ss, value_str)) {
            std::istringstream(value_str) >> val;
        }
        if (operation == "insert") {
            avl.insert(val);
            outfile << "insert," << val << "\n";
        }
        else if (operation == "search") {
            bool found = avl.find(val);
            outfile << "search," << val << "," << (found ? "true" : "false") << "\n";
        }
        else if (operation == "findmax") {
            try {
                int max = avl.findmax();
                outfile << "findmax," << max << "\n";
            }
            catch (std::runtime_error& e) {
                outfile << "findmax,null\n";
            }
        }
        else if (operation == "findmin") {
            try {
                int min = avl.findmin();
                outfile << "findmin," << min << "\n";
            }
            catch (std::runtime_error& e) {
                outfile << "findmin,null\n";
            }
        }
        else if (operation == "delete") {
            bool deleted = avl.remove(val); 
            if (deleted) {
                outfile << "delete," << val << "\n";
            } else {
                outfile << "delete," << val << ",null\n";
            }
        }
    }

    file.close();
    outfile.close();
    return 0;
}