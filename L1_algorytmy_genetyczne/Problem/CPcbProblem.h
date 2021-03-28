#ifndef L1_ALGORYTMY_GENETYCZNE_CPCBPROBLEM_H
#define L1_ALGORYTMY_GENETYCZNE_CPCBPROBLEM_H

#include <vector>
#include <string>

#define PATH_POINTS 4

class CPcbProblem {

public:
    explicit CPcbProblem(std::string sFileName);
    CPcbProblem(int iBoardX, int iBoardY, std::vector<int> vPoints);
    ~CPcbProblem();

    void vLoadFromFile();
    void vSetBoard(int iX, int iY);
    void vSetPoints(std::vector<int> vPoints);

    int iGetPathsQuantity();
    int iGetBoardDimension(bool dimension);
    int *iGetPoints(int iPathId);
    int iGetPoint(int iRow, int iColumn);

    std::string sGetFile();
    std::string sToString();

private:
    int i_board_size_x;
    int i_board_size_y;

    int **pi_points;        // macierz n x [start_x, start_y, end_x, end_y]
    int i_paths_quantity;   // n

    std::string s_file_name;

    static void v_allocate_matrix(int ***piMatrix, int iColumns, int iRows);
    static void v_deallocate_matrix(int **piMatrix, int iRows);

    std::string s_get_points();
};


#endif //L1_ALGORYTMY_GENETYCZNE_CPCBPROBLEM_H
