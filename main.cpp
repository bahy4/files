#include <iostream>
#include <fstream>
#include <string>

int main() {
    std::ifstream inputFile("input.txt");
    std::ofstream outputFile("output.txt");
    std::string line;
    
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
        }
        inputFile.close();
    }
    
    return 0;
}