#include "CPopulation.h"

CPopulation::CPopulation(CPcbProblem *pcProblem, int iSize) {
    pc_problem = pcProblem;
    i_population_size = iSize;
    i_generation = 0;
    d_best_fitness = std::numeric_limits<double>::max();
    i_best_individual_index = -1;
    d_population_fitness = 0;
    pc_best_individual = nullptr;
    pc_individuals = new CIndividual *[i_population_size];
    v_initialize_individuals();
}

CPopulation::~CPopulation() {
    pc_problem = nullptr;
    delete pc_best_individual;
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

void CPopulation::vDie() {
    i_generation++;
    d_population_fitness = 0;

    for (int ii = 0; ii < i_population_size; ++ii) {
        if (ii != i_best_individual_index) {
            delete pc_individuals[ii];
        }
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

int CPopulation::iGetBestIndividualIndex() {
    return i_best_individual_index;
}

void CPopulation::vSetBestFitness(double dBestFitness) {
    d_best_fitness = dBestFitness;
}

void CPopulation::vSetBestIndividual(int iIndex) {
    i_best_individual_index = iIndex;
}

void CPopulation::vSetBestIndividual(CIndividual *pcIndividual) {
    pc_best_individual = pcIndividual;
    d_best_fitness = pc_best_individual->dGetFitness();
}

void CPopulation::vAddPopulationFitness(double dFitness) {
    d_population_fitness += dFitness;
}