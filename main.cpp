#include <iostream>
#include <fstream>
#include <string>

int main() {
    std::ifstream inputFile("input.txt");
    std::string line;
    
    if (inputFile.is_open()) {
        while (std::getline(inputFile, line)) {
            std::cout << line << std::endl;
        }
        inputFile.close();
    } else {
        std::cerr << "Не удалось открыть файл input.txt" << std::endl;
        return 1;
    }
    
    return 0;
}