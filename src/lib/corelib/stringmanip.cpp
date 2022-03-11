//
// Created by Gabriel Motta on 3/10/22.
//
#include "core/stringmanip.hpp"

bool Core::StringManipulation::isNumber(const std::string& s)
{
  return !s.empty() && std::find_if(s.begin(),
                                    s.end(), [](unsigned char c) { return !std::isdigit(c); }) == s.end();
}