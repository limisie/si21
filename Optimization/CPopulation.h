#ifndef L1_ALGORYTMY_GENETYCZNE_CPOPULATION_H
#define L1_ALGORYTMY_GENETYCZNE_CPOPULATION_H


#include "Representation/CIndividual.h"

class CPopulation {

public:
    CPopulation(CPcbProblem *pcProblem, int iSize);
    CPopulation(CPopulation &cPopulation);
    ~CPopulation();

    CIndividual * pcInitializeRandomIndividual(int iIndex);
    void vInitializeRandomPopulation();
    double dGetAdaptationGrade(int iIndex);
    void vCountPopulationFitness();
    void vDie();

private:
    CPcbProblem *pc_problem;
    CIndividual **pc_individuals;
    int i_population_size;
    int i_generation;

    double d_best_fitness;
    CIndividual *pc_best_individual;
    double d_population_fitness;

    void v_initialize_individuals();

public:
    double dGetBestFitness();
    double dGetPopulationFitness();
    int iGetGeneration() const;
    int iGetSize() const;

    CIndividual *pcGetIndividual(int iIndex);
    CIndividual *pcGetBestIndividual();

    void vSetIndividual(int iIndex, CIndividual *pcIndividual);
    void vSetBestIndividual(CIndividual *pcIndividual);
    void vSetBestFitness(double dFitness);
};

#endif //L1_ALGORYTMY_GENETYCZNE_CPOPULATION_H
