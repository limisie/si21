#ifndef L1_ALGORYTMY_GENETYCZNE_COPTIMIZER_H
#define L1_ALGORYTMY_GENETYCZNE_COPTIMIZER_H

#include "../Problem/CPcbProblem.h"
#include "CPopulation.h"

class COptimizer {

public:
    COptimizer(CPcbProblem *pcProblem, double *pdPenalties, int iPopulationSize);

    ~COptimizer();

    CIndividual *pcRandom();
    CIndividual *pcOptimize();

    void vInitializeRandomPopulation();

private:
    CPcbProblem *pc_problem;
    CPopulation *pc_population;
    double *pd_penalties;

    int i_selection_mode;
    int i_crossover_mode;
    int i_stop_condition_mode;

    int i_iterations;
    double d_expected_fitness;

    double d_tournament_percentage;
    double d_crossover_probability;
    double d_mutation_probability;

    int i_tournament_selection();
    int i_roulette_selection();

    void v_crossover(CIndividual *pcKid, CIndividual *pcDad);
    void v_single_point_crossover(CIndividual *pcKid, CIndividual *pcDad);
    void v_multipoint_crossover(CIndividual *pcKid, CIndividual *pcDad);

    double d_grade_individual(CIndividual *pcIndividual);
    int i_selection();
    bool b_stop_condition();

public:
    void vSetExpectedFitness(double dExpectedFitness);
    void vSetNumberOfIterations(int iIterations);
    void vSetTournamentPercentage(double dPercentage);
    void vSetCrossoverProbability(double dCrossoverProbability);
    void vSetMutationProbability(double dMutationProbability);

};

#endif //L1_ALGORYTMY_GENETYCZNE_COPTIMIZER_H
