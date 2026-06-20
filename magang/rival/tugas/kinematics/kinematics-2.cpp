#include<bits/stdc++.h>
#define convert(x) ((x)*M_PI/180.0)
using namespace std;

struct DH{
    double theta; 
    double d;    
    double a;     
    double alpha; 
};

void DH_transform(double alpha, double a, double d, double theta, double T[4][4]){
    double a_rad=convert(alpha);
    double t_rad=convert(theta);
    T[0][0]=cos(t_rad);
    T[0][1]=-sin(t_rad)*cos(a_rad);
    T[0][2]=sin(t_rad)*sin(a_rad);
    T[0][3]=a*cos(t_rad);

    T[1][0]=sin(t_rad);
    T[1][1]=cos(t_rad)*cos(a_rad);
    T[1][2]=-cos(t_rad)*sin(a_rad);
    T[1][3]=a*sin(t_rad);

    T[2][0]=0;
    T[2][1]=sin(a_rad);
    T[2][2]=cos(a_rad);
    T[2][3]=d;

    T[3][0]=0;
    T[3][1]=0;
    T[3][2]=0;
    T[3][3]=1;
}

void hitung(double A[4][4], double B[4][4], double R[4][4]){
    double temp[4][4]={0};
    for(int i=0; i<4; i++)
        for(int j=0; j<4; j++)
            for(int k=0; k<4; k++)
                temp[i][j]+=A[i][k]*B[k][j];
    for (int i=0; i<4; i++)
        for(int j=0; j<4; j++)
            R[i][j]=temp[i][j];
}

void posisi_arm(DH joint[3], double &x, double &y, double &z){
    double T1[4][4], T2[4][4], T3[4][4];
    double T12[4][4], T123[4][4];
    DH_transform(joint[0].alpha, joint[0].a, joint[0].d, joint[0].theta, T1);
    DH_transform(joint[1].alpha, joint[1].a, joint[1].d, joint[1].theta, T2);
    DH_transform(joint[2].alpha, joint[2].a, joint[2].d, joint[2].theta, T3);
    hitung(T1, T2, T12);
    hitung(T12, T3, T123);
    x = T123[0][3];
    y = T123[1][3];
    z = T123[2][3];
}

int main() {
    char tipe; 
    double t1, t2, t3;
    cin >> tipe >> t1 >> t2 >> t3;
    DH joint[3];
    if(tipe=='L' || tipe=='l'){
        joint[0]={t1, 5, 0, 90};
        joint[1]={t2, 0, 3, 0};
        joint[2]={t3, 0, 2, 0};
    }else if(tipe=='D' || tipe=='d'){
        joint[0]={t1, 6, 0, 90};
        joint[1]={t2, 0, 3, 0};
        joint[2]={t3, 0, 2, 0};
    }
    double x, y, z;
    posisi_arm(joint, x, y, z);
    cout << fixed << setprecision(2);
    cout << floor(x*100)/100 << "\n" << floor(y*100)/100 << "\n" << floor(z*100)/100 << "\n";
    return 0;
}