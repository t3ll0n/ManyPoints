//Tellon Smith
//CMPS 1063 - Program 3
//Point.cpp
//Implements Pong class in Point.h

#include "Point.h"
#include <string>


using namespace std;

Point::Point()
{
	xValue = 0;
	yValue = 0;
}

Point::Point(int x, int y)
{
	xValue = x;
	yValue = y;
}


Point::~Point()
{
}


void Point::changeXValue(int newXValue)
{
	xValue = newXValue;
}

void Point::changeYValue(int newYValue)
{
	yValue = newYValue;
}

int Point::provideXValue()
{
	return xValue;
}

int Point::provideYValue()
{
	return yValue;
}

string Point::pointToString()
{
	return "(" + to_string(xValue) + "," + to_string(yValue) + ")";
}

int Point::comparePoint(Point pointB)
{
	int result;

	if ((provideXValue() < pointB.provideXValue()) || (provideXValue() == pointB.provideXValue()\
		&& provideYValue() < pointB.provideYValue()))
	{
		result = -1;
	}
	else if (provideXValue() == pointB.provideXValue() && provideYValue() == pointB.provideYValue())
	{
		result = 0;
	}
	else result = 1;

	return result;
}