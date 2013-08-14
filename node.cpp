#include <cmath>
#include "node.hpp"

using namespace std;
template <typename T>
char Node<T>::getDirection(Node *n)
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
