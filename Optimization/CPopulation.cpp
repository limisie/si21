#include "CPopulation.h"

CPopulation::CPopulation(CPcbProblem *pcProblem, int iSize) {
    pc_problem =pcProblem;
    i_population_size = iSize;
    i_generation = 0;
    d_best_fitness = std::numeric_limits<double>::max();
    pc_individuals = new CIndividual*[i_population_size];
    v_initialize_individuals();
}

CPopulation::~CPopulation() {
    pc_problem = nullptr;
    delete [] pc_individuals;
}

int CPopulation::iGetSize() const {
    return i_population_size;
}

int CPopulation::iGetGeneration() const {
    return i_generation;
}

void CPopulation::vDie() {
    i_generation++;

    CIndividual *pc_best = pc_individuals[i_best_individual_index];
    for (int ii = 0; ii < i_population_size; ++ii) {
        if (ii != i_best_individual_index) {
            delete pc_individuals[ii];
        }
    }
    int i_new_best = 0;

    pc_individuals[i_new_best] = pc_best;
    i_best_individual_index = i_new_best;
}

CIndividual *CPopulation::pcGetIndividual(int iIndex) {
    return pc_individuals[iIndex];
}

void CPopulation::v_initialize_individuals() {
    for (int ii = 0; ii < i_population_size; ++ii) {
        pc_individuals[ii] = new CIndividual(pc_problem);
    }
}

double CPopulation::dGetBestFitness() {
    return d_best_fitness;
}

CIndividual* CPopulation::pcGetBestIndividual() {
    return pc_individuals[i_best_individual_index];
}

int CPopulation::iGetBestIndividualIndex() {
    return i_best_individual_index;
}

void CPopulation::vSetBestFitness(double dBestFitness) {
    d_best_fitness = dBestFitness;
}

CIndividual* CPopulation::pcInitializeRandomIndividual(int iIndex) {
    if (pc_individuals[iIndex] != nullptr) {
        delete pc_individuals[iIndex];
    }
    pc_individuals[iIndex] = new CIndividual(pc_problem);
    pc_individuals[iIndex]->vInitializeRandomPaths();
    return pc_individuals[iIndex];
}

void CPopulation::vSetBestIndividual(int iIndex) {
    i_best_individual_index = iIndex;
}