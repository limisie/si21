#include <set>
#include "COptimizer.h"
#include "../Problem/CPcbProblemLoader.h"

#define SAVE_TO_FILE true


COptimizer::COptimizer(CPcbProblem *pcProblem, double *pdPenalties, int iPopulationSize) {
    pc_problem = pcProblem;
    pc_population = new CPopulation(pc_problem, iPopulationSize);
    pd_penalties = pdPenalties;

    i_selection_mode = 0;
    i_crossover_mode = 0;
    i_stop_condition_mode = 0;

    i_iterations = 0;
    d_expected_fitness = 0;

    d_tournament_percentage = 0.7;
    d_crossover_probability = 0.75;
    d_mutation_probability = 0.25;
}

COptimizer::~COptimizer() {
    pc_problem = nullptr;
    delete pc_population;
    pd_penalties = nullptr;
}

CIndividual *COptimizer::pcRandom() {
    while (!b_stop_condition()) {

        double d_best = std::numeric_limits<double>::max();
        double d_worst = 0;
        double d_sum = 0;

        for (int ii = 0; ii < pc_population->iGetSize(); ii++) {
            CIndividual *pc_individual = pc_population->pcInitializeRandomIndividual(ii);
            double d_fitness = d_grade_individual(pc_individual);

            if (d_fitness < pc_population->dGetBestFitness()) {
                pc_population->vSetBestIndividual(new CIndividual(*pc_individual));
            }
        }

        if (SAVE_TO_FILE) {
            for (int ii = 0; ii < pc_population->iGetSize(); ++ii) {
                double d_fitness = pc_population->pcGetIndividual(ii)->dGetFitness();
                if (d_fitness > d_worst) {
                    d_worst = d_fitness;
                }
                if (d_fitness < d_best) {
                    d_best = d_fitness;
                }
                d_sum += d_fitness;
            }

            v_write_population_data_to_file(pc_population->iGetGeneration(),
                                            d_best,
                                            d_worst,
                                            d_sum / pc_population->iGetSize());
        }

        pc_population->vDie();

    }
    return pc_population->pcGetBestIndividual();
}

CIndividual *COptimizer::pcOptimize() {
    CRandom c_random = CRandom();
    CPopulation *pc_new;
    vInitializeRandomPopulation();

    while (!b_stop_condition()) {
        pc_new = new CPopulation(*pc_population);
        pc_population->vCountPopulationFitness();

        double d_best = std::numeric_limits<double>::max();
        double d_worst = 0;
        double d_sum = 0;

        for (int ii = 0; ii < pc_population->iGetSize(); ++ii) {
            int i_current_individual = i_selection();
            CIndividual *pc_mother = pc_population->pcGetIndividual(i_current_individual);
            auto *pc_kid = new CIndividual(*pc_mother);
            pc_new->vSetIndividual(ii, pc_kid);

            double d_probability = c_random.dRandomDoubleInclusiveRange(0.0, 1.0);
            if (d_probability < d_crossover_probability) {
                int i_father_index = i_selection();
                while (i_current_individual == i_father_index) {
                    i_father_index = i_selection();
                }
                CIndividual *pc_father = pc_population->pcGetIndividual(i_father_index);
                v_crossover(pc_kid, pc_father);
            }

            d_probability = c_random.dRandomDoubleInclusiveRange(0, 1);
            if (d_probability < d_mutation_probability) {
                v_mutate(pc_kid);
            }

            double d_fitness = d_grade_individual(pc_kid);
            if (d_fitness < pc_population->dGetBestFitness()) {
                pc_population->vSetBestFitness(d_fitness);
                pc_new->vSetBestIndividual(new CIndividual(*pc_kid));
            }
        }

        if (SAVE_TO_FILE) {
            for (int ii = 0; ii < pc_population->iGetSize(); ++ii) {
                double d_fitness = pc_population->pcGetIndividual(ii)->dGetFitness();
                if (d_fitness > d_worst) {
                    d_worst = d_fitness;
                }
                if (d_fitness < d_best) {
                    d_best = d_fitness;
                }
                d_sum += d_fitness;
            }

            v_write_population_data_to_file(pc_population->iGetGeneration(),
                                            d_best,
                                            d_worst,
                                            d_sum / pc_population->iGetSize());
        }

        delete pc_population;
        pc_population = pc_new;
    }
    return pc_population->pcGetBestIndividual();
}

void COptimizer::v_write_population_data_to_file(int iGeneration, double dBest, double dWorst, double dAverage) {
    CPcbProblemLoader c_loader = CPcbProblemLoader(pc_problem);
    c_loader.vSaveLine(s_file_name, iGeneration, dBest, dWorst, dAverage);
}

void COptimizer::v_mutate(CIndividual *pcIndividual) {
    CRandom cRandom = CRandom();
    int i_path_quantity = pc_problem->iGetPathsQuantity();
    int i_path_to_mutate = cRandom.iRandomIntInclusiveRange(0, i_path_quantity - 1);

    pcIndividual->vMutate(i_path_to_mutate);
    pcIndividual->vUpdate();
}

void COptimizer::v_crossover(CIndividual *pcKid, CIndividual*pcDad) {
    switch (i_crossover_mode) {
        case 0:
            v_single_point_crossover(pcKid, pcDad);
            break;
        case 1:
            v_multipoint_crossover(pcKid, pcDad);
            break;
    }
    pcKid->vUpdate();
}

void COptimizer::v_single_point_crossover(CIndividual *pcKid, CIndividual*pcDad) {
    CRandom c_random = CRandom();
    int i_paths_quantity = pc_problem->iGetPathsQuantity();
    int i_point = c_random.iRandomIntInclusiveRange(0, i_paths_quantity - 1);

    for (int ii = i_point; ii < i_paths_quantity; ++ii) {
        pcKid->vSetPath(ii, pcDad->vGetPath(ii));
    }
}

void COptimizer::v_multipoint_crossover(CIndividual *pcKid, CIndividual *pcDad) {
    CRandom c_random = CRandom();
    int i_paths_quantity = pc_problem->iGetPathsQuantity();

    for (int ii = 0; ii < i_paths_quantity; ++ii) {
        if(c_random.dRandomDoubleInclusiveRange(0.0, 1.0) < d_crossover_probability) {
            pcKid->vSetPath(ii, pcDad->vGetPath(ii));
        }
    }
}

int COptimizer::i_selection() {
    switch (i_selection_mode) {
        case 0:
            return i_tournament_selection();
        case 1:
            return i_roulette_selection();
    }
    return true;
}

int COptimizer::i_tournament_selection() {
    int i_winner_index = -1;
    double d_best_fitness = std::numeric_limits<double>::max();

    int i_individuals_set_size = pc_population->iGetSize() * d_tournament_percentage;
    std::set<int> si_chosen;

    CRandom c_random = CRandom();
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
    int i_index = 0;
    double d_partial_sum = 0;

    CRandom c_random = CRandom();
    double d_pick = c_random.dRandomDoubleInclusiveRange(0.0, 1.0);

    while (d_pick > d_partial_sum) {
        double d_adaptation_grade = pc_population->dGetAdaptationGrade(i_index);
        d_partial_sum += d_adaptation_grade;
        i_index++;
    }

    return i_index - 1;
}

double COptimizer::d_grade_individual(CIndividual *pcIndividual) {
    double d_grade = 0;
    int *pi_violations;
    pi_violations = pcIndividual->iGetViolations();

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
    }
}

void COptimizer::vSetExpectedFitness(double dExpectedFitness) {
    d_expected_fitness = dExpectedFitness;
    i_stop_condition_mode = 1;
}

void COptimizer::vSetNumberOfIterations(int iIterations) {
    i_iterations = iIterations;
    i_stop_condition_mode = 0;
}

void COptimizer::vSetTournamentPercentage(double dPercentage) {
    d_tournament_percentage = dPercentage;
}

void COptimizer::vSetCrossoverProbability(double dCrossoverProbability) {
    d_crossover_probability = dCrossoverProbability;
}

void COptimizer::vSetMutationProbability(double dMutationProbability) {
    d_mutation_probability = dMutationProbability;
}

void COptimizer::vSetFileName(std::string sFileName) {
    s_file_name = sFileName;
}
