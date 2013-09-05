#include <iostream>
#include <cmath>

using namespace std;

template <typename T>
class Node
{
	T x;						/* X coord */
	T y;						/* Y coord */
	double avgWait;	/* Average waiting time */
	char direction;	/* Heading direction */
	int localWait;	/* Local time waiting*/
	int timesPassed;/* Times I got in this node*/
	public:
	inline Node(T x, T y, char direction) {this->x = x; this->y = y; this->direction = direction; avgWait = 0.; localWait = 1; timesPassed = 0;}
	inline Node() {avgWait = 0.; localWait = 1; timesPassed = 0;}
	inline friend bool operator== (const Node<T> &lhs, const Node<T> &rhs){return ((lhs.direction == rhs.direction) && (lhs.x == rhs.x) && (lhs.y == rhs.y));}
	inline friend bool operator!= (const Node<T> &lhs, const Node<T> &rhs) {return !(lhs == rhs);}
	inline friend bool operator< (const Node<T> &lhs, const Node<T> &rhs){ return (lhs.x == rhs.x) ? (lhs.y < rhs.y): (lhs.x < rhs.x);}
	inline friend ostream& operator<< (ostream &out, const Node<T> &node) {out << node.x << '-' << node.y; return out;}
	
	inline double getAvgWait() {return avgWait;}
	inline void wait(){++localWait;}
	
	inline void leave(){avgWait = (avgWait*timesPassed + localWait)/++timesPassed; localWait = 1;}
	
	inline void enter(){localWait = 1;}
	
	inline void setX(T x) {this->x = x;}
	inline void setY(T y) {this->y = y;}
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

