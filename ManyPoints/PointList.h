//Tellon Smith
//CMPS 1063 - Program 3
//PointList.h
//Declare a PointList type for the Many Points application

#pragma once

#include "Point.h"

using namespace std;

const int MAXSIZE = 50;

typedef Point PointArray[MAXSIZE];

class PointList
{
public:
	//initializes PointList
	PointList();

	//empties PointList
	~PointList();

	//inserts a Point to the PointList
	//precond: PointList is initialized, Point is initialized
	//postcond: Point is added to this PointList and listSize is incremented and
	//          the rest of the PointList is unchanged
	void insertPoint(Point point);

	//to the return the Point values (x,y) of the pointList index number
	//precond: PointList is initialized, Point is initialized
	//postcond: returns the Point values (x,y) of the pointList index number. if the
	//          index number is equal to the listSize, it returns the Point values
	//          of the first index
	Point providePoint(int index);

	//to return the value of listSize
	//precond: listSize initialized
	//postcond: returns the value of listSize
	int provideListSize();

	//to perform a swap between two points in the PointArray type array
	//precond: array initialized, requires two point index in the array to be swapped
	//postcond: returns the array with the points swapped 
	void swapPoints(Point & pointA, Point & pointB);

	//to perform a slection sort on the PointArray type array
	//precond: array initialzed
	//postcond: returns the array with the points sorted in ascending order
	void sortPointList();

	//to perform a binary search on the PointArray type array for point(userPoint) 
	//precond: array initialized, point(userPoint) initialized 
	//postcond: returns the index number of a matching point in the array
	//          or -1 if the point(key) was not found
	int searchPoint(Point userPoint);

	//to remove a point in the PointArray type array 
	//precond: array initialized, requires the index number in the array of the point
	//		   to remove and 
	//postcond: returns the array with the point removed and all other points shifted
	//          up and listSize decremented
	void removePoint(int index);	

private:
	//stores the number of points inserted into the array. It is incremented by the
	//insertPoint function after each insertion.
	int listSize;

	PointArray pointList;
};

