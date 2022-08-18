#include <iostream>
#include <string>
#include <list>
#include <chrono>
#include <deque>
#include <vector>

#include <fiff/tag.hpp>
#include <fiff/input.hpp>
#include <fiff/output.cpp>
#include <fiff/formatting.hpp>

#include <core/stringmanip.hpp>

#include <utils/commandlineinput.hpp>

#include "color.h"

void processUserCommand(const std::string& command);

void load(const std::string& command);
void show(const std::string& command);
void list(const std::string& command);
void edit(const std::string& command);
void create(const std::string& command);
void copy(const std::string& command);
void remove(const std::string& command);
void close(const std::string& command);
void exit(const std::string& command);

struct LogEntry{
    std::chrono::time_point<std::chrono::system_clock> time;
    std::string user_command;
    std::string result;
};

struct tag_node{
    std::vector<int> id;
    Fiff::Tag* tag;
};

struct FiffSource{
    std::string name;
    std::string path;
    Endian::Absolute endianness;

    std::list<tag_node> tags;

    void printTags(unsigned int detail, const std::vector<int>& id_match = {});
    void printBlocks();
    void printMatching();
    void indexNodes();

    friend std::ostream& operator<<(std::ostream& os, const FiffSource& dt);
};

std::ostream& operator<<(std::ostream& os, const FiffSource& fs)
{
    os << "Name: " << fs.name << "\n";
    os << "Path: " << fs.path << "\n";
    os << "Endian: ";
    if(fs.endianness == Endian::Absolute::big) {
        os << "big";
    } else if (fs.endianness == Endian::Absolute::little){
        os << "little";
    } else {
        os << "unknown";
    }
    return os;
}

std::list<LogEntry> activity_log;
std::vector<FiffSource*> fiff_sources;
bool continue_running = true;

int main(int argc, char* argv[])
{
    (void)argc;
    (void)argv;

    

    while(continue_running){
        std::string cmd;
        std::cout << "<<< ";
        std::getline(std::cin, cmd);
        std::cout << "Command: " << cmd << "\n";
        processUserCommand(cmd);
    }

    return 0;
}

void processUserCommand(const std::string& command)
{
    auto index = command.find(' ');
    std::string cmd = command.substr(0, index);

    if(cmd == "list"){
        list(command.substr(index + 1));
    } else if(cmd == "load"){
        load(command.substr(index + 1));
    } else if(cmd == "show"){
        show(command.substr(index + 1));
    } else if(cmd == "exit" || cmd == "quit"){
        exit(command.substr(index + 1));
    }
}

void load(const std::string& command)
{
    std::cout << "Load from file: " << command << "\n";

    auto inFile = Fiff::Input::fromFile(command);

    FiffSource* source = new FiffSource;

    while(!inFile.atEnd()){
        tag_node node;
        node.tag = new Fiff::Tag;

        *(node.tag) = inFile.getTag();
        source->tags.push_back(node);
    }

    source->name = command;
    source->path = command;
    source->endianness = inFile.getEndianess();
    source->indexNodes();

    fiff_sources.push_back(source);
}

void show(const std::string& command)
{
    (void)command;
    
    auto index = command.find(' ');
    std::string cmd = command.substr(0, index);
    std::string rest = command.substr(index + 1);

    unsigned int detail = INT_MAX;
    std::vector<int> match;
 
    if(cmd == "detail" && Core::StringManipulation::isNumber(rest)){
        detail = std::stoi(rest);
    } else if(cmd == "match") {
        auto vec = Core::StringManipulation::getVectorFrom<int>(rest, '.');
        for(auto& element : vec){
            match.push_back(element);
        }
    }

    if (cmd == "blocks"){
        for(auto& source : fiff_sources){
            source->printBlocks();
        }
    } else {
        for(auto& source : fiff_sources){
            source->printTags(detail, match);
        }
    }
}

void list(const std::string& command)
{
    (void)command;
    auto size = fiff_sources.size();
    std::cout << "You have " << size;

    if(size == 1)
        std::cout << " file";
    else
        std::cout << " files";

    std::cout << " open.\n";

    if(size){
        std::cout << "\n----------\n";
        for(auto* element : fiff_sources){
            std::cout << *element << "\n----------\n";
        }
    }
}

void edit(const std::string& command)
{
    (void)command;
}

void create(const std::string& command)
{
    (void)command;

}

void copy(const std::string& command)
{
    (void)command;

}

void remove(const std::string& command)
{
    (void)command;

}

void close(const std::string& command)
{
    (void)command;

}

void exit(const std::string& command)
{
    (void)command;
    continue_running = false;
}

void FiffSource::indexNodes()
{
    std::deque<int> index_stack;
    index_stack.push_back(0);

    for(auto& node : tags){
        index_stack.back() += 1;
        if(node.tag->kind == Fiff::Kind::block_start){
            index_stack.push_back(1);
        }
        for(auto index : index_stack){
            node.id.push_back(index);
        }
        if (node.tag->kind == Fiff::Kind::block_end){
            index_stack.pop_back();
        }
    }
}

void FiffSource::printTags(unsigned int detail, const std::vector<int>& id_match)
{
    std::string indent = "  ";

    for(auto& node : this->tags){
        bool print_data = false;
        if(node.tag->kind == Fiff::Kind::block_start || 
        node.tag->kind == Fiff::Kind::block_end){
            print_data = true;
        } else if(detail < (node.id.size()) || id_match.size() > node.id.size()) {
            continue;
        }

        bool not_a_match = false;
        for(size_t i= 0; i < id_match.size(); ++i){
            if (id_match[i] != node.id[i]){
                not_a_match = true;
                break;
            }
        }
        if(not_a_match){
            continue;
        }

        for (size_t i = 0 ; i < node.id.size() - 1; ++i){
            std::cout << indent;
        }
        std::cout << COLOR_YELLOW << "(" << node.id.front();
        for (size_t i = 1; i < node.id.size(); ++i){
            std::cout << "." << node.id.at(i);
        }
        std::cout << ")  " << COLOR_DEFAULT;

        std::cout << Fiff::Formatting::metaDataAsString(*(node.tag));
        if(print_data){
            std::cout << ", " << Fiff::Formatting::dataAsString(*(node.tag));
        }
        std::cout << "\n";
    }
}

void FiffSource::printBlocks()
{
    std::string indent = "  ";

    for(auto& node : this->tags){
        if(node.tag->kind == Fiff::Kind::block_start){
            for (size_t i = 0 ; i < node.id.size() - 2; ++i){
                std::cout << indent;
            }

            std::cout << COLOR_YELLOW << "(" << node.id.front();
            for (size_t i = 1; i < node.id.size() - 1; ++i){
                std::cout << "." << node.id.at(i);
            }
            std::cout << ")  " << COLOR_DEFAULT;

            std::cout << Fiff::Formatting::dataAsString(*(node.tag)) << "\n";
        }
    }
}