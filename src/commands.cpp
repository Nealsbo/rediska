#include "msgHandler.h"

int PutCommand(CommandData& data);
int GetCommand(CommandData& data);
int DelCommand(CommandData& data);


std::unordered_map<std::string, FuncHandler> CommandMap {
    {"PUT", PutCommand},
    {"GET", GetCommand},
    {"DEL", DelCommand}
};

int PutCommand(CommandData& data) {
    std::cout << "INFO: Call of PUT command\n";
    return 0;
}

int GetCommand(CommandData& data) {
    std::cout << "INFO: Call of GET command\n";
    return 0;
}

int DelCommand(CommandData& data) {
    std::cout << "INFO: Call of DEL command\n";
    return 0;
}