#include <set>
#include "COptimizer.h"

COptimizer::COptimizer(CPcbProblem *pcProblem, double *pdPenalties, int iPopulationSize, int iMode) {
    pc_problem = pcProblem;
    pc_population = new CPopulation(pc_problem, iPopulationSize);
    pd_penalties = pdPenalties;
    i_stop_condition_mode = iMode;
    i_iterations = 0;
    d_expected_fitness = 0;

    d_tournament_percentage = 1;
}

COptimizer::~COptimizer() {
    pc_problem = nullptr;
    delete pc_population;
    pd_penalties = nullptr;
}

CIndividual *COptimizer::pcRandom() {
    while (!b_stop_condition()) {
        for (int ii = 0; ii < pc_population->iGetSize(); ii++) {
            CIndividual *pc_individual = pc_population->pcInitializeRandomIndividual(ii);
            double d_fitness = d_grade_individual(pc_individual);

            if (d_fitness < pc_population->dGetBestFitness()) {
                pc_population->vSetBestIndividual(new CIndividual(*pc_individual));
            }
        }
        pc_population->vDie();
    }
    return pc_population->pcGetBestIndividual();
}

CIndividual *COptimizer::pcOptimize() {
    while (!b_stop_condition()) {
    }
    return pc_population->pcGetBestIndividual();
}

int COptimizer::i_tournament_selection() {
    int i_winner_index = -1;
    double d_best_fitness = std::numeric_limits<double>::max();

    int i_individuals_set_size = pc_population->iGetSize() * d_tournament_percentage;
    std::set<int> si_chosen;

    CRandom c_random;
    while (si_chosen.size() < i_individuals_set_size) {
        int i_random = c_random.iRandomIntInclusiveRange(0, pc_population->iGetSize() - 1);
        bool b_is_unique = si_chosen.insert(i_random).second;

        if (b_is_unique) {
            double d_individual_fitness = pc_population->pcGetIndividual(i_random)->dGetFitness();
            if (d_individual_fitness < d_best_fitness) {
                i_winner_index = i_random;
                d_best_fitness = d_individual_fitness;
            }
        }
    }
    return i_winner_index;
}

int COptimizer::i_roulette_selection() {

}

double COptimizer::d_grade_individual(CIndividual *pcIndividual) {
    double d_grade = 0;
    int *pi_violations = pcIndividual->iGetViolations();

    for (int ii = 0; ii < VIOLATION_TYPES; ++ii) {
        d_grade += pd_penalties[ii] * (double) pi_violations[ii];
    }

    pcIndividual->vSetFitness(d_grade);
    return d_grade;
}

bool COptimizer::b_stop_condition() {
    switch (i_stop_condition_mode) {
        case 0:
            return i_iterations < pc_population->iGetGeneration();
        case 1:
            return d_expected_fitness > pc_population->dGetBestFitness();
    }
    return true;
}

void COptimizer::vInitializeRandomPopulation() {
    for (int ii = 0; ii < pc_population->iGetSize(); ++ii) {
        CIndividual *pc_new;
        pc_new = pc_population->pcInitializeRandomIndividual(ii);
        d_grade_individual(pc_new);
        pc_population->vAddPopulationFitness(pc_new->dGetFitness());
    }

}

void COptimizer::vSetExpectedFitness(double dExpectedFitness) {
    d_expected_fitness = dExpectedFitness;
}

void COptimizer::vSetNumberOfIterations(int iIterations) {
    i_iterations = iIterations;
}

void COptimizer::vSetTournamentPercentage(double dPercentage) {
    d_tournament_percentage = dPercentage;
}
