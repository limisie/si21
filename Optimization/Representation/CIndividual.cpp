#include "CIndividual.h"

CIndividual::CIndividual(CPcbProblem *pcProblem) {
    pc_problem = pcProblem;
    pc_paths = new CPath*[pc_problem->iGetPathsQuantity()];
    v_initialize_paths();
    v_initialize_board();

    pi_violations = new int[VIOLATION_TYPES];
}

CIndividual::~CIndividual() {
    pc_problem = nullptr;
    delete [] pc_paths;
    v_deallocate_matrix(pi_board, pc_problem->iGetPathsQuantity());
    delete pi_violations;
}

void CIndividual::vInitializeRandomPaths() {
    v_set_random_paths();
    v_bake();
    v_set_violations();
}

void CIndividual::v_set_random_paths() {
    for (int ii = 0; ii < pc_problem->iGetPathsQuantity(); ++ii) {
        pc_paths[ii]->vSetRandomPath(pc_problem->iGetBoardDimension(true), pc_problem->iGetBoardDimension(false));
    }
}

void CIndividual::v_bake() {
    int i_current_x, i_current_y, i_new_position_x, i_new_position_y, i_direction, i_step = 0;

    for (int ii = 0; ii < pc_problem->iGetPathsQuantity(); ++ii) {
        i_current_x = pc_paths[ii]->iGetStartPoints(true);
        i_current_y = pc_paths[ii]->iGetStartPoints(false);
        i_new_position_x = i_current_x;
        i_new_position_y = i_current_y;

        for (int jj = 0; jj < pc_paths[ii]->iGetSegmentsQuantity(); ++jj) {
            i_current_x = i_new_position_x;
            i_current_y = i_new_position_y;

            i_direction = get<0> (pc_paths[ii]->iGetSegment(jj));
            i_step = get<1> (pc_paths[ii]->iGetSegment(jj));

            switch (i_direction) {
                case UP:
                    i_new_position_y += i_step;
                    for (int kk = i_current_y + 1; kk <= i_new_position_y; ++kk) {
                        pi_board[i_current_x][kk] += 1;
                    }
                    break;
                case RIGHT:
                    i_new_position_x += i_step;
                    for (int kk = i_current_x + 1; kk <= i_new_position_x; ++kk) {
                        pi_board[kk][i_current_y] += 1;
                    }
                    break;
                case DOWN:
                    i_new_position_y -= i_step;
                    for (int kk = i_current_y - 1; kk >= i_new_position_y; --kk) {
                        pi_board[i_current_x][kk] += 1;
                    }
                    break;
                case LEFT:
                    i_new_position_x -= i_step;
                    for (int kk = i_current_x + 1; kk >= i_new_position_x; --kk) {
                        pi_board[kk][i_current_y] += 1;
                    }
                    break;
            }
        }
    }
}

void CIndividual::v_set_violations() {
    //TODO: ocena osobnika
}

void CIndividual::v_deallocate_matrix(int **piMatrix, int iRows) {
    for (int ii = 0; ii < iRows; ii++) {
        delete piMatrix[ii];
    }
    delete piMatrix;
}

void CIndividual::v_allocate_matrix(int ***piMatrix, int iColumns, int iRows) {
    *piMatrix = new int *[iRows];
    for (int ii = 0; ii < iRows; ii++) {
        (*piMatrix)[ii] = new int[iColumns];
    }
}

void CIndividual::v_initialize_matrix(int ***piMatrix, int iColumns, int iRows) {
    for (int ii = 0; ii < iRows; ii++) {
        for (int jj = 0; jj < iColumns; ++jj) {
            (*piMatrix)[ii][jj] = 0;
        }
    }
}

void CIndividual::v_initialize_paths() {
    for (int ii = 0; ii < pc_problem->iGetPathsQuantity(); ++ii) {
        int *i_points;
        i_points = pc_problem->iGetPoints(ii);

        pc_paths[ii] = new CPath(i_points[0], i_points[1], i_points[2], i_points[3]);

        i_points = nullptr;
        delete i_points;
    }
}

void CIndividual::v_initialize_board() {
    int i_paths = pc_problem->iGetPathsQuantity();
    int i_board_x = pc_problem->iGetBoardDimension(true);
    int i_board_y = pc_problem->iGetBoardDimension(false);

    v_allocate_matrix(&pi_board, i_board_x, i_board_y);
    v_initialize_matrix(&pi_board, i_board_x, i_board_y);

    for (int ii = 0; ii < i_paths; ++ii) {
        pi_board[pc_problem->iGetPoint(ii, 1)][pc_problem->iGetPoint(ii, 0)] += 1;
        pi_board[pc_problem->iGetPoint(ii, 3)][pc_problem->iGetPoint(ii, 2)] += 1;
    }
}

std::string CIndividual::s_get_points() {
    std::string s_board;
    int i_board_x = pc_problem->iGetBoardDimension(true);
    int i_board_y = pc_problem->iGetBoardDimension(false);

    for (int i = 0; i < i_board_y; i++) {
        for (int j = 0; j < i_board_x; j++) {
            s_board += std::to_string(pi_board[i][j]) + " ";
        }
        s_board += "\n";
    }

    return s_board;
}

void CIndividual::vSetFitness(double dFitness) {
    d_fitness = dFitness;
}

CPath CIndividual::cGetPath(int id) {
    return *pc_paths[id];
}

std::string CIndividual::sToString() {
    return s_get_points();
}

double CIndividual::dGetFitness() {
    return d_fitness;
}

int *CIndividual::iGetViolations() {
    return pi_violations;
}
