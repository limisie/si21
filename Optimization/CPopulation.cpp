#include "CPopulation.h"

CPopulation::CPopulation(CPcbProblem *pcProblem, int iSize) {
    pc_problem = pcProblem;
    i_population_size = iSize;
    i_generation = 0;
    d_best_fitness = std::numeric_limits<double>::max();
    d_population_fitness = 0;
    pc_best_individual = nullptr;
    pc_individuals = new CIndividual *[i_population_size];
    v_initialize_individuals();
}

CPopulation::CPopulation(CPopulation &cPopulation) {
    pc_problem = cPopulation.pc_problem;
    i_population_size = cPopulation.i_population_size;
    i_generation = cPopulation.i_generation + 1;

    pc_individuals = new CIndividual *[i_population_size];
    v_initialize_individuals();

    d_best_fitness = cPopulation.d_best_fitness;
    pc_best_individual = cPopulation.pc_best_individual;
//    if (cPopulation.pc_best_individual != nullptr) {
//        pc_best_individual = new CIndividual(*cPopulation.pc_best_individual);
//    } else {
//        pc_best_individual = nullptr;
//    }
    d_population_fitness = 0;
}

CPopulation::~CPopulation() {
    pc_problem = nullptr;
//    delete pc_best_individual;
    delete[] pc_individuals;
}

CIndividual *CPopulation::pcInitializeRandomIndividual(int iIndex) {
    pc_individuals[iIndex] = new CIndividual(pc_problem);
    pc_individuals[iIndex]->vInitializeRandomPaths();
    return pc_individuals[iIndex];
}

void CPopulation::vInitializeRandomPopulation() {
    for (int ii = 0; ii < i_population_size; ++ii) {
        pc_individuals[ii] = new CIndividual(pc_problem);
        pc_individuals[ii]->vInitializeRandomPaths();
    }
}

double CPopulation::dGetAdaptationGrade(int iIndex) {
    return pc_individuals[iIndex]->dGetFitness() / d_population_fitness;
}

void CPopulation::vDie() {
    i_generation++;
    d_population_fitness = 0;

    for (int ii = 0; ii < i_population_size; ++ii) {
        delete pc_individuals[ii];
    }
}

void CPopulation::v_initialize_individuals() {
    for (int ii = 0; ii < i_population_size; ++ii) {
        pc_individuals[ii] = new CIndividual(pc_problem);
    }
}

double CPopulation::dGetBestFitness() {
    return d_best_fitness;
}

int CPopulation::iGetGeneration() const {
    return i_generation;
}

int CPopulation::iGetSize() const {
    return i_population_size;
}

CIndividual *CPopulation::pcGetIndividual(int iIndex) {
    return pc_individuals[iIndex];
}

CIndividual *CPopulation::pcGetBestIndividual() {
    return pc_best_individual;
}

void CPopulation::vSetBestIndividual(CIndividual *pcIndividual) {
    delete pc_best_individual;
    pc_best_individual = pcIndividual;
    d_best_fitness = pc_best_individual->dGetFitness();
}

void CPopulation::vSetBestFitness(double dFitness) {
    d_best_fitness = dFitness;
}

double CPopulation::dGetPopulationFitness() {
    return d_population_fitness;
}

void CPopulation::vCountPopulationFitness() {
    d_population_fitness = 0;

    for (int ii = 0; ii < i_population_size; ++ii) {
        d_population_fitness += pc_individuals[ii]->dGetFitness();
    }
}

void CPopulation::vSetIndividual(int iIndex, CIndividual *pcIndividual) {
    if (pc_individuals[iIndex] != nullptr) {
        delete pc_individuals[iIndex];
    }
    pc_individuals[iIndex] = pcIndividual;
}
