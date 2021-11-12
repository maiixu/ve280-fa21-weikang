//
// Created by makersmelx on 2021/6/21.
//
#include "plugin.h"
#include <iostream>
#include <sstream>
#include <regex>

class Simple : public Plugin {
public:
    Simple() : Plugin() {
        this->name = "simple";
        this->author = "makersmelx";
        this->description = "A simple demo";
        this->help = "Type \"simple\" in the program. It will show one message.";
    }

    string response(const string &str) const override {
        return "1+1=2. Plugin is easy. You get it.";
    }

    int matchRule(const string &str) const override {
        return (str == "simple");
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
    return new Simple;
}

extern "C" int *destroy(Plugin *p) {
    delete p;
    return 0;
}