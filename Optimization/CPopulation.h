#ifndef L1_ALGORYTMY_GENETYCZNE_CPOPULATION_H
#define L1_ALGORYTMY_GENETYCZNE_CPOPULATION_H


#include "Representation/CIndividual.h"

class CPopulation {

public:
    CPopulation(CPcbProblem *pcProblem, int iSize);
    ~CPopulation();

    CIndividual * pcInitializeRandomIndividual(int iIndex);
    void vInitializeRandomPopulation();
    double dGetAdaptationGrade(int iIndex);
    void vDie();

private:
    CPcbProblem *pc_problem;
    CIndividual **pc_individuals;
    int i_population_size;
    int i_generation;

    double d_best_fitness;
    int i_best_individual_index;
    CIndividual *pc_best_individual;
    double d_population_fitness;

    void v_initialize_individuals();

public:
    void vAddPopulationFitness(double dFitness);

    double dGetBestFitness();
    int iGetGeneration() const;
    int iGetSize() const;

    CIndividual *pcGetIndividual(int iIndex);
    CIndividual *pcGetBestIndividual();
    int iGetBestIndividualIndex();

    void vSetBestFitness(double dBestFitness);
    void vSetBestIndividual(int iIndex);
    void vSetBestIndividual(CIndividual *pcIndividual);
};

#endif //L1_ALGORYTMY_GENETYCZNE_CPOPULATION_H
