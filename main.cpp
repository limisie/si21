#include <iostream>
#include "Problem/CPcbProblem.h"

#define B_DEBUG true
#define TEST_FILE_PATH "/Users/limi/Desktop/INF/6_SI/L1_algorytmy_genetyczne/Test_Cases/zad1.txt"

int main() {
    std::string sFileName = TEST_FILE_PATH;
    auto cPcbProblem = CPcbProblem(sFileName);
    cPcbProblem.vLoadFromFile();
    std::cout << cPcbProblem.sToString() << "\n";
}
