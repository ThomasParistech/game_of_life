/*********************************************************************************************************************
 * File : cells_grid.cpp                                                                                             *
 *                                                                                                                   *
 * Game of Life                                                                                                      *
 *                                                                                                                   *
 * 2021 Thomas Rouch                                                                                                 *
 *********************************************************************************************************************/

#include <opencv2/imgproc.hpp>
#include "cells_grid.h"

CellsGrid::CellsGrid(int x_min, int x_max, int y_min, int y_max) : x_min_(x_min),
                                                                   x_max_(x_max),
                                                                   y_min_(y_min),
                                                                   y_max_(y_max)
{
    cells_img_.create(y_max_ - y_min_, x_max_ - x_min_, CV_8UC3);
}

void CellsGrid::add_living_cell(int i, int j)
{
    living_cells_[i].insert(j);
}

void CellsGrid::clear()
{
    living_cells_.clear();
}

void CellsGrid::update()
{
    // First step
    tmp_cells_.clear();
    for (const auto &set_x : living_cells_)
        for (int y : set_x.second)
            update_neighbors(set_x.first, y);

    // Second step
    living_cells_.clear();
    for (const auto &set_x : tmp_cells_)
        for (auto y_count : set_x.second)
            if (y_count.second == 3 || y_count.second == 16 + 2 || y_count.second == 16 + 3)
                if (x_min_ <= set_x.first && set_x.first < x_max_ && y_min_ <= y_count.first && y_count.first < y_max_)
                    living_cells_[set_x.first].insert(y_count.first);
}

void CellsGrid::generate_image(cv::Mat &output_img, int output_width, int output_height)
{
    cells_img_.setTo(cv::Vec3b::all(255)); // White background
    for (const auto &set_x : living_cells_)
        for (int y : set_x.second)
            cells_img_.at<cv::Vec3b>(y, set_x.first) = cv::Vec3b::all(0); // Black cell

    cv::resize(cells_img_, output_img, cv::Size(output_width, output_height), 0, 0, cv::INTER_NEAREST);
}

void CellsGrid::update_neighbors(int x_ref, int y_ref)
{
    for (int x : {x_ref - 1, x_ref, x_ref + 1})
        for (int y : {y_ref - 1, y_ref, y_ref + 1})
            if ((x != x_ref || y != y_ref))
                tmp_cells_[x][y]++;

    tmp_cells_[x_ref][y_ref] += 16;
}
