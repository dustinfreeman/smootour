smootour
========

A temporally-smoothed contour class for OpenCV, with an approach based on implicit surfaces.

YT("RKrylKFUceY", print = TRUE)

This work inspired by my question on Stack Overflow:

http://stackoverflow.com/questions/23525856/simplifying-a-contour-to-a-fixed-length-to-smooth-over-several-frames

Where [one poster](http://stackoverflow.com/a/23603696/2518451) observed that temporally-averaging points around a contour was not a useful approach. This should be a better one.

How to use smootour:

    //initial setup
    cv::Mat frame;
    frame = get_frame(cap); //get first frame for sizing.
    Smootour smootour(frame.rows, frame.cols);
    
    //in loop
      //assume frame is updated
      //create binary cv::Mat threshold from frame
      
      smootour.update(threshold);
      
      std::vector<std::vector<cv::Point> > smooth_contours;
      smooth_contours = smootour.get_contours();
  
    
  
