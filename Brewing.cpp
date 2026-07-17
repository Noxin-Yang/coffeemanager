#include "Brewing.hpp"


int Brewing_Guide::guide_number = 1;
Brewing_Guide::Brewing_Guide(float temper, float siz, string rati, string drip, string pourte, string brewt) {
	Water_Temperature = temper;
	Grind_Size = siz;
	Coffee_to_Water_Ratio = rati;
	Dripper = drip;
	Pouring_Technique = pourte;
	Brew_time = brewt;
	id = guide_number;
	guide_number++;

}
Brewing_Guide::~Brewing_Guide() = default;
int Brewing_Guide::get_id() const {
	return id;
}
float Brewing_Guide::get_temperature() const {
	return Water_Temperature;
}
float Brewing_Guide::get_size() const {
	return Grind_Size;
}
string Brewing_Guide::get_ratio() const {
	return Coffee_to_Water_Ratio;
}
string Brewing_Guide::get_dripper() const {
	return Dripper;

}
string Brewing_Guide::get_technique() const {
	return Pouring_Technique;

}
string Brewing_Guide::get_Brewtime() const {
	return Brew_time;

}
void Brewing_Guide::set_temperature(int temper) {
	Water_Temperature = temper;

}
void Brewing_Guide::set_size(float siz) {
	Grind_Size = siz;

}
void Brewing_Guide::set_ratio(string rati) {
	Coffee_to_Water_Ratio = rati;

}
void Brewing_Guide::set_dripper(string drip) {
	Dripper = drip;

}
void Brewing_Guide::set_pourtech(string pourte) {
	Pouring_Technique = pourte;

}
void Brewing_Guide::set_brewtime(string brewt) {

	Brew_time = brewt;
}
