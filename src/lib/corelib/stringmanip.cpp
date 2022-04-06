//
// Created by Gabriel Motta on 3/10/22.
//
#include "core/stringmanip.hpp"

bool Core::StringManipulation::isNumber(const std::string& s)
{
  return !s.empty() && std::find_if(s.begin(),
                                    s.end(), [](unsigned char c) { return !std::isdigit(c); }) == s.end();
}

bool Core::StringManipulation::endsWith(const std::string& string, const std::string& suffix)
{
  if(string.length() >= suffix.length())
  {
    if(0 == string.compare(string.length() - suffix.length(), suffix.length(), suffix))
    {
      return true;
    }
  }
  return false;
}

