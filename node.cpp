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

//TODO: Implement a config to store variables
const double sigma = 0.4;
using namespace std;

template <typename T>
class SiteId
{

	T x;		/* X coord */
	T y;		/* Y coord */
	char direction;	/* Heading direction */
	string myId = "";
	bool valid;

    public:
    inline SiteId()
	{
        	valid = false;
		stringstream out;
		out << "invalid";
		myId = out.str();
	}

	inline SiteId(T x, T y, char dir )
	{
        	valid = true;

		this->x = x;
		this->y = y;
		this->direction = dir;

		string s;
		stringstream out;
		out << x << ' ' << y << ' ' << dir;
		myId = out.str();
	}

   	inline bool isValid() const {return valid;}
	inline T getX() const {return x;}
	inline T getY() const {return y;}
	inline char getDirection() const {return direction;}
	inline string asStr() const {return myId;}

	inline friend bool operator== (const SiteId<T> &lhs, const SiteId<T> &rhs){return ((lhs.direction == rhs.direction) && (lhs.x == rhs.x) && (lhs.y == rhs.y));}
	inline friend bool operator!= (const SiteId<T> &lhs, const SiteId<T> &rhs) {return !(lhs == rhs);}
	inline friend bool operator< (const SiteId<T> &lhs, const SiteId<T> &rhs){ return (lhs.x == rhs.x) ? (lhs.y < rhs.y): (lhs.x < rhs.x);}
	inline friend ostream& operator<< (ostream &out, const SiteId<T> &id) {out << id.x << ' ' << id.y << ' ' << id.direction; return out;}

	inline static char getDirection(T x, T y, T ox, T oy, int numDir)
	{
        //TODO: use 360/numDir to find out how many directions there are.
		int angle = atan2(y - oy, ox - ox) * 180. / M_PI;
		if ((angle >= 315) || (angle < 45))
			return 'E';
		if ((angle >= 45) && (angle < 135))
			return 'N';
		if ((angle >= 135) && (angle < 225))
			return 'W';
		if ((angle >= 225) && (angle < 315))
			return 'S';
        return '?';
	}
};

template <typename T>
struct SiteIdHash: public std::unary_function<SiteId<T>, size_t> {
        size_t operator()(const SiteId<T> &k) const{
        size_t h1 = std::hash<T>()(k.getX());
        size_t h2 = std::hash<T>()(k.getY());
        size_t h3 = std::hash<char>()(k.getDirection());
        return (h1 ^ (h2 << 1)) ^ h3;
    }
};

template<typename T>
struct SiteIdEqual : public std::unary_function<SiteId<T>, bool> {

   bool operator()(const SiteId<T>& left, const SiteId<T>& right) const
   {
      return left == right;
   }
};


template <typename T>
class Node
{
	double avgWait = 0.;	/* Average waiting time */
	int localWait = 1;		/* Local time waiting */
	T siteId;
	int lastTrip;			/* Last trip ID */
	public:
	double timeCoef = 1;/* Times I got in this node*/
	inline Node(T id, int tripID) {this->siteId = id; lastTrip = tripID;}
	inline Node()     {}
	inline T getID() {return siteId;}

	inline double getAvgWait() {return avgWait;}
	inline void wait(){++localWait;}

	inline void leave()
	{
		avgWait = (1. - sigma)*avgWait + sigma*localWait; 
		localWait = 1; 
	}

	inline void enter(int tripID)
	{
		int deltaTrip = tripID - lastTrip;
		localWait = 1; 
		timeCoef = timeCoef*pow(1. - sigma, deltaTrip) + sigma;
		lastTrip = tripID;
	}
	
	/* Only look to timeCoef */
	inline void visit(int tripID)
	{
		timeCoef = timeCoef*pow(1. - sigma, tripID - lastTrip);
		lastTrip = tripID;
	}
	inline friend ostream& operator<< (ostream &out, const Node<T> &node) {out << node.siteId; return out;}
};

