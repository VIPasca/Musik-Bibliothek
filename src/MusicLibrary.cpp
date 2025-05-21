#include <iostream>
#include <fstream>
#include "json.hpp"
#include "MusicLibrary.hpp"

using json = nlohmann::json;
using namespace std;

MusicLibrary::MusicLibrary(const string& file) : filename(file) {}

void MusicLibrary::loadOrCreate() {
    ifstream inFile(filename);

    if (inFile.is_open()) {
        inFile >> libraryData;
        cout << "Bibliothek geladen.\n";
        inFile.close();
    } else {
        cout << "Keine Bibliothek gefunden. Neue Bibliothek wird erstellt.\n";
        libraryData["songs"] = json::array();
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