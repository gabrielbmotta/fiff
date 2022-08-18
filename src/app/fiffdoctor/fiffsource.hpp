#ifndef FIFF_FIFFDOCTOR_FIFFSOURCE_HPP
#define FIFF_FIFFDOCTOR_FIFFSOURCE_HPP

#include <fiff/tag.hpp>
#include <fiff/input.hpp>
#include <fiff/output.hpp>
#include <fiff/formatting.hpp>

#include <list>

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

std::ostream& operator<<(std::ostream& os, const FiffSource& fs);

#endif