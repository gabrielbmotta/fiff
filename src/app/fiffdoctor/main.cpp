#include <iostream>
#include <string>
#include <list>
#include <chrono>

#include <fiff/tag.hpp>
#include <fiff/input.hpp>
#include <fiff/output.cpp>
#include <utils/commandlineinput.hpp>

void processUserCommand(const std::string& command);

void load(const std::string& command);
void show(const std::string& command);
void list(const std::string& command);
void edit(const std::string& command);
void create(const std::string& command);
void copy(const std::string& command);
void remove(const std::string& command);
void close(const std::string& command);

void indexTags(FiffSource* source);

struct LogEntry{
    std::chrono::time_point<std::chrono::system_clock> time;
    std::string user_command;
    std::string result;
};

struct tag_node{
    std::string id;
    Fiff::Tag* tag;
};

struct FiffSource{
    std::string name;
    std::list<tag_node> tags;
};

std::list<LogEntry> activity_log;
std::list<FiffSource*> fiff_sources;

int main(int argc, char* argv[])
{
    bool continue_running = true;

    while(continue_running){
        std::string cmd;
        std::cout << "<<< ";
        std::cin >> cmd;
        processUserCommand(cmd);
    }   
}

void processUserCommand(const std::string& command)
{
    auto index = command.find(' ');
    std::string cmd = command.substr(0, index);

    if(cmd == "list"){
        list(command.substr(index + 1));
    }
}

void load(const std::string& command)
{
    auto inFile = Fiff::Input::fromFile(command);

    FiffSource* source = new FiffSource;

    while(!inFile.atEnd()){
        tag_node node;
        node.tag = new Fiff::Tag;

        *(node.tag) = inFile.getTag();
        source->tags.push_back(node);
    }
}

void show(const std::string& command)
{

}

void list(const std::string& command)
{
    auto size = fiff_sources.size();
    std::cout << "You have " << size;

    if(size == 1)
        std::cout << " file ";
    else
        std::cout << " files";

    std::cout << " open";
    
    for(auto element : fiff_sources){
        std::cout << " - " << element->name << "\n";
    }
}

void edit(const std::string& command)
{

}

void create(const std::string& command)
{

}

void copy(const std::string& command)
{

}

void remove(const std::string& command)
{

}

void close(const std::string& command)
{

}

void indexTags(FiffSource* source)
{
    
}
