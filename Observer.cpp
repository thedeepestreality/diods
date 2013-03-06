//#include "Observer.h"
#include <cstdio>
#include <sstream>
#include <cmath>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
//#include <opencv2/calib3d/calib3d.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace std;
using namespace cv;

#define pi 3.141593

class Observer
{
private:

	double x;
	double y;
	double phi;

public:

	void FindCoords(cv::Mat &img);
	void SetCoords(double x, double y, double phi);
	double GetX() {return x;}
	double GetY() {return y;}
	double GetPhi() {return phi;}
};

void Observer::FindCoords(Mat &img)
{
	vector<vector<Point> > contours;
	vector<Vec4i> hierarchy;
	vector<Point> approx;

	double square_side = 0.0; //in pixels (измеренная в ходе работы алгоритма)
	double square_side_cm = 12.2; //сторона квадарата в реале, в сантиметрах, измеренная заранее
	double square_side_max = 0.0; // максимальная сторона квадрата - скорее все искомая не "деформированная" проекцией
	double square_side_min = 0.0; // минимальная сторона - та, которая поернулась
	double distance = 0.0; //перпендикуляр до плоскости, параллельной плоскости изображения, проходящей через центр маячка
	double sides[4] = {0.0, 0.0, 0.0, 0.0}; // стороны квадрата - маячка
	double angle = 0.0; //угол поворота робота вокруг своей оси - фи
	double focal_length = 700.0;
	double from_mayat_center_to_image_center_in_px = 0.0;
	double x_coord = 0.0;
	double x_min = 100000.0, x_max = 0.0;

	double a1=0, a2=0, b1=0, b2=0;
	Point diag_intersection;

	Mat gray(img.size(),CV_8UC1);
	cvtColor(img,gray,CV_BGR2GRAY);
	threshold(gray,gray,150,255,THRESH_BINARY);
	findContours(gray,contours,hierarchy,CV_RETR_TREE,CV_CHAIN_APPROX_SIMPLE);
	for (int i=0;i<contours.size();++i)
	{
		approxPolyDP(contours[i],approx,arcLength(contours[i],true)*0.02,true);
		if (approx.size()==4 && contourArea(approx,0)>100 && isContourConvex(approx))
		{
			if (hierarchy[i][2]>=0)
			{
				//Оцениваем сторону квадрата
				circle(img, approx[0], 6, Scalar(0,0,255),3);
				circle(img, approx[1], 6, Scalar(0,255,0),3);
				circle(img, approx[2], 6, Scalar(255,0,0),3);
				circle(img, approx[3], 6, Scalar(0,0,0),3);
				circle(img, approx[4], 6, Scalar(0,100,20),3); // я думал все четыре точки в контуре, ан нет.
				//красный - зеленый = сторона
				square_side = sqrt(pow(approx[0].x-approx[1].x,2)+pow(approx[0].y-approx[1].y,2));
				distance = (focal_length*square_side_cm)/square_side;
				printf("distance is %f\n", distance);
				for (int ii=0; ii<4; ii++){
					if(approx[ii].x > x_max){
						x_max = approx[ii].x;
					}
					if(approx[ii].x < x_min){
						x_min = approx[ii].x;
					}
				}
				square_side_min = x_max - x_min;

				//наибольшая сторона "квадрата"
				for (int ii=0, max=0, min=100000; ii<4; ii++){
					if (ii!=3){
						sides[ii] = sqrt(pow(approx[ii].x-approx[ii+1].x,2)+pow(approx[ii].y-approx[ii+1].y,2));
					} else {
						sides[ii] = sqrt(pow(approx[ii].x-approx[0].x,2)+pow(approx[ii].y-approx[0].y,2));
					}
					if (sides[ii]>max){
						max = sides[ii];
					}
					square_side_max = max;
				}

				angle = acos(square_side_min/square_side_max) * 180 / pi;
				

				//нахождение центра маячка: это точка пересечения диагоналей
				//находим сначала уравнения прямых: коэффициенты a,b (ax+b=y)

				//потом находим точку пересечения (x,y) a1*x+b1=a2*x+b2
				diag_intersection.x = (approx[0].x+approx[1].x+approx[2].x+approx[3].x)/4;
				diag_intersection.y = (approx[0].y+approx[1].y+approx[2].y+approx[3].y)/4;
				//считаем расстояние в пикселях от центра изображения до точки пересечения
				from_mayat_center_to_image_center_in_px = sqrt(pow(img.cols/2-diag_intersection.x,2)+pow(img.rows/2-diag_intersection.y,2));

				x_coord = (distance * from_mayat_center_to_image_center_in_px) / focal_length;
				line(img, diag_intersection, Point(img.cols/2, img.rows/2), Scalar(255,0,0), 2);

				SetCoords(x_coord, distance, angle);
				printf("mat.cols(x): %d, Mat.rows(y): %d\n", img.cols, img.rows);
				printf("y(distance): %f, x: %f, angle: %f || from_mayat_to_center: %f\n", distance, x_coord, angle, from_mayat_center_to_image_center_in_px);

				vector<Point> child_approx;
				approxPolyDP(contours[hierarchy[i][2]],child_approx,arcLength(contours[hierarchy[i][2]],1)*0.02,1);
				if (child_approx.size()==4 && contourArea(child_approx,0)>100 && isContourConvex(child_approx))
				{
					drawContours(img,contours,i,Scalar(0,255,0),3);
					drawContours(img,contours,hierarchy[i][2],Scalar(0,0,255),3);
				}
			} else {


			}
		}
	}
}

void Observer::SetCoords(double iks, double igrek, double fi)
{
	x = iks;
	y = igrek;
	phi = fi;
}