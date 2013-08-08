#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include <set>
#include <iostream>

#define nOfLines 75882909
#define NGrid 20
#define MAXMETRES 40000

using namespace std;

template <typename T>
class node
{
	T x;						/* X coord */
	T y;						/* Y coord */
	char direction;	/* Heading direction */
	public:
	inline node(double x, double y, char direction) { this->x = x; this->y = y; this->direction = direction;}
	inline friend bool operator== (const node& lhs, const node& rhs){return ((lhs.direction == rhs.direction) && (lhs.x == rhs.x) && (lhs.y == rhs.y));}
	inline friend bool operator< (const node& lhs, const node& rhs){ return (lhs.x == rhs.x) ? (lhs.y < rhs.y): (lhs.x < rhs.x);}
	inline void setX(T x) {this->x = x;}
	inline T getX() {return this->x;}
	inline void setY(T y) {this->y = y;}
	inline T getY() {return this->y;}
	inline void setDirection(char d){this->direction = d;}
	char getDirection(node *n);
};
