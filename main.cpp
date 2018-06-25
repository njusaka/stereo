
#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <iostream>
#include <opencv2/calib3d/calib3d.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include "include/light_tracking.h"
#include <stdlib.h>
using namespace cv;
using namespace std;
Mat M1, M2, D1, D2, T, R;

Point center_l;
Point center_r;
int plus_x1_x2, sub_x1_x2;
int pic_info[4];
bool left_mouse = false;

Rect roi1, roi2;
int numberOfDisparities = 0, SADWindowSize = 0;
int main()
{
 
	VideoCapture cap(0);
	cap.set(CV_CAP_PROP_FRAME_WIDTH, 1080 );

	cap.set(CV_CAP_PROP_FRAME_HEIGHT, 480 );


	if (!cap.isOpened())
	{
		cout << "error happened while open cam 2" << endl;
		return -1;
	}
	double fps;
    	char string[10]; 

    	double t = 0;


	__light_tracking lt;
	__light_tracking rt;



	while (1)
	{
		t = (double)cv::getTickCount();

		Mat imgy, imgl, imgr, imgLr, imgRr;
		cap >> imgy;


		imgr = imgy(Rect(0, 0, int(imgy.cols/2), imgy.rows));
		imgl = imgy(Rect(int(imgy.cols / 2), 0, int(imgy.cols - imgy.cols / 2), imgy.rows));//????????col
 		t = ((double)cv::getTickCount() - t) / cv::getTickFrequency();
	        fps = 1.0 / t;

        	sprintf(string, "%.2f", fps);      // ????????
            	std::string fpsString("FPS:");
            	fpsString += string;                    
		 putText(imgy,                  // ????
                    fpsString,                  // string?????
                    cv::Point(5, 20),           // ????,???????
                    cv::FONT_HERSHEY_SIMPLEX,   // ????
                    0.5,                    // ????
                    cv::Scalar(0, 0, 0));           // ????
													  //imshow("left", imgl);
															  //imshow("right", imgr);

		lt.set_InputMat_BGR(imgl);
		lt.update();
		lt.show_Image("tracking_l");

		center_l = lt.get_Center();

		rt.set_InputMat_BGR(imgr);
		rt.update();
		rt.show_Image("tracking_r");

		center_r = rt.get_Center();
		plus_x1_x2 = center_l.x + center_r.x;
		sub_x1_x2  = center_l.x - center_r.x;
	

		cout << 1.802*pow(10, 4) * pow(sub_x1_x2, -1.92) + 11.6 << endl;



		waitKey(1);
	}
	return 0;
}

