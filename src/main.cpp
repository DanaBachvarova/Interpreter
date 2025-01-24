#include "../include/parser.hpp"
#include "../include/ast.hpp"
#include "../include/lexer.hpp"
#include <iostream>
#include <vector>

int main() {
    // Примерен списък от токени за IF блок
    std::string input = R"(
        IF x > 10
            LET y = 20
            PRINT y
        ELSE
            LET y = 30
            PRINT y
        ENDIF
    )";
    std::vector<Token> tokens = Lexer(input).tokenize();

    // Създаваме парсер
    Parser parser(tokens);

    try {
        // Парсваме блока
        Block* block = parser.parse();

        // Принтираме резултата
        if (block) {
            std::cout << "Parsed block successfully:\n";
            block->print();
        } else {
            std::cout << "Failed to parse block.\n";
        }

        // Освобождаваме памет
        delete block;
    } catch (const std::exception& e) {
        std::cerr << "Error during parsing: " << e.what() << '\n';
    }

    return 0;
}
