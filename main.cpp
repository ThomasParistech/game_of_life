/*********************************************************************************************************************
 * File : main.cpp                                                                                                   *
 *                                                                                                                   *
 * Game of Life                                                                                                      *
 *                                                                                                                   *
 * 2021 Thomas Rouch                                                                                                 *
 *********************************************************************************************************************/

#include <map>
#include <set>
#include <vector>
class CellsGrid
{
public:

    void add_living_cell(int i, int j)
    {
        living_cells_[i].insert(j);
    }

    void clear()
    {
        living_cells_.clear();
    }


private:
    std::map<int, std::set<int>> living_cells_;             // Cell at (i,j) exists <=> living_cells_[i][j] exists
};

int main(int argc, char **argv)
{

    return 0;
}
