//
// Created by makersmelx on 2021/6/21.
//

#include "pluginManager.h"
#include <dirent.h>
#include <dlfcn.h>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <vector>

using namespace std;

int PluginManager::registerPlugin(CreateFunc *cFunc, DestroyFunc *dFunc) {
    unique_ptr<Plugin, std::function<DestroyFunc>> p(cFunc(), dFunc);
    pluginList.push_back(std::move(p));
    return 0;
}

string PluginManager::loadPlugin(const string &message) {
    string buffer;
    stringstream ss(message);
    ss >> buffer;
    ss >> buffer;
    return readDynamicLibrary("./" + buffer) == 0 ? "Loading succeeds" : "Loading fails";
}


string PluginManager::removePlugin(const string &message) {
    string buffer;
    stringstream ss(message);
    ss >> buffer;
    ss >> buffer;
    return removePluginByName(buffer) == 0 ? "Removal succeeds" : "Removal fails";
}

int PluginManager::readDynamicLibrary(const string &filename) {
    // open .so file
    auto plugin = dlopen(filename.c_str(), RTLD_LAZY);
    const char *error = dlerror();
    if (error) {
        cout << error << endl;
        return 1;
    }
    // load the function named "create" in .so
    auto createFunction = (CreateFunc *) dlsym(plugin, "create");
    error = dlerror();
    if (error) {
        cout << error << endl;
        return 1;
    }
    // load the function named "destory" in .so
    auto destroyFunction = (DestroyFunc *) dlsym(plugin, "destroy");
    error = dlerror();
    if (error) {
        cout << error << endl;
        return 1;
    }
    // construct an instance of the handler and add into the plugin list
    this->registerPlugin(createFunction, destroyFunction);
    return 0;
}

int PluginManager::discoverPlugin(const string &dirname) {
    // open the directory
    DIR *dir = opendir(dirname.c_str());
    struct dirent *dirEntry;
    int ret;
    // iterate over the files
    while ((dirEntry = readdir(dir))) {
        string filename = dirEntry->d_name;
        string ext = filename.substr(filename.find_last_of('.') + 1);
        if (ext != "so") {
            continue;
        }
        string absolutePath = string(dirname) + "/" + filename;
        ret = this->readDynamicLibrary(absolutePath);
        if (ret > 0) {
            continue;
        }
    }
    return 0;
}

string PluginManager::applyPlugin(const string &message) {
    for (auto &itr:this->pluginList) {
        if (itr->matchRule(message)) {
            return itr->response(message);
        }
    }
    return "";
}

string PluginManager::printPlugin(const string &message) {
    string buffer;
    stringstream ss(message);
    ss >> buffer;
    ss >> buffer;
    for (auto &itr:this->pluginList) {
        if (itr->name == buffer) {
            return itr->toString();
        }
    }
    return "Not found";
}

int PluginManager::removePluginByName(const string &name) {
    auto itr = find_if(pluginList.begin(), pluginList.end(),
                       [name](unique_ptr<Plugin, std::function<DestroyFunc>> &p) { return p->name == name; });
    // not found
    if (itr == pluginList.end()) {
        return 1;
    }
    pluginList.erase(itr);
    return 0;
}
