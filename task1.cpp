#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <iomanip>

int main() {
    std::ifstream inputFile("input.txt");
    std::ifstream in("inputtable.txt");
    std::ofstream outputFile("output.txt");
    std::string line;
    int n, m;
    in >> n >> m;
    in.ignore();
    
    if (!inputFile.is_open()) {
        std::cerr << "Не удалось открыть файл input.txt" << std::endl;
        return 1;
    }
    else if(!outputFile.is_open()){
        std::cerr << "Не удалось открыть файл output.txt" << std::endl;
        return 1;
    }
    else{
        while (std::getline(inputFile, line)) {
            outputFile << line << std::endl;
            std::cout << line << std::endl;
        }
        inputFile.close();
        outputFile.close();
    }

    for (int i = 0; i < n; ++i) {
        std::getline(in, line);
        std::stringstream ss(line);
        
        for (int j = 0; j < m; ++j) {
            std::string cell;
            std::getline(ss, cell, ',');
            std::cout << std::setw(10) << std::stoi(cell);
            if (j != m - 1) std::cout << " ";
        }
        std::cout << std::endl;
    }
    in.close();
    
    return 0;
}