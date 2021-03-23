/*********************************************************************************************************************
 * File : main.cpp                                                                                                   *
 *                                                                                                                   *
 * Game of Life                                                                                                      *
 *                                                                                                                   *
 * 2021 Thomas Rouch                                                                                                 *
 *********************************************************************************************************************/

#include <iostream>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <time.h>
#include "cells_grid.h"

int main(int argc, char **argv)
{
    // Init living cells
    srand(time(nullptr));
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

    const int output_width = 600;
    const int output_heigth = 450;
    cv::VideoWriter video_writer("/tmp/game_of_life.mp4", cv::VideoWriter::fourcc('M', 'J', 'P', 'G'), 30,
                                 cv::Size(output_width, output_heigth));

    cv::Mat img;
    bool keep_updating = true;
    int k = 0;
    while (keep_updating)
    {
        std::cout << "Update " << k << std::endl;
        grid.generate_image(img, output_width, output_heigth);
        cv::putText(img, std::to_string(k), cv::Point(5, 30), cv::FONT_HERSHEY_SIMPLEX, 1,
                    cv::Vec3b(0, 0, 255), 2, cv::LINE_AA);

        video_writer.write(img);
        cv::imshow("", img);
        cv::waitKey(1);
        keep_updating = grid.update();
        k++;
    }

    return 0;
}
