#pragma once
#ifndef NOTIFICATION_SYSTEM_H
#define NOTIFICATION_SYSTEM_H

#include <string>
#include <iostream>
using namespace std;

class NotificationSystem {
public:
    NotificationSystem(const string& type, const string& status)
        : type(type), status(status) {}

    void sendNotification() const {
        cout << "Отправка уведомления типа " << type << ". Статус: " << status << endl;
    }

    void checkStatus() const {
        cout << "Статус уведомления: " << status << endl;
    }

private:
    string type;
    string status;
};

#endif // NOTIFICATION_SYSTEM_H
