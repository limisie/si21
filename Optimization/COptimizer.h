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

private:
    CPcbProblem *pc_problem;
    CPopulation *pc_population;
    double *pd_penalties;

    int i_stop_condition_mode;
    int i_iterations;
    double d_expected_fitness;

    void v_grade_individual(CIndividual *pcIndividual);
    bool b_stop_condition();

public:
    double dGetAdjustmentGrade(int iIndividual);
    double dGetFitness(int iIndividual);

    void vSetExpectedFitness(double dExpectedFitness);
    void vSetNumberOfIterations(int iIterations);

    void v_grade_individual(CIndividual &pcIndividual);
};

#endif //L1_ALGORYTMY_GENETYCZNE_COPTIMIZER_H
