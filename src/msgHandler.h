#pragma once

#include <iostream>
#include <string>
#include <unordered_map>
#include <functional>


struct CommandData {
    std::string key;
    std::string value;
    bool IsResponseMsg;
    std::string response;
};

typedef std::function<int(CommandData& data)> FuncHandler;

extern std::unordered_map<std::string, FuncHandler> CommandMap;

class MsgHandler {
public:
    MsgHandler();
    ~MsgHandler();

    int ParseMessage(const std::string& msg);

private:
    bool FindCommand(const std::string& cmd);
    void ApplyCommand(const std::string& cmd, CommandData& data);

    bool hasResponse;
    std::string response;
};