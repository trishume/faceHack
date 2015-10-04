#include <opencv2/objdetect/objdetect.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include <dlib/opencv.h>
#include <dlib/image_processing/frontal_face_detector.h>
#include <dlib/image_processing/render_face_detections.h>
#include <dlib/image_processing.h>
#include <dlib/gui_widgets.h>

#include <iostream>
#include <queue>
#include <stdio.h>
#include <math.h>

#include "constants.h"

using namespace std;

/** Function Headers */
void detectAndDisplay( cv::Mat frame );
void dlibDetect( cv::Mat frame, dlib::frontal_face_detector &detector, dlib::shape_predictor &pose_model);

/** Global variables */
//-- Note, either copy these two files from opencv/data/haarscascades to your current folder, or change these locations
cv::String face_cascade_name = "../res/haarcascade_frontalface_alt.xml";
cv::CascadeClassifier face_cascade;
std::string main_window_name = "Capture - Face detection";
cv::Mat debugImage;

/**
 * @function main
 */
int main( int argc, const char** argv ) {
//  assert(argc > 1);
  cv::VideoCapture cap("/Users/tristan/misc/rick.mp4");
  // cv::VideoCapture cap(-1);
  cv::Mat frame;

  // Load the cascades
  if( !face_cascade.load( face_cascade_name ) ){ printf("--(!)Error loading face cascade, please change face_cascade_name in source code.\n"); return -1; };

  cv::namedWindow(main_window_name,CV_WINDOW_NORMAL);
  // cv::moveWindow(main_window_name, 400, 100);

  // Load face detection and pose estimation models.
  dlib::frontal_face_detector dlib_detector = dlib::get_frontal_face_detector();
  dlib::shape_predictor pose_model;
  dlib::deserialize("../res/shape_predictor_68_face_landmarks.dat") >> pose_model;

   // Read the video stream
  if( cap.isOpened() ) {
    while( true ) {
      cap >> frame;
      // mirror it
      // cv::flip(frame, frame, 1);
      frame.copyTo(debugImage);

      // Apply the classifier to the frame
      if( !frame.empty() ) {
        detectAndDisplay( frame );
       dlibDetect(frame, dlib_detector, pose_model);
      }
      else {
        printf(" --(!) No captured frame -- Break!");
        break;
      }

      imshow(main_window_name,debugImage);

      int c = cv::waitKey(10);
      if( (char)c == 'c' ) { break; }
      if( (char)c == 'f' ) {
        imwrite("frame.png",frame);
      }

    }
  }

  return 0;
}

void detectAndDisplay( cv::Mat frame ) {
  std::vector<cv::Rect> faces;
  //cv::Mat frame_gray;

  // std::vector<cv::Mat> rgbChannels(3);
  // cv::split(frame, rgbChannels);
  // cv::Mat frame_gray = rgbChannels[2];

  //cvtColor( frame, frame_gray, CV_BGR2GRAY );
  //equalizeHist( frame_gray, frame_gray );
  //cv::pow(frame_gray, CV_64F, frame_gray);
  //-- Detect faces
  face_cascade.detectMultiScale( frame, faces, 1.30, 5, 0
    |CV_HAAR_SCALE_IMAGE
    |CV_HAAR_FIND_BIGGEST_OBJECT
    ,
    cv::Size(40, 40) );

  for( int i = 0; i < faces.size(); i++ )
  {
    rectangle(debugImage, faces[i], 1234);
  }
}

void dlibDetect( cv::Mat frame, dlib::frontal_face_detector &detector, dlib::shape_predictor &pose_model) {
  dlib::cv_image<dlib::bgr_pixel> cimg(frame);

  // Detect faces
  std::vector<dlib::rectangle> faces = detector(cimg);
  // Find the pose of each face.
  // std::vector<full_object_detection> shapes;
  // for (unsigned long i = 0; i < faces.size(); ++i)
  //   shapes.push_back(pose_model(cimg, faces[i]));
   for( int i = 0; i < faces.size(); i++ ) {
     dlib::rectangle r = faces[i];
     cv::Rect cRect(r.left(),r.top(),r.width(),r.height());
     rectangle(debugImage, cRect, 9015);
   }
}
