#include <iostream>
#include <fstream>
#include "json.hpp"
#include "MusicLibrary.hpp"

using json = nlohmann::json;
using namespace std;


nlohmann::json& MusicLibrary::testDataAccess() {                        //Befehl wurde mit Hilfe von Ai erarbeitet
    return libraryData;
}
const nlohmann::json& MusicLibrary::getLibraryData() const {            //Befehl wurde mit Hilfe von Ai erarbeitet
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

void MusicLibrary::editSong() {
    string eingabe;
    cout << "Gib die ID oder den Titel des Songs ein, welcher bearbeitet werden soll: ";
    cin.ignore();
    getline(cin, eingabe);

    bool found = false;

    for (auto& song : libraryData["songs"]) {
        if (to_string(song["id"].get<int>()) == eingabe || song["title"] == eingabe) {
            found = true;
            string title, artist, album;
            string yearStr;

            cout << "Neuer Titel (" << song["title"] << "): ";
            getline(cin, title);
            if (!title.empty()) song["title"] = title;
            
            cout << "Neuer Künstler (" << song["artist"] << "): ";
            getline(cin, artist);
            if (!artist.empty()) song["artist"] = artist;

            cout << "Neues Album (" << song["album"] << "): ";
            getline(cin, album);
            if (!album.empty()) song["album"] = album;

            cout << "Neues Erscheinungsjahr (" << song["year"] << "): ";
            getline(cin, yearStr);
            if (!yearStr.empty()) song["year"] = stoi(yearStr);

            save();
            cout << "Song wurde aktualisiert.\n";
            break;
        }
    }

    if (!found) {
        cout << "Kein passender Song gefunden.\n";
    }
}

void MusicLibrary::addPodcast() {
    string title, artist; 
    int id_Podcast = libraryData["next_id_Podcast"];

    cout << "Titel: ";
    getline(cin >> ws, title);

    cout << "Kuenstler: ";
    getline(cin, artist);

    json newPodcast = {
        {"id_Podcast", id_Podcast},
        {"title", title},
        {"artist", artist},
    };

    libraryData["songs"].push_back(newPodcast);

    libraryData["next_id_Podcast"] = id_Podcast +1;

    save();

    cout << "Podcast wurde zur Bibliothek hinzugefuegt.\n";
}

void MusicLibrary::searchSong() {
    string searchcommand;
    cout << "Welcher Song soll gesucht werden?\n";
    cin.ignore();
    getline(cin, searchcommand);

    bool found = false;

    for (const auto& song : libraryData["songs"]) {
        string title = song["title"];
        if (title.find(searchcommand) != string::npos) {
            cout << "Gefundener Song:\n";
            cout << "Titel: " << song["title"] << "\n";
            cout << "Kuenstler: " << song["artist"] << "\n";
            cout << "ID: " << song["id"] << "\n";
            found = true;
        }
    }

    if (!found){
        cout << "Kein Song gefunden.\n";
    }
}