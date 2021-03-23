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

    void update()
    {
        // First step
        tmp_cells_.clear();
        for (const auto &set_x : living_cells_)
            for (int y : set_x.second)
                update_neighbors(set_x.first, y);
    }

private:
    void update_neighbors(int x_ref, int y_ref)
    {
        for (int x : {x_ref - 1, x_ref, x_ref + 1})
            for (int y : {y_ref - 1, y_ref, y_ref + 1})
                if ((x != x_ref || y != y_ref))
                    tmp_cells_[x][y]++;

        tmp_cells_[x_ref][y_ref] += 16;
    }

    std::map<int, std::set<int>> living_cells_;             // Cell at (i,j) exists <=> living_cells_[i][j] exists
    std::map<int, std::map<int, unsigned char>> tmp_cells_; // Coef at [i,j] counts the number of neighbors of the cell [i,j]
                                                            // There's maximum 8 neighbors. If the cell was alive, we add 16
                                                            // to the count, i.e. we set the 4th bit.
};

int main(int argc, char **argv)
{

    return 0;
}
