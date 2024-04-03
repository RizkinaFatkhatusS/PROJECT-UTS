#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

const int MAX_PINJAMAN = 5;

struct buku {
    int nomor;
    string nama;
    string pengarang;
    int tahun;
    string penerbit;
    buku* next;
    buku* prev;
};

struct peminjaman {
    string nama_peminjam;
    int nomor_buku;
    string nama_buku;
    string tanggal_peminjam;
    peminjaman* next;
};

//menu staff admin 
void printMenuStaffAdmin() {
    cout << "============================================"<<endl;
    cout << "|                MENU ADMIN                |"<<endl;
    cout << "============================================"<<endl;
    cout << "| 1. Input Data Buku                       |"<<endl;
    cout << "| 2. Tampilkan Data Buku                   |"<<endl;
    cout << "| 3. Edit Data Buku                        |"<<endl;
    cout << "| 4. Hapus Data Buku                       |"<<endl;
    cout << "| 5. Tampilkan Data Peminjaman             |"<<endl;
    cout << "| 6. Kebali ke Menu Utama                  |"<<endl;
    cout << "============================================"<<endl;
    cout << "Pilih Opsi : ";
} 
//menu masasiswa
void printMenuMahasiswa() {
    cout << "==========================================="<<endl;
    cout << "|              MENU MAHASISWA             |"<<endl;
    cout << "==========================================="<<endl;
    cout << "| 1. Daftar Buku                          |"<<endl;
    cout << "| 2. Pencarian Buku                       |"<<endl;
    cout << "| 3. Pinjam Buku                          |"<<endl;
    cout << "| 4. Kembali Menu Utama                   |"<<endl;
    cout << "==========================================="<<endl;
    cout << " Pilih Opsi : ";
}
//untuk menambahkan buku
void inputBuku(buku* &head, buku* &tail) {
    buku* baru = new buku;
    cout << "============================================"<<endl;
    cout << "|             MASUKAN DATA BUKU            |"<<endl;
    cout << "============================================"<<endl;
    cout << "Nomor Buku :";
    cin  >> baru->nomor;
    cin.ignore();
    cout << "Judul Buku :";
    getline(cin, baru->nama);
    cout << "Pengarang :";
    getline(cin, baru->pengarang);
    cout << "Tahun Terbit :";
    cin  >> baru->tahun;
    cin.ignore();
    cout << "Penerbit :";
    getline(cin, baru->penerbit);

    baru->next = nullptr;
    baru->prev = tail;
    if (tail) {
        tail->next = baru;
    } else {
        head = baru;
    }
    tail = baru;

    cout << " \nBUKU DATA BERHASIL DITAMBAH.\n";
}
//untuk menampilkan daftar bukku yang sudah diinput
void tampilkanDataBuku(buku* head) {
    cout << "==================================================================================="<<endl;
    cout << "|                               DAFTAR BUKU                                       |"<<endl;
    cout << "==================================================================================="<<endl;
    if (!head) {
        cout <<" Tidak ada Data Buku.\n";
        return;
    }

    cout <<"|" << left << setw(5) << "Nomor"
         <<"|" << setw(29) << "Judul Buku"
         <<"|" << setw(14) << "Pengarang"
         <<"|" << setw(13) << " Tahun Terbit"
         <<"|" << setw(15) << "Penerbit" << " | " << endl;
    cout <<"-----------------------------------------------------------------------------------"<<endl;
    buku* temp = head;
    while (temp) {
        cout <<"|" << left << setw(5) << temp->nomor
             <<"|" << setw(29) << temp->nama
             <<"|" << setw(14) << temp->pengarang
             <<"|" << setw(13) << temp->tahun
             <<"|" << setw(15) << temp->penerbit << " | " << endl;
        temp = temp->next;
    }
    cout << "==================================================================================="<<endl;
}
//untu edit daftar buku
void editBuku(buku* head, int nomor) {
    buku* temp = head;
    while (temp && temp->nomor != nomor) {
        temp = temp->next; 
    }

    if (temp) {
        cout << "\nEdit Data Buku Nomor " << nomor << "\n";
        cout << " udul Buku : ";
        cin.ignore();
        getline(cin, temp->nama);
        cout << "Pengarang : ";
        getline(cin, temp->pengarang);
        cout << "Tahun Terbit : ";
        cin  >> temp->tahun;
        cin.ignore();
        cout << "Penerbit :";
        getline(cin, temp->penerbit);
        cout << "\nData Buku berhasil diubah.\n";
    } else {
        cout << " Buku dengan Nomor " << nomor << " tidak ditemukan.\n";
    }
}
//menghapus data buku yang tidak diperlukan
void hapusBuku(buku* head, buku* &tail, int nomor) {
    buku* temp = head;
    buku* prev = nullptr;
    while (temp && temp->nomor != nomor) {
        prev = temp;
        temp = temp->next;
    }
    if (temp) {
        if (prev) {
            prev->next = temp->next;
        } else {
            head = temp->next;
        }
        if (temp->next) {
            temp->next->prev = prev;
        } else {
            tail = prev;
        }
        delete temp;
        cout << "Buku dengan Nomor " << nomor << "telah dihapus.\n";
    } else {
        cout << "Buku dengan Nomor " << nomor << "tidak ditemukan.\n";
    }
}
//mencari buku / menu search
void cariBuku(buku* head) {
    string keyword;

    cout << " Masukan judul atau Pengarang buku : ";
    cin.ignore();
    getline(cin, keyword);

    buku* temp = head;
    bool found = false;

    cout << "==================================================================================="<<endl;
    cout << "|                               HASIL PENCARIAN                                   |"<<endl;
    cout << "==================================================================================="<<endl;
    cout <<"|" << left << setw(5) << "Nomor"
         <<"|" <<setw(29) << "Judul Buku"
         <<"|" << setw(14) << "Pengarang"
         <<"|" << setw(13) << "Tahun Terbit"
         <<"|" << setw(15) << "Penerbit" << " | " <<endl;
     cout <<"-----------------------------------------------------------------------------------"<<endl;

    while (temp) {
        if (temp->nama.find(keyword) != string::npos || temp->pengarang.find(keyword) != string::npos) {
            cout <<"|" << left << setw(5) << temp->nomor
                 <<"|" << setw(29) << temp->nama
                 <<"|" << setw(14) << temp->pengarang 
                 <<"|" << setw(13) << temp->tahun
                 <<"|" << setw(15) << temp->penerbit << " | " <<endl;
            found = true;
        }
        temp = temp->next;
    cout << "==================================================================================="<<endl;
    }
    if (!found) {
        cout << "Buku tidak ditemukan.\n";
    }
}
//untuk meminjam buku 
void pinjamBuku(peminjaman* &headPeminjaman, buku* headbuku) {
    string nama_peminjam, tanggalpinjam;
    cout << "+ \nMasukan Nama Peminjam : ";
    cin.ignore();
    getline(cin, nama_peminjam);

    int nomorBukuDipinjam[MAX_PINJAMAN];
    int jumlahPinjaman = 0;

    do {
        cout << "Masukan Nomor Buku  : ";
        int nomorBuku;
        cin  >> nomorBuku;
        cin.ignore();

        buku* bukuDipinjam = headbuku;
        bool bukuDitemukan = false;
        while (bukuDipinjam) {
            if (bukuDipinjam->nomor == nomorBuku) {
                bukuDitemukan = true;
                break;
            }
            bukuDipinjam = bukuDipinjam->next;
        }

        if (!bukuDitemukan) {
            cout <<" Buku dengan Nomor " << nomorBuku << " tidak ditemukan.\n";
        } else {
            nomorBukuDipinjam[jumlahPinjaman++] = nomorBuku;
        }

        if (jumlahPinjaman >= MAX_PINJAMAN) {
            cout << "Anda telah mencapai batas maksimum peminjaman buku.\n";
            break;
        }

        char lanjut;
        cout << "Apakah Anda ingin meminjam buku lagi? (y/n): ";
        cin >> lanjut;
        if (lanjut != 'y' && lanjut != 'Y')
            break;

    } while (jumlahPinjaman < MAX_PINJAMAN);

    cout << "Masukan Tanggal Peminjaman (DD/MM/YY): ";
    cin.ignore();
    getline(cin, tanggalpinjam);

    for (int i = 0; i < jumlahPinjaman; ++i) {
        peminjaman* baru = new peminjaman;
        baru->nama_peminjam = nama_peminjam;
        baru->nomor_buku = nomorBukuDipinjam[i];

        buku* bukuDipinjam = headbuku;
        while (bukuDipinjam && bukuDipinjam->nomor != nomorBukuDipinjam[i]) {
            bukuDipinjam = bukuDipinjam->next;
        }
        baru->nama_buku = bukuDipinjam->nama;
        baru->tanggal_peminjam = tanggalpinjam;
        baru->next = headPeminjaman;
        headPeminjaman = baru;

        cout << "Buku \"" << baru->nama_buku << "\" berhasil dipinjam oleh " << nama_peminjam << ".\n";
    }
}
//menampilkan tabel peminjaman
void tampilkanPeminjaman(peminjaman* head)  {
    cout << "================================================================================="<<endl;
    cout << "|                               DAFTAR BUKU                                      |"<<endl;
    cout << "=================================================================================="<<endl;
    if (!head) {
        cout << "Tidak ada data peminjaman.\n";
        return;
    }

    cout <<"|" << left << setw(20) << "Nama Peminjam"
         <<"|" << setw(10) << "Nomor Buku"
         <<"|" << setw(31) << "Nama Buku"
         <<"|" << setw(15) << "Tanggal " << " | " <<endl;
     cout << "=================================================================================="<<endl;
    
    peminjaman* temp = head;
    while (temp) {
        cout <<"|" <<  left << setw(20) << temp->nama_peminjam
             <<"|" << setw(10) << temp->nomor_buku
             <<"|" <<  setw(31) << temp->nama_buku
             <<"|" << setw(15) << temp->tanggal_peminjam << " | " <<endl;
        temp = temp->next;
    }
      cout << "=================================================================================="<<endl;
}

int main() {
    int pilihan, subPilihan;
    buku* headbuku = nullptr;
    buku* tailbuku = nullptr;
    peminjaman* headpeminjaman = nullptr;

    do {
        cout << "============================================="<<endl;
        cout << "|      Selamat Datang Di Perpustakaan       |"<<endl;
        cout << "============================================="<<endl;
        cout << "| MENU:                                     |"<<endl;
        cout << "| 1. Sebagai Pengelola                      |"<<endl;
        cout << "| 2. Sebagai Mahasiswa                      |"<<endl;
        cout << "| 3. Exit                                   |"<<endl;
        cout << "============================================="<<endl;
        cout << "Pilih Opsi: ";
        cin >> pilihan; 

        switch (pilihan) {
            case 1:
                do {
                    printMenuStaffAdmin();
                    cin >> subPilihan;
                    int nomorBuku;

                    switch (subPilihan) {
                        case 1:
                            inputBuku(headbuku, tailbuku);
                            break;
                        case 2:
                            tampilkanDataBuku(headbuku);
                            break;
                        case 3:
                            cout << "Masukkan Nomor Buku untuk Edit: ";
                            cin >> nomorBuku;
                            editBuku(headbuku, nomorBuku);
                            break;
                        case 4:
                            cout << "Masukkan Nomor Buku untuk Hapus: ";
                            cin >> nomorBuku;
                            hapusBuku(headbuku, tailbuku, nomorBuku);
                            break;
                        case 5:
                            tampilkanPeminjaman(headpeminjaman);
                            break;
                        case 6:
                            break;
                        default:
                            cout << "Pilihan tidak valid.\n";
                            break;
                    }
                } while (subPilihan != 6);
                break;
            case 2:
                do {
                    printMenuMahasiswa();
                    cin >> subPilihan;

                    switch (subPilihan) {
                        case 1:
                            tampilkanDataBuku(headbuku);
                            break;
                        case 2:
                            cariBuku(headbuku);
                            break;
                        case 3:
                            pinjamBuku(headpeminjaman, headbuku);
                            break;
                        case 4:
                            break;
                        default:
                            cout << "Pilihan tidak valid.\n";
                            break;
                    }
                } while (subPilihan != 4);
                break;
            case 3:
                cout << "Terima Kasih telah menggunakan sistem perpustakaan.\n";
                break;
            default:
                cout << "Pilihan tidak valid.\n";
                break;
        }
    } while (pilihan != 3);
    // TODO: Implement memory clean-up for linked list
    return 0;
}