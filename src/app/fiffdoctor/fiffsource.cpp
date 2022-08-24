#include "fiffsource.hpp"

#include "color.h"

#include <deque>

int FiffSource::id_count = 0;

FiffSource::FiffSource()
:id(++id_count)
{  
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