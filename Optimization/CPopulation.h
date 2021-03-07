#ifndef L1_ALGORYTMY_GENETYCZNE_CPOPULATION_H
#define L1_ALGORYTMY_GENETYCZNE_CPOPULATION_H


#include "Representation/CIndividual.h"

class CPopulation {

public:
    CPopulation(CPcbProblem *pcProblem, int iSize);
    ~CPopulation();

    void vInitRandomPopulation();
    int iGetSize() const;
    CIndividual *pcGetIndividual(int iIndex);

private:
    int i_population_size;
    CPcbProblem *pc_problem;
    CIndividual **pc_individuals;

    void v_initialize_individuals();
};



#endif //L1_ALGORYTMY_GENETYCZNE_CPOPULATION_H
