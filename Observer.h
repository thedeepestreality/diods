#include <opencv2/core/core.hpp>
//#include <opencv2/imgproc/imgproc.hpp>
//#include <opencv2/calib3d/calib3d.hpp>
//#include <opencv2/highgui/highgui.hpp>

class Observer
{
private:

	double x;
	double y;
	double phi;

public:

	Observer(){}
	void FindCoords(cv::Mat &img);
	void SetCoords(double x, double y, double phi);
	double GetX() {return x;}
	double GetY() {return y;}
	double GetPhi() {return phi;}
};