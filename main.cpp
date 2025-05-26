#include <iostream>
#include "json.hpp"
#include "MusicLibrary.hpp"

using json = nlohmann::json;
using namespace std;

int main() {
    MusicLibrary lib("musikbibliothek.json");
    lib.loadOrCreate();
    
    int auswahl;

    do {
        cout << "\n==== Musikbibliothek ====\n";
        cout << "1. Bibliothek anzeigen\n";
        cout << "2. Song hinzufuegen\n";
        cout << "3. Song bearbeiten\n";
        cout << "0. Beenden\n";
        cin >> auswahl;

        switch (auswahl) {
            case 1:
                lib.printLibrary();
                break;
            case 2:
                lib.addSong();
                break;
            case 3:
                lib.editSong();
                break;
            case 0:
                cout << "Programm beendet.\n";
                break;
            default:
                cout << "Ungültige Eingabe.\n";
        }
    } while (auswahl !=0);

    return 0;
    
}