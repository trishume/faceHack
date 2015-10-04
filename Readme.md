# FaceHack

This is a terrible hack I made in 6 hours for the [TerribleHack](http://terriblehack.website/) hackathon ([see other entries](http://terriblehack.devpost.com/submissions)), a parody hackathon for making stupid things. See the [DevPost submission](http://devpost.com/software/facehack) for more screenshots and explanation.

It uses OpenCV and [dlib](http://blog.dlib.net/2014/08/real-time-face-pose-estimation.html) to perform face pose detection on downloaded Youtube videos and webcam photos. It then uses a triangulation of the detected face points to texture map a picture of your face onto the faces in the video. The face detection is computed beforehand in a C++ program and outpus location data in a JSON file, which is read by a Three.JS web page that renders the video and synchronizes the mapped rendering of a face on top of the video.

![Gif](http://i.imgur.com/0geqsOU.gif)

![Face detection](http://i.imgur.com/w7lfLjW.png)

In the demo, my face is warped over Rick Astley in the "Never gonna give you up" video.
The lips of the warped face and the rotation both follow Rick because of the flexible mapping.

## How to run

There's a lot of things in the `.gitignore` file since there's some large data and copy-pasted videos and libraries.
Because I was frantically trying to finish it in 6 hours a lot of the paths are hard-coded and there isn't a good linking and resources loading story.

You'll need to do at least the following things:
- Downoad [dlib](http://dlib.net/) and put it in the `dlib` folder, this is because the only good building method for DLib is to include its CMake file in your project and have it compile with your project. :|
- Put the DLib face model, a photo of yourself, and a video into the `res` folder for processing.
- make a `build` folder, cd into it, and run `cmake ..`
- alter all the paths in the source code to work
- run `make`, then run `./bin/faceHack`, this will process the video and output a JSON file
- copy the required resources and put them in the `web` directory and run a simple HTTP server like `ruby -run -e httpd . -p 9090`
- visit `http://localhost:9090/` to view your video
