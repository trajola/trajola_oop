// fill.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <deque>

using namespace std;
enum Points {
	EMPTY = 0,
	BORDER = 1,
	POINT = 2,
	FILL = 3,
	ERROR = -1
};
typedef Points Pictures[100][100];

struct PicCoords {
	int i;
	int j;
};


ifstream OpenFileForReading(const string & fileName)
{
	ifstream strm(fileName);
	if (!strm.is_open())
		cout << "Failed to open " << fileName << "\n";
	return move(strm);
}

ofstream OpenFileForWriting(const string & fileName)
{
	ofstream strm(fileName);
	if (!strm.is_open())
		cout << "Failed to open " << fileName << "\n";
	return move(strm);
}

char Point2Char(const Points & point)
{
	switch (point)
	{
		case EMPTY:	return ' ';
		case BORDER:return '#';
		case POINT: return 'O';
		case FILL:	return '.';
		default:	return '@';
	}
}

Points Char2Point(const char & ch)
{
	switch (ch)
	{
		case ' ': return EMPTY;
		case '#': return BORDER;
		case 'O': return POINT;
		case '.': return FILL;
		default:  return ERROR;
	}
}

bool ReadPictures(Pictures pic, const string & fileName, deque<PicCoords> & positionsToFill)
{
	ifstream inFile = OpenFileForReading(fileName);
	if (!inFile)
		return false;
	for (int i = 0; i < 100; i++)
	{
		string str;
		if (!getline(inFile, str))
			str.clear();
		for (int j = 0; j < str.length(); j++)
		{
			pic[i][j] = Char2Point(str.at(j));
			if (pic[i][j] == POINT)
				positionsToFill.push_front({ i, j });
			
			if (pic[i][j] == ERROR)
				return false;
		}
		for (int j = str.length(); j < 100; j++)
			pic[i][j] = EMPTY;

		
	/*	for (int j = 0; j < 100; j++) 
		{
			try 
			{
				pic[i][j] = Char2Point(str.at(j));
				if (pic[i][j] == POINT)
					positionsToFill.push_front({ i, j });

				if (pic[i][j] == ERROR)
					return false;
			}
			catch (std::out_of_range)
			{
				pic[i][j] = EMPTY;
			}
		}*/


	}
	return true;
}

bool PrintPictures(Pictures pic, const string & fileName)
{
	ofstream outFile = OpenFileForWriting(fileName);
	if (!outFile)
		return false;
	
	for (int i = 0; i < 100; i++)
	{
		for (int j = 0; j < 100; j++)
			if(!outFile.put(Point2Char(pic[i][j])))
				return false;
		if (!outFile.put('\n'))
			return false;
	}
	return true;
}

bool isValidPos (const PicCoords & picPos)
{
	if (picPos.i >= 100 || picPos.i < 0)
		return false;
	if (picPos.j >= 100 || picPos.j < 0)
		return false;
	return true;
}

bool PutPoint(Pictures pic, const PicCoords & picPos, const Points & point) 
{
	if (!isValidPos(picPos))
		return false;
	pic[picPos.i][picPos.j] = point;
	return true;
}

Points GetPoint(Pictures pic, const PicCoords & picPos)
{
	if (!isValidPos(picPos))
		return ERROR;
	return pic[picPos.i][picPos.j];
}

PicCoords DoStep(const PicCoords & picPos, const PicCoords step)
{
	return { picPos.i + step.i, picPos.j + step.j };
}

bool FillingFigure(Pictures pic, const PicCoords & startPos)
{
	vector<PicCoords> steps = { { -1, 0 }, { 1, 0 }, { 0, -1 }, { 0, 1 } };
	deque<PicCoords> queue;
	queue.push_front(startPos);  
	if (!PutPoint(pic, startPos, POINT))
		return false;
	while (!queue.empty())
	{	
		for (auto step : steps)
		{
			PicCoords newPos = DoStep(queue.front(), step); 
			if (isValidPos(newPos) && GetPoint(pic, newPos) == EMPTY)
			{
				if (!PutPoint(pic, newPos, FILL))
					return false;
				queue.push_back(newPos);
			}
		}
		queue.pop_front();
	}
	return true;
}

bool FillingPic(Pictures pic, deque<PicCoords> & positionsToFill)
{
	for (auto pos : positionsToFill)
		if (!FillingFigure(pic, pos))
			return false;

	return true;
}


int main(int argc, char * argv[])
{
	if (argc != 3)
	{
		cout << "Invalid number of arguments.\n";
		cout << "Usage: fill.exe <input file> <output file>\n";
		return 1;
	}

	Pictures pic;
	deque<PicCoords> positionsToFill;
	if (!ReadPictures(pic, argv[1], positionsToFill))
	{
		cout << "Something's gone wrong while reading picture.\n";
		return 1;
	}
	
	if (!FillingPic(pic, positionsToFill))
	{
		cout << "Something's gone wrong while filling picture.\n";
		return 1;
	}

	if (!PrintPictures(pic, argv[2]))
	{
		cout << "Something's gone wrong while writing picture.\n";
		return 1;
	}

	return 0;
}
