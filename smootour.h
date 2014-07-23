//
//  smootour.h
//  smootour-test
//
//  Created by Dustin Freeman on 17-05-14.
//  Copyright (c) 2014 dustinfreeman. All rights reserved.
//

#ifndef smootour_test_smootour_h
#define smootour_test_smootour_h

#include <vector>
#include <opencv2/opencv.hpp>

#define SMOO_FADE_RATE 0.8

class Smootour {
protected:
    float fade_rate;

    cv::Mat implicit_image;
    //from which we get the implicit surface
    int image_count;
    
public:
	void init(int rows, int cols, float _fade_rate);

    Smootour(int rows, int cols, float _fade_rate);
    
    void update(cv::Mat thresholded_image);
    
    std::vector<std::vector<cv::Point> > get_contours();
    
    cv::Mat get_implicit_image();
};

#endif

void Smootour::init(int rows, int cols,
	float _fade_rate = SMOO_FADE_RATE) {
	implicit_image = cv::Mat::zeros(rows, cols, CV_32FC1);
	image_count = 0;
}

Smootour::Smootour(int rows = 0, int cols = 0,
    float _fade_rate = SMOO_FADE_RATE) {
	init(rows, cols, _fade_rate);
}

void Smootour::update(cv::Mat thresholded_image) {
    //We expect our thresholded image to have values of either 0 or 1.

    cv::Mat local_thresholded;
    cv::threshold(thresholded_image, local_thresholded, 0.5f, 1, cv::THRESH_BINARY);
    cv::Mat local_thresholded_f;
    local_thresholded.convertTo(local_thresholded_f, CV_32FC1);
    
    //areas of 0 in update images are faded over time
    implicit_image *= fade_rate;
    
    //using max instead of a blend so that areas the contour
    // does not respond sluggishly to movement.
    cv::max(implicit_image, local_thresholded_f, implicit_image);
    
    image_count++;
}

std::vector<std::vector<cv::Point> > Smootour::get_contours() {
    //do thresholding on implicit_image,
    // return the contour of 0.5
    
    cv::Mat thresholded_implicit_image_f;
    cv::threshold(implicit_image, thresholded_implicit_image_f, 0.5f, 1, cv::THRESH_BINARY);
    
    cv::Mat thresholded_implicit_image;
    thresholded_implicit_image_f.convertTo(thresholded_implicit_image, CV_8UC1);
    
    std::vector<std::vector<cv::Point> > smooth_contours;
    cv::findContours(thresholded_implicit_image, smooth_contours, CV_RETR_TREE, CV_CHAIN_APPROX_NONE );
    
    return smooth_contours;
}

cv::Mat Smootour::get_implicit_image() {
    return implicit_image;
}


