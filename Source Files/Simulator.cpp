#include "Simulator.h"
#include <sstream>
#include <iostream>
#include <fstream>
#include <math.h>

#define LOG_FILE		"log.txt"
#define SNAPSHOT_FILE	"snapshot.txt"

Simulator::Simulator(int bus_stops, int buses, int drive_time, double lambda, int boarding_time, int simulation_time) {
	_bus_stops = bus_stops;
	_buses = buses;
	_drive_time = drive_time;
	_lambda = lambda;
	_boarding_time = boarding_time;
	_simulation_time = simulation_time;

	bus_list = NULL;
	stop_list = NULL;
	systemClock = 0;

    srand(25);
}

Simulator::~Simulator() {
}

void Simulator::initialize() {
	bus_list = new Bus[_buses];
	stop_list = new Stop[_bus_stops];
	systemClock = 0;

	for (int i = 0; i < _buses; i++) { //Initializing Buses
		bus_list[i].setName(i + 1);
	}

	for (int i = 0; i < _bus_stops; i++) { //Initializing Stops
		stop_list[i].setName(i + 1);
	}

	for (int i = 0; i < _bus_stops; i++) {
		Event e1(0, 1, 0, i + 1); //Adding events for initializing 1 person in starting at each stop
		addEvent(e1);
	}

	for (int i = 0; i < _buses; i++) {
		Event e1(0, 2, i + 1, (i + 1) * (_bus_stops / _buses)); //Adding events for Bus Initialization
		addEvent(e1);
	}

	for (int i = 0; i < _simulation_time / 3600; i++) {
		Event e1 = Event(3600 * (i + 1), 4, 0, 0); //Adding event for Snapshot
		addEvent(e1);
	}
    // empty files
    ofstream snapFile, logFile;
    snapFile.open(SNAPSHOT_FILE);
    snapFile.close();
    logFile.open(LOG_FILE);
    logFile.close();
}

void Simulator::logging(string s) {
    ofstream logFile;
    logFile.open(LOG_FILE, std::ios_base::app);
    logFile << s;
    logFile.close();
}

void Simulator::snapshot() {
    printf("\nSnapshot");
    ofstream snapFile;
    snapFile.open(SNAPSHOT_FILE, std::ios_base::app);
    ostringstream ss;
    ss << "\n\n\nSnapshot at System Clock: " << systemClock;
    snapFile << ss.str();

    for (int i = 0; i < _bus_stops; i++) {
        ss.str(std::string());
        ss << "\n\n * * * * * * * * * * * * * * * * * * * * Stop: " << (i + 1) << " * * * * * * * * * * * * * * * * * * * * ";
        ss << "\nMinimum Waiting People: " << stop_list[i].getMinNum();
        ss << "\nMaximum Waiting People: " << stop_list[i].getMaxNum();
        ss << "\nTotal people in Queue: " << stop_list[i].getTotalPeople();
        ss << "\nTotal buses that arrived: " << stop_list[i].getTotalBuses();
        ss << "\nPeople still in Queue: " << stop_list[i].getPeople();

        if (stop_list[i].getTotalBuses() == 0) {
            stop_list[i].setTotalBuses(1);
        }
        ss << "\nAverage Waiting People: " << ((stop_list[i].getTotalPeople()) / stop_list[i].getTotalBuses());

        stop_list[i].setMinNum(-1);
        stop_list[i].setMaxNum(-1);
        stop_list[i].setTotalPeople(0);
        stop_list[i].setTotalBuses(0);
        snapFile << ss.str();
    }

    for (int i = 0; i <_buses; i++) {
        ss.str(std::string());
        ss << "\n\n * * * * * * * * * * * * * * * * * * * * Bus: " << (i + 1) << " * * * * * * * * * * * * * * * * * * * * ";
        if (bus_list[i].getPos() == 1) {
            ss << "\nBus is at the stop: " << bus_list[i].getCurrent_stop();
        }

        if (bus_list[i].getPos() == 2) {
            ss << "\nBus is on the way to the stop: " << (bus_list[i].getCurrent_stop() + 1);
        }

        if (bus_list[i].getPos() == 3) {
            ss << "\nBus is in waiting queue at stop: " << (bus_list[i].getCurrent_stop() + 1);
        }
        snapFile << ss.str();
    }
    snapFile.close();
}

void Simulator::addEvent(Event e1) {
	double t = e1.getTime();

	if (event_queue.size() == 0) { //When the queue is empty
		event_queue.push_back(e1);
		return;
	}

	bool added = false;
	list<Event>::iterator it;
	for (it = event_queue.begin(); it != event_queue.end(); ++it) {
		if (t < it->getTime() && it == event_queue.begin()) {  //When the event to be added has the earliest time
			event_queue.insert(it, e1);
			added = true;
			break;
		}
		if (t < it->getTime()) {  //When the event needs to be added somewhere between the queue
			event_queue.insert(it, e1);
			added = true;
			break;
		}
	}
	if (added != true && it == event_queue.end()) { //When the event needs to be added at last
		event_queue.push_back(e1);
	}
}

void Simulator::event_handler(Event e) {
    std::ostringstream ss;
    if (e.getType() == 1) { //Arrival of Person Handler

        ss.str(std::string());
        ss << "\nSystem Clock: " << systemClock << " : Person Arrived at stop: " << e.getStop();
        logging(ss.str());       //Log: Person arrived at stop

        stop_list[e.getStop() - 1].setPeople(stop_list[e.getStop() - 1].getPeople() + 1); //Adding a person to the stop

        stop_list[e.getStop() - 1].setTotalPeople(stop_list[e.getStop() - 1].getTotalPeople() + 1); //Increasing total number of people for that hour

        if (stop_list[e.getStop() - 1].getMinNum() == -1) {  //To initialize
            stop_list[e.getStop() - 1].setMinNum(stop_list[e.getStop() - 1].getPeople());
        }

        if (stop_list[e.getStop() - 1].getMaxNum() == -1) { //To initialize
            stop_list[e.getStop() - 1].setMaxNum(stop_list[e.getStop() - 1].getPeople());
        }

        if (stop_list[e.getStop() - 1].getPeople() < stop_list[e.getStop() - 1].getMinNum()) {  //updating minNum
            stop_list[e.getStop() - 1].setMinNum(stop_list[e.getStop() - 1].getPeople());
        }

        if (stop_list[e.getStop() - 1].getPeople() > stop_list[e.getStop() - 1].getMinNum()) { //updating maxNum
            stop_list[e.getStop() - 1].setMaxNum(stop_list[e.getStop() - 1].getPeople());
        }

        Event e1(systemClock + getNextPersonTime(), 1, 0, e.getStop()); //Generate event for next persons arrival
        addEvent(e1);
    }

    if (e.getType() == 2) { //Arrival of Bus handler
        if (stop_list[e.getStop() - 1].getBusAtStop() == 0) {  //No bus at the stop so enter
            ss.str(std::string());
            ss << "\nSystem Clock: " << systemClock << " : Bus arrived at stop: " << e.getStop();
            logging(ss.str());          //Log: Bus arriving at stop

            bus_list[e.getBus() - 1].setCurrent_stop(e.getStop()); //updating current stop of bus

            bus_list[e.getBus() - 1].setPos(1);  //pos = 1 means bus at stop

            stop_list[e.getStop() - 1].setTotalBuses(stop_list[e.getStop() - 1].getTotalBuses() + 1); //Increasing the number of buses at the stop

            stop_list[e.getStop() - 1].setBusAtStop(1); //Setting to indicate bus at stop


            ss.str(std::string());
            ss << "\nSystem Clock: " << systemClock << " : Number of people at bus stop: " << stop_list[e.getStop() - 1].getPeople();
            logging(ss.str());          //Log: Bus arriving at stop

            if (stop_list[e.getStop() - 1].getPeople() == 0) {  //If the queue at stop is empty
                ss.str(std::string());
                ss << "\nSystem Clock: " << systemClock << " : No people in queue at stop: " << e.getStop();
                logging(ss.str());

                int tempStop = e.getStop(); //Temporary variable to save original event stop

                if (e.getStop() + 1 > 15) {
                    e.setStop(0); //To accomodate going from stop 15 to 1
                }

                Event e1(systemClock + _drive_time, 2, e.getBus(), (e.getStop() + 1)); //generating event for bus departing
                addEvent(e1);

                ss.str(std::string());
                ss << "\nSystem Clock: " << systemClock << " : Bus departing stop for next stop: " << e.getStop() + 1; 
                logging(ss.str());     //Log: Bus Departing
                stop_list[tempStop - 1].setBusAtStop(0); //To indicate no bus at the stop

                bus_list[e.getBus() - 1].setPos(2); //To indicate the bus is in motion

                if (stop_list[tempStop - 1].busesWaiting.size() > 0) { //Check if buses are waiting in queue at stop
                    Bus bus = stop_list[tempStop - 1].busesWaiting.front();
                    stop_list[tempStop - 1].busesWaiting.pop_front();
                    int nextBus = bus.getName(); //Find the name of bus next in line
                    Event e2(systemClock, 2, nextBus, tempStop); //Generate event for bus to arrive at stop
                    addEvent(e2);

                    ss.str(std::string());
                    ss << "\nSystem Clock: " << systemClock << " : Next bus in Queue is arriving at stop: " << tempStop;
                    logging(ss.str());    //Log: bus exits queue and arrives at stop
                }
                else {
                    stop_list[tempStop - 1].setBusAtStop(0); //If queue empty then set the value to 0
                }
            }

            else {
                Event e1(systemClock + _boarding_time, 3, e.getBus(), e.getStop());
                addEvent(e1);
            }
        }

        else { //Already a bus at the stop
            stop_list[e.getStop() - 1].busesWaiting.push_back(bus_list[e.getBus() - 1]);  //Add bus to the Waiting at queue
            ss.str(std::string());
            ss << "\nSystem Clock: " << systemClock << " : Bus in waiting queue at stop: " << e.getStop();
            logging(ss.str());
            bus_list[e.getBus() - 1].setPos(3);
        }
    }

    if (e.getType() == 3) {  //Boarder Event Handler

        ss.str(std::string());
        ss << "\nSystem Clock: " << systemClock << " : Person boarding at stop: " << e.getStop();
        logging(ss.str());      //Log: Person Boarding

        stop_list[e.getStop() - 1].setPeople(stop_list[e.getStop() - 1].getPeople() - 1);  //Reducing people in queue after boarding

        if (stop_list[e.getStop() - 1].getPeople() == 0) {  //If queue becomes empty
            ss.str(std::string());
            ss << "\nSystem Clock: " << systemClock << " : No people in queue at stop: " << e.getStop();
            logging(ss.str());       //Log: Queue empty

            int tempStop = e.getStop(); //Temporary variable to store original event stop
            if (e.getStop() + 1 > 15) {
                e.setStop(0);
            }
            Event e1(systemClock + _drive_time, 2, e.getBus(), (e.getStop() + 1)); //Depart bus to next stop
            addEvent(e1);
            ss.str(std::string());
            ss << "\nSystem Clock: " << systemClock << " : Bus departing stop for next stop: " << (e.getStop() + 1);
            logging(ss.str());

            bus_list[e.getBus() - 1].setPos(2); //To indicate bus is in motion

            stop_list[tempStop - 1].setBusAtStop(0); //To indicate no bus is at stop
            if (stop_list[tempStop - 1].busesWaiting.size() > 0) {  //Check if buses are waiting in queue at stop
                Bus bus = stop_list[tempStop - 1].busesWaiting.front();
                stop_list[tempStop - 1].busesWaiting.pop_front();

                int nextBus = bus.getName(); //Find the name of bus next in line
                Event e2(systemClock, 2, nextBus, tempStop); //Generate event for bus to arrive at stop
                addEvent(e2);
                ss.str(std::string());
                ss << "\nSystem Clock: " << systemClock << " : Next bus in Queue is arriving at stop: " << tempStop;
                logging(ss.str());    //Log: bus exits queue and arrives at stop
            }
            else {
                stop_list[tempStop - 1].setBusAtStop(0);  //If queue empty then set the value to 0
            }
        }
        else {
            ss.str(std::string());
            ss << "\nSystem Clock: " << systemClock << " : Number of people at bus stop: " << stop_list[e.getStop() - 1].getPeople();
            logging(ss.str());    //Log: People at bus stop
            Event e1(systemClock + _boarding_time, 3, e.getBus(), e.getStop()); //Board the next person in queue
            addEvent(e1);
        }
    }

    if (e.getType() == 4) {
        snapshot(); //Take a snapshot
    }
}

double Simulator::getNextPersonTime() {
    int num = rand() % 100000;
    double fnum = ((double)num) / 100000;
    return  -1 * (log(1 - fnum) / _lambda);
}

void Simulator::simulate() {
    initialize();
    logging("Logs \n");

    ofstream snapFile;
    snapFile.open(SNAPSHOT_FILE, std::ios_base::app);
    ostringstream ss;
    ss << "Snapshots \n";
    ss << "Average waiting people = (Total people coming into queue)/(Total buses arrived at the stop)";
    snapFile << ss.str();
    snapFile.close();

    while (systemClock < _simulation_time) {
        Event e1 = event_queue.front();
        event_queue.pop_front();

        systemClock = e1.getTime();


        if (e1.getType() == 1 || e1.getType() == 3) {
            event_handler(e1);
        }

        if (e1.getType() == 2) {
            event_handler(e1);
        }

        if (e1.getType() == 4) {
            event_handler(e1);
        }

        if (event_queue.size() == 0) {
            cout << "Event Queue Empty"; //Queue empty so exit simulation
            break;
        }
    }

    cout << "\n\nSimulation Ended\n";
    logging("\n\n Simulation Ended");
}