#ifndef L1_ALGORYTMY_GENETYCZNE_CPOPULATION_H
#define L1_ALGORYTMY_GENETYCZNE_CPOPULATION_H


#include "Representation/CIndividual.h"

class CPopulation {

public:
    CPopulation(CPcbProblem *pcProblem, int iSize);
    ~CPopulation();

    void vInitRandomPopulation();

private:
    int i_population_size;
    CPcbProblem *pc_problem;
    CIndividual **pc_individuals;

    void v_initialize_individuals();
    void v_initialize_paths();

public:
    int iGetSize() const;
    CIndividual *pcGetIndividual(int iIndex);
};

#endif //L1_ALGORYTMY_GENETYCZNE_CPOPULATION_H
