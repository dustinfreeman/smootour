//
//  main.cpp
//  smootour-test
//
//  Created by Dustin Freeman on 17-05-14.
//  Copyright (c) 2014 dustinfreeman. All rights reserved.
//

#include <iostream>

#include "../../smootour.h"

#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>

void erode_and_dilate(cv::Mat mat, bool erode = true, bool dilate = true) {
	//apply both operations to the mat

	//http://docs.opencv.org/doc/tutorials/imgproc/erosion_dilatation/erosion_dilatation.html
	
	if (erode) {
		int erosion_type = cv::MORPH_RECT;
		int erosion_size = 3;

		cv::Mat erode_element = cv::getStructuringElement( erosion_type,
										cv::Size( 2*erosion_size + 1, 2*erosion_size+1 ),
										cv::Point( erosion_size, erosion_size ) );
		cv::erode( mat, mat, erode_element );
	}

	if (dilate) {
		int dilation_type = cv::MORPH_RECT;
		int dilation_size = 5;

		cv::Mat dilate_element = cv::getStructuringElement( dilation_type,
										cv::Size( 2*dilation_size + 1, 2*dilation_size+1 ),
										cv::Point( dilation_size, dilation_size ) );
		cv::dilate( mat, mat, dilate_element );
	}
}

cv::Mat get_frame(cv::VideoCapture cap) {
    const int SCALE_DOWN = 2;
    cv::Mat frame;
    cap >> frame;
    cv::Mat scaled_frame(frame.rows/SCALE_DOWN, frame.cols/SCALE_DOWN, CV_8UC4);
    cv::resize(frame, scaled_frame, cv::Size(frame.cols/SCALE_DOWN, frame.rows/SCALE_DOWN), 1.0/SCALE_DOWN, 1.0/SCALE_DOWN);
    
    return scaled_frame;
}

int main(int argc, const char * argv[])
{
    std::cout << "smootour test running...!\n";
    
    //image processing
    cv::VideoCapture cap(0);
    if (!cap.isOpened()) {
        std::cout << "failed to connect to camera \n";
        return -1;
    }
    cv::Mat frame;
    frame = get_frame(cap); //get first frame for sizing.
    std::cout << "frame size: " << frame.cols << "," << frame.rows << "\n";
    
    cv::Scalar match_colour(200,0,0);
    
    cv::Mat thresholded(frame.rows, frame.cols, CV_8UC1);
    
    //window display initialization
    cv::namedWindow("smootour-test", CV_WINDOW_NORMAL);
    cv::Mat windowFrame(frame.rows*2, frame.cols*2, CV_8UC3);
    cv::Rect frameROI(0, 0, frame.cols, frame.rows);
    cv::Mat displayThreshold = windowFrame(cv::Rect(frame.cols, 0, frame.cols, frame.rows));
    
    //initialize with correct row and column size
    //could also initialize with the first binary image.
    Smootour smootour(frame.rows, frame.cols);
    
    bool running = true;
    while(running) {
        //display live webcam view in upper corner of image.
        frame = get_frame(cap);
        frame.copyTo(windowFrame(frameROI));
        //frame.copyTo(windowFrame);
        
        //threshold
        const float RANGE_FACTOR = 0.2;
        cv::Scalar low_match(match_colour[0]*(1-RANGE_FACTOR), match_colour[1]*(1-RANGE_FACTOR), match_colour[2]*(1-RANGE_FACTOR));
        cv::Scalar high_match(match_colour[0]*(1+RANGE_FACTOR), match_colour[1]*(1+RANGE_FACTOR), match_colour[2]*(1+RANGE_FACTOR));
        cv::inRange(frame, low_match, high_match, thresholded);
        
        erode_and_dilate(thresholded);
        thresholded.copyTo(displayThreshold);
        
        
        //display live thresholded image.
        
        
        //plain contours

        
        //smooth contours
        
        
        //display implicit function image, threshold at 0.
        

        
        
        
        
        cv::imshow("smootour-test", windowFrame);
        
        int key = cv::waitKey(30);
        if (key != -1) {
            switch(key) {
                case 27: //ESC
                    running = false;
                    break;
                
                default:
                    std::cout << "key " << key << "\n";
                    break;
            };
        }
    }
    
    return 0;
}

