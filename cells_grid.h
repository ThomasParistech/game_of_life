/*********************************************************************************************************************
 * File : cells_grid.h                                                                                               *
 *                                                                                                                   *
 * Game of Life                                                                                                      *
 *                                                                                                                   *
 * 2021 Thomas Rouch                                                                                                 *
 *********************************************************************************************************************/

#ifndef CELLS_GRID_H
#define CELLS_GRID_H

#include <map>
#include <set>
#include <opencv2/core/mat.hpp>

class CellsGrid
{
public:
    CellsGrid(int x_min, int x_max, int y_min, int y_max);

    void add_living_cell(int i, int j);

    void clear();

    bool update();

    void generate_image(cv::Mat &output_img, int output_width, int output_height);

private:
    void update_neighbors(int x_ref, int y_ref);

    cv::Mat cells_img_;
    const int x_min_, x_max_;
    const int y_min_, y_max_;

    int num_living_cells_;
    std::map<int, std::set<int>> living_cells_;             // Cell at (i,j) exists <=> living_cells_[i][j] exists
    std::map<int, std::map<int, unsigned char>> tmp_cells_; // Coef at [i,j] counts the number of neighbors of the cell [i,j]
                                                            // There's maximum 8 neighbors. If the cell was alive, we add 16
                                                            // to the count, i.e. we set the 4th bit.
};

#endif // CELLS_GRID_H