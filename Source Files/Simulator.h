#pragma once
#include <list>
#include <string>

#include "Event.h"
#include "Bus.h"
#include "Stop.h"

using namespace std;

class Simulator
{
public:
	Simulator(int bus_stops, int buses, int drive_time, double lambda, int boarding_time, int simulation_time);
    ~Simulator();

public:
	void initialize();
    void logging(string s);
    void snapshot();
    void addEvent(Event e1);
    void event_handler(Event e);
    double getNextPersonTime();
    void simulate();

private:
    // simulation paramters
    int _bus_stops;
    int _buses;
    int _drive_time;
    double _lambda;
    int _boarding_time;
    int _simulation_time;

    list<Event> event_queue;          //Event Queue
    Bus* bus_list;           //The list of buses
    Stop *stop_list;    //The list of Stops
    double systemClock;  //System Clock
};

