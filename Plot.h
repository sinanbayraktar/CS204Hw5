#include<iostream>

using namespace std;

struct Point
{
	int x;
	double y;

	// default constructor
	Point::Point ()
		:x(0), y(0.0)
	{}

};

class Plot
{
private:
	int size;
	Point *elements;

public:
	Plot();  //default constructor
	Plot(const Plot &);  //deep copy constructor
	~Plot();  //destructor

	bool Plot::operator == (const Plot &rhs);  // returns true if equal
	Plot  Plot::operator + (const Plot & rhs);   // adding to plots
	Plot  Plot::operator + (const Point & rhs);  // adding a point to a plot
	Plot  Plot::operator - (const Point & rhs);   // removing a point from a plot
	const Plot & Plot::operator = (const Plot & rhs);   // making lhs equal to rhs as two plots

	void Plot :: BubbleSort();   // advanced sorting function
	bool Plot :: isExist (Point wanted);
	int Plot :: getPos (Point wanted);

	int getSize () const;
	Point* Plot :: getElements () const;
	void setSize (int num);
	void setElements (Point* set);

};

//free func prototypes
ostream &operator << (ostream & output, Plot & graph);  // cout
Plot operator + (Point newpoint, const Plot &  graph);
Plot  operator += (Plot &  lhs, const Plot & rhs);  // adding two plots
Plot  operator -= (Plot &  lhs, const Point & rhs);  // removing rhs point from lhs plot
