#include "Bus.h"

Bus::Bus() {
    _name = 0;
    _current_stop = 0;
    _pos = 0;
}

Bus::Bus(int name, int current_stop, int pos) {
    _name = name;
    _current_stop = current_stop;
    _pos = pos;
}

int Bus::getName() {
    return _name;
}

void Bus::setName(int name) {
    _name = name;
}

int Bus::getCurrent_stop() {
    return _current_stop;
}

void Bus::setCurrent_stop(int current_stop) {
    _current_stop = current_stop;
}

int Bus::getPos() {
    return _pos;
}

void Bus::setPos(int pos) {
    _pos = pos;
}