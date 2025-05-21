#include <iostream>
#include "json.hpp"
#include "MusicLibrary.hpp"

using json = nlohmann::json;

int main() {
    MusicLibrary lib("musikbibliothek.json");
    lib.loadOrCreate();
    lib.printLibrary();
    return 0;
    
}