#include "CPcbProblemLoader.h"

CPcbProblemLoader::CPcbProblemLoader(CPcbProblem *pcProblem) {
    pc_problem = pcProblem;
}

CPcbProblemLoader::~CPcbProblemLoader() {
    pc_problem = nullptr;
    b_close();
}

void CPcbProblemLoader::vLoad() {
    if (b_open_to_read()) {
        v_load_board();
        v_load_points();
    }
    b_close();
}

void CPcbProblemLoader::v_load_board() {
    std::string s_line;
    std::string s_x;
    std::string s_y;
    std::getline(s_file, s_line);

    std::istringstream ss(s_line);
    std::getline(ss, s_x, ';');
    std::getline(ss, s_y, ';');

    pc_problem->vSetBoard(std::stoi( s_x ), std::stoi( s_y ));
}

void CPcbProblemLoader::v_load_points() {
    std::string s_line;
    std::string s_int;
    std::vector<int> v_ints;

    while (std::getline(s_file, s_line)) {
        std::istringstream ss(s_line);
        while (std::getline(ss, s_int, ';')) {
            v_ints.push_back(std::stoi( s_int ));
        }
    }

    pc_problem->vSetPoints(v_ints);
}

bool CPcbProblemLoader::b_open_to_read() {
    try {
        s_file.open(pc_problem->sGetFile());
    } catch (...) {}
    return s_file.is_open();
}

bool CPcbProblemLoader::b_close() {
    try {
        s_file.close();
    } catch (...) {}
    return !s_file.is_open();
}

