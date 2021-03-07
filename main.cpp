#include <iostream>
#include "Problem/CPcbProblem.h"
#include "Optimization/Representation/CIndividual.h"
#include "Helper/CRandom.h"
#include "Optimization/COptimizer.h"

#define TEST_FILE_PATH "/Users/limi/Desktop/INF/6_SI/L1_algorytmy_genetyczne/Test_Cases/zad0.txt"

void vTestRandom() {
    CRandom cRandom = CRandom();

    std::cout << cRandom.iRandomInt() << "\n";
    std::cout << cRandom.iRandomIntInclusiveRange(0, 3) << "\n";
}

void vTestLoading() {
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

void vTestOptimizer() {
    std::string sFileName = TEST_FILE_PATH;
    CPcbProblem *cPcbProblem;
    cPcbProblem = new CPcbProblem(sFileName);
    cPcbProblem->vLoadFromFile();
    std::cout << cPcbProblem->sToString() << "\n";

    double *pdPenalties;
    pdPenalties = new double[VIOLATION_TYPES] {1, 1, 1, 1, 1};

    COptimizer cOptimizer = COptimizer(cPcbProblem, pdPenalties, 10);
    cOptimizer.vInitRandomPopulation();
    cOptimizer.vGadePopulation();
    cOptimizer.vShowPopulation();
}

int main() {
    vTestOptimizer();
}

//TODO: PYTANIA
//- stopień nieprzystosowania czy funkcja przystosowania?
//- czy jest sens operować na genotypie skoro ma zmienną długość?
