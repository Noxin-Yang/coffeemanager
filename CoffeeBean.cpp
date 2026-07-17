#include "CoffeeBean.hpp"
#include <sstream>
using namespace std;
int Coffeebean::bean_number = 1;

Coffeebean::Coffeebean( string nm, string ori, string rd, string pm, vector<string>& fl) {
	Name = nm;
	Origin = ori;
	Roasted_Date = rd;
	Processing_method = pm;
	Flavor = fl;
	id = bean_number;
	bean_number++;
}
Coffeebean::~Coffeebean() = default;
int Coffeebean::get_id() const {
	return id;
}
string Coffeebean::get_name() const {
	return Name;
}
string Coffeebean::get_origin() const {
	return Origin;
}
string Coffeebean::get_date() const {
	return Roasted_Date;
}
string Coffeebean::get_method() const {
	return Processing_method;
}
string Coffeebean::get_flavor() const {
	std::ostringstream oss;
	for (size_t i = 0; i < Flavor.size(); ++i) {
		if (i) oss << ' ';
		oss << Flavor[i];
	}
	return oss.str();
}

bool Coffeebean::operator<(const Coffeebean& other) const {
	return id < other.id;
}

void Coffeebean::set_id(int i) {
	id = i;
}
void Coffeebean::set_origin(string ori) {
	Origin = ori;
}
void Coffeebean::set_date(string rd) {
	Roasted_Date = rd;
}
void Coffeebean::set_method(string pm) {
	Processing_method = pm;
}
void Coffeebean::set_flavor(vector<string>& fl) {
	Flavor = fl;
}
