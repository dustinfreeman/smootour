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

#define SMOO_DEFAULT_SMOOTH_AMOUNT 0.6

class Smootour {
protected:
    float smooth_amount;

    cv::Mat implicit_image;
    //from which we get the implicit surface
    int image_count;
    
public:
    Smootour(int rows, int cols, int _smooth_amount);
    
    void update(cv::Mat thresholded_image);
    
    std::vector<std::vector<cv::Point> > get_contours();
    
    cv::Mat get_implicit_image();
};

#endif

Smootour::Smootour(int rows, int cols,
    int _smooth_amount = SMOO_DEFAULT_SMOOTH_AMOUNT)
    : smooth_amount(_smooth_amount) {
    
    implicit_image = cv::Mat::zeros(rows, cols, CV_8UC1);
    image_count = 0;
}

void Smootour::update(cv::Mat thresholded_image) {
    //smoothly add the thresholded_image to our implicit image

    //ensure our thresholded image is 0 or 1.
    cv::Mat local_thresholded;
    cv::threshold(thresholded_image, local_thresholded, 0.5f, 1, cv::THRESH_BINARY);
    
    if (image_count == 0) {
        implicit_image = local_thresholded.clone();
    } else {
        //merge
        //TODO need better than cv::addWeighted
        //for each pixel: new & smoothed value
        //if new == 0 && smoothed == 0 -> 0
        //if new == 1 && smoothed == 1 -> 1
        //if new == 1 && smoothed == 0 -> smooth_amount
        //if new == 0 && smoothed == x -> x*(1-smooth_amount)
        //Problem: if smooth_amount is small,
        // values in implicit_image never get over our 0.5f threshold
        
        cv::addWeighted(implicit_image, (1 - smooth_amount), local_thresholded, smooth_amount, 0, implicit_image);
    }
    
    image_count++;
}

std::vector<std::vector<cv::Point> > Smootour::get_contours() {
    //do thresholding on implicit_image, return contours on either
    //side of 0.5
    
    cv::Mat thresholded_implicit_image;
    cv::threshold(implicit_image, thresholded_implicit_image, 0.5f, 1, cv::THRESH_BINARY);
    
    std::vector<std::vector<cv::Point> > smooth_contours;
    cv::findContours(thresholded_implicit_image, smooth_contours, CV_RETR_TREE, CV_CHAIN_APPROX_NONE );
    
    return smooth_contours;
}

cv::Mat Smootour::get_implicit_image() {
    return implicit_image;
}


