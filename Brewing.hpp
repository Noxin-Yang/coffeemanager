#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;
class Brewing_Guide {
private:
	int id;
	float Water_Temperature;
	float Grind_Size;
	string Coffee_to_Water_Ratio;
	string Dripper;
	string Pouring_Technique;
	string Brew_time;
	static int guide_number;
public:
	Brewing_Guide(float temper, float siz, string rati, string drip, string pourte, string brewt);
	~Brewing_Guide();
	int get_id() const;
	float get_temperature() const;
	float get_size() const;
	string get_ratio() const;
	string get_dripper() const;
	string get_technique() const;
	string get_Brewtime() const;
	void set_temperature(int temper);
	void set_size(float siz);
	void set_ratio(string rati);
	void set_dripper(string drip);
	void set_pourtech(string pourte);
	void set_brewtime(string brewt);




};