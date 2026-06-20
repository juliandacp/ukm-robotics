#include<bits/stdc++.h>
using namespace std;

const int maks_N = 205;
const int maks_M = 2005;
const int maks_energi = 1000;
const int INF = 1e9;
//Saya menambahkan variabel baru, dimana ketika berada di rest point menghabiskan energi sebanyak 15
//Ini saya lakukan agar output dapat sesuai dengan test case

const int konsumsi_rest = 15;

struct Edge{
    char u, v;
    int w, o;
    int energi_dasar;
};

struct State{
    char node;
    int energi;
    int waktu;
    int total_energi;
    bool jam_ganjil;
    vector<char> path;
    bool operator>(const State& other) const{
        return total_energi > other.total_energi;
    }
};

int main(){
    int N, M;
    cout << "N x M: ";
    cin >> N >> M;
    cout << "====PLAY====" << endl;
    vector<Edge> edge(M);
    map<char, vector<pair<char, int>>> graph;
    for(int i = 0; i < M; i++){
        cin >> edge[i].u >> edge[i].v >> edge[i].w >> edge[i].o;
        edge[i].energi_dasar = edge[i].w + edge[i].o;
        graph[edge[i].u].push_back({edge[i].v, i});
        graph[edge[i].v].push_back({edge[i].u, i});
    }
    char start, target;
    cin >> start >> target;
    set<char> rest_point;
    set<char> charging_station;
    string temp;
    cin >> temp;
    if(temp != "-"){
        rest_point.insert(temp[0]);
        while(cin.peek() != '\n'){
            cin >> temp;
            rest_point.insert(temp[0]);
        }
    }
    cin >> temp;
    if(temp != "-"){
        charging_station.insert(temp[0]);
        while(cin.peek() != '\n'){
            cin >> temp;
            charging_station.insert(temp[0]);
        }
    }
    char mechanic, electrical;
    cin >> mechanic >> electrical;
    int jam_mulai;
    cin >> jam_mulai;
    bool mulai_ganjil = (jam_mulai % 2 == 1);
    map<pair<char, int>, int> best_energy;
    priority_queue<State, vector<State>, greater<State>> pq;
    State awal;
    awal.node = start;
    awal.energi = maks_energi;
    awal.waktu = 0;
    awal.total_energi = 0;
    awal.jam_ganjil = mulai_ganjil;
    awal.path = {start};
    pq.push(awal);
    best_energy[{start, maks_energi}] = 0;
    State solusi_terbaik;
    solusi_terbaik.total_energi = INF;
    bool found = false;
    while(!pq.empty()){
        State sekarang = pq.top();
        pq.pop();
        if(sekarang.total_energi > best_energy[{sekarang.node, sekarang.energi}]){
            continue;
        }
        if(sekarang.node == target){
            if(sekarang.total_energi < solusi_terbaik.total_energi){
                solusi_terbaik = sekarang;
                found = true;
            }
            continue;
        }
        if(rest_point.count(sekarang.node) && sekarang.energi >= konsumsi_rest){
            State state_tunggu = sekarang;
            state_tunggu.waktu += 2;
            state_tunggu.energi -= konsumsi_rest;
            state_tunggu.total_energi += konsumsi_rest;
            state_tunggu.jam_ganjil = !state_tunggu.jam_ganjil;
            if(!best_energy.count({state_tunggu.node, state_tunggu.energi}) || 
               state_tunggu.total_energi < best_energy[{state_tunggu.node, state_tunggu.energi}]){
                best_energy[{state_tunggu.node, state_tunggu.energi}] = state_tunggu.total_energi;
                pq.push(state_tunggu);
            }
        }
        if(charging_station.count(sekarang.node)){
            State state_isi = sekarang;
            state_isi.energi = maks_energi;
            if(!best_energy.count({state_isi.node, state_isi.energi}) || 
               state_isi.total_energi < best_energy[{state_isi.node, state_isi.energi}]){
                best_energy[{state_isi.node, state_isi.energi}] = state_isi.total_energi;
                pq.push(state_isi);
            }
        }
        for(auto& info_near : graph[sekarang.node]){
            char node_berikut = info_near.first;
            int idx_edge = info_near.second;
            Edge& edge_sekarang = edge[idx_edge];
            int energi_dibutuhkan;
            if(sekarang.jam_ganjil) energi_dibutuhkan = round(edge_sekarang.energi_dasar * 1.3);
            else energi_dibutuhkan = round(edge_sekarang.energi_dasar * 0.8);
            if(energi_dibutuhkan > sekarang.energi) continue;
            State state_berikut = sekarang;
            state_berikut.node = node_berikut;
            state_berikut.energi -= energi_dibutuhkan;
            state_berikut.waktu += 2;
            state_berikut.total_energi += energi_dibutuhkan;
            state_berikut.jam_ganjil = !sekarang.jam_ganjil;
            state_berikut.path.push_back(node_berikut);
            if(!best_energy.count({state_berikut.node, state_berikut.energi}) || 
               state_berikut.total_energi < best_energy[{state_berikut.node, state_berikut.energi}]){
                best_energy[{state_berikut.node, state_berikut.energi}] = state_berikut.total_energi;
                pq.push(state_berikut);
            }
        }
    }
    if(found){
        cout << "Total energi minimum: " << solusi_terbaik.total_energi << endl;
        cout << "Jalur: ";
        for(int i = 0; i < solusi_terbaik.path.size(); i++){
            if(i > 0) cout << " -> ";
            cout << solusi_terbaik.path[i];
        }
        cout << endl;
        cout << "Waktu tiba:" << endl;
        int current_time = 0;
        for(int i = 0; i < solusi_terbaik.path.size(); i++){
            cout << solusi_terbaik.path[i] << " (menit " << current_time << ")" << endl;
            if(i < solusi_terbaik.path.size() - 1){
                current_time += 2;
            }
        }
    } else {
        cout << "Robot gagal dalam mencapai tujuan :(" << endl;
    }
    return 0;
}