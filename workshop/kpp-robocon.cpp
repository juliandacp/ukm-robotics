#include<bits/stdc++.h>
using namespace std;

class Game{
    public:
    string nama_game;
    string developer;
    unsigned short tahun_rilis;
    float rating;
    float harga;
    Game(){}
    
    Game(string nama_gameInput, string developerInput, unsigned short tahun_rilisInput, float ratingInput, float hargaInput){
        nama_game=nama_gameInput;
        developer=developerInput;
        tahun_rilis=tahun_rilisInput;
        rating=ratingInput;
        harga=hargaInput;
    }
    void inputDataUmum(){
        cout << "\n=== INFORMASI GAME ===" << endl;
        cout << "Nama Game: ";
        getline(cin, nama_game);
        cout << "Developer: ";
        getline(cin, developer);
        cout << "Tahun Rilis: ";
        cin >> tahun_rilis;
        cout << "Rating (0-10): ";
        cin >> rating;
        cout << "Harga: Rp";
        cin >> harga;
    }
        void startAnalisis(){
        cout << "\n=== ANALISIS GAME ===" << endl;
    }
};

class RPG: public Game{
    public:
    unsigned int jumlah_karakter;
    float alur_cerita;
    unsigned int quest;
    RPG(){}
    RPG(string nama_gameInput, string developerInput, unsigned short tahun_rilisInput, float ratingInput, float hargaInput, unsigned int jumlah_karakterInput, float alur_ceritaInput, unsigned int questInput)
        : Game(nama_gameInput, developerInput, tahun_rilisInput, ratingInput, hargaInput){
            jumlah_karakter=jumlah_karakterInput;
            alur_cerita=alur_ceritaInput;
            quest=questInput;
    }
    void inputDataRPG(){
        inputDataUmum();
        cout << "Jumlah Karakter: ";
        cin >> jumlah_karakter;
        cout << "Alur Cerita (0-10): ";
        cin >> alur_cerita;
        cout << "Jumlah Quest: ";
        cin >> quest;
        cin.ignore();
    }
    void ujiKelayakan(){
        startAnalisis();
            if(rating>=7 && alur_cerita>=7.5 && quest>=25){
                cout << "Status: LAYAK DIMAINKAN" << endl;
                cout << "Alasan: " << endl;
                cout << "- Rating sangat baik (" << rating << "/10)" << endl;
                cout << "- Alur cerita luar biasa (" << alur_cerita << "/10)" << endl;
                cout << "- " << quest << " quest tersedia" << endl;
            }else{
                cout << "Status: TIDAK LAYAK DIMAINKAN" << endl;
                cout << "Alasan: " << endl;
                if(rating<7) cout << "- Rating buruk (" << rating << "/10)" << endl;
                if(alur_cerita<7.5) cout << "- Alur cerita kurang (" << alur_cerita << "/10)" << endl;
                if(quest<25) cout << "- Quest yang tersedia hanya " << quest << " quest" << endl;
            }
        }
};

class FPS: public Game{
    public:
    unsigned int jumlah_map;
    unsigned int jumlah_senjata;
    unsigned int jumlah_player_aktif;
    FPS(){}
    FPS(string nama_gameInput, string developerInput, unsigned short tahun_rilisInput, float ratingInput, float hargaInput, unsigned int jumlah_mapInput, unsigned int jumlah_senjataInput, unsigned int jumlah_player_aktifInput)
        : Game(nama_gameInput, developerInput, tahun_rilisInput, ratingInput, hargaInput){
            jumlah_map=jumlah_mapInput;
            jumlah_senjata=jumlah_senjataInput;
            jumlah_player_aktif=jumlah_player_aktifInput;
    }
    void inputDataFPS(){
        inputDataUmum();
        cout << "Jumlah Map: ";
        cin >> jumlah_map;
        cout << "Jumlah Senjata: ";
        cin >> jumlah_senjata;
        cout << "Jumlah Player Aktif: ";
        cin >> jumlah_player_aktif;
        cin.ignore();
    }
    void ujiKelayakan(){
        startAnalisis();
        if(rating>=7 && jumlah_map>=5 && jumlah_player_aktif>=1000000){
            cout << "Status: LAYAK DIMAINKAN" << endl;
                cout << "Alasan: " << endl;
                cout << "- Rating sangat baik (" << rating << "/10)" << endl;
                cout << "- Memiliki " << jumlah_player_aktif << " pemain aktif" << endl;
                cout << "- " << jumlah_map << " map tersedia" << endl;
            }else{
                cout << "Status: TIDAK LAYAK DIMAINKAN" << endl;
                cout << "Alasan: " << endl;
                if(rating<7) cout << "- Rating buruk (" << rating << "/10)" << endl;
                if(jumlah_player_aktif<1000000) cout << "- Memiliki kurang dari 1 juta pemain aktif" << endl;
                if(jumlah_map<5) cout << "- Map yang tersedia hanya " << jumlah_map << " map" << endl;
        }
    }
};

class Strategy: public Game{
    public:
    float kompleksitas;
    float avg_lama_match;
    float kesulitan;
    Strategy(){}
    Strategy(string nama_gameInput, string developerInput, unsigned short tahun_rilisInput, float ratingInput, float hargaInput, float kompleksitasInput, float avg_lama_matchInput, float kesulitanInput)
        : Game(nama_gameInput, developerInput, tahun_rilisInput, ratingInput, hargaInput){
            kompleksitas=kompleksitasInput;
            avg_lama_match=avg_lama_matchInput;
            kesulitan=kesulitanInput;
    }
    void inputDataStrategy(){
        inputDataUmum();
        cout << "Tingkat Kompleksitas (0-10): ";
        cin >> kompleksitas;
        cout << "Rata-rata Lama Match (Menit): ";
        cin >> avg_lama_match;
        cout << "Tingkat Kesulitan (0-10): ";
        cin >> kesulitan;
        cin.ignore();
    }
    void ujiKelayakan(){
        startAnalisis();
        if(rating>=7 && (kompleksitas>=5 || kesulitan>=5)){
            cout << "Status: LAYAK DIMAINKAN" << endl;
                cout << "Alasan: " << endl;
                cout << "- Rating sangat baik (" << rating << "/10)" << endl;
                cout << "- Kompleksitas permainan tinggi (" << kompleksitas << "/10)" << endl;
                cout << "- Tingkat kesulitan game tinggi (" << kesulitan << "/10)" << endl;
            }else{
                cout << "Status: TIDAK LAYAK DIMAINKAN" << endl;
                cout << "Alasan: " << endl;
                if(rating<7) cout << "- Rating buruk (" << rating << "/10)" << endl;
                if(kompleksitas<5) cout << "- Kompleksitas permainan kurang" << endl;
                if(kesulitan<5) cout << "- Terlalu mudah" << endl;
        }
    }
};

int main(){
    int opsi;
    cout << "=== JENIS GAME ===" << endl;
    cout << "1. RPG" << endl;
    cout << "2. FPS" << endl;
    cout << "3. Strategy" << endl;
    cout << "Pilih Game (1-3): ";
    cin >> opsi;  
    cin.ignore();
    switch(opsi){
    case 1:{
        RPG gameRPG;
        gameRPG.inputDataRPG();
        gameRPG.ujiKelayakan();
        break;
    }
    case 2:{
        FPS gameFPS;
        gameFPS.inputDataFPS();
        gameFPS.ujiKelayakan();
        break;
    }
    case 3:{
        Strategy gameStrategy;
        gameStrategy.inputDataStrategy();
        gameStrategy.ujiKelayakan();
        break;
    }
    default:
        cout << "Pilihan tidak valid!!!" << endl;
        break;
    }
    return 0;
}