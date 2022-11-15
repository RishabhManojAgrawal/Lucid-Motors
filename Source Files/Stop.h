#pragma once

#include "Bus.h"
#include <list>

using namespace std;

class Stop
{
public:
    Stop();
    Stop(int name, int people);

public:
    int getName();
    void setName(int name);

    int getPeople();
    void setPeople(int people);

    int getBusAtStop();
    void setBusAtStop(int bus_at_stop);

    int getMinNum();
    void setMinNum(int minNum);

    int getMaxNum();
    void setMaxNum(int maxNum);

    int getTotalPeople();
    void setTotalPeople(int totalPeople);

    int getTotalBuses();
    void setTotalBuses(int totalBuses);

public:
    list<Bus> busesWaiting;          //Queue of buses waiting at stop

private:
    int _name;
    int _people;
    int _bus_at_stop;         //If there is a bus at the stop
    int _minNum;              //minimum number of people in queue
    int _maxNum;              //Maximum number of people in queue
    int _totalPeople;         //Total people enetering the queue in an hour
    int _totalBuses;          //Total buses entering the queue in an hour
};

