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
    std::list<tag_node> tags;

    void indexNodes();
};

std::list<LogEntry> activity_log;
std::vector<FiffSource*> fiff_sources;

int main(int argc, char* argv[])
{
    (void)argc;
    (void)argv;

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
    } else if(cmd == "load"){
        load(command.substr(index + 1));
    } else if(cmd == "show"){
        show(command.substr(index + 1));
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

    source->indexNodes();

    fiff_sources.push_back(source);
}

void show(const std::string& command)
{
    (void)command;
    std::string indent = "  ";
    int indent_count = 0;
    for(auto& source : fiff_sources){
        for(auto& node : source->tags){
            bool print_data = false;
            if(node.tag->kind == Fiff::Kind::block_start){
                ++indent_count;
                print_data = true;
            }
            for (int i = 0 ; i < indent_count ; ++i){
                std::cout << indent;
            }
            if (node.tag->kind == Fiff::Kind::block_end){
                --indent_count;
                print_data = true;
            }
            std::cout << "(" << node.id.front();
            for (size_t i = 1; i < node.id.size(); ++i){
                std::cout << "." << node.id.at(i);
            }
            std::cout << ")   ";
            std::cout << Fiff::Formatting::metaDataAsString(*(node.tag));
            if(print_data){
                std::cout << Fiff::Formatting::dataAsString(*(node.tag));
            }
            std::cout << "\n";
        }
    }
}

void list(const std::string& command)
{
    (void)command;
    auto size = fiff_sources.size();
    std::cout << "You have " << size;

    if(size == 1)
        std::cout << " file ";
    else
        std::cout << " files";

    std::cout << " open.\n";
    
    for(auto element : fiff_sources){
        std::cout << " - " << element->name << "\n";
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

void FiffSource::indexNodes()
{
    std::deque<int> index_stack;
    index_stack.push_back(1);

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