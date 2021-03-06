// fill.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <deque>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;
enum class Cell
{
	EMPTY = ' ',
	BORDER = '#',
	START = 'O',
	FULL = '.',
	ERROR = -1
};
typedef Cell Canvas[100][100];

struct CellCoord
{
	int row;
	int col;
};

ifstream OpenFileForReading(const string& fileName)
{
	ifstream strm(fileName);
	if (!strm.is_open())
		cout << "Failed to open " << fileName << "\n";
	return move(strm);
}

ofstream OpenFileForWriting(const string& fileName)
{
	ofstream strm(fileName);
	if (!strm.is_open())
		cout << "Failed to open " << fileName << "\n";
	return move(strm);
}

Cell Char2Cell(char ch)
{
	switch (ch)
	{
	case ' ':
		return Cell::EMPTY;
	case '#':
		return Cell::BORDER;
	case 'O':
		return Cell::START;
	case '.':
		return Cell::FULL;
	default:
		return Cell::ERROR;
	}
}

bool IsValidPos(const CellCoord& picturePos)
{
	if (picturePos.row >= 100 || picturePos.row < 0)
		return false;
	if (picturePos.col >= 100 || picturePos.col < 0)
		return false;
	return true;
}

Cell GetCell(Canvas& picture, const CellCoord& picturePos)
{
	if (!IsValidPos(picturePos))
		return Cell::ERROR;
	return picture[picturePos.row][picturePos.col];
}

bool PutCell(Canvas& picture, const CellCoord& picturePos, const Cell& point)
{
	if (!IsValidPos(picturePos))
		return false;
	picture[picturePos.row][picturePos.col] = point;
	return true;
}

bool ReadPicture(Canvas& picture, const string& fileName, vector<CellCoord>& startPositionsToFill)
{
	ifstream inFile = OpenFileForReading(fileName);
	if (!inFile)
		return false;
	for (int row = 0; row < 100; row++)
	{
		string str;
		if (!getline(inFile, str))
			str.clear();
		for (int col = 0; col < 100; col++)
		{
			try
			{
				Cell point = Char2Cell(str.at(col));
				if (point == Cell::START)
					startPositionsToFill.push_back({ row, col });
				if (point == Cell::ERROR)
					return false;
				PutCell(picture, { row, col }, point);
			}
			catch (std::out_of_range &)
			{
				PutCell(picture, { row, col }, Cell::EMPTY);
			}
		}
	}
	return true;
}

bool PrintPicture(Canvas& picture, const string& fileName)
{
	ofstream outFile = OpenFileForWriting(fileName);
	if (!outFile)
		return false;

	for (int row = 0; row < 100; row++)
	{
		for (int col = 0; col < 100; col++)
			if (!outFile.put(static_cast<char>(picture[row][col])))
				return false;
		if (!outFile.put('\n'))
			return false;
	}
	return true;
}

CellCoord DoStep(const CellCoord& picturePos, const CellCoord& step)
{
	return { picturePos.row + step.row, picturePos.col + step.col };
}

bool FloodFill(Canvas& picture, const CellCoord& startPos)
{
	vector<CellCoord> steps = { { -1, 0 }, { 1, 0 }, { 0, -1 }, { 0, 1 } };
	deque<CellCoord> queue;
	queue.push_front(startPos);
	while (!queue.empty())
	{
		for (auto step : steps)
		{
			CellCoord newPos = DoStep(queue.front(), step);
			if (IsValidPos(newPos) && GetCell(picture, newPos) == Cell::EMPTY)
			{
				if (!PutCell(picture, newPos, Cell::FULL))
					return false;
				queue.push_back(newPos);
			}
		}
		queue.pop_front();
	}
	return true;
}

bool TryFloodFillPicture(const string& inFileName, const string& outFileName)
{
	Canvas picture;
	vector<CellCoord> startPositionsToFill;
	if (!ReadPicture(picture, inFileName, startPositionsToFill))
	{
		cout << "Something's gone wrong while reading picture\n";
		return false;
	}

	auto FloodFillPicture = [&picture](const CellCoord& coord) {
		return FloodFill(picture, coord);
	};

	if (!all_of(startPositionsToFill.begin(), startPositionsToFill.end(), FloodFillPicture))
	{
		cout << "Something's gone wrong while filling picture\n";
		return false;
	}

	if (inFileName == outFileName || !PrintPicture(picture, outFileName))
	{
		cout << "Something's gone wrong while writing picture\n";
		return false;
	}
	return true;
}

int main(int argc, char* argv[])
{
	if (argc != 3)
	{
		cout << "Invalid number of arguments\n";
		cout << "Usage: fill.exe <input file> <output file>\n";
		return 1;
	}

	if (!TryFloodFillPicture(argv[1], argv[2]))
	{
		cout << "Can't do filling\n";
		return 1;
	}
	return 0;
}
