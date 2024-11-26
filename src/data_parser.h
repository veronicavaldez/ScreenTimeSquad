#ifndef DATA_PARSER_H
#define DATA_PARSER_H

#include <string>
#include <vector>
#include "UserSession.h"

std::vector<User> parseTSV(const std::string& filePath);

#endif
