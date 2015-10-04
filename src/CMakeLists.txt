ADD_EXECUTABLE( faceHack main.cpp constants.h helpers.cpp helpers.h)
TARGET_LINK_LIBRARIES( faceHack dlib ${OpenCV_LIBS} )
