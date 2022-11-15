// Simulator.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "Simulator.h"

int main()
{
	int bus_stops = 10;
	int buses = 5;
	int drive_time = 300;
	double lambda = 0.083;
	int boarding_time = 10;
	int simulation_time = 28800;

	Simulator simulator(bus_stops, buses, drive_time, lambda, boarding_time, simulation_time);
	cout << "Simulation started..." << endl;
	cout << "It may take a long time. Please wait..." << endl;
	simulator.simulate();
	cout << "Terminate.." << endl;
}

