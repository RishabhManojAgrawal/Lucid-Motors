#include "Stop.h"

Stop::Stop() {
	_name = 0;
	_people = 0;
	_bus_at_stop = 0;
	_totalBuses = 0;
	_totalPeople = 0;
	_minNum = 0;
	_maxNum = 0;
}

Stop::Stop(int name, int people) {
	_name = name;
	_people = people;
	_bus_at_stop = 0;
	_totalBuses = 0;
	_totalPeople = 0;
	_minNum = 0;
	_maxNum = 0;
}

int Stop::getName() {
	return _name;
}

void Stop::setName(int name) {
	_name = name;
}

int Stop::getPeople() {
	return _people;
}

void Stop::setPeople(int people) {
	_people = people;
}

int Stop::getBusAtStop() {
	return _bus_at_stop;
}

void Stop::setBusAtStop(int bus_at_stop) {
	_bus_at_stop = bus_at_stop;
}

int Stop::getMinNum() {
	return _minNum;
}

void Stop::setMinNum(int minNum) {
	_minNum = minNum;
}

int Stop::getMaxNum() {
	return _maxNum;
}

void Stop::setMaxNum(int maxNum) {
	_maxNum = maxNum;
}

int Stop::getTotalPeople() {
	return _totalPeople;
}

void Stop::setTotalPeople(int totalPeople) {
	_totalPeople = totalPeople;
}

int Stop::getTotalBuses() {
	return _totalBuses;
}

void Stop::setTotalBuses(int totalBuses) {
	_totalBuses = totalBuses;
}