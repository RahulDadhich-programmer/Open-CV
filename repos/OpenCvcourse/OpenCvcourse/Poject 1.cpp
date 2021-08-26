#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include<iostream>

using namespace cv;
using namespace std;

///////project-1 virtual paint//////

Mat img;
VideoCapture cap(0);
vector < vector<int>>newPoints;//to store all points

///////Color Values///
///hmin,smin,vmin,hmax,smax,vmax
	
vector<vector<int>>myColors{ {5,64,193,24,187,255 },//orange
{52, 78, 19, 130, 255, 255} };//Blue

vector < Scalar>myColorvalues{ {255,113,0},{35,128,221}};//Green

////////////////////////////////////////

 

vector<vector<int>> findColor(Mat img)
{
	Mat imgHSV;
	cvtColor(img, imgHSV, COLOR_BGR2HSV);

	for (int i = 0; i < myColors.size(); i++)
	{
		Scalar lower(myColors[i][0], myColors[i][1], myColors[i][2]);
		Scalar upper(myColors[i][3], myColors[i][4], myColors[i][5]);
		Mat mask;
		inRange(imgHSV, lower, upper, mask);
		//imshow(to_string(i), mask);
		Point myPoint = getContours(mask);
		if (myPoint.x != 0) {
			newPoints.push_back({ myPoint.x,myPoint.y,i });
		}
	}
	return newPoints;
}

void drawOnCanvas(vector<vector<int>> newPoints, vector<Scalar> myColorValues)
{

//	for (int i = 0; i < newPoints.size(); i++)
	//{
		//circle(img, Point(newPoints[i][0], newPoints[i][1]), 10, myColorValues[newPoints[i][2]], FILLED);
	//	}
}

void main() {

	while (true) {

		cap.read(img);
		newPoints = findColor(img);
		drawOnCanvas(newPoints,myColorvalues);

		imshow("Images", img);
		waitKey(1);
	}
}