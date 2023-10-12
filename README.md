# LF_OPENGL

## Description
Robust tuned Line Follower Virtual Robot that’s animated with OpenGL platform. Refined with Jacobian matrix to control, the robot able to read every line be it thin or sharp turn.

## Requirements
Cygwin with default and some packages including:
- gcc-g++
- make
- libGLU-devel
- libGLU1
- libglut3
- libglut-devel
- libGL-devel
- libGL1
- xinit
- xorg-server
> Xinit and xorg server are important for the runtime server.

## How to Run
- Open Cygwin Terminal
- Go into robot directory by using ``` cd ```
- In the directory, use command:
  ```make```
- after that, use command:
  ```startxwin ./namaprogram -- +iglx -nowgl```
