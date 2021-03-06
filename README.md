smootour
========

A temporally-smoothed contour class for OpenCV, with an approach similar to implicit surfaces.

<a href="http://www.youtube.com/watch?feature=player_embedded&v=RKrylKFUceY
" target="_blank"><img src="http://img.youtube.com/vi/RKrylKFUceY/0.jpg" 
alt="Smootour on YouTube!" width="480" height="360" border="10" /></a>

Inspired by [my question on Stack Overflow] (http://stackoverflow.com/questions/23525856/simplifying-a-contour-to-a-fixed-length-to-smooth-over-several-frames), where [one poster](http://stackoverflow.com/a/23603696/2518451) observed that temporally-averaging points around a contour was not a feasible approach. This should be a better, by avoiding defining specific points between frames.

How to use smootour:

    Smootour smootour(img_height, img_width);
    
    //in loop
      //thresholded_image is a binary image
      
      smootour.update(thresholded_image);
      std::vector<std::vector<cv::Point> >smooth_contours = smootour.get_contours();
  
    
  
