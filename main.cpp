#include "Manager.hpp"
#include "Brewing.hpp"
#include "CoffeeBean.hpp"
#include <iostream>
#include <vector>
#include <string>
#include <exception>
#include <filesystem>

using namespace std;

static string read_line(const string& prompt = "") {
    string s;
    if (!prompt.empty()) cout << prompt;
    std::getline(cin, s);
    return s;
}

static int read_int(const string& prompt = "") {
    while (true) {
        string s = read_line(prompt);
        try {
            size_t pos;
            int v = stoi(s, &pos);
            if (pos == s.size()) return v;
        } catch (...) {
        }
        cout << "Please enter a valid integer." << endl;
    }
}

static float read_float(const string& prompt = "") {
    while (true) {
        string s = read_line(prompt);
        try {
            size_t pos;
            float v = stof(s, &pos);
            if (pos == s.size()) return v;
        } catch (...) {
        }
        cout << "Please enter a valid floating-point number." << endl;
    }
}

static filesystem::path resolve_save_path(const string& filename) {
    filesystem::path path(filename);
    if (path.is_absolute()) {
        return path;
    }

    filesystem::path source_dir = filesystem::path(__FILE__).parent_path();
    if (source_dir.empty()) {
        source_dir = filesystem::current_path();
    }
    return source_dir / path;
}

int main() {
    Manager& maner = Manager::get_manager();
    cout << "-----------------------------------------------------------" << endl;
    cout << "---------------Coffeebeans Management System ----------------" << endl;
    cout << "-----------------------------------------------------------" << endl;
    cout << "------------------------- Welcome! ------------------------" << endl;
    cout << "-----------------------------------------------------------" << endl;
    string choice;
    while (true) {
        cout << "Please choose an option:" << endl;
        cout << "1. Add a bean" << endl;
        cout << "2. Add a guide" << endl;
        cout << "3. Remove a bean" << endl;
        cout << "4. Remove a guide" << endl;
        cout << "5. Find a bean" << endl;
        cout << "6. Find a guide" << endl;
        cout << "7. Reset a bean" << endl;
        cout << "8. Reset a guide" << endl;
        cout << "9. Add a pair (by indices)" << endl;
        cout << "10. Make a pair (by indices)" << endl;
        cout << "11. Delete a pair (by bean index)" << endl;
        cout << "12. Reset a pair (by bean name)" << endl;
        cout << "13. Show combination (by bean index)" << endl;
        cout << "14. Save to file" << endl;
        cout << "Q. Quit" << endl;

        choice = read_line("> ");
        if (choice.empty()) continue;
        if (choice == "Q" || choice == "q") break;

        try {
        if (choice == "1") {
            string name = read_line("Name: ");
            string origin = read_line("Origin: ");
            string date = read_line("Roasted date: ");
            string method = read_line("Processing method: ");
            int fcount = read_int("Number of flavors: ");
            vector<string> flavors;
            flavors.reserve(fcount);
            for (int i = 0; i < fcount; ++i) {
                string f = read_line("Flavor " + to_string(i+1) + ": ");
                flavors.push_back(f);
            }
            Coffeebean bean(name, origin, date, method, flavors);
            maner.add_bean(bean);
            cout << "Bean added." << endl;
        } else if (choice == "2") {
            float temp = read_float("Water temperature (float): ");
            float size = read_float("Grind size (float): ");
            string ratio = read_line("Ratio: ");
            string dripper = read_line("Dripper: ");
            string technique = read_line("Pouring technique: ");
            string brewt = read_line("Brew time: ");
            Brewing_Guide guide(temp, size, ratio, dripper, technique, brewt);
            maner.add_guide(guide);
            cout << "Guide added." << endl;
        } else if (choice == "3") {
            int idx = read_int("Bean index: ");
            maner.delete_bean(idx);
            cout << "Bean removed (if index valid)." << endl;
        } else if (choice == "4") {
            int idx = read_int("Guide index: ");
            maner.delete_guide(idx);
            cout << "Guide removed (if index valid)." << endl;
        } else if (choice == "5") {
            int idx = read_int("Bean index: ");
            Coffeebean b = maner.find_bean(idx);
            cout << "Bean: " << b.get_id() << " " << b.get_name() << " " << b.get_origin() << " " << b.get_date() << " " << b.get_method() << " " << b.get_flavor() << endl;
        } else if (choice == "6") {
            int idx = read_int("Guide index: ");
            Brewing_Guide g = maner.find_guide(idx);
            cout << "Guide: " << g.get_id() << " temp=" << g.get_temperature() << " size=" << g.get_size() << " dripper=" << g.get_dripper() << " ratio=" << g.get_ratio() << " time=" << g.get_Brewtime() << " technique=" << g.get_technique() << endl;
        } else if (choice == "7") {
            int idx = read_int("Bean index to reset: ");
            string name = read_line("New name: ");
            string origin = read_line("New origin: ");
            string date = read_line("New date: ");
            string method = read_line("New method: ");
            int fcount = read_int("Number of flavors: ");
            vector<string> flavors; flavors.reserve(fcount);
            for (int i = 0; i < fcount; ++i) { string f = read_line("Flavor " + to_string(i+1) + ": "); flavors.push_back(f); }
            Coffeebean nb(name, origin, date, method, flavors);
            maner.reset_bean(nb, idx);
            cout << "Bean reset." << endl;
        } else if (choice == "8") {
            int idx = read_int("Guide index to reset: ");
            float temp = read_float("Water temperature: ");
            float size = read_float("Grind size: ");
            string ratio = read_line("Ratio: ");
            string dripper = read_line("Dripper: ");
            string technique = read_line("Technique: ");
            string brewt = read_line("Brew time: ");
            Brewing_Guide ng(temp, size, ratio, dripper, technique, brewt);
            maner.reset_guide(ng, idx);
            cout << "Guide reset." << endl;
        } else if (choice == "9" || choice == "10") {
            int bi = read_int("Bean index: ");
            int gi = read_int("Guide index: ");
            maner.making_pairs(bi, gi);
            cout << "Pair created (if indices valid)." << endl;
        } else if (choice == "11") {
            int bi = read_int("Bean index: ");
            Coffeebean b = maner.find_bean(bi);
            maner.delete_pair(b);
            cout << "Pair deleted (if existed)." << endl;
        } else if (choice == "12") {
            string name = read_line("Bean name to replace: ");
            int nbi = read_int("New bean index: ");
            int ngi = read_int("New guide index: ");
            Coffeebean nb = maner.find_bean(nbi);
            Brewing_Guide ng = maner.find_guide(ngi);
            maner.reset_pair(name, nb, ng);
            cout << "Pair reset (if name matched)." << endl;
        } else if (choice == "13") {
            int bi = read_int("Bean index: ");
            Coffeebean b = maner.find_bean(bi);
            maner.Show_Combination(b);
        } else if (choice == "14") {
            string filename = read_line("Filename (default: test.txt): ");
            if (filename.empty()) {
                filename = "test.txt";
            }
            filesystem::path save_path = resolve_save_path(filename);
            maner.saveManagerToFile(save_path.string());
            cout << "Saved to " << filesystem::absolute(save_path) << endl;
        } else {
            cout << "Unknown option." << endl;
        }
        } catch (const exception& ex) {
            cout << "Error: " << ex.what() << endl;
        }
    }
    cout << "Goodbye." << endl;
    return 0;
}
