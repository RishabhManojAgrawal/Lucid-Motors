#pragma once
class Bus
{
public:
    Bus();
    Bus(int name, int current_stop, int pos);
 
public:
    int getName();
    void setName(int name);

    int getCurrent_stop();
    void setCurrent_stop(int current_stop);

    int getPos();
    void setPos(int pos);

private:
    int _name;
    int _current_stop;

    //pos = 1: Bus at stop
    //pos = 2: Bus on the way
    //pos = 3: Bus in waiting queue
    int _pos;
};

