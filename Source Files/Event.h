#pragma once
class Event
{
public:
    Event(double time, int type, int bus, int stop);

public:
    double getTime();
    void setTime(double time);

    int getType();
    void setType(int type);

    int getBus();
    void setBus(int bus);

    int getStop();
    void setStop(int stop);

private:
    double _time;     //Time of event occuring

    //type 1 = Arrival of person event
    //type 2 = Arrival of Bus event
    //type 3 = Boarding of person event
    //type 4 = Snapshot event
    int _type;        //Type of event: Person, Arrival, Boarder 
    int _bus;         //Bus number associated with the event
    int _stop;        //Stop name associated with the event
};

