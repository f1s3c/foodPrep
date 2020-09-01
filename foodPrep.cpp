#include <fstream>
#include <iostream>
#include <ctime>
#include <string>

using namespace std;

struct
{
    bool hleb {0};
    bool jogurt {0};
    bool mleko {0};
    int mlekoChoice {0};
    bool jaja {0};

} osnovne;

int readFoodFiles(string fileName, string* mealStr);
void welcome();
void mainCourseRandomize(ostream& file);
void openAppend();
void openNew();
void osnovneNamirnice(ostream& file);
void hlebiKifle(ostream& file);
void lucyChoice(ostream& file);
void randomize(string foodID, string* meal, int count, ostream& file);
void writeToSpisak(string foodID, string data, ostream& file);
void miscItems(ostream& file);
void fileWriteStavke(ostream& file);

#define STAVKE_MAX 20

int main()
{
    // ifstream file("spisak.txt");
    // if (!file) {
    // cerr << "Can't open file." << endl;
    // exit(1);                             
    // }

    cout << "\n\n======================== Welcome :) =========================" << endl;
    welcome();

    cout << "\nTo je to za danas. :)\n";
    
    return 0;
}

int readFoodFiles(string fileName, string* mealStr)
{
    ifstream file(fileName);
    int lines = 0;

    if (file.is_open()) {
        while (getline(file, mealStr[lines]))
            ++lines;
        file.close();
    }

    return lines;
}

void welcome()
{
    bool selection {0};
    cout << "\nJel zelis novi spisak [1], ili da dopises nesto na stari [0]? ";
    cin >> selection;

    if (selection)
        openNew();
    else 
        openAppend();
}

void openAppend()
{
    ofstream file;
    cout << "Otvaram stari." << endl;
    file.open("spisak.txt", ios::app);
    fileWriteStavke(file);
    file.close();
}

void openNew()
{
    ofstream spisakFile;
    cout << "Otvaram novi." << endl;
    spisakFile.open("spisak.txt", ios::out | ios::trunc);
    cout << "\nPisem izabranu hranu u fajl." << endl;
    mainCourseRandomize(spisakFile);
    osnovneNamirnice(spisakFile);
    spisakFile.close();
}

void mainCourseRandomize(ostream& spisakFile)
{
    string glavnoStr[STAVKE_MAX];
    int glavnoLines = readFoodFiles("food/glavno.txt", glavnoStr);
    randomize("Glavno jelo:", glavnoStr, glavnoLines, spisakFile);

    string prilogStr[STAVKE_MAX];
    int prilogLines = readFoodFiles("food/prilog.txt", prilogStr);
    randomize("Prilog:", prilogStr, prilogLines, spisakFile);
    
    string salataStr[STAVKE_MAX];
    int salataLines = readFoodFiles("food/salata.txt", salataStr);
    randomize("Salata:", salataStr, salataLines, spisakFile);

    string voceStr[STAVKE_MAX];
    int voceLines = readFoodFiles("food/voce.txt", voceStr);
    randomize("Voce:", voceStr, voceLines, spisakFile);

    // for (int i=0; i<5; ++i)
    //     cout << glavnoStr[i] << endl;                   // debug info
    // cout << glavnoLines;
}

void randomize(string foodID, string* meal, int count, ostream& spisakFile)
{
    std::srand(std::time(nullptr));
    int mealChoice = std::rand() % count;
    //cout << mealChoice << endl;
    string* foodSelection = meal + mealChoice;
    cout << *foodSelection << endl;

    writeToSpisak(foodID, *foodSelection, spisakFile);
}

void writeToSpisak(string foodID, string data, ostream& file)
{
    static int i = 0;
    if (i == 0)
        file << "============= Za Jelo =============\n" << endl;
    i = 1;

    file << foodID << endl;
    file << "- " << data << "\n" << endl;
}

void osnovneNamirnice(ostream& file)
{
    bool selection {0};
    cout << "\nDa li su potrebne osnove? (Hleb, jogurt, mleko, jaja): ";
    cin >> selection;

    if (selection) {
        file << "======== Osnovne Namirnice ========\n" << endl;

        cout << "Hleb: ";
        cin >> osnovne.hleb;
        if (osnovne.hleb == 1)
            file << "- Hleb" << endl;

        cout << "Jogurt: ";
        cin >> osnovne.jogurt;
            if (osnovne.jogurt == 1)
                file << "- Jogurt" << endl;

        cout << "Mleko: ";
        cin >> osnovne.mleko;

        if (osnovne.mleko) {
            cout << "Obicno [0], alpro [1] ili oba [2]: ";
            cin >> osnovne.mlekoChoice;
                if (osnovne.mlekoChoice == 0)
                    file << "- Obicno Mleko";
                else if (osnovne.mlekoChoice == 1)
                    file << "- Kokosovo ili Bademovo Mleko" << endl;
                else if (osnovne.mlekoChoice == 2)
                    file << "- Obicno + Kokosovo ili Bademovo Mleko" << endl;
        }

        cout << "Jaja: ";
        cin >> osnovne.jaja;
            if (osnovne.jaja == 1)
                file << "- Jaja" << endl;

        file << "\n";
    }

    hlebiKifle(file);
}

void hlebiKifle(ostream& file)
{
    bool selection {0};
    cout << "\nNeki dorucak, hleb i kifle? ";
    cin >> selection;
    
    if (selection) {
        file << "========== Hleb i Kifle ===========\n" << endl;
        fileWriteStavke(file);
    }

    lucyChoice(file);
}

void lucyChoice(ostream& file)
{
    bool selection {0};
    cout << "\nLucy belo meso i sargarepa? ";
    cin >> selection;
    if (selection) {
        file << "============== Lucy ===============\n" << endl;
        file << "Napravi belo meso i sargarepu." << endl;
    }
        
    miscItems(file);
}

void miscItems(ostream& file)
{
    bool selection {0};
    cout << "\nJel zelis da dodas jos nesto? ";
    cin >> selection;

    if (selection) {
        file << "\n======== Dodatne namirnice ========\n" << endl;
        fileWriteStavke(file);
    }
}

void fileWriteStavke(ostream& file)
{
    cout << "\n[0] za izlaz.\n" << endl;
    string data;
    int z=0;
    int i=0;

    while(true) {
        cout << "[" << i+1 << "]. stavka: ";

            if(z == 0)
            cin.ignore();
        z = 1;

        getline(cin, data, '\n');

        if (data == "0") {
            data = ":)";
            break;
        }
        ++i;
        file << "- ";
        file << data << endl;
    }
}