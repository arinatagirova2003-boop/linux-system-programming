#include "argparser.h"
#include <cstdlib>

void parseArguments(char* argv[], int argc, int* outArray) {
    for (int i = 0; i < argc; ++i) {
        outArray[i] = std::atoi(argv[i]);
    }
}
