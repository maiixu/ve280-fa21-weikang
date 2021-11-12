#include <iostream>
#include <regex>
#include "plugin.h"
#include "pluginManager.h"
#include "prompt.h"

using namespace std;

int main(int argc, char **argv) {
    if (argc < 2) {
        cout << "Missing the directory for plugins." << endl;
        exit(1);
    }
    cout << WELCOME << endl;
    PluginManager pm = PluginManager();
    pm.discoverPlugin(argv[1]);
    while (true) {
        cout << "dadsh > ";
        string message, reply;
        getline(cin, message);
        if (message == "exit") {
            break;
        } else if (regex_match(message, regex("^print\\s+\\S+$"))) {
            reply = pm.printPlugin(message);
        } else if (regex_match(message, regex("^load\\s+\\S+$"))) {
            reply = pm.loadPlugin(message);
        } else if (regex_match(message, regex("^remove\\s+\\S+$"))) {
            reply = pm.removePlugin(message);
        } else {
            reply = pm.applyPlugin(message);
        }
        if (reply.empty()) {
            reply = message;
        }
        cout << reply << endl;
    }
}
