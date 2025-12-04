#include <iostream>
#include <string>
#include "sort.h"
#include "argparser.h"

int main(int argc, char* argv[]) {
    if (argc < 3) {
        std::cerr << "Usage: " << argv[0] << " -a/-d <numbers>\n";
        return 1;
    }

    bool order;
    std::string option = argv[1];

    if (option == "-a") order = true;
    else if (option == "-d") order = false;
    else {
        std::cerr << "Unknown option: " << option << "\n";
        return 1;
    }

    int count = argc - 2;
    int* numbers = new int[count];
    parseArguments(&argv[2], count, numbers);

    bubbleSort(numbers, count, order);

    std::cout << "In order: ";
    for (int i = 0; i < count; ++i) {
        std::cout << numbers[i] << " ";
    }
    std::cout << "\n";

    delete[] numbers;
    return 0;
}
