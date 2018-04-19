//Tellon Smith
//CMPS 1063 - Program 3
//PointList.cpp
//Implements PontList class in PointList.h

#include "PointList.h"
#include "Point.h"
#include <iostream>
using namespace std;


PointList::PointList()
{
	listSize = 0;
}


PointList::~PointList()
{
}

void PointList::insertPoint(Point point)
{
	pointList[listSize] = point;

	listSize++;
}

Point PointList::providePoint(int index)
{
	if (index < (listSize))
	{
		return pointList[index];
	}
	return pointList[0];
}

int PointList::provideListSize()
{
	return listSize;
}

void PointList::swapPoints(Point & pointA, Point & pointB)
{
	//temporary point
	Point tempPoint;

	tempPoint = pointA;
	pointA = pointB;
	pointB = tempPoint;
}

void PointList::sortPointList()
{
	int mindex;
	Point pointA;
	Point pointB;

	for (int i = 0; i < (listSize - 1); i++)
	{
		mindex = i;
		
		for (int j = (i + 1); j < listSize; j++)
		{
			pointA = pointList[mindex];
			pointB = pointList[j];

			//checks if pointB is less than pointA
			if (pointA.comparePoint(pointB) == 1)
			{
				mindex = j;
			}
		}
		//swap points
		swapPoints(pointList[i], pointList[mindex]);
	}
}

int PointList::searchPoint(Point userPoint)
{
	int first = 0;
	int last = (listSize - 1);
	int midPoint;
	bool found = false;
	int index = -1;

	while (!found && first <= last)
	{
		midPoint = (first + last) / 2;

		//if userPoint is equal to the midPoint
		if (userPoint.comparePoint(pointList[midPoint]) == 0)
		{
			found = true;
			index = midPoint;
		}
		else if (userPoint.comparePoint(pointList[midPoint]) == -1)
		{
			last = (midPoint - 1);
		}
		else first = (midPoint + 1);
	}//end while
	return index;
}

void PointList::removePoint(int index)
{
	//blank/empty point (0,0)
	Point blankPoint;

	//sets the index point to (0,0) 
	pointList[index] = blankPoint;

	for (int i = index; i < listSize; i++)
	{
		if (i == (listSize - 1))
		{
			//sets last point to (0,0)
			pointList[i] = blankPoint;
		}
		//moves up points in the array
		else pointList[i] = pointList[i + 1];
	}
	//decrements the number of points in the array after removal
	listSize--;
}
