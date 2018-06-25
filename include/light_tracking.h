#ifndef __Light_Tracking_H
#define __Light_Tracking_H

#include <opencv2/opencv.hpp>
#include <iostream>
#include <cmath>

using namespace std;
using namespace cv;

inline bool is_leftEdge(Mat src, int x, int y, const uchar threshold);
inline bool is_rightEdge(Mat src, int x, int y, const uchar threshold);
inline bool is_point(Mat src, int x, int y, const uchar threshold);
class __light_tracking {
public:
	__light_tracking();

	void set_InputMat_BGR(Mat in) {
		src = in.clone();
		result = src.clone();
		cvtColor(src, src, COLOR_BGR2GRAY);
		threshold(src,src,220,255, THRESH_BINARY);
		imshow("g",src);
		//GaussianBlur(src, src, Size(3, 3), 0, 0);
		
	}

	Mat  get_Mat_Result() { return result.clone(); }

	vector<Point> get_Edge_L() { return edge_L; }

	vector<Point> get_Edge_R() { return edge_R; }

	Point get_Center() { return center; }

	void  show_Image(const string window_name) { imshow(window_name, result); }

	bool  update();

	bool  update(Mat in);

private:

	Mat src;
	Mat result;
	vector<Point> edge_L, edge_R;
	Point center;


};




#endif	// __Light_Tracking_H
