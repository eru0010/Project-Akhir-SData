// ktp.h
#ifndef KTP_H
#define KTP_H

#include <iostream>
#include <string>
using namespace std;

struct KTP {
    string nama;
    string ttl;
    string alamat;
    string agama;
    string pekerjaan;
    bool sudahDiisi = false;

    void inputDariUser() {
        if (sudahDiisi) return;
        cout << "\n--------------------------------------------------\n";
        cout << "MASUKKAN DATA KTP ANDA\n";
        cout << "--------------------------------------------------\n";
        cout << "Nama lengkap     : "; getline(cin, nama);
        cout << "Tempat/Tgl Lahir : "; getline(cin, ttl);
        cout << "Alamat           : "; getline(cin, alamat);
        cout << "Agama            : "; getline(cin, agama);
        cout << "Pekerjaan        : "; getline(cin, pekerjaan);
        sudahDiisi = true;
        cout << "Data KTP berhasil disimpan!\n";
        cout << "--------------------------------------------------\n";
    }

    void tampilkan() const {
        if (!sudahDiisi) {
            cout << "Data KTP belum diisi.\n";
            return;
        }
        cout << "\n--------------------------------------------------\n";
        cout << "DATA KTP PEMILIK AKUN\n";
        cout << "--------------------------------------------------\n";
        cout << "Nama          : " << nama << "\n";
        cout << "Tempat/Tgl Lahir : " << ttl << "\n";
        cout << "Alamat        : " << alamat << "\n";
        cout << "Agama         : " << agama << "\n";
        cout << "Pekerjaan     : " << pekerjaan << "\n";
        cout << "--------------------------------------------------\n";
    }
};

extern KTP dataKTP;

#endif