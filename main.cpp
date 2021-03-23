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
#include <iostream>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

class CellsGrid
{
public:
    CellsGrid(int x_min, int x_max, int y_min, int y_max) : x_min_(x_min),
                                                            x_max_(x_max),
                                                            y_min_(y_min),
                                                            y_max_(y_max)
    {
        cells_img_.create(y_max_ - y_min_, x_max_ - x_min_, CV_8UC3);
    }

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

        // Second step
        living_cells_.clear();
        for (const auto &set_x : tmp_cells_)
            for (auto y_count : set_x.second)
                if (y_count.second == 3 || y_count.second == 16 + 2 || y_count.second == 16 + 3)
                    if (x_min_ <= set_x.first && set_x.first < x_max_ && y_min_ <= y_count.first && y_count.first < y_max_)
                        living_cells_[set_x.first].insert(y_count.first);
    }

    void generate_image(cv::Mat &output_img, int output_width, int output_height)
    {
        cells_img_.setTo(cv::Vec3b::all(255)); // White background
        for (const auto &set_x : living_cells_)
            for (int y : set_x.second)
                cells_img_.at<cv::Vec3b>(y, set_x.first) = cv::Vec3b::all(0); // Black cell

        cv::resize(cells_img_, output_img, cv::Size(output_width, output_height), 0, 0, cv::INTER_NEAREST);
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

    cv::Mat cells_img_;
    const int x_min_, x_max_;
    const int y_min_, y_max_;

    std::map<int, std::set<int>> living_cells_;             // Cell at (i,j) exists <=> living_cells_[i][j] exists
    std::map<int, std::map<int, unsigned char>> tmp_cells_; // Coef at [i,j] counts the number of neighbors of the cell [i,j]
                                                            // There's maximum 8 neighbors. If the cell was alive, we add 16
                                                            // to the count, i.e. we set the 4th bit.
};

int main(int argc, char **argv)
{
    // Init living cells
    int x_min = 0;
    int x_max = 100;
    int y_min = 0;
    int y_max = 75;
    CellsGrid grid(x_min, x_max, y_min, y_max);
    double proba = 0.4;
    for (int i = x_min; i < x_max; i++)
        for (int j = y_min; j < y_max; j++)
            if ((static_cast<float>(rand()) / static_cast<float>(RAND_MAX)) < proba)
                grid.add_living_cell(i, j);


    cv::Mat img;
    for (int k = 0; k < 900; k++)
    {
        std::cout << "Update " << k << std::endl;
        grid.generate_image(img, output_width, output_heigth);
        cv::putText(img, std::to_string(k), cv::Point(5, 30), cv::FONT_HERSHEY_SIMPLEX, 1,
                    cv::Vec3b(0, 0, 255), 2, cv::LINE_AA);

        cv::imshow("", img);
        cv::waitKey(0);
        grid.update();
    }

    return 0;
}
