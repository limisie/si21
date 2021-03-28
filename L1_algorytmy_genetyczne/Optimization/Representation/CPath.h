#ifndef L1_ALGORYTMY_GENETYCZNE_CPATH_H
#define L1_ALGORYTMY_GENETYCZNE_CPATH_H

#include "../../Helper/CRandom.h"
#include <tuple>
#include <vector>

#define UP 0
#define RIGHT 1
#define DOWN 2
#define LEFT 3

class CPath {

public:
    CPath();
    CPath(int iStartX, int iStartY, int iEndX, int iEndY);

    void vSetRandomPath(int iMaxX, int iMaxY);

    int iGetStartPoints(bool dimension) const;
    std::tuple<int, int> iGetSegment(int iSegmentId);
    int iGetSegmentsQuantity();
    int iGetPathLength();
    std::vector<std::tuple<int, int>> vGetPath();
    void vSetPath(CPath *pcPath);
    std::string sToString();

private:
    int i_start_x;
    int i_start_y;
    int i_end_x;
    int i_end_y;

    int i_path_length;
    std::vector<std::tuple<int, int>> v_path;

    int i_get_direction(bool bX, int iCurrent);

    int i_get_random_direction(int iCurrentX, int iCurrentY);

    int i_get_random_step();

    void vMutate(int iMaxX, int iMaxY);

    void vMutate(int iMaxX, int iMaxY, int iMutationPower);
};


#endif //L1_ALGORYTMY_GENETYCZNE_CPATH_H
