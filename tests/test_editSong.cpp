#include "catch.hpp"
#include "MusicLibrary.hpp"
#include <fstream>

void createTestLibrary(const std::string& filename) {
    std::ofstream out(filename);
    out << R"({
        "next_id": 2,
        "songs": [
            {
                "id": 1,
                "title": "Altes Lied",
                "artist": "Alter Kuenstler",
                "album": "Altes Album",
                "year": 2023,
                "favorite": false
            }
        ]
    })";
    out.close();
}

TEST_CASE("Song bearbeiten", "[edit]") {
    std::string testFile = "test_edit.json";
    createTestLibrary(testFile);

    MusicLibrary lib(testFile);
    lib.loadOrCreate();

    auto& data= lib.testDataAccess();
    for (auto& song : data["songs"]) {
        if (song["id"] == 1) {
            song["title"] = "Neuer Title";
            song["artist"] = "Neuer Kuenstler";
            song["album"] = "Neues Album";
            song["year"] = 2025;
            song["favorite"] = true;
        }
    }

    lib.save();

    MusicLibrary lib2(testFile);
    lib2.loadOrCreate();
    auto json = lib2.getLibraryData();

    REQUIRE(json["songs"][0]["title"] == "Neuer Title");
    REQUIRE(json["songs"][0]["artist"] == "Neuer Kuenstler");
    REQUIRE(json["songs"][0]["album"] == "Neues Album");
    REQUIRE(json["songs"][0]["year"] == 2025);
    REQUIRE(json["songs"][0]["favorite"] == true);

    std::remove(testFile.c_str());
}
