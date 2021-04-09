#include "CPcbProblemLoader.h"

CPcbProblemLoader::CPcbProblemLoader(CPcbProblem *pcProblem) {
    pc_problem = pcProblem;
}

CPcbProblemLoader::~CPcbProblemLoader() {
    b_close(true);
    b_close(false);
}

void CPcbProblemLoader::vLoad() {
    if (b_open_to_read()) {
        v_load_board();
        v_load_points();
    }
    b_close(true);
}

void CPcbProblemLoader::v_load_board() {
    std::string s_line;
    std::string s_x;
    std::string s_y;
    std::getline(s_input_file, s_line);

    std::istringstream ss(s_line);
    std::getline(ss, s_x, ';');
    std::getline(ss, s_y, ';');

    pc_problem->vSetBoard(std::stoi( s_x ), std::stoi( s_y ));
}

void CPcbProblemLoader::v_load_points() {
    std::string s_line;
    std::string s_int;
    std::vector<int> v_ints;

    while (std::getline(s_input_file, s_line)) {
        std::istringstream ss(s_line);
        while (std::getline(ss, s_int, ';')) {
            v_ints.push_back(std::stoi( s_int ));
        }
    }

    pc_problem->vSetPoints(v_ints);
}

bool CPcbProblemLoader::b_open_to_read() {
    try {
        s_input_file.open(pc_problem->sGetFile());
    } catch (...) {}
    return s_input_file.is_open();
}

bool CPcbProblemLoader::b_close(bool bInputFile) {
    bool b_result = false;

    if (bInputFile) {
        try {
            s_input_file.close();
        } catch (...) {}
        b_result = !s_input_file.is_open();
    } else {
        try {
            s_output_file.close();
        } catch (...) {}
        b_result = !s_output_file.is_open();
    }
    return b_result;
}

void CPcbProblemLoader::vSaveLine(std::string sFileName, int iGeneration, double dBest, double dWorst, double dAverage) {
    b_open_to_write(sFileName);
    std::string s_line = std::to_string((int)iGeneration) + ";" + std::to_string(static_cast<std::int64_t>(dBest)) + ";" + std::to_string(static_cast<std::int64_t>(dWorst)) + ";" + std::to_string(static_cast<std::int64_t>(dAverage));

    s_output_file << s_line << std::endl;
    b_close(false);
}

bool CPcbProblemLoader::b_open_to_write(std::string sFileName) {
    try {
        s_output_file.open(sFileName, std::ios_base::app);
    } catch (...) {}
    return s_output_file.is_open();
}
