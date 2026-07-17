#include <windows.h>
#include "Manager.hpp"
#include <algorithm>
#include <iterator>
#include <iostream>
#include <fstream>
#include <string>
#include <stdexcept>
#include<iomanip>

namespace {
bool is_valid_utf8(const std::string& text) {
	size_t i = 0;
	while (i < text.size()) {
		unsigned char c = static_cast<unsigned char>(text[i]);
		size_t extra = 0;
		if (c <= 0x7F) {
			++i;
			continue;
		} else if ((c & 0xE0) == 0xC0) {
			extra = 1;
		} else if ((c & 0xF0) == 0xE0) {
			extra = 2;
		} else if ((c & 0xF8) == 0xF0) {
			extra = 3;
		} else {
			return false;
		}

		if (i + extra >= text.size()) {
			return false;
		}
		for (size_t j = 1; j <= extra; ++j) {
			unsigned char next = static_cast<unsigned char>(text[i + j]);
			if ((next & 0xC0) != 0x80) {
				return false;
			}
		}
		i += extra + 1;
	}
	return true;
}

std::string to_utf8(const std::string& text) {
	if (text.empty()) {
		return "";
	}
	if (is_valid_utf8(text)) {
		return text;
	}

	int wide_size = MultiByteToWideChar(CP_ACP, 0, text.c_str(), -1, nullptr, 0);
	if (wide_size <= 0) {
		return text;
	}

	std::wstring wide(static_cast<size_t>(wide_size), L'\0');
	MultiByteToWideChar(CP_ACP, 0, text.c_str(), -1, wide.data(), wide_size);

	int utf8_size = WideCharToMultiByte(CP_UTF8, 0, wide.c_str(), -1, nullptr, 0, nullptr, nullptr);
	if (utf8_size <= 0) {
		return text;
	}

	std::string utf8(static_cast<size_t>(utf8_size), '\0');
	WideCharToMultiByte(CP_UTF8, 0, wide.c_str(), -1, utf8.data(), utf8_size, nullptr, nullptr);
	utf8.pop_back();
	return utf8;
}

void writeBean(std::ofstream& ofs, const Coffeebean& bean) {
	ofs << "Bean_id: " << bean.get_id() << "\n"
		<< "Name: " << to_utf8(bean.get_name()) << "\n"
		<< "Roasted_date: " << to_utf8(bean.get_date()) << "\n"
		<< "Origin: " << to_utf8(bean.get_origin()) << "\n"
		<< "Procession: " << to_utf8(bean.get_method()) << "\n"
		<< "Flavor: " << to_utf8(bean.get_flavor()) << "\n\n";
}

void writeGuide(std::ofstream& ofs, const Brewing_Guide& guide) {
	ofs << "Guide_id: " << guide.get_id() << "\n"
		<< "Water_Temperature: " << guide.get_temperature() << "\n"
		<< "Griding_Size: " << guide.get_size() << "\n"
		<< "Dripper: " << to_utf8(guide.get_dripper()) << "\n"
		<< "Coffee_to_Water_Ratio: " << to_utf8(guide.get_ratio()) << "\n"
		<< "Brewing_Time: " << to_utf8(guide.get_Brewtime()) << "\n"
		<< "Brewing_Technique: " << to_utf8(guide.get_technique()) << "\n\n";
}
}
//增

void Manager::add_bean(Coffeebean coffbe) {
	Beans.push_back(coffbe);

}
void Manager::add_guide(Brewing_Guide guid) {
	Guides.push_back(guid);

}
void Manager::making_pairs(int i, int k) {
    if (i < 0 || static_cast<size_t>(i) >= Beans.size()) { throw out_of_range("Bean index is out of range."); }
    if (k < 0 || static_cast<size_t>(k) >= Guides.size()) { throw out_of_range("Guide index is out of range."); }

	Combinations.insert(make_pair(Beans[i], Guides[k]));
}
//删
void Manager::delete_bean(int i) {
    if (i < 0 || static_cast<size_t>(i) >= Beans.size()) { throw out_of_range("Bean index is out of range."); }
	Beans.erase(Beans.begin()+i);

}
void Manager::delete_guide(int k) {
    if (k < 0 || static_cast<size_t>(k) >= Guides.size()) { throw out_of_range("Guide index is out of range."); }
	Guides.erase(Guides.begin() + k);

}
void Manager::delete_pair(Coffeebean coffbe) {
	auto it = Combinations.find(coffbe);
	if (it != Combinations.end()) {
		Combinations.erase(it);
	}

}
//查
Coffeebean Manager::find_bean(int i) {
    if (i < 0 || static_cast<size_t>(i) >= Beans.size()) { throw out_of_range("Bean index is out of range."); }
	return Beans[i];
}
Brewing_Guide Manager::find_guide(int k) {
    if (k < 0 || static_cast<size_t>(k) >= Guides.size()) { throw out_of_range("Guide index is out of range."); }
	return Guides[k];

}
void Manager::Show_Combination(Coffeebean coffbe) {
	cout << "The brewing guide of " << coffbe.get_name() << " is" << endl;
	auto it = Combinations.find(coffbe);
	if (it == Combinations.end()) {
		cout << "No brewing guide found for " << coffbe.get_name() << endl;
		return;
	}
	const Brewing_Guide& guide = it->second;
	cout << "Temperature of the water: " << guide.get_temperature() << endl;
	cout << " Griding size : " << guide.get_size() << endl;
	cout << "Coffee_to_Water_Ratio: " << guide.get_ratio() << endl;
	cout << "Dripper: " << guide.get_dripper() << endl;
	cout << "Brew_time :" << guide.get_Brewtime() << endl;
};
//改
void Manager::reset_bean(Coffeebean coffbe, int i) {
    if (i < 0 || static_cast<size_t>(i) >= Beans.size()) { throw out_of_range("Bean index is out of range."); }

	Beans.at(i) = coffbe;
}
void Manager::reset_guide(Brewing_Guide guid, int k) {
    if (k < 0 || static_cast<size_t>(k) >= Guides.size()) { throw out_of_range("Guide index is out of range."); }
	Guides.at(k) = guid;

}
void Manager::reset_pair(string name, Coffeebean coffbe, Brewing_Guide guid) {
	auto it = find_if(Combinations.begin(), Combinations.end(),
		[&](const auto& p) {
			return p.first.get_name() == name;
		});

	if (it != Combinations.end()) {
		Combinations.erase(it);
		Combinations.insert(make_pair(coffbe, guid));
	}
}
//写
void Manager::saveManagerToFile(std::string filename) {
	std::ofstream ofs(filename, std::ios::binary);
	if (!ofs.is_open()) {
		throw runtime_error("Failed to open file: " + filename);
	}

	ofs << "\xEF\xBB\xBF";

	ofs << "========== Paired Beans ==========\n\n";
	for (auto it = Combinations.begin(); it != Combinations.end(); ++it) {
		writeBean(ofs, it->first);
	}

	ofs << "========== Paired Guides ==========\n\n";
	for (auto it = Combinations.begin(); it != Combinations.end(); ++it) {
		writeGuide(ofs, it->second);
	}

	ofs << "========== All Beans ==========\n\n";
	for (auto it = Beans.begin(); it != Beans.end(); ++it) {
		writeBean(ofs, *it);
	}

	ofs << "========== All Guides ==========\n\n";
	for (auto it = Guides.begin(); it != Guides.end(); ++it) {
		writeGuide(ofs, *it);
	}

	ofs.close();
}

