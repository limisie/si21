#ifndef L1_ALGORYTMY_GENETYCZNE_CINDIVIDUAL_H
#define L1_ALGORYTMY_GENETYCZNE_CINDIVIDUAL_H

#include "../../Problem/CPcbProblem.h"
#include "CPath.h"

#define VIOLATION_TYPES 5
#define K1 0
#define K2 1
#define K3 2
#define K4 3
#define K5 4

class CIndividual {

public:

    explicit CIndividual(CPcbProblem *pc_problem);
    ~CIndividual();

    void vInitializeRandomPaths();

private:
    CPcbProblem *pc_problem;
    CPath **pc_paths;
    int **pi_board;

    //k1 - liczba przecięć,
    //k2 - sumaryczna długość ścieżek,
    //k3 - sumaryczna liczba segmentów tworzących ścieżki.
    //k4 - liczba ścieżek poza płytką,
    //k5 - sumaryczna długość części ścieżek poza płytką.
    int *pi_violations;
    double d_fitness;

    void v_set_random_paths();
    void v_bake();
    void v_set_violations();

    static void v_deallocate_matrix(int **piMatrix, int iRows);
    static void v_allocate_matrix(int ***piMatrix, int iColumns, int iRows);
    static void v_initialize_matrix(int ***piMatrix, int iColumns, int iRows);
    void v_initialize_paths();
    void v_initialize_board();
    std::string s_get_points();

public:
    int *iGetViolations();

    void vSetFitness(double dFitness);
    double dGetFitness() const;

    CPath cGetPath(int id);
    std::string sToString();
};


#endif //L1_ALGORYTMY_GENETYCZNE_CINDIVIDUAL_H
