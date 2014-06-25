#include "cv_grid.h"
#include <deque>

using namespace csg;
////////////////////////////////////////////////////////////////////////////////
/// \brief grid::grid
///////////////////////////////////////////////////////////////////////////////
grid::grid()
{}

grid::grid(cv::Mat &src, const int rows_, const int cols_, cv::Scalar rectColor_,cv::Scalar lineColor_)
    :rows(rows_),cols(cols_),rectColor(rectColor_),lineColor(lineColor_)
{
    src.copyTo(gridImage);

    gridWidth = src.cols/cols;
    gridHeight = src.rows/rows;

    color = new cv::Scalar[cols*rows+1];
}

void grid::init(const cv::Mat &src, const int rows_, const int cols_, cv::Scalar rectColor_,cv::Scalar lineColor_)
{
    src.copyTo(gridImage);

    rows = rows_;
    cols = cols_;
    rectColor = rectColor_;
    lineColor = lineColor_;

    gridWidth = src.cols/cols;
    gridHeight = src.rows/rows;

    color = new cv::Scalar[cols*rows+1];
}

void grid::setRectColor(const cv::Scalar rectColor_)
{
    if(rectColor != rectColor_)
        rectColor = rectColor_;
}

void grid::setLineColor(const cv::Scalar lineColor_)
{
    if(lineColor != lineColor_)
        lineColor= lineColor_;
}

void grid::drawGrid()
{
    for(int i=1;i<cols;i++){
        cv::line(gridImage,cv::Point(i*gridWidth,0),
                 cv::Point(i*gridWidth,gridImage.rows),
                 lineColor);
    }

    for(int i=0;i<rows;i++){
        cv::line(gridImage,cv::Point(0,i*gridHeight),
                 cv::Point(gridImage.cols,i*gridHeight),
                 lineColor);
    }
}

void grid::fillRect(const cv::Point &rectCoord)
{
    if(rectCoord.x <= 0||rectCoord.x > cols||rectCoord.y > rows||rectCoord.y <= 0)
        throw std::range_error("rect coordinate out of range\n");

    cv::Rect rect = cv::Rect((rectCoord.x-1)*gridWidth+1,(rectCoord.y-1)*gridHeight+1,
                             gridWidth-1,gridHeight-1);
    cv::rectangle(gridImage,rect,rectColor,CV_FILLED);

    color[(rectCoord.x-1)*cols+rectCoord.y] = rectColor;
}

void csg::floodFill2(grid &image,cv::Point seedPoint,cv::Scalar oldColor,cv::Scalar newColor)
{
    if(image.getRectColor(seedPoint) != oldColor||image.getRectColor(seedPoint) == newColor
            ||seedPoint.x <= 0||seedPoint.x > image.getCols()
            ||seedPoint.y <= 0||seedPoint.y > image.getrows())
        return;

    image.setRectColor(newColor);
    image.fillRect(seedPoint);

    image.showGrid();

    csg::floodFill2(image,cv::Point(seedPoint.x-1,seedPoint.y),oldColor,newColor);
    csg::floodFill2(image,cv::Point(seedPoint.x+1,seedPoint.y),oldColor,newColor);
    csg::floodFill2(image,cv::Point(seedPoint.x,seedPoint.y-1),oldColor,newColor);
    csg::floodFill2(image,cv::Point(seedPoint.x,seedPoint.y+1),oldColor,newColor);
}

void csg::floodFill3(grid &image,cv::Point seedPoint,cv::Scalar oldColor,cv::Scalar newColor)
{
    if(image.getRectColor(seedPoint) != oldColor||image.getRectColor(seedPoint) == newColor
            ||seedPoint.x <= 0||seedPoint.x > image.getCols()
            ||seedPoint.y <= 0||seedPoint.y > image.getrows())
        return;

    std::deque<cv::Point> seedPoints;
    seedPoints.clear();
    seedPoints.push_back(seedPoint);

    image.setRectColor(newColor);

    std::deque<cv::Point>::iterator iter;

    for(iter = seedPoints.begin();iter != seedPoints.end();iter++){
        image.fillRect(*iter);

        if(iter->x > 1)
            if(image.getRectColor(cv::Point((*iter).x-1,(*iter).y)) == oldColor){
                image.fillRect(cv::Point((*iter).x-1,(*iter).y));
                seedPoints.push_back(cv::Point((*iter).x-1,(*iter).y));
                seedPoints.end()++;
            }

        if(iter->x < image.getCols())
            if(image.getRectColor(cv::Point((*iter).x+1,(*iter).y)) == oldColor){
                image.fillRect(cv::Point((*iter).x+1,(*iter).y));
                seedPoints.push_back(cv::Point((*iter).x+1,(*iter).y));
                seedPoints.end()++;
            }

        if(iter->y > 1)
            if(image.getRectColor(cv::Point((*iter).x,(*iter).y-1)) == oldColor){
                image.fillRect(cv::Point((*iter).x,(*iter).y-1));
                seedPoints.push_back(cv::Point((*iter).x,(*iter).y-1));
                seedPoints.end()++;
            }

        if(iter->y < image.getrows())
            if(image.getRectColor(cv::Point((*iter).x,(*iter).y+1)) == oldColor){
                image.fillRect(cv::Point((*iter).x,(*iter).y+1));
                seedPoints.push_back(cv::Point((*iter).x,(*iter).y+1));
                seedPoints.end()++;
            }

        image.showGrid();
    }
    return;
}

