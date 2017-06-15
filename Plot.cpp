#include<iostream>
#include "Plot.h"

using namespace std;

//********************************
// Constructor                   *
//********************************
Plot::Plot ()  
{
	size = 0;
	elements = NULL;
}

//********************************
// Deep Copy Constructor         *
//********************************
Plot::Plot(const Plot &copy)
{
	size = copy.size;
	elements = new Point [size];

	for(int i = 0; i<size; i++)
	{
		elements[i] = copy.elements[i];
	}
}

//********************************
// Destructor                    *                                    
//********************************
Plot::~Plot()
{
	delete [this->size] elements;
	elements = NULL;
	size=0;
}

//********************************
// Operator Overloads            *                                    
//********************************
const Plot & Plot::operator = (const Plot & rhs)  
{
	if (this != &rhs)
	{
		size = rhs.size;	
		elements = new Point [size];

		for(int i = 0; i<size; i++)
		{
			elements[i] = rhs.elements[i];
		}	
	}

	return *this;
}


Plot  Plot::operator + (const Point & rhs) 
{
	Plot result(*this);
	int sizeResult;
	Point *elementsResult;
	sizeResult = this->size + 1;
	elementsResult = new Point [sizeResult];

	for(int i = 0; i<this->size; i++)
	{
		elementsResult[i] = this->elements[i];
	}
	(elementsResult [sizeResult-1]) = rhs;

	result.elements = elementsResult;
	result.size = sizeResult;

	result.BubbleSort();
	return result;
}

Plot  Plot::operator + (const Plot & rhs)  
{
	Plot result(*this);
	int sizeResult;
	Point *elementsResult;
	sizeResult = this->size + rhs.size;
	elementsResult = new Point [sizeResult];

	int i;
	for(i = 0; i<this->size; i++)
	{
		elementsResult[i] = this->elements[i];
	}

	for(i; i<sizeResult; i++)
	{
		elementsResult[i] = rhs.elements[i - this->size];
	}

	result.elements = elementsResult;
	result.size = sizeResult;

	result.BubbleSort();
	return result;
}

Plot  Plot::operator - (const Point & rhs)  
{
	Plot result(*this);

	if (this->isExist(rhs))
	{
		int sizeResult;
		Point *elementsResult;
		sizeResult = this->size - 1;
		elementsResult = new Point [sizeResult];

		int i;
		for(i = 0; i<this->getPos(rhs); i++)
		{
			elementsResult[i] = this->elements[i];
		}

		i++;

		for(i; i<size; i++)
		{
			elementsResult[i-1] = this->elements[i];
		}

		result.elements = elementsResult;
		result.size = sizeResult;
	}
	return result;
}

bool Plot::operator == (const Plot &rhs)  
{
	if (this->size != rhs.size)
		return false;
	else
	{
		for (int i = 0; i < size; i++)
		{
			if (this->elements[i].x != rhs.elements[i].x || this->elements[i].y != rhs.elements[i].y)
				return false;
		}
		return true;
	}
}


void Plot :: BubbleSort()  // Advanced sorting function
{
	int i, j, flag = 1;    // set flag to 1 to start first pass
	Point temp;             // holding variable
	bool samex = false;
	for(i = 1; (i <= this->size) && flag; i++)
	{
		flag = 0;
		for (j=0; j < (this->size -1); j++)
		{
			if (this->elements[j+1].x < this->elements[j].x)      // ascending order simply changes to <
			{ 
				temp = this->elements[j];             // swap elements
				this->elements[j] = this->elements[j+1];
				this->elements[j+1] = temp;
				flag = 1;               // indicates that a swap occurred.
			}

			else if (this->elements[j+1].x == this->elements[j].x)
			{
				samex = true;;  // is there at least 1 same x block
			}
		}
	}  // now array is sorted

	if (samex)
	{
		int count=1;
		for (int i = 0; i < size; i++)
		{
			if (this->elements[i+1].x == this->elements[i].x)  // if same x, increase count
				count++;

			if (this->elements[i+1].x != this->elements[i].x && count-1)  // if same x block has just finished
			{
				Point *Resultelements = new Point [this->size - count +1];  // new array for eliminating same x s
				int j;
				for (j = 0 ; j < i - count + 1 ; j++)
					Resultelements [j] = this->elements [j];   // filling new array with old values till the repeat
				double averagesum = 0;
				for (j; j < i + 1; j++)   // calculating overall sum of y values for repeating x
					averagesum = averagesum + this->elements [j].y;
				Resultelements [i - count + 1].x = this->elements [j-1].x;  
				Resultelements [i - count + 1].y = averagesum / count;    // adding average y value
				for (j; j < size; j++)  // filling new array with old values after the repeat
					Resultelements [j - count + 1] = this->elements [j];
				elements = Resultelements;
				size = size - count + 1;
				count = 1;
			}
		}
	}
}


bool Plot :: isExist (Point wanted)
{
	for (int i = 0; i<this->size; i++)
	{
		if (this->elements[i].x == wanted.x && this->elements[i].y == wanted.y)
			return true;
	}
	return false;
}

int Plot :: getPos (Point wanted)
{
	for (int i = 0; i<this->size; i++)
	{
		if (this->elements[i].x == wanted.x && this->elements[i].y == wanted.y)
			return i;
	}
}

int Plot :: getSize () const
{
	return this->size;
}

Point* Plot :: getElements () const
{
	return (this->elements);
}

void Plot :: setSize (int num)
{
	this->size = num;
}

void Plot :: setElements (Point *set)
{
	(this->elements) = set;
}

//********************************
// Free Functions                *
//********************************

ostream &operator << (ostream & output, Plot & graph)  
{
	graph.BubbleSort();
	if (graph.getSize() >= 1)
	{
		output<<'('<<graph.getElements()[0].x<<", "<<graph.getElements()[0].y<<')';
		for (int i = 1; i < graph.getSize(); i++)
		{
			output<<", "<<'('<<graph.getElements()[i].x<<", "<<graph.getElements()[i].y<<')';			
		}
	}
	return output;
}

Plot operator + (Point newpoint, const Plot &  graph)  
{
	Plot result;
	int sizeResult= graph.getSize() + 1;
	Point *elementsResult= new Point [sizeResult];

	for(int i = 0; i<graph.getSize(); i++)
	{
		elementsResult[i] = graph.getElements()[i];
	}
	elementsResult [sizeResult-1] = newpoint;

	result.setSize(sizeResult);
	result.setElements (elementsResult);

	result.BubbleSort();
	return result;
}

Plot  operator += (Plot &  lhs, const Plot & rhs)  
{
	Plot result;
	int sizeResult;
	Point *elementsResult;
	sizeResult = lhs.getSize() + rhs.getSize();
	elementsResult = new Point [sizeResult];

	int i;
	for(i = 0; i<lhs.getSize(); i++)
	{
		elementsResult[i] = lhs.getElements()[i];
	}

	for(i; i<sizeResult; i++)
	{
		elementsResult[i] = rhs.getElements()[i - lhs.getSize()];
	}

	result.setElements(elementsResult);
	result.setSize(sizeResult);

	result.BubbleSort();
	lhs = result;
	return result;
}

Plot  operator -= (Plot &  lhs, const Point & rhs)  
{
	Plot result (lhs);

	if (lhs.isExist(rhs))
	{
		int sizeResult;
		Point *elementsResult;
		sizeResult = lhs.getSize() - 1;
		elementsResult = new Point [sizeResult];

		int i;
		for(i = 0; i<lhs.getPos(rhs); i++)
		{
			elementsResult[i] = lhs.getElements()[i];
		}

		i++;

		for(i; i<lhs.getSize(); i++)
		{
			elementsResult[i-1] = lhs.getElements()[i];
		}

		result.setElements(elementsResult);
		result.setSize(sizeResult);
	}
	lhs = result;
	return result;
}
