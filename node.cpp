/*
 * ----------------------------------------------------------------------------
 * This software is in the BESOURO BEER-WARE LICENSE and I opted to keep it
 * as a free software, and as so, anyone who find this software useful shall
 * pay me (Enrique Fynn) <fynn@fr4c74l.com> a beer.
 * The license for this software comes in the same directory you found it
 * as LICENSE
 *
 * I prefer Weiss, IPA, or any strong brown ale. But just any beer will do.
 * ----------------------------------------------------------------------------
 */

#include <iostream>
#include <sstream>
#include <cmath>

using namespace std;

template <typename T>
class Node
{
	string id;
	T x;			/* X coord */
	T y;			/* Y coord */
	double avgWait;	/* Average waiting time */
	char direction;	/* Heading direction */
	int localWait;	/* Local time waiting*/
	inline void setID()
	{
		string s;
		stringstream out;
		out << x << '-' << y;
		id = out.str();
	}
	public:
	int lTrip;		/* Last trip */
	int timesPassed;/* Times I got in this node*/
	inline Node(T x, T y, char direction) {this->x = x; this->y = y; setID(); this->direction = direction; avgWait = 0.; localWait = 1; timesPassed = 0;}
	inline Node() {avgWait = 0.; localWait = 1; timesPassed = 0;}
	inline friend bool operator== (const Node<T> &lhs, const Node<T> &rhs){return ((lhs.direction == rhs.direction) && (lhs.x == rhs.x) && (lhs.y == rhs.y));}
	inline friend bool operator!= (const Node<T> &lhs, const Node<T> &rhs) {return !(lhs == rhs);}
	inline friend bool operator< (const Node<T> &lhs, const Node<T> &rhs){ return (lhs.x == rhs.x) ? (lhs.y < rhs.y): (lhs.x < rhs.x);}
	inline friend ostream& operator<< (ostream &out, const Node<T> &node) {out << node.x << '-' << node.y; return out;}
	
	inline double getAvgWait() {return avgWait;}
	inline void wait(){++localWait;}
	
	inline void leave(){avgWait = (avgWait*timesPassed + localWait)/++timesPassed; localWait = 1;}
	inline void enter(int nTrip){localWait = 1; lTrip = nTrip;}

	inline T getX() {return x;}
	inline T getY() {return y;}
	inline string getID() {return id;}
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

