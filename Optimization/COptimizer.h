#ifndef L1_ALGORYTMY_GENETYCZNE_COPTIMIZER_H
#define L1_ALGORYTMY_GENETYCZNE_COPTIMIZER_H

#include "../Problem/CPcbProblem.h"
#include "CPopulation.h"
#include <iostream>

class COptimizer {

public:
    COptimizer(CPcbProblem *pcProblem, double *pdPenalties, int iPopulationSize, int iMode);
    ~COptimizer();

    CIndividual * pcRandom();
    CIndividual *pcOptimize();

    void vInitializeRandomPopulation();

private:
    CPcbProblem *pc_problem;
    CPopulation *pc_population;
    double *pd_penalties;

    int i_stop_condition_mode;
    int i_iterations;
    double d_expected_fitness;

    double d_tournament_percentage;

    int i_tournament_selection();
    int i_roulette_selection();

    double d_grade_individual(CIndividual *pcIndividual);
    bool b_stop_condition();

public:
    void vSetExpectedFitness(double dExpectedFitness);
    void vSetNumberOfIterations(int iIterations);
    void vSetTournamentPercentage(double dPercentage);
};

#endif //L1_ALGORYTMY_GENETYCZNE_COPTIMIZER_H
