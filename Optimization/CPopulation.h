#ifndef L1_ALGORYTMY_GENETYCZNE_CPOPULATION_H
#define L1_ALGORYTMY_GENETYCZNE_CPOPULATION_H


#include "Representation/CIndividual.h"

class CPopulation {

public:
    CPopulation(CPcbProblem *pcProblem, int iSize);
    ~CPopulation();


private:
    CPcbProblem *pc_problem;
    CIndividual **pc_individuals;
    int i_population_size;
    int i_generation;
    double d_best_fitness;
    int i_best_individual_index;

    void v_initialize_individuals();

public:
    double dGetBestFitness();
    int iGetGeneration() const;
    int iGetSize() const;
    CIndividual *pcGetIndividual(int iIndex);
    CIndividual *pcGetBestIndividual();

    CIndividual * pcInitializeRandomIndividual(int iIndex);
    void vSetBestFitness(double dBestFitness);
    void vSetBestIndividual(int iIndex);

    void vDie();

    int iGetBestIndividualIndex();
};

#endif //L1_ALGORYTMY_GENETYCZNE_CPOPULATION_H
