#include<iostream>
#include<fstream>
#include<sstream>
#include<string>
#include"bst.h"

using namespace std;
int main(){
    std::ifstream file("../../../../benchmark/benchmark_operations.csv");
    std::string line;
    BST bst;
    if(!file.is_open()){
        std::cerr << "error can't open file" << std::endl;
        return 1;
    }
    else {
        std::cout << "File opened successfully." << std::endl;
    }
    while(getline(file,line)){
        std::istringstream ss(line);
        std::string operation;
        std::string value_str;
        int val = 0;
        if (getline(ss, operation, ',') && getline(ss, value_str)) {
            std::istringstream(value_str) >> val;
        }
        if(operation == "insert"){
            bst.insert(val);
        }
        else if(operation == "search"){
            bool found = bst.find(val);
            printf(found ? "true\n":"flase\n");
        }
        else if(operation == "findmax"){
            try{
                int max = bst.findmax();
                printf("max: %d\n",max);
            }
            catch(std::runtime_error& e){
                std::cerr << "Error:" << e.what() << std::endl;
            }
        }
        else if(operation == "findmin"){
            try{
                int min = bst.findmin();
                printf("min: %d\n",min);
            }
            catch(std::runtime_error& e){
                std::cerr << "Error:" << e.what() << std::endl;
            }
        }
    }
    file.close();
    return 0;
}