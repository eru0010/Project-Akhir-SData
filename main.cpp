// main.cpp
#include "ktp.h"
#include "bioskop.h"

// Definisi global
KTP dataKTP;

void jalankanSistem(KTP& ktpUser) {
    // Inisialisasi 20+ film
    AVLTree daftarFilm;
    Film films[] = {
        {"Avengers: Endgame", "Action", 50000},
        {"Oppenheimer", "Drama", 55000},
        {"Spirited Away", "Animation", 40000},
        {"The Matrix", "Sci-Fi", 50000},
        {"Inception", "Sci-Fi", 52000},
        {"Interstellar", "Sci-Fi", 53000},
        {"Parasite", "Thriller", 48000},
        {"Joker", "Drama", 49000},
        {"Dune", "Sci-Fi", 51000},
        {"No Time to Die", "Action", 50000},
        {"Spider-Man", "Action", 52000},
        {"Black Panther", "Action", 49000},
        {"Titanic", "Romance", 45000},
        {"Avatar", "Sci-Fi", 54000},
        {"Lion King", "Animation", 40000},
        {"Frozen II", "Animation", 41000},
        {"Toy Story 4", "Animation", 42000},
        {"Jurassic World", "Action", 50000},
        {"Top Gun", "Action", 51000},
        {"Barbie", "Comedy", 47000},
        {"Conjuring 3", "Horror", 45000},
        {"Inside Out 2", "Family", 42000}
    };
    int n = sizeof(films) / sizeof(films[0]);
    for (int i = 0; i < n; i++) {
        daftarFilm.insert(films[i]);
    }

    RiwayatSLL riwayat;
    stack<Pemesanan*> stackAntrian;
    queue<Pemesanan*> antrianPembatalan;

    bool logout = false;
    while (true) {
        cls();
        garis();
        cout << "SISTEM PEMESANAN TIKET BIOSKOP\n";
        garis();
        cout << "1. Login Admin\n2. Login User\n3. Keluar\nPilih: ";
        int pilih;
        cin >> pilih;
        cin.ignore(); // clear buffer

        if (pilih == 3) return;

        string pass;
        bool isAdmin = false;
        if (pilih == 1) {
            cout << "Password admin: "; getline(cin, pass);
            if (pass == "admin123") isAdmin = true;
            else { cout << "Gagal login!\n"; cin.get(); continue; }
        } else if (pilih == 2) {
            cout << "Password user: "; getline(cin, pass);
            if (pass == "user123") isAdmin = false;
            else { cout << "Gagal login!\n"; cin.get(); continue; }
        }

        // Input KTP jika user dan belum diisi
        if (!isAdmin) {
            if (!ktpUser.sudahDiisi) {
                cls();
                ktpUser.inputDariUser();
                cin.get();
            }
            cls();
            cout << "Login berhasil sebagai User.\n";
            ktpUser.tampilkan();
            cin.get();
        }

        // Menu utama
        do {
            cls();
            garis();
            cout << "MENU\n";
            garis();
            cout << "1. Lihat Daftar Film (AVL)\n";
            cout << "2. Pesan Tiket\n";
            cout << "3. Riwayat Pemesanan\n";
            if (isAdmin) {
                cout << "4. Kelola Pembatalan (Queue)\n";
                cout << "5. Lihat Antrian (Stack)\n";
                cout << "6. Laporan Sistem\n";
                cout << "7. Uji Huffman + Efisiensi\n";
            }
            cout << "8. Logout\nPilih: ";
            int menu;
            cin >> menu;
            cin.ignore();

            if (menu == 1) {
                daftarFilm.display(); cin.get();
            }
            else if (menu == 2) {
                string nama, judul; int jml;
                cout << "Nama pemesan: "; getline(cin, nama);
                daftarFilm.display();
                cout << "Judul film: "; getline(cin, judul);
                cout << "Jumlah tiket (1-10): "; cin >> jml; cin.ignore();
                if (jml >= 1 && jml <= 10) {
                    Film* f = daftarFilm.search(judul);
                    if (f) {
                        riwayat.tambah(nama, f->judul, jml);
                        Pemesanan* p = new Pemesanan(nama, f->judul, jml);
                        stackAntrian.push(p);
                        cout << "Pemesanan berhasil!\nTotal: Rp " << p->total << "\n";
                    } else cout << "Film tidak ditemukan!\n";
                } else cout << "Jumlah harus antara 1-10!\n";
                cin.get();
            }
            else if (menu == 3) {
                riwayat.tampilkan(); cin.get();
            }
            else if (isAdmin && menu == 4) {
                if (!antrianPembatalan.empty()) {
                    Pemesanan* p = antrianPembatalan.front();
                    antrianPembatalan.pop();
                    cout << "Pembatalan disetujui: " << p->nama << "\n";
                    delete p;
                } else cout << "Tidak ada antrian pembatalan.\n";
                cin.get();
            }
            else if (isAdmin && menu == 5) {
                if (stackAntrian.empty()) cout << "Antrian kosong.\n";
                else {
                    stack<Pemesanan*> temp = stackAntrian;
                    int i = 1;
                    while (!temp.empty()) {
                        cout << i++ << ". " << temp.top()->nama << "\n";
                        temp.pop();
                    }
                }
                cin.get();
            }
            else if (isAdmin && menu == 6) {
                tampilkanLaporan(riwayat); cin.get();
            }
            else if (isAdmin && menu == 7) {
                string teks = "Avengers";
                HuffmanTree huf(teks);
                cout << "Teks uji: " << teks << "\n";
                cout << "Efisiensi Huffman: " << fixed << huf.efisiensi(teks) << "%\n";
                cin.get();
            }
            else if (menu == 8) {
                logout = true;
            }
            else {
                cout << "Pilihan tidak valid.\n"; cin.get();
            }
        } while (!logout);
    }
}

int main() {
    jalankanSistem(dataKTP);
    return 0;
}