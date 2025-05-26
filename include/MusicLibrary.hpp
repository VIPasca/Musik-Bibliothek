#pragma once
#include <string>
#include "json.hpp"

class MusicLibrary {
private:
    nlohmann::json libraryData;
    std::string filename;

public:
    nlohmann::json& testDataAccess();
    const nlohmann::json& getLibraryData() const;           //Befehl wurde mit Hilfe von Ai erarbeitet
    MusicLibrary(const std:: string& file);
    void loadOrCreate();
    void save();
    void printLibrary();
    void addSong();
    void editSong();
};