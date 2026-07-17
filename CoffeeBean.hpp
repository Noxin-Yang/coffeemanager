#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;
class Coffeebean {

private:
	int id;
	string Name;
	string Origin;
	string Roasted_Date;
	string Processing_method;
	vector<string> Flavor;
	static int bean_number;
public:
	Coffeebean(string nm, string ori, string rd, string pm, vector<string>& fl);
	~Coffeebean();
	int get_id() const;
	string get_name() const;
	string get_origin() const;
	string get_date() const;
	string get_method() const;
	string get_flavor() const;
	void set_id(int i);
	void set_origin(string ori);
	void set_date(string rd);
	void set_method(string pm);
	void set_flavor(vector<string>& fl);
	bool operator<(const Coffeebean& other) const;
};