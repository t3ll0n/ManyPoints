//Tellon Smith
//CMPS 1063 - Program 3
//Point.h
//Declare a Point type for the Many Points application

#pragma once

#include <fstream>

using namespace std;

class Point
{
public:
	//initialize Point members
	//precond: this Point is not initialized
	//postcond: this Point is initialized to default values
	Point();
	Point(int, int);

	//destroys this point
	//precond: Point must have constructed
	//postcond: Pont is destructed
	~Point();

	//changes the value of x to a new value
	//precond: none
	//postcond: the value of x is changed to a new value  (xValue = newXValue)
	void changeXValue(int newXValue);

	//changes the value of x to a new value
	//precond: none
	//postcond: the value of y is changed to a new value  (yValue = newYValue)
	void changeYValue(int newYValue);

	//to return the value of x
	//precond: none
	//postcond: returns the the value of x
	int provideXValue();

	//to return the value of y
	//precond: none
	//postcond: returns the the value of y
	int provideYValue();

	//to return the string of a Point. Example: (4,6)
	//precond: none
	//postcond: returns the string of a Point
	string pointToString();

	//to compare the point to another point (pointB)
	//precond: requires a point to compare itself to (pointB)
	//postcond: returns -1 if less than pointB, 0 if equal and 1 otherwise
	int comparePoint(Point pointB);


private:
	int xValue;
	int yValue;
};

