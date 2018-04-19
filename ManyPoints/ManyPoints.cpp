//-------------------------------------------------------------------------------------------------------
//
// Name: Smith, Tellon
//
// Course: CS 1063 - Data Structures & ADT, Spring 15, Dr. Stringfellow
//
// Program Assignment : #3
//
// Due Date: Wednesday, Mar. 11, 2015, 9AM
//
// Purpose: This program reads in multiple point values (x,y) from an input file and outputs the 
//          distance between successive points, it then sorts the points in ascending order and 
//          offers the option to remove a point
//
//-------------------------------------------------------------------------------------------------------

#include <iostream>
#include <iomanip>
#include "Point.h"
#include "PointList.h"
#include <cmath>
#include <sstream>
#include "CImg.h"

using namespace std;
using namespace cimg_library;

//constants for the graphics
const int MAXX = 600;	//width of image
const int MAXY = 600;	//height of image
const unsigned char black[] = {0};	//pen color

//Purpose: open streams
//Requires: an input stream and output stream
//Returns: an opened input stream and an opened output stream
void openFiles(ifstream & infile, ofstream & outfile);

//Purpose: inserts a point containing x,y values into an array which is read in from the input file 
//Requires: an opened input stream, and an array  
//Returns: none
void insertPointValues(ifstream & infile, PointList & pointList);


//Purpose: calulates the distance between two points (x,y) 
//Requires: two points (pontA and pointB) 
//Returns: the distance between the two points 
double findDistance(Point pointA, Point pointB);


//Purpose: prints a table with point values (x,y) and the distance between successive points and the
//         total distance
//Requires: an opened output stream, array of points (pointList), the array distances and the total
//          distance
//Returns:  output stream with table of information appended to it. Arrays unchanged
void printResutls(ofstream & outfile, PointList pointList, double* distances, double totalDistance);

//Purpose: prints heading info to outfile
//Requires: an opened output stream
//Returns: output stream with the heading appended to it
void printHeadings(ofstream & outfile);

//Purpose: prints welcome message
//Requires: an opened output stream
//Returns: output stream with the welcome message appended to it
void printWelcomeMessage(ofstream & outfile);

//Purpose: prints exit message
//Requires: an opened output stream 
//Returns: output stream with the exit message appended to it
void printExitMessage(ofstream & outfile);

//Purpose: provides the distances between successive points
//Requires: the array of points (pointList) and an array to store the distances (distances) 
//Returns: the array updated with the distances between successive points
void provideDistanceBetweenPoints(PointList pointList, double* distances);

//Purpose: provides the total distance between points
//Requires: the array of distances, array of points, and the totalDistance variable 
//Returns:
void provideTotalDistance(double* distances, PointList pointList, double & totalDistances);

//Purpose: gets if the user wants to remove a point from the array
//Requires: the user choice (Y or N)
//Returns: true or false
void getChoice(ofstream & outfile, bool & choice);

//Purpose: gets user input (x,y) for a point to remove and checks if it exist in the array  
//Requires: the array, userPoint and pointIndex
//Returns: the user point and pointIndex. array unchanged
void getUserPoint(PointList & pointList, Point & userPoint, int & pointIndex);

//Purpose: prints a message stating that user point has been removed
//Requires: an opened output stream and the user point 
//Returns: output stream with the appended to it
void printPointRemovedMessage(ofstream & outfile, Point UserPoint);

//Purpose: initializes the graphics system and then draw the desired image
//Requires: the array (initialized) 
//Returns: points in the list will be connected and drawn at 2X magnification and 
//         shifted by 85 (to some what center the image). array is unchanged
void drawPoints(PointList & pointList);

int main()
{
	ofstream outfile;
	ifstream infile;

	//stores the distances between successive points
	double distances[50];
	//stores total distance between points
	double totalDistance;

	PointList pointList;
	bool choice = true;
	Point userPoint;
	int pointIndex;

	//open streams
	openFiles(infile, outfile);

	printHeadings(outfile);

	printWelcomeMessage(outfile);

	insertPointValues(infile, pointList);

	provideDistanceBetweenPoints(pointList, distances);

	provideTotalDistance(distances, pointList, totalDistance);
	
	printResutls(outfile, pointList, distances, totalDistance);

	drawPoints(pointList);

	//sort pointList Array 
	pointList.sortPointList();

	//recalculate distances between points, total distance and print results 
	provideDistanceBetweenPoints(pointList, distances);
	provideTotalDistance(distances, pointList, totalDistance);
	printResutls(outfile, pointList, distances, totalDistance);	
	drawPoints(pointList);
		
	do
	{
		//ask if user wants to remove a point
		getChoice(outfile, choice);
		
		if (choice == true)
		{
			getUserPoint(pointList, userPoint, pointIndex);
		}
	} while (choice == true && pointIndex == -1);
		
	if (choice == true)
	{
		//removes point
		pointList.removePoint(pointIndex);

		//recalculate distances between points, total distance and print results 
		provideDistanceBetweenPoints(pointList, distances);
		provideTotalDistance(distances, pointList, totalDistance);
		printResutls(outfile, pointList, distances, totalDistance);
		printPointRemovedMessage(outfile, userPoint);
		drawPoints(pointList);
	}

	printExitMessage(outfile);

	//close files 
	infile.close();
	outfile.close();

	system("pause");
	return 0;
}


void openFiles(ifstream & infile, ofstream & outfile)
{
	char inFileName[40];
	char outFileName[40];

	//open input stream
	cout << "\nPlease enter the input file name: ";
	cin >> inFileName;
	infile.open(inFileName);

	//display error message if specified cannot be opened
	if (!infile)
	{
		cout << "\nERROR: cannot open the specified file. please run the program again." << endl;
		system("pause");
		exit(1);
	}

	//open output stream
	cout << "Enter the output file name: ";
	cin >> outFileName;
	outfile.open(outFileName);
}

void insertPointValues(ifstream & infile, PointList & pointList)
{
	Point point;

	int x;
	int y;

	//only reads if it receives two values per loop, thus not affected if infile has
	//a carriage return or not
	while (infile >> x >> y)
	{
		//changes value in the point
		point.changeXValue(x);
		point.changeYValue(y);

		//inserts point into the array
		pointList.insertPoint(point);
	}
}



void printResutls(ofstream & outfile, PointList pointList, double* distances, double totalDistance)
{
	outfile << "_____________________________" << endl;
	outfile << "Point A   Point B    Distance" << endl;
	outfile << "_____________________________" << endl;

	//loops through and prints each point in the array and the respected distance
	for (int i = 0; i < pointList.provideListSize(); i++)
	{

		Point pointA = pointList.providePoint(i);
		Point pointB = pointList.providePoint(i + 1);


		outfile << left << fixed << setprecision(2) << setw(10) << pointA.pointToString() << setw(10)\
			<< pointB.pointToString() << right << setw(6) << distances[i] << endl;

	}//end of loop
	//prints total distance
	outfile << "\nThe total distance is " << fixed << setprecision(2) << totalDistance << endl;
}

void printHeadings(ofstream & outfile)
{
	outfile << "\nName: Tellon Smith" << endl;
	outfile << "Course: CS 1063 - Data Structures & ADT, Spring 15, Dr. Stringfellow" << endl;
	outfile << "Program Assignment: #3" << endl;
	outfile << "Due Date: Wednesday, Mar. 11, 2015, 9AM" << endl;
	outfile << "Purpose: This program reads in multiple point values (x,y) from an input" << endl;
	outfile << "         file and outputs the distance between successive points" << endl;
	outfile << "         it then sorts the points in ascending order and offers" << endl;
	outfile << "         the option to remove a point" << endl;
}


void printWelcomeMessage(ofstream & outfile)
{
	outfile << "\nWelcome to the Many Points Distance Program!" << endl;
}

void printExitMessage(ofstream & outfile)
{
	outfile << "\nThank you for using the Many Points Distance Program... Goodbye!" << endl;
}

double findDistance(Point pointA, Point pointB){

	return sqrt(pow((pointA.provideXValue() - pointB.provideXValue()), 2) + pow((pointA.provideYValue()\
		- pointB.provideYValue()), 2));
}

void provideDistanceBetweenPoints(PointList pointList, double* distances)
{
	for (int i = 0; i < pointList.provideListSize(); i++)
	{
		Point pointA = pointList.providePoint(i);
		Point pointB = pointList.providePoint(i + 1);
		distances[i] = findDistance(pointA, pointB);
	}
}

void provideTotalDistance(double* distances, PointList pointList, double & totalDistances)
{
	totalDistances = 0;

	for (int i = 0; i < pointList.provideListSize(); i++)
	{
		totalDistances += distances[i];
	}
}

void getChoice(ofstream & outfile, bool & choice)
{
	char ch;

	cout << "\nDo you want to remove a point? Enter Y or N: " << endl;
	cin >> ch;
	ch = toupper(ch);

	while ((ch != 'Y') && (ch != 'N'))
	{
		cout << "Please enter a Y or N: ";
		cin >> ch;
		ch = toupper(ch);
	}

	if (ch == 'N')
	{
		outfile << "\nNo point was removed!" << endl;
		choice = false;
	}
	else choice = true;
}

void getUserPoint(PointList & pointList, Point & userPoint, int & pointIndex)
{
	int x;
	int y;

	cout << "\nPlease enter the x y coordinates of a point to remove " << endl;
	cin >> x >> y;

	//set x and y values of user point
	userPoint.changeXValue(x);
	userPoint.changeYValue(y);

	pointIndex = pointList.searchPoint(userPoint);

	if (pointIndex == -1)
	{
		cout << "\nThe point you entered does not exist in the array!" << endl;
	}
}

void printPointRemovedMessage(ofstream & outfile, Point UserPoint)
{
	outfile << "\nPoint " << UserPoint.pointToString() << " was removed!" << endl;
}

void drawPoints(PointList & pointList)
{
	//width,height,depth,number of channels
	CImg<unsigned char> theImage(MAXX, MAXY, 1, 3);
	CImgDisplay main_disp(theImage, "Connect the Dots");

	//Write 0 to every pixel(turn it black), then display the image
	theImage.fill(255, 255, 255);
	theImage.display(main_disp);

	Point point1, point2;

	//draw lines between each successive point
	for (int i = 0; i < pointList.provideListSize() - 1; i++)
	{
		point1 = pointList.providePoint(i);
		point2 = pointList.providePoint(i + 1);

		//draw lines
		theImage.draw_line((85 + point1.provideXValue()) * 2, (85 + point1.provideYValue()) * 2,
			(85 + point2.provideXValue()) * 2, (85 + point2.provideYValue()) * 2, black);
	}

	//Connect last and first point
	point1 = pointList.providePoint(pointList.provideListSize() - 1);
	point2 = pointList.providePoint(0);

	//draw line
	theImage.draw_line((85 + point1.provideXValue()) * 2, (85 + point1.provideYValue()) * 2,
		(85 + point2.provideXValue()) * 2, (85 + point2.provideYValue()) * 2, black);

	//give instructions to user to close the display
	//then wait for them to do so
	theImage.draw_text(0, 500, "Click the Close X Button to EXIT!", black);
	theImage.display(main_disp);
	system("pause");
	main_disp.close();
}
