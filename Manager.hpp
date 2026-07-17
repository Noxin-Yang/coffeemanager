#pragma once
#include "Brewing.hpp"
#include "CoffeeBean.hpp"
#include <map>
#include <vector>
#include <string>
using namespace std;
class Manager {
private:
    vector<Brewing_Guide> Guides;
    vector<Coffeebean> Beans;
    map<Coffeebean, Brewing_Guide> Combinations;

    Manager() = default;
    ~Manager() = default;
    Manager(const Manager&) = delete;
    Manager& operator=(const Manager&) = delete;

public:
    static Manager& get_manager() {
        static Manager instance;  
        return instance;
    }
    //增
    void add_bean(Coffeebean coffbe);
    void add_guide(Brewing_Guide guid);
    void making_pairs(int i, int k);
    //删
    void delete_bean(int i);
    void delete_guide(int k);
    void delete_pair(Coffeebean coffbe);
    //查
    Coffeebean find_bean(int i);
    Brewing_Guide find_guide(int k);
    void Show_Combination(Coffeebean coffbe);
    //改
    void reset_bean(Coffeebean coffbe,int i);
    void reset_guide(Brewing_Guide guid, int k);
    void reset_pair(string name,Coffeebean coffbe, Brewing_Guide guid);
    //写
    void saveManagerToFile(string filename);
   





  


};