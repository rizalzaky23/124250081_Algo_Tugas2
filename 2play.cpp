#include <iostream>
#include <iomanip>
#include <stdlib.h>
using namespace std;

struct Lagu{
	string judul;
	string penyanyi;
	string durasi;
	int tahun;
	Lagu* kiri;
	Lagu* kanan;
};

void clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void pauseScreen() {
    cout << endl << "Tekan Enter untuk melanjutkan...";
    string dummy;
    getline(cin, dummy);
}

Lagu* buatNodeBaru(string judul, string penyanyi, string durasi, int tahun){
	Lagu* nodeBaru = new Lagu();
	nodeBaru->judul = judul;
    nodeBaru->penyanyi = penyanyi;
    nodeBaru->durasi = durasi;
    nodeBaru->tahun = tahun;
    nodeBaru->kiri = NULL;
    nodeBaru->kanan = NULL;
    return nodeBaru;
	
}

void tambahKePTB(Lagu*& root, string judul, string penyanyi, string durasi, int tahun) {
	if (root == NULL) {
        root = buatNodeBaru(judul, penyanyi, durasi, tahun);
        return;
    }
    
    if (judul < root->judul) {
        tambahKePTB(root->kiri, judul, penyanyi, durasi, tahun);
    } else {
        tambahKePTB(root->kanan, judul, penyanyi, durasi, tahun);
    }
	
}

void simpanLaguKeFile(string judul, string penyanyi, string durasi, int tahun) {
    FILE *file = fopen("data_lagu.txt", "a"); 
    
    if (file != NULL) {
        fprintf(file, "%s\n", judul.c_str());
        fprintf(file, "%s\n", penyanyi.c_str());
        fprintf(file, "%s\n", durasi.c_str());
        fprintf(file, "%d\n", tahun);
        
        fclose(file); 
    } else {
        cout << "Gagal membuka file untuk menyimpan data!" << endl;
    }
}

void muatDataDariFile(Lagu*& root) {
    FILE *file = fopen("data_lagu.txt", "r"); 
    
    if (file != NULL) {
        char bufferJudul[150];
        char bufferPenyanyi[150];
        char bufferDurasi[20];
        int tahun;
        
        while (fscanf(file, " %[^\n]", bufferJudul) == 1) {
            fscanf(file, " %[^\n]", bufferPenyanyi);
            fscanf(file, " %[^\n]", bufferDurasi);
            fscanf(file, "%d", &tahun);
           
            tambahKePTB(root, bufferJudul, bufferPenyanyi, bufferDurasi, tahun);
        }
        
        fclose(file); 
    }
}

void cetakBarisLagu(Lagu* root, int &nomor) {
    cout << left << setw(4) << nomor++ 
         << setw(30) << root->judul 
         << setw(20) << root->penyanyi 
         << setw(10) << root->durasi 
         << root->tahun << endl;
}

void tampilPreOrder(Lagu* root, int &nomor) {
    if (root != NULL) {
        cetakBarisLagu(root, nomor);
        tampilPreOrder(root->kiri, nomor);
        tampilPreOrder(root->kanan, nomor);
    }
}

void tampilInOrder(Lagu* root, int &nomor) {
    if (root != NULL) {
        tampilInOrder(root->kiri, nomor);
        cetakBarisLagu(root, nomor);
        tampilInOrder(root->kanan, nomor);
    }
}

void tampilPostOrder(Lagu* root, int &nomor) {
    if (root != NULL) {
        tampilPostOrder(root->kiri, nomor);
        tampilPostOrder(root->kanan, nomor);
        cetakBarisLagu(root, nomor);
    }
}

void menuTambahLagu(Lagu*& rootLagu) {
    clearScreen();
    string judulBaru, penyanyiBaru, durasiBaru;
    int tahunBaru;
    
    cout << "--- TAMBAH LAGU BARU ---" << endl;
    cout << "Masukkan Judul Lagu     : ";
    getline(cin, judulBaru);
    
    cout << "Masukkan Nama Penyanyi  : ";
    getline(cin, penyanyiBaru);
    
    cout << "Masukkan Durasi (mm:ss) : ";
    getline(cin, durasiBaru);
    
    cout << "Masukkan Tahun Terbit   : ";
    cin >> tahunBaru;
    cin.ignore(10000, '\n');
    
    tambahKePTB(rootLagu, judulBaru, penyanyiBaru, durasiBaru, tahunBaru);
    simpanLaguKeFile(judulBaru, penyanyiBaru, durasiBaru, tahunBaru);
    
    cout << "\n[ Lagu berhasil ditambahkan dan disimpan permanen! ]" << endl;
    pauseScreen();
}



void menuTampilLagu(Lagu* root){
	char pilih;
	if (root == NULL) {
        clearScreen();
        cout << "--- DAFTAR LAGU ---" << endl;
        cout << "Belum ada lagu di dalam sistem." << endl;
        pauseScreen();
        return;
    }
    
    do{
		clearScreen();
		cout << "===== MENU TAMPIL LAGU =====" << endl;
        cout << "1. Pre-order" << endl;
        cout << "2. In-order (Urutan abjad A-Z)" << endl;
        cout << "3. Post-order" << endl;
        cout << "0. Kembali ke Menu Utama" << endl;
        cout << "Pilih jenis penelusuran : ";
		cin >> pilih;
		cin.ignore(10000, '\n');
		
		if (pilih == '0') break;

        if (pilih == '1' || pilih == '2' || pilih == '3') {
            clearScreen();
            cout << "======================================================================\n";
            if (pilih == '1') cout << "                     DAFTAR LAGU (PRE-ORDER)                  \n";
            else if (pilih == '2') cout << "                     DAFTAR LAGU (IN-ORDER)                   \n";
            else if (pilih == '3') cout << "                     DAFTAR LAGU (POST-ORDER)                 \n";
            cout << "======================================================================\n";
           
            cout << left << setw(4) << "No" 
                 << setw(30) << "Judul Lagu" 
                 << setw(20) << "Penyanyi" 
                 << setw(10) << "Durasi" 
                 << "Tahun" << endl;
            cout << "----------------------------------------------------------------------\n";

            int nomor = 1;
            if (pilih == '1') tampilPreOrder(root, nomor);
            else if (pilih == '2') tampilInOrder(root, nomor);
            else if (pilih == '3') tampilPostOrder(root, nomor);
            
            cout << "----------------------------------------------------------------------\n";
            pauseScreen();
        } else {
            cout << "Pilihan tidak valid!" << endl;
            pauseScreen();
        }

    } while (pilih != '0');
}

void programSelesai(){
    clearScreen();
    cout << "Terimakasih Telah menggunakan Program :)" << endl;
    pauseScreen();
}	

int main(){
    char pilih;
    Lagu* rootLagu = NULL;
    muatDataDariFile(rootLagu);
    
    do{
        clearScreen();
        cout << "===== 2PLAY =====" << endl;
        cout << "1. Tambah Lagu" << endl;
        cout << "2. Tampil Daftar Lagu" << endl;
        cout << "3. Cari Lagu" << endl;
        cout << "4. Tambah Lagu ke Playlist" << endl;
        cout << "5. Lihat Playlist" << endl;
        cout << "6. Putar Playlist" << endl;
        cout << "7. Replay Lagu" << endl;
        cout << "8. Riwayat Lagu" << endl;
        cout << "9. Hapus Lagu" << endl;
        cout << "0. Keluar" << endl;
        cout << "Pilih Menu : ";
        cin >> pilih;
        cin.ignore(10000, '\n'); 
        
        switch(pilih){
			case '1': menuTambahLagu(rootLagu);
			break;
			case '2': menuTampilLagu(rootLagu);
			break;
            case '0': 
                programSelesai();
                return 0;
            default: 
                cout << "Pilihan Tidak Valid, Silahkan Pilih Menu yang tersedia" << endl;
                pauseScreen();
                break;
        }
        
    }while(pilih != '0');
    
    return 0;
}
