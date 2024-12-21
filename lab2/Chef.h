#pragma once
#ifndef CHEF_H
#define CHEF_H

#include <iostream>
#include <string>
using namespace std;

class Chef {
public:
    Chef(const string& им€, int опыт, const string& уровеньЌавыков)
        : им€(им€), опыт(опыт), уровеньЌавыков(уровеньЌавыков) {}

    void готовить() {
        cout << им€ << " готовит с " << опыт << " летним опытом." << endl;
    }

    void тренировка(const string& новыйЌавык) {
        уровеньЌавыков = новыйЌавык;
        cout << им€ << " освоил новый навык: " << уровеньЌавыков << endl;
    }

    void улучшениеЌавыков() {
        опыт += 1;
        cout << им€ << " улучшил свои навыки! “еперь у него " << опыт << " лет опыта." << endl;
    }

private:
    string им€;
    int опыт;
    string уровеньЌавыков;
};

#endif // CHEF_H
