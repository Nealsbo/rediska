#include "msgHandler.h"

MsgHandler::MsgHandler() {

}

MsgHandler::~MsgHandler() {

}

int MsgHandler::ParseMessage(const std::string& msg) {
    hasResponse = false;
    std::cout << "INFO: Message handler called\n";
    std::cout << "INFO: Parsing ...\n";
    std::cout << "INFO:     Msg:\n";
    std::cout << "INFO: " << msg << "\n";
    std::cout << "INFO: ---------------\n";

    int first_divider  = msg.find_first_of(' ');
    int second_divider = msg.find_first_of(' ', first_divider+1);

    std::string cmd   = msg.substr(0, first_divider);
    std::string key   = msg.substr(first_divider + 1, second_divider - first_divider - 1);
    std::string value = msg.substr(second_divider + 1);

    std::cout << "INFO: cmd:   |" << cmd << "|\n";
    std::cout << "INFO: key:   |" << key << "|\n";
    std::cout << "INFO: value: |" << value << "|\n";

    if(FindCommand(cmd)) {
        CommandData data;
        data.key = key;
        data.value = value;
        ApplyCommand(cmd, data);

        if(data.IsResponseMsg) {
            hasResponse = true;
            response = data.response;
        }
    }

    return 0;
}

bool MsgHandler::FindCommand(const std::string& cmd) {
    if(CommandMap.find(cmd) != CommandMap.end()) {
        return true;
    }
    return false;
}

void MsgHandler::ApplyCommand(const std::string& cmd, CommandData& data) {
    auto func = CommandMap.find(cmd)->second;
    func(data);
}