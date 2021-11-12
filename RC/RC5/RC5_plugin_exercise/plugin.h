//
// Created by makersmelx on 2021/6/21.
//

#ifndef HANDLER_H
#define HANDLER_H

#include "string"

using namespace std;

class Plugin {
public:
    string name;
    string author;
    string description;
    string help;
public:
    /*
     * Decide if this plugin will be used to deal with the input message
     * Return 1 if the input message meets the rule of this plugin, else 0
     * message: the input message
     */
    virtual int matchRule(const string &message) const = 0;

    /*
     * Generate the response message from the input message
     * Return the response message
     * message: the input message
     */
    virtual string response(const string &message) const = 0;

    /*
     * Show the introduction and help/usage of the plugin
     * Return the display message
     */
    virtual string toString() const = 0;

    virtual ~Plugin() = default;
};

typedef Plugin *CreateFunc();

typedef int *DestroyFunc(Plugin *);

#endif //HANDLER_H
