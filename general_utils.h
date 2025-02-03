#ifndef GENERAL_UTILS_H
#define GENERAL_UTILS_H

#include <string>
#include <vector>
#include <map>
#include <chrono>
#include <sstream>
#include <iomanip>

std::vector<std::string> list_ports();
std::string getTimestamp();
bool isWithinSafeZone(float x, float y, float z);
float extractValue(const std::string& response, const std::string& key);

#endif
