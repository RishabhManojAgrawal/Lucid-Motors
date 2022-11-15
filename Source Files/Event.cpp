#include "Event.h"
Event::Event(double time, int type, int bus, int stop) {
    _time = time;
    _type = type;
    _bus = bus;
    _stop = stop;
}


double Event::getTime() {
    return _time;
}

void Event::setTime(double time) {
    _time = time;
}

int Event::getType() {
    return _type;
}

void Event::setType(int type) {
    _type = type;
}

int Event::getBus() {
    return _bus;
}

void Event::setBus(int bus) {
    _bus = bus;
}

int Event::getStop() {
    return _stop;
}

void Event::setStop(int stop) {
    _stop = stop;
}