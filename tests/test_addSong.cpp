#include "catch.hpp"
#include <fstream>
#include <cstdio>
#include "json.hpp"
#include "MusicLibrary.hpp"


TEST_CASE("Ein Song wird erfolgreich hinzugefügt und ID wird erhöht", "[addSong]") {
    std::string testFilename = "test_add_song.json";
    std::remove(testFilename.c_str());

    MusicLibrary lib(testFilename);
    lib.loadOrCreate();

    int currentId = lib.testDataAccess()["next_id"];

    nlohmann::json testSong = {
        {"id", currentId},
        {"title", "Testtitel"},
        {"artist", "Testkuenstler"},
        {"album", "Testalbum"},
        {"year", 2025},
        {"favorite", true}
    };

    lib.testDataAccess()["songs"].push_back(testSong);
    lib.testDataAccess()["next_id"] = currentId + 1;
    lib.save();

    MusicLibrary loaded(testFilename);
    loaded.loadOrCreate();

    auto songs = loaded.getLibraryData()["songs"];          //Befehl getLibraryData wurde mit Hilfe von Ai erarbeitet
    REQUIRE(songs.size() == 1);
    REQUIRE(songs[0]["id"] == 1);
    REQUIRE(loaded.getLibraryData()["next_id"] == 2);

    std::remove(testFilename.c_str());
}
