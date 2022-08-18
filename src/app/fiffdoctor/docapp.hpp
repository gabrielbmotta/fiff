#ifndef FIFF_FIFFDOCTOR_DOCAPP_HPP
#define FIFF_FIFFDOCTOR_DOCAPP_HPP

#include "fiffsource.hpp"

#include <string>
#include <map>
#include <chrono>

class DocApp{
public:
    DocApp();

    void run();    

private:
    void processUserInput(const std::string& command);
    
    //Commands
    void load(const std::string& command);
    void show(const std::string& command);
    void list(const std::string& command);
    void edit(const std::string& command);
    void create(const std::string& command);
    void copy(const std::string& command);
    void remove(const std::string& command);
    void close(const std::string& command);
    void exit(const std::string& command);

    typedef void (DocApp::*CmdFunc)(const std::string&);

    std::map<std::string, CmdFunc> _commandFnMap;

    std::vector<FiffSource*> fiff_sources;

    bool _running;
};

#endif

    // struct LogEntry{
    //     std::chrono::time_point<std::chrono::system_clock> time;
    //     std::string user_command;
    //     std::string result;
    // };
    // std::list<LogEntry> activity_log;