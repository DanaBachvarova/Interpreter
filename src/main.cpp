#include <iostream>
#include <vector>
#include <string>
#include "../include/lexer.hpp" // Импортираме lexer
#include "../include/ast.hpp" // Токените ще се използват тук
#include "../include/parser.hpp" // Парсер за обработка на токени

int main() {
    // Входен текст за теста
    std::string input = R"(
        LET x = 10
        READ y
        LABEL start
        GOTO start
    )";

    try {
        // Създаваме lexer и го използваме да токенизираме входния текст
        Lexer lexer(input);
        std::vector<Token> tokens = lexer.tokenize(); // Преобразуваме текст в токени

        // Създаваме парсер и подаваме токените
        Parser parser(tokens);

        // Парсваме блока
        Block* block = parser.parse();

        // Проверяваме дали блокът е успешно парснат
        if (!block || block->statements.empty()) {
            std::cerr << "Парсването не върна резултат!" << std::endl;
            return 1;
        }

        // Обхождаме и проверяваме всяко изречение
        for (Statement* stmt : block->statements) {
            if (auto* readStmt = dynamic_cast<ReadStatement*>(stmt)) {
                std::cout << "READ: " << readStmt->variableName << std::endl;
            } else if (auto* letStmt = dynamic_cast<LetStatement*>(stmt)) {
                std::cout << "LET: " << letStmt->variableName;
                if (letStmt->value) {
                    std::cout << " = " << letStmt->value;
                }
                std::cout << std::endl;
            } else if (auto* labelStmt = dynamic_cast<LabelStatement*>(stmt)) {
                std::cout << "LABEL: " << labelStmt->labelName << std::endl;
            } else {
                std::cout << "Неизвестно изречение!" << std::endl;
            }
        }

        // Освобождаваме паметта
        delete block;
    } catch (const std::exception& ex) {
        std::cerr << "Грешка: " << ex.what() << std::endl;
    }

    return 0;
}
