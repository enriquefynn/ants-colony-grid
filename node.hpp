#pragma once
#include <iostream>

using namespace std;

template <typename T>
class Node
{
	T x;						/* X coord */
	T y;						/* Y coord */
	char direction;	/* Heading direction */
	public:
	inline Node(T x, T y, char direction) { this->x = x; this->y = y; this->direction = direction;}
	inline Node() {}
	inline friend bool operator== (const Node& lhs, const Node& rhs){return ((lhs.direction == rhs.direction) && (lhs.x == rhs.x) && (lhs.y == rhs.y));}
	inline friend bool operator< (const Node& lhs, const Node& rhs){ return (lhs.x == rhs.x) ? (lhs.y < rhs.y): (lhs.x < rhs.x);}
	inline void setX(T x) {this->x = x;}
	inline T getX() {return this->x;}
	inline void setY(T y) {this->y = y;}
	inline T getY() {return this->y;}
	inline void setDirection(char d){this->direction = d;}
	char getDirection(Node *n);
};

