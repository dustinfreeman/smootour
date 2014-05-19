smootour
========

A temporally-smoothed contour class for OpenCV, with an approach based on implicit surfaces.

<a href="http://www.youtube.com/watch?feature=player_embedded&v=RKrylKFUceY
" target="_blank"><img src="http://img.youtube.com/vi/RKrylKFUceY/0.jpg" 
alt="Smootour on YouTube!" width="480" height="360" border="10" /></a>

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
  
    
  
