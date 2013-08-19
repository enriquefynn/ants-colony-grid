#include <iostream>
#include <cmath>

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
	inline friend bool operator== (const Node<T> &lhs, const Node<T> &rhs){return ((lhs.direction == rhs.direction) && (lhs.x == rhs.x) && (lhs.y == rhs.y));}
	inline friend bool operator!= (const Node<T> &lhs, const Node<T> &rhs) {return !(lhs == rhs);}
	inline friend bool operator< (const Node<T> &lhs, const Node<T> &rhs){ return (lhs.x == rhs.x) ? (lhs.y < rhs.y): (lhs.x < rhs.x);}
	inline friend ostream& operator<< (ostream &out, const Node<T> &node) {out << node.x << '-' << node.y; return out;}
	
	inline void setX(T x) {this->x = x;}
	inline T getX() {return this->x;}
	inline void setY(T y) {this->y = y;}
	inline T getY() {return this->y;}
	inline void setDirection(char d){this->direction = d;}
	inline char getDirection(Node *n)
	{
		int angle = atan2(this->y - n->y, this->x - n->x) * 180. / M_PI;
		if ((angle >= 315) && (angle < 45))
			return 'E';
		if ((angle >= 45) && (angle < 135))
			return 'N';
		if ((angle >= 135) && (angle < 225))
			return 'W';
		if ((angle >= 225) && (angle < 315))
			return 'S';
	}
};

