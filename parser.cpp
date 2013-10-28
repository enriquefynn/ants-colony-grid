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

#include <fstream>
#include <sstream>
#include <iostream>
#include <string>
#include <unistd.h>
#include <cfloat>
#include "graph.hpp"
#define nOfLines 75882909
#define NGrid 20
#define MAXMETRES 40000
#define NO_NODE SiteId<int>(-1,-1,'_')


using namespace std;


int main(int argc, char* argv[])
{
	double MULTIPLIER = 1;// 0.3048/100.0 //.003048 (feet to meters) for seattle buses, 1000 for cabspotting, 100 for syntetic
	double INTERVAL = 30;
	double TIME_STEP = 3; //3 for seattle buses, 80 for cabspotting, 30000 for syntetic
	int MAX_OPTIONS = 10000;
	
	char opt;
	int testLine;
	bool testFlag = false;
	while ((opt = getopt(argc, argv, "t:hi:I:r:m:")) != -1)
	{
		switch(opt)
		{
			case 't':
				testLine = stoi(optarg);
				break;
			case 'i':
				INTERVAL = stod(optarg);
				break;
			case 'I':
				TIME_STEP = stod(optarg);
				break;
			case 'r':
				MULTIPLIER = stod(optarg);
				break;
			case 'm':
				MAX_OPTIONS = stoi(optarg);
				break;

			case 'h':
			default:
				puts("Receives the input from stdin\n\
					Options:\n\
						\t-t <line>: Begin to test from <line> inclusive till EOF\n\
						\t-i <interval>: Expected interval between log entries\n\
						\t-I <limit>: <limit> * <interval> is the maximum time between entries for it to be considered\n\
						\t-r <multiplier>: Number by which to multiply the x/y values.\n\
						\t-m <maximum options>: consider the top <maximum options> estimates only\
						 ");
				exit(1);
		}
	}

	double xd, yd; //Delta x and delta y.
	int x, y, oldX = 0, oldY = 0; //Normalized x and y.
	int meas;
    	SiteId<int> siteId, oldSiteId = SiteId<int>();

	int tripId, oldTripId = 0; //Current and previous ID
	char d;

	Graph *g = new Graph();

	int line = 0;
	int trips = 0;
	bool newTrip = false, oldNewTrip = false;
	bool bigGap = false, oldBigGap = false;

	string b;
	int time, oldTime = 0;
	getline(cin, b); //Remove first line comment.

	vector<pair<double, SiteId<int> > > *p = new vector<pair<double, SiteId<int> > >();

	cout << "#probability largestErrorProbability fromSite toSite errorSite time tripId entryNum" << endl;
	
	while(cin >> xd >> yd >> b >> tripId >> time >> meas) {
		++line;
		if(line %100 == 0) cerr << "."; //show progress

		x = (int)(xd*MULTIPLIER);
		y = (int)(yd*MULTIPLIER);
		//d = 'x'; 
		d = SiteId<int>::getDirection(x,y,oldX,oldY,4);

		siteId = SiteId<int>(x,y,d);
		newTrip = false;
		bigGap = false;

		if(tripId != oldTripId)
		{
			newTrip = true;
			trips++;
		}
		if (!newTrip && time - oldTime > INTERVAL * TIME_STEP)
		{
			bigGap = true;
		}


		//forecast
		if(trips!= 1)
		{
			if(newTrip && !oldNewTrip)//start a new series in gnuplot file
			{
				if(oldBigGap)	cout << endl; //there is one empty line already
				else cout << endl << endl;    //thre is no empty line
			}

			if(bigGap && !oldBigGap )//skip one entry
			{
				if(!newTrip) cout << endl; //but only if this is not a new trip
			}
		}

		if (!newTrip && !bigGap)
		{
			double probability = 0;
			SiteId<int> nodePredicted = SiteId<int>();

			double smallestError = DBL_MAX;
			double smallestErrorProb = 0;
			SiteId<int> smallestErrorPredicted = SiteId<int>();

			int countOpts = 0;
			for (auto pprob : *p)
			{
				double error = pow(pprob.second.getX()-x,2) + pow(pprob.second.getY()-y,2);	
				if (pprob.second == siteId)
				{

					nodePredicted = pprob.second;
					probability = pprob.first;
				}
				else if(error < smallestError)
				{
					smallestError = error;
					smallestErrorPredicted = pprob.second;
					smallestErrorProb = pprob.first;
				}
				
				//Consider only up to MAX_OPTS responses
				if(++countOpts > MAX_OPTIONS)
					break;
			}
			//If the prediction worked, then probability > 0 and node went from OldSiteId to siteId. The next closest prediction was smallestErrorPrediction. 
			//If the prediction did not work, then probability == 0 and node went from OldSiteId to siteId. The closest prediction to siteId is smallestErrorPredicted. 
			cout << probability << " " << smallestErrorProb << " " << oldSiteId << " " << siteId  << " " << smallestErrorPredicted << " " << time << " " << trips << " " << meas << endl;
		}

		//Map building

		if (testFlag && (line == testLine))
			break;

		if (!newTrip && !bigGap)
		{
			g->insert(siteId, trips, SAMETRIP); 
		}
		else //if(newTrip || bigGap)
		{
			//A big gap does not start a new trip, as the variable trips was not incremented 
			//in this case, but prevents an edge to be added from the current to the new vertex.
			g->insert(siteId, trips, NEWTRIP); 
			if (oldTripId > tripId)
			{
				cerr << "FILE MUST BE ORDERED at line: " << line << '\n'
				<< oldTripId << ' ' << tripId << endl;
				return 3;
			}
		}

		delete p;
		p = g->predictNexts(siteId, 0, 1);
		oldTripId = tripId;
		oldTime = time;
		oldNewTrip = newTrip;
		oldBigGap = bigGap;
		oldX = x;
		oldY = y;
		oldSiteId = siteId;
	}
	if (testFlag)
		while(cin >> tripId >> x >> y)
		{

		}
	//g->print(trips);

	cerr << endl;
	return 0;
}
