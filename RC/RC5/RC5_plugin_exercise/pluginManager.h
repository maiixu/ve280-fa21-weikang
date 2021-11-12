//
// Created by mike on 2021/6/21.
//

#ifndef LAB6_PLUGINMANAGER_H
#define LAB6_PLUGINMANAGER_H

#include <vector>
#include "plugin.h"
#include <functional>
#include <memory>

class PluginManager {
private:
    // unique_ptr is a kind of pointer
    std::vector<std::unique_ptr<Plugin, std::function<DestroyFunc>>> pluginList;
public:
    /*
     * Load all the dynamic libraries with the function named "create" in a specific directory.
     * Will skip if one dynamic library fails
     * Return 0 if succeeds, other if fails
     */
    int discoverPlugin(const std::string &);

    /*
     * Based on the input message, decide which plugin will be applied to deal with the input
     * Return the reply
     * message: user input from the cli. Should be like "print <plugin name>"
     */
    std::string applyPlugin(const std::string &);

    /*
     * Print the information of a plugin
     * Return the string to print as reply
     */
    std::string printPlugin(const std::string &);

    /*
     * Extract the name of the dynamic library from the input and load it.
     * Return a message that informs whether the loading is success of not
     * message: user input from the cli. Should be like "load <.so filename>"
     */
    std::string loadPlugin(const std::string &);

    /*
     * Extract the name of the plugin from the input and remove the plugin.
     * Return a message that informs whether the removal is success of not
     * message: user input from the cli. Should be like "remove <plugin name>"
     */
    std::string removePlugin(const std::string &);

private:
    /*
     * Load the dynamic library with the function named "create"
     * Return 0 if succeeds, other if fails
     */
    int readDynamicLibrary(const std::string &);

    /*
     * Use the constructor function from the dynamic library. Construct a new instance of the plugin and add into the plugin list
     * Return 0 if succeeds
     */
    int registerPlugin(CreateFunc *, DestroyFunc *);

    /*
     * Remove the plugin by its name
     * Return 0 if succeeds, other value if fails
     */
    int removePluginByName(const std::string &);
};

#endif //LAB6_PLUGINMANAGER_H
