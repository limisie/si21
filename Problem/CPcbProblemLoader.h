#ifndef L1_ALGORYTMY_GENETYCZNE_CPCBPROBLEMLOADER_H
#define L1_ALGORYTMY_GENETYCZNE_CPCBPROBLEMLOADER_H


#include <iostream>
#include <sstream>
#include <fstream>
#include "CPcbProblem.h"

class CPcbProblemLoader {

public:
    explicit CPcbProblemLoader(CPcbProblem *pcProblem);
    ~CPcbProblemLoader();

    void vLoad();

private:
    CPcbProblem *pc_problem;
    std::ifstream s_file;

    bool b_open_to_read();
    bool b_close();

    void v_load_board();
    void v_load_points();
};


#endif //L1_ALGORYTMY_GENETYCZNE_CPCBPROBLEMLOADER_H
