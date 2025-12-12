#include "Game.h"
#include <iostream>
#include <algorithm>
using namespace std;

// Constructor 
Game::Game() {
    root = new Node{"Semua Game", "", true, {}};

    vector<string> daftarGenre = {"Action", "RPG", "Sports", "Horror"};

    for (auto& g : daftarGenre) {
        root->children.push_back(new Node{g, "", true, {}});
    }

    Load();

    bool fileKosong = true;
    for (auto genreNode : root->children) {
        if (!genreNode->children.empty()) {
            fileKosong = false;
            break;
        }
    }

    if(fileKosong) {
        TambahGame("Assassins Creed Unity", "Action", true);
        TambahGame("Dragon Age: Inquisition", "RPG", true);
        TambahGame("F1 25", "Sports", true);
        TambahGame("FIFA 25", "Sports", true);
        TambahGame("Fallout 4", "RPG", true);
        TambahGame("God of War", "Action", true);
        TambahGame("Grand Theft Auto V", "Action", true);
        TambahGame("Kingdom Come: Deliverance", "RPG", true);
        TambahGame("MotoGP 25", "Sports", true);
        TambahGame("NBA 2K25", "Sports", true);
        TambahGame("Outlast", "Horror", true);
        TambahGame("Phasmophobia", "Horror", true);
        TambahGame("Red Dead Redemption 2", "Action", true);
        TambahGame("Resident Evil 7", "Horror", true);
        TambahGame("Rocket League", "Sports", true);
        TambahGame("Silent Hill 2", "Horror", true);
        TambahGame("The Elder Scrolls V: Skyrim", "RPG", true);
        TambahGame("The Evil Within", "Horror", true);
        TambahGame("The Legend of Zelda: Breath of the Wild", "Action", true);
        TambahGame("The Witcher 3: Wild Hunt", "RPG", true);
    }
    
}

// Destructor
Game::~Game() {
    // Tidak wajib
}

// Login Admin 
void Game::LoginAdmin(const string& username, const string& password) {
    if (username == Admin_Username && password == Admin_Password) {
        isAdmin_LogIn = true;
        cout << "Login admin berhasil!\n";
    } else {
        cout << "Username atau password salah!\n";
    }
}

// Fungsi Rekursif 
Node* Game::CariGenreNode(Node* node, const string& genre) {
    if (node->isGenre && node->nama == genre) return node;

    for (auto child : node->children) {
        Node* found = CariGenreNode(child, genre);
        if (found) return found;
    }
    return nullptr;
}

void Game::TampilkanTree(Node* node, int depth) {
    for (int i = 0; i < depth; i++) cout << "  ";
    cout << "- " << node->nama;
    if (!node->isGenre) cout << " (Genre: " << node->genre << ")";
    cout << "\n";

    for (auto child : node->children) {
        TampilkanTree(child, depth + 1);
    }
}

void Game::CariHuruf(Node* node, char huruf) {
    if (!node->isGenre && tolower(node->nama[0]) == huruf) {
        cout << "- " << node->nama << " (" << node->genre << ")\n";
    }
    for (auto child : node->children) {
        CariHuruf(child, huruf);
    }
}

void Game::CariGenre(Node* node, const string& genre) {
    if (!node->isGenre && node->genre == genre) {
        cout << "- " << node->nama << "\n";
    }
    for (auto child : node->children) {
        CariGenre(child, genre);
    }
}

bool Game::HapusGameRec(Node* node, const string& nama) {
    for (int i = 0; i < node->children.size(); i++) {
        if (!node->children[i]->isGenre && node->children[i]->nama == nama) {
            node->children.erase(node->children.begin() + i);
            return true;
        }
        if (HapusGameRec(node->children[i], nama))
            return true;
    }
    return false;
}

// Tambah & Hapus Game 
void Game::TambahGame(const string& nama, const string& genre, bool bypassAdmin) {
    if (!bypassAdmin && !isAdmin_LogIn) {
        cout << "Hanya admin yang dapat menambah game!\n";
        return;
    }

    Node* genreNode = CariGenreNode(root, genre);
    if (!genreNode) {
        cout << "Genre tidak ditemukan!\n";
        return;
    }

    // Cara baru menambah game
    genreNode->children.push_back(new Node{nama, genre, false, {}});

    sort(genreNode->children.begin(), genreNode->children.end(),
        [](Node* a, Node* b) {
            return a->nama < b->nama;
        });

    if (!bypassAdmin)
        cout << "Game '" << nama << "' berhasil ditambahkan!\n";
}


void Game::HapusGame(const string& nama) {
    if (!isAdmin_LogIn) {
        cout << "Hanya admin yang dapat menghapus game!\n";
        return;
    }

    if (HapusGameRec(root, nama)) {
        cout << "Game " + nama + " berhasil dihapus!\n";
    } else {
        cout << "Game tidak ditemukan!\n";
    }
}

// SAVE / LOAD 
void Game::SaveToFile(Node *node, ofstream &file) {
    if (!node) return;
    if (!node->isGenre) {
        file << node->genre << ";" << node->nama << "\n";
    }
    for (auto child : node->children) {
        SaveToFile(child, file);
    }
}

void Game::Save(bool bypassAdmin) {
    if (!isAdmin_LogIn && !bypassAdmin) {
        cout << "Hanya admin yang dapat menyimpan data!\n";
        return;
    }

    ofstream file("game_data.txt");
    if (!file) return;

    SaveToFile(root, file);
    file.close();

    if (!bypassAdmin)  // supaya tidak muncul saat load awal
        cout << "Data game telah tersimpan.\n";
}

void Game::Load() {
    ifstream file("game_data.txt");
    if (!file) return;

    string genre, nama;

    while (true) {
        if (!getline(file, genre, ';')) break;
        if (!getline(file, nama)) break;
        if (genre != "" && nama != "") {
            TambahGame(nama, genre, true);
        }
    }
    file.close();
}

// OUTPUT 
void Game::TampilkanSemuaGame() {
    cout << "\nDAFTAR GAME: \n";
    TampilkanTree(root, 0);
}

void Game::CariGameBerdasarkanGenre(const string& genre) {
    cout << "\nGAME DENGAN GENRE " << genre << ": \n";
    CariGenre(root, genre);
}

void Game::CariGameBerdasarkanHurufAwal(char huruf) {
    huruf = tolower(huruf);
    cout << "\nGAME DENGAN HURUF AWAL '" << huruf << "': \n";
    CariHuruf(root, huruf);
}
