#include "include/light_tracking.h"

__light_tracking::__light_tracking() {
	
	src.release();
	result.release();
	edge_L.clear();
	edge_R.clear();
	center.x = center.y = 0;
}

bool __light_tracking::update() {

	//result = src.clone();
	//Canny(src, src, 3, 9, 3);      //findContours();??????????

	const int near_threshold = 10;
	const int gray_threshold = 230;
	
	int x, y;
	int i;
	bool flag_find = false;

	vector<Point> center_arr;
	
	edge_L.clear();
	edge_R.clear();
	for (y = 5; y < src.rows - 5; y += 2) {
		bool is_left_edge_found = false;

		for (x = 5; x < src.cols - 5; x++) 	{
			if (is_leftEdge(src, x, y, gray_threshold)) {
				is_left_edge_found = true;
				edge_L.push_back(Point(x, y));  //??????,
			}
			if (is_rightEdge(src, x, y, gray_threshold) && is_left_edge_found) {
				flag_find = true;
				edge_R.push_back(Point(x, y));
				if (flag_find) 
					break;
			}
		}
		if (flag_find == 1)
			break;
	}

	if (flag_find) {
		
		i = 0;									// i?????????????vector??
		center_arr.push_back(Point((edge_L[0].x + edge_R[0].x) / 2, y));		
												// ???????

		for (; y < src.rows - 5; y++) {
			bool is_find_l = false;				// ????????
			bool is_find_r = false;				// ????????
			// ???
			for (x = edge_L[i].x - near_threshold; x < edge_L[i].x + near_threshold; x++) {
				if (is_leftEdge(src, x, y, gray_threshold)) {
					edge_L.push_back(Point(x, y));
					is_find_l = true;
					//break;
				}
			}

			//  ???
			for (x = edge_R[i].x - near_threshold; x < edge_R[i].x + near_threshold; x++) {
				if (is_rightEdge(src, x, y, gray_threshold)) {
					edge_R.push_back(Point(x, y));
					is_find_r = true;
					//break;
				}
			}

			// ??????????,????
			if (is_find_l && is_find_r) {
				center_arr.push_back(Point((edge_L[i].x + edge_R[i].x) / 2, y));
				i++;									// ?????
			}
		}

		// ????
		int x_avg = 0;
		int y_avg = 0;
		for (int j = 0; j < center_arr.size(); j++) {
			x_avg += center_arr[j].x;
			y_avg += center_arr[j].y;
		}
		x_avg /= center_arr.size();
		y_avg /= center_arr.size();
		center.x = x_avg;
		center.y = y_avg;
		cout << "x:" << center.x << "y:" << center.y << endl;
		// ??
		for (int j = 0; j < i; j++) {
			circle(result, edge_L[j], 1, Scalar(0, 128, 255), 2);
			circle(result, edge_R[j], 1, Scalar(255, 128, 0), 2);
		}
		circle(result, center, 1, Scalar(255, 255, 0), 2);
	}
	else {
		for (y = 5; y < src.rows - 1; y ++) {

			for (x = 5; x < src.cols - 1; x++) {
				if (is_point(src, x, y, 250)) {
					center.x = x;
					center.y = y;
				}
				
			}
		
		}
		cout << "x:" << center.x << "y:" << center.y << endl;
		circle(result, center, 1, Scalar(255, 255, 0), 2);

	}

	return flag_find;
}

bool __light_tracking::update(Mat in) {

	set_InputMat_BGR(in);
	return update();
}

// ???????
inline bool is_leftEdge(Mat src, int x, int y, const uchar threshold) {
	
	if (x < 5 || x > src.cols - 5)
		return false;

	// ??7??
	if (/*src.at<uchar>(y, x - 3) <= threshold &&*/ src.at<uchar>(y, x - 2) <= threshold && src.at<uchar>(y, x - 1) <= threshold &&
		src.at<uchar>(y, x) > threshold &&
		src.at<uchar>(y, x + 1) > threshold && src.at<uchar>(y, x + 2) > threshold /*&& src.at<uchar>(y, x + 3) > threshold*/)
		return true;
	else
		return false;
}

inline bool is_rightEdge(Mat src, int x, int y, const uchar threshold) {

	if (x < 5 || x > src.cols - 5)
		return false;

	// ??7??
	if (/*src.at<uchar>(y, x - 3) > threshold &&*/ src.at<uchar>(y, x - 2) > threshold && src.at<uchar>(y, x - 1) > threshold &&
		src.at<uchar>(y, x) > threshold &&
		src.at<uchar>(y, x + 1) <= threshold && src.at<uchar>(y, x + 2) <= threshold /*&& src.at<uchar>(y, x + 3) <= threshold*/)
		return true;
	else
		return false;
}

inline bool is_point(Mat src, int x, int y, const uchar threshold) {

	if (x < 5 || x > src.cols - 5)
		return false;

	if (src.at<uchar>(y, x) == threshold )
		return true;
	else
		return false;
}
