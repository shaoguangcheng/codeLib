#ifndef CV_GRID_H
#define CV_GRID_H

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

#include <stdexcept>

namespace csg {
    class grid
    {
    public:
        grid();
        grid(cv::Mat &src,const int rows_,const int cols_,cv::Scalar rectColor_ = cv::Scalar(0,0,0),
             cv::Scalar lineColor_ = cv::Scalar(255,255,255));

        ~grid(){delete [] color;}

        void init(const cv::Mat &src,const int rows_,const int cols_,
                  cv::Scalar rectColor_ = cv::Scalar(0,0,0),
                   cv::Scalar lineColor_ = cv::Scalar(255,255,255));

        void drawGrid();
        void setRectColor(const cv::Scalar rectColor_);
        void setLineColor(const cv::Scalar lineColor_);
        void fillRect(const cv::Point &rectCoord);
        cv::Scalar getRectColor(const cv::Point &rectCoord){return color[(rectCoord.x-1)*cols+rectCoord.y];}

        inline int getCols(){return cols;}
        inline int getrows(){return rows;}
        inline void showGrid(){cv::imshow("grid",gridImage);cv::waitKey(50);}
        inline void saveGrid(const std::string &fileName){cv::imwrite(fileName,gridImage);}

    private:
        int rows;
        int cols;

        int gridWidth;
        int gridHeight;

        cv::Mat gridImage;

        cv::Scalar rectColor;
        cv::Scalar lineColor;

        cv::Scalar *color;
    };

    void floodFill2(grid &image,cv::Point seedPoint,cv::Scalar oldColor,cv::Scalar newColor);
    void floodFill3(grid &image,cv::Point seedPoint,cv::Scalar oldColor,cv::Scalar newColor);

}
#endif // CV_GRID_H
