#include "CPopulation.h"

CPopulation::CPopulation(CPcbProblem *pcProblem, int iSize) {
    pc_problem =pcProblem;
    i_population_size = iSize;
    pc_individuals = new CIndividual*[i_population_size];
}

CPopulation::~CPopulation() {
    pc_problem = nullptr;
    delete [] pc_individuals;
}

void CPopulation::vInitRandomPopulation() {
    v_initialize_individuals();
    v_initialize_paths();
}

int CPopulation::iGetSize() const {
    return i_population_size;
}

CIndividual *CPopulation::pcGetIndividual(int iIndex) {
    return pc_individuals[iIndex];
}

void CPopulation::v_initialize_individuals() {
    for (int ii = 0; ii < i_population_size; ++ii) {
        pc_individuals[ii] = new CIndividual(pc_problem);
    }
}

void CPopulation::v_initialize_paths() {
    for (int ii = 0; ii < i_population_size; ++ii) {
        pc_individuals[ii]->vInitializeRandomPaths();
    }
}