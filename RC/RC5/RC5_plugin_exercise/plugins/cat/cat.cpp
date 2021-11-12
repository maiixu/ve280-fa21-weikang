//
// Created by makersmelx on 2021/6/21.
//
#include "plugin.h"
#include <iostream>
#include <sstream>
#include <regex>
#include <unistd.h>
#include <sys/wait.h>

class Cat : public Plugin {
public:
    Cat() : Plugin() {
        this->name = "cat";
        this->author = "makersmelx";
        this->description = "Have some nyan cats in your terminal";
        this->help = "Usage: cat <seconds>\n\tseconds: the time (sec) that the nyan cat will appear";
    }

    string response(const string &str) const override {
        stringstream ss(str);
        string buffer;
        int time;
        ss >> buffer >> time;
        int pid;
        pid = fork();
        if (pid < 0) {
            cout << "Nyan is not here. Try later..." << endl;
        } else if (pid == 0) {
            // child process
            execl("plugins/cat/nyan", "nyan", NULL);
            exit(0);
        } else {
            // parent process
            sleep(time);
            kill(pid, SIGTERM);
        }
        // the program changes the background of the terminal. Need to get it back.
        system("clear");
        system("tput reset");
        return "Nyan....Next please.";
    }

    int matchRule(const string &str) const override {
        std::regex re("^(cat)(\\s)+[0-9]+$");
        return regex_match(str.begin(), str.end(), re);
    }

    string toString() const override {
        string output = "Name: " + this->name + "\n"
                        + "Author: " + this->author + "\n"
                        + "Description: " + this->description + "\n"
                        + "Help: " + this->help;
        return output;
    }
};

extern "C" Plugin *create() {
    return new Cat();
}

extern "C" int *destroy(Plugin *p) {
    delete p;
    return 0;
}