#include <opencv2/opencv.hpp>

#ifdef _MSC_VER
# if CV_MAJOR_VERSION == 2 && CV_MINOR_VERSION == 4 && CV_SUBMINOR_VERSION == 2
// OpenCV 2.3.1
#  if defined(_DEBUG)
#  pragma comment(lib, "opencv_core242d.lib")
#  pragma comment(lib, "opencv_highgui242d.lib")
#  pragma comment(lib, "opencv_imgproc242d.lib")
#  pragma comment(lib, "opencv_video242d.lib")
#  pragma comment(lib, "opencv_ml242d.lib")

#  pragma comment(lib, "opencv_calib3d242d.lib")
#  pragma comment(lib, "opencv_objdetect242d.lib")
#  pragma comment(lib, "opencv_features2d242d.lib")
#  pragma comment(lib, "opencv_contrib242d.lib")
#  pragma comment(lib, "opencv_ts242d.lib")
#  pragma comment(lib, "opencv_legacy242d.lib")
#  pragma comment(lib, "opencv_flann242d.lib")
#  pragma comment(lib, "opencv_gpu242d.lib")
# else
#  pragma comment(lib, "opencv_core242.lib")
#  pragma comment(lib, "opencv_highgui242.lib")
#  pragma comment(lib, "opencv_imgproc242.lib")
#  pragma comment(lib, "opencv_video242.lib")
#  pragma comment(lib, "opencv_ml242.lib")

#  pragma comment(lib, "opencv_calib3d242.lib")
#  pragma comment(lib, "opencv_objdetect242.lib")
#  pragma comment(lib, "opencv_features2d242.lib")
#  pragma comment(lib, "opencv_contrib242.lib")
#  pragma comment(lib, "opencv_ts242.lib")
#  pragma comment(lib, "opencv_legacy242.lib")
#  pragma comment(lib, "opencv_flann242.lib")
#  pragma comment(lib, "opencv_gpu242.lib")
# endif //#  if defined(_DEBUG)

# endif //# if CV_MAJOR_VERSION == 2 && CV_MINOR_VERSION == 3
#endif //#ifdef _MSC_VER