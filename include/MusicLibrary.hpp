#pragma once
#include <string>
#include "json.hpp"

class MusicLibrary {
private:
    nlohmann::json libraryData;
    std::string filename;

public:
    MusicLibrary(const std:: string& file);
    void loadOrCreate();
    void save();
    void printLibrary();
};