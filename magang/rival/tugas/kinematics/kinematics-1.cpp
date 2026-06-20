#include<bits/stdc++.h>
using namespace std;

int main(){
    string nama;
    cin >> nama;
    vector<array<double,3>>cmds;
    string line;
    while(getline(cin, line)){
        if(line.empty()) continue;
        if(line=="GAS") break;
        for(int i=0; i<line.length(); i++){
            if(line[i]==',') line[i]=' ';
        }
        stringstream ss(line);
        double a,b,c;
        if(!(ss >> a)) continue;
        if(!(ss >> b)) b=0.0;
        if(!(ss >> c)) c=0.0;
        cmds.push_back({a,b,c});
    }
    const double R=0.15;
    vector<double>theta(3); 
    double wheel_radius=0.01; 
    if(nama=="LILDAN"){
        cout << "▼\n";
        wheel_radius=127.0/2000.0;
        theta[0]=45.0*M_PI/180.0;
        theta[1]=180.0*M_PI/180.0;
        theta[2]=315.0*M_PI/180.0;
    }else if(nama=="DHARMI"){
        cout << "▲\n";
        wheel_radius=48.0/2000.0;
        theta[0]=120.0*M_PI/180.0;
        theta[1]=240.0*M_PI/180.0;
        theta[2]=0.0*M_PI/180.0;
    }

    for(auto &trip : cmds){
        double vx=trip[0];
        double vy=trip[1];
        double w=trip[2];
        for(int i=0; i<3; i++){
            double om=(-sin(theta[i])*vx+cos(theta[i])*vy+R*w)/wheel_radius;
            if(fabs(om)<0.005) om=0.0;
            cout << fixed << setprecision(2) << om << "\n";
        }
    }
    return 0;
}