#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "MusicLibrary.hpp"
#include <fstream>
#include <cstdio>

TEST_CASE("Bibliothek wird erstllt, wenn keine Datei vorhanden ist", "[loadOrCreate]") {

    std::string testDatei = "testbibliothek.json";

    std::remove(testDatei.c_str());
    MusicLibrary lib(testDatei);
    lib.loadOrCreate();

    std::ifstream inFile(testDatei);
    REQUIRE(inFile.good());

    inFile.close();
    std::remove(testDatei.c_str());
}