#include "TFIDFCalculator.h"
#include "QueryHandler.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>

std::vector<std::string> loadDocumentList(const std::string& filename) {
    std::vector<std::string> filenames;
    std::ifstream file(filename);

    if (!file.is_open()) {
        std::cerr << "Error: Cannot open " << filename << std::endl;
        return filenames;
    }

    std::string line;
    while (std::getline(file, line)) {
        if (!line.empty()) {
            filenames.push_back(line);
        }
    }

    file.close();
    return filenames;
}

int main() {
    std::cout << "TF-IDF Text Analyzer" << std::endl;
    std::cout << "====================" << std::endl;

    std::vector<std::string> filenames = loadDocumentList("documents.txt");

    if (filenames.empty()) {
        std::cerr << "Error: No documents found in documents.txt" << std::endl;
        return 1;
    }

    std::cout << "Loading " << filenames.size() << " documents..." << std::endl;

    TFIDFCalculator calculator;
    calculator.loadDocuments(filenames);

    std::cout << "Documents loaded successfully!" << std::endl;
    std::cout << "Total unique words: " << calculator.getAllWords().size() << std::endl;
    std::cout << std::endl;
    std::cout << "Available commands:" << std::endl;
    std::cout << "  WORD <word>" << std::endl;
    std::cout << "  WORD_IN_DOC <word> <document>" << std::endl;
    std::cout << "  DOC <document>" << std::endl;
    std::cout << "  QUERY <word1> <word2> ..." << std::endl;
    std::cout << "  EXIT" << std::endl;
    std::cout << std::endl;

    QueryHandler handler(calculator);
    std::string query;

    while (true) {
        std::cout << "> ";
        std::getline(std::cin, query);

        if (query == "EXIT" || query == "exit") {
            break;
        }

        handler.processQuery(query);
        std::cout << std::endl;
    }

    return 0;
}