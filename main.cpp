#include "config.h"
#include <opencv2\core\core.hpp>
#include <opencv2\highgui\highgui.hpp>
#include <sstream>

using namespace cv;

#define pi 3.141593

void findSquare(Mat &img);
vector<vector<Point>> findClusters(Mat &img);
bool checkPair(Point x, vector<Point> equiv);


int main()
{
	Mat src;
	
	//vector<vector<Point>> merged;
	/*
	VideoCapture cap(0);
	while(true)
	{
		cap>>src;
		merged=findClusters(src);
		imshow("src",src);
		if (waitKey(30)>=0) break;
	}*/
	
	VideoCapture cap(0);
	while(true)
	{
		cap>>src;
		findSquare(src);
		imshow("src",src);
		if (waitKey(30)>=0) break;

	}


	return 0;
}

void findSquare(Mat &img)
{
	vector<vector<Point>> contours;
	vector<Vec4i> hierarchy;
	vector<Point> approx;

	Mat gray(img.size(),CV_8UC1);
	cvtColor(img,gray,CV_BGR2GRAY);
	threshold(gray,gray,150,255,THRESH_BINARY);
	imshow("Gray",gray);
	findContours(gray,contours,hierarchy,CV_RETR_TREE,CV_CHAIN_APPROX_SIMPLE);
	for (int i=0;i<contours.size();++i)
	{
		approxPolyDP(contours[i],approx,arcLength(contours[i],true)*0.02,true);
		if (approx.size()==4 && contourArea(approx,0)>100 && isContourConvex(approx))
		{
			if (hierarchy[i][2]>=0)
			{
				vector<Point> child_approx;
				approxPolyDP(contours[hierarchy[i][2]],child_approx,arcLength(contours[hierarchy[i][2]],1)*0.02,1);
				if (child_approx.size()==4 && contourArea(child_approx,0)>100 && isContourConvex(child_approx))
				{
					drawContours(img,contours,i,Scalar(0,255,0),3);
					drawContours(img,contours,hierarchy[i][2],Scalar(0,0,255),3);
				}
			}
		}
	}
}

bool check1dim(vector<int> vect, int elem)
{
	//bool res=false;
	
	for (int i=0;i<vect.size();++i)
		if (vect[i]==elem)
			return true;
	return false;
}

vector<vector<Point>> merge(vector<Point> &equiv,vector<vector<Point>> clusters)
{
	vector<vector<Point>> merged;
	vector<int> curr_equiv;
	vector<int> singles;
	vector<vector<int>> final;

	while(equiv.size()>0)
	{
		curr_equiv.push_back(equiv[0].x);
		for (int i=0;i<curr_equiv.size();++i)
		{
			for (int j=0;j<equiv.size();++j)
			{
				if (equiv[j].x==curr_equiv[i])
				{
					if (!check1dim(curr_equiv,equiv[j].y))
						curr_equiv.push_back(equiv[j].y);
					equiv.erase(equiv.begin()+j);
					j--;
				}

				else if (equiv[j].y==curr_equiv[i])
				{
					if (!check1dim(curr_equiv,equiv[j].x))
						curr_equiv.push_back(equiv[j].x);
					equiv.erase(equiv.begin()+j);
					j--;
				}
				
			}
		}
		final.push_back(curr_equiv);
		curr_equiv.clear();
	}
	for (int i=0;i<clusters.size();++i)
	{
		bool found=false;
		for (int j=0;j<final.size();++j)
		{
			for (int k=0;k<final[j].size();++k)
			{
				if (final[j][k]==i)
				{
					found=true;
					break;
				}
			}
			if (found) break;
		}
		if (!found) singles.push_back(i);
	}
	int count=0;
	for (int i=0;i<final.size();++i)
	{	
		merged.push_back(vector<Point>());
		for (int j=0;j<final[i].size();++j)
		{
			for (int k=0;k<clusters[final[i][j]].size();++k)
				merged[i].push_back(Point(clusters[final[i][j]][k].y,clusters[final[i][j]][k].x));
		}
	}
	for (int i=0;i<singles.size();++i)
	{
		merged.push_back(vector<Point>());
		for (int j=0;j<clusters[singles[i]].size();++j)
			merged[merged.size()-1].push_back(Point(clusters[singles[i]][j].y,clusters[singles[i]][j].x));
	}
	
	return merged;
}

bool checkPair(Point x, vector<Point> equiv)
{
	for (int i=0;i<equiv.size();++i)
		if (equiv[i].x==x.x && equiv[i].y==x.y)
			return false;
	return true;
}

vector<vector<Point>> sieve(vector<vector<Point>> merged)
{
	vector<vector<Point>> ret;
	double a;
	double b;
	for (int i=0;i<merged.size();++i)
	{
		double area=merged[i].size();
		if (area>50 && area<500)
		{
			RotatedRect ell=fitEllipse(merged[i]);
			
			if (ell.size.width>=ell.size.height)
			{
				a=ell.size.width;
				b=ell.size.height;
			}
			else
			{
				b=ell.size.width;
				a=ell.size.height;
			}
			
			if (abs(a/b-1)<0.2)
			{
				ret.push_back(merged[i]);
			}
		}
	}
	return ret;
}

vector<vector<Point>> findClusters(Mat &img)
{
	Mat gray(img.size(),CV_8UC1);
	cvtColor(img,gray,CV_BGR2GRAY);
	threshold(gray,gray,100,255,THRESH_BINARY);

	int num=0;
	vector<vector<Point>> clusters;
	vector<Point> equiv;
	
	vector<Point> tmp;

	short int prev_line[640];
	short int curr_line[640];



	if (gray.at<byte>(0,0)>0)
	{
		num++;
		tmp.push_back(Point(0,0));
		clusters.push_back(tmp);
		tmp.clear();

		curr_line[0]=num-1;
	}
	else
	{
		curr_line[0]=-1;
	}

	
	for (int i=1;i<gray.cols;++i)
	{
		if (gray.at<byte>(0,i)>0)
		{
			if (curr_line[i-1]<0)
			{
				num++;
				tmp.push_back(Point(0,i));
				clusters.push_back(tmp);
				tmp.clear();
				curr_line[i]=num-1;
			}
			else
			{
				clusters[curr_line[i-1]].push_back(Point(0,i));
				curr_line[i]=curr_line[i-1];
			}
		}
		else
		{
			curr_line[i]=-1;
		}
	}
	for (int i=0;i<640;++i)
	{
		prev_line[i]=curr_line[i];
		curr_line[i]=-1;
	}

	try
	{
		for (int i=1;i<gray.rows;++i)
		{
			//First element
			if (gray.at<byte>(i,0)>0)
			{
				if (prev_line[0]>-1)
				{
					curr_line[0]=prev_line[0];
					clusters[curr_line[0]].push_back(Point(i,0));
				}
				else if(prev_line[1]>-1)
				{
					curr_line[0]=prev_line[1];
					clusters[curr_line[0]].push_back(Point(i,0));
				}
				else
				{
					num++;
					tmp.push_back(Point(i,0));
					clusters.push_back(tmp);
					tmp.clear();
					curr_line[0]=num-1;
				}
				
			}
			else
				curr_line[0]=-1;
			
			//Others
			for (int j=1;j<gray.cols;++j)
			{
				
				if (gray.at<byte>(i,j)>0)
				{
					if (j>0 && prev_line[j-1]>-1)
						curr_line[j]=prev_line[j-1];

					if (prev_line[j]>-1)
						curr_line[j]=prev_line[j];

					if (j>0 && curr_line[j-1]>-1)
						curr_line[j]=curr_line[j-1];

					if (j+1<gray.cols && prev_line[j+1]>-1)
					{
						if (curr_line[j]<0)
							curr_line[j]=prev_line[j+1];
						else
						{
							if (curr_line[j]!=prev_line[j+1] && checkPair(Point(curr_line[j],prev_line[j+1]),equiv))
								equiv.push_back(Point(curr_line[j],prev_line[j+1]));
						}
					}

					if (curr_line[j]<0)
					{
						num++;
						tmp.push_back(Point(i,j));
						clusters.push_back(tmp);
						tmp.clear();
						curr_line[j]=num-1;
					}
					else
					{
						clusters[curr_line[j]].push_back(Point(i,j));
					}
				}
				else
					curr_line[j]=-1;
			}
			
		
			//printf("length1: %d, length2: %d\n",sizeof(curr_line),sizeof(prev_line));
			
			for (int k=0;k<640;++k)
			{
				prev_line[k]=curr_line[k];
				curr_line[k]=-1;
			}
		
		}
	}
	catch(Exception e)
	{
		printf("Error: %s\n", e.err);
	}
	
	vector<vector<Point>> merged=merge(equiv,clusters);

	

	return sieve(merged);
}