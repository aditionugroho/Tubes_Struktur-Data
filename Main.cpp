#include <iostream>
#include <cctype>  // Tambah untuk isalpha
#include "Game.h"
#include "Game.cpp"
using namespace std;

int main() {
    Game game;
    int pilihan;
    string nama, genre;
    string username, password;

    while (true) {
    cout << "\n---Perpustakaan Game---\n";
    cout << "1. Login Admin\n";
    cout << "2. Tampilkan Semua Game\n";
    cout << "3. Cari Game Berdasarkan Huruf Awal\n";
    cout << "4. Cari Game Berdasarkan Genre\n";
    cout << "5. Keluar\n";
    cout << "Pilih menu: ";
    cin >> pilihan;
        if (cin.fail()) {
            cin.clear();             
            cin.ignore(1000, '\n');  
            cout << "Input harus berupa angka 1-5!\n";
            continue;                 
        }
    cin.ignore();

    switch (pilihan) {
    case 1: {
        cout << "Masukkan username: ";
        getline(cin, username);
        cout << "Masukkan password: ";
        getline(cin, password);

        game.LoginAdmin(username, password);

        // Jika login berhasil -> masuk menu admin
        if (game.isAdmin_LogIn) {
            int pilihanAdmin;
            while (true) {
                cout << "\n---Menu Admin---\n";
                cout << "1. Tambah Game\n";
                cout << "2. Simpan Data Game\n";
                cout << "3. Hapus Game\n";
                cout << "4. Kembali\n";
                cout << "Pilih menu: ";
                cin >> pilihanAdmin;
                    if (cin.fail()) {
                        cin.clear();             
                        cin.ignore(1000, '\n');  
                        cout << "Input harus berupa angka 1-5!\n";
                        continue;                 
                    }
                cin.ignore();

                if (pilihanAdmin == 1) {
                    cout << "Masukkan nama game: ";
                    getline(cin, nama);
                    cout << "Masukkan genre(Action/RPG/Sports/Horror): ";
                    getline(cin, genre);
                    game.TambahGame(nama, genre, true); // bypass admin
                }
                else if (pilihanAdmin == 2) {
                    game.Save(true);
                }
                else if (pilihanAdmin == 3) {
                    cout << "Masukkan nama game yang dihapus: ";
                    getline(cin, nama);
                    game.HapusGame(nama);
                }
                else if (pilihanAdmin == 4) {
                    break; // kembali ke menu utama
                }
                else {
                    cout << "Input harus berupa angka 1-4!\n";
                }
            }
        }
        break;
    }

    case 2:
        game.TampilkanSemuaGame();
        break;

    case 3: {
        char huruf;
        cout << "Masukkan huruf awal(A-Z): ";
        cin >> huruf;
        cin.ignore();
        game.CariGameBerdasarkanHurufAwal(huruf);
        break;
    }

    case 4: {
        cout << "\n---Pilih Genre---\n";
        cout << "1. Action\n";
        cout << "2. RPG\n";
        cout << "3. Sports\n";
        cout << "4. Horror\n";
        cout << "Pilih: ";
        int pilihGenre; 
        cin >> pilihGenre;
            if (cin.fail()) {
                cin.clear();             
                cin.ignore(1000, '\n');  
                cout << "Input harus berupa angka 1-4!\n";
                continue;                 
            }
        cin.ignore();
        if (pilihGenre==1)
            game.CariGameBerdasarkanGenre("Action");
        else if (pilihGenre==2)
            game.CariGameBerdasarkanGenre("RPG");  
        else if (pilihGenre==3)
            game.CariGameBerdasarkanGenre("Sports");
        else if (pilihGenre==4)
            game.CariGameBerdasarkanGenre("Horror");
        else
            cout << "Input harus berupa angka 1-4!\n";
        break;
    }

    case 5:
        cout << "Keluar aplikasi...\n";
        return 0;

    default:
        cout << "Input harus berupa angka 1-5!\n";
        }
    }
}

