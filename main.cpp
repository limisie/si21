#include <iostream>
#include "Problem/CPcbProblem.h"
#include "Optimization/Representation/CIndividual.h"
#include "Helper/CRandom.h"
#include "Optimization/COptimizer.h"

#define TEST_FILE_PATH "/Users/limi/Desktop/INF/6_SI/L1_algorytmy_genetyczne/Test_Cases/zad0.txt"

void vRunRandom() {
    CRandom cRandom = CRandom();

    std::cout << cRandom.iRandomInt() << "\n";
    std::cout << cRandom.iRandomIntInclusiveRange(0, 3) << "\n";
}

void vRunIndividualInitialization() {
    std::string sFileName = TEST_FILE_PATH;
    CPcbProblem *cPcbProblem;
    cPcbProblem = new CPcbProblem(sFileName);
    cPcbProblem->vLoadFromFile();
    std::cout << cPcbProblem->sToString() << "\n";

    CIndividual cIndividual = CIndividual(cPcbProblem);
    std::cout << cIndividual.sToString() << "\n";

    cIndividual.vInitializeRandomPaths();
    std::cout << cIndividual.sToString() << "\n";
}

void vRunRandomOptimizer() {
    std::string sFileName = TEST_FILE_PATH;
    CPcbProblem *cPcbProblem;
    cPcbProblem = new CPcbProblem(sFileName);
    cPcbProblem->vLoadFromFile();
    std::cout << cPcbProblem->sToString() << "\n";

    double *pdPenalties;
    pdPenalties = new double[VIOLATION_TYPES] {100000, 100, 10, 1, 1};

    COptimizer cOptimizer = COptimizer(cPcbProblem, pdPenalties, 10);
    cOptimizer.vSetNumberOfIterations(1000);
    CIndividual *pcBest = cOptimizer.pcRandom();
    std::cout << pcBest->sToString() << std::endl;
}

void vRunOptimizer() {
    std::string sFileName = TEST_FILE_PATH;
    CPcbProblem *cPcbProblem;
    cPcbProblem = new CPcbProblem(sFileName);
    cPcbProblem->vLoadFromFile();
    std::cout << cPcbProblem->sToString() << "\n";

    double *pdPenalties;
    pdPenalties = new double[VIOLATION_TYPES] {100000, 100, 1000, 1, 1};

    COptimizer cOptimizer = COptimizer(cPcbProblem, pdPenalties, 300);
    cOptimizer.vSetNumberOfIterations(300);
    CIndividual *pcBest = cOptimizer.pcOptimize();
    std::cout << pcBest->sToString() << std::endl;
}

int main() {
    vRunOptimizer();
}
