#include <iostream>
#include <fstream>
#include "json.hpp"
#include "MusicLibrary.hpp"

using json = nlohmann::json;
using namespace std;


nlohmann::json& MusicLibrary::testDataAccess() {
    return libraryData;
}
const nlohmann::json& MusicLibrary::getLibraryData() const {
    return libraryData;
}


MusicLibrary::MusicLibrary(const string& file) : filename(file) {}

void MusicLibrary::loadOrCreate() {
    ifstream inFile(filename);

    if (inFile.is_open()) {
        inFile >> libraryData;
        cout << "Bibliothek geladen.\n";
        inFile.close();

        if (!libraryData.contains("next_id")) {
            libraryData["next_id"] = 1;
        }
    } else {
        cout << "Keine Bibliothek gefunden. Neue Bibliothek wird erstellt.\n";
        libraryData["songs"] = json::array();
        libraryData["next_id"] = 1;
        save();
    }
}

void MusicLibrary::save() {
    ofstream outFile(filename);
    outFile << libraryData.dump(4);
    outFile.close();
    cout << "Bibliothek gespeichert.\n";
}

void MusicLibrary::printLibrary() {
    cout << libraryData.dump(4) << endl;
}

void MusicLibrary::addSong() {
    string title, artist, album; 
    int year;
    int id = libraryData["next_id"];

    cout << "Titel: ";
    getline(cin >> ws, title);

    cout << "Kuenstler: ";
    getline(cin, artist);

    cout << "Album: ";
    getline(cin, album);

    cout << "Erscheinungsjahr: ";
    cin >> year;

    json newSong = {
        {"id", id},
        {"title", title},
        {"artist", artist},
        {"album", album},
        {"year", year}
    };

    libraryData["songs"].push_back(newSong);

    libraryData["next_id"] = id +1;

    save();

    cout << "Song wurde zur Bibliothek hinzugefuegt.\n";
}