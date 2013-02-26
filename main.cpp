#include "config.h"
#include <opencv2\core\core.hpp>
#include <opencv2\highgui\highgui.hpp>

using namespace cv;

Point findTriangle(Mat &img);

int main()
{
	Mat src;
	Point cntr;
	VideoCapture cap(0);
	
	while(true)
	{
		cap>>src;
		cntr=findTriangle(src);
		imshow("src",src);
		if (waitKey(30)>=0) break;
	}
	//src=imread("cap.png");
	//cntr=findTriangle(src);
	//	imshow("src",src);
	//waitKey(0);

	return 0;
}
Point findTriangle(Mat &img)
{
	vector<vector<Point>> contours;
	vector<Point> centers;

	Mat gray(img.size(),CV_8UC1);
	cvtColor(img,gray,CV_BGR2GRAY);
	double bright=0;
	double diff=0;
	for (int i=0;i<480;++i)
		for (int j=0;j<640;++j)
		{
			bright+=gray.at<byte>(i,j);
			diff+=gray.at<byte>(i,j)*gray.at<byte>(i,j);
		}
	bright/=307200;
	diff/=307200;
	diff-=bright*bright;
	diff=sqrt(diff);
	printf("bright: %f diff: %f\n",bright,diff);
	threshold(gray,gray,bright,255,THRESH_BINARY);
	imshow("gray",gray);
	findContours(gray,contours,CV_RETR_LIST, CV_CHAIN_APPROX_NONE);
	for (int i=0;i<contours.size();++i)
	{
		double area=contourArea(contours[i]);
		if (area>50 && area<500)
		{
			RotatedRect ellips=fitEllipse(contours[i]);
			double areaDiff=abs(area/(ellips.size.height*ellips.size.width*3.141592/4)-1);
			double axes=abs(ellips.size.width/ellips.size.height-1);
			if (areaDiff<0.1 && axes<0.1)
			{
				ellipse(img,ellips,Scalar(0,0,255));
				centers.push_back(ellips.center);
			}
			//drawContours(img,contours,i,Scalar(255,0,0));
			printf("%d: areaDiff: %f area: %f\n",i,areaDiff,area);
		}
	}
	printf("centers: %d\n",centers.size());
	Point center(0,0);
	for (int i=0;i<centers.size();++i)
	{
		center.x+=centers[i].x;
		center.y+=centers[i].y;
	}
	center.x/=3;
	center.y/=3;
	circle(img,center,5,Scalar(0,0,255));
	return center;
}