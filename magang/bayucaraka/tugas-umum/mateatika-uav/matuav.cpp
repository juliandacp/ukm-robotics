#include<bits/stdc++.h>
using namespace std;

struct vec3{
    double x, y, z;
};

struct vec4{
    double x, y, z, w;
};

struct mat3{
    double m[3][3];
};

struct mat4{
    double m[4][4];
};

mat3 mat3_transpose(const mat3 &A){
    mat3 T{};
    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
            T.m[i][j] = A.m[j][i];
        }
    }
    return T;
}

vec3 mat3_vec3_mul(const mat3 &R, const vec3 &v){
    vec3 res{};
    res.x = R.m[0][0]*v.x + R.m[0][1]*v.y + R.m[0][2]*v.z;
    res.y = R.m[1][0]*v.x + R.m[1][1]*v.y + R.m[1][2]*v.z;
    res.z = R.m[2][0]*v.x + R.m[2][1]*v.y + R.m[2][2]*v.z;
    return res;
}

mat4 mat4_identity(){
    mat4 T{};
    for(int i=0;i<4;i++){
        for(int j=0;j<4;j++){
            T.m[i][j] = (i==j ? 1.0 : 0.0);
        }
    }
    return T;
}

mat4 mat4_mul(const mat4 &A, const mat4 &B){
    mat4 C{};
    for(int i=0;i<4;i++){
        for(int j=0;j<4;j++){
            C.m[i][j] = 0;
            for(int k=0;k<4;k++){
                C.m[i][j] += A.m[i][k] * B.m[k][j];
            }
        }
    }
    return C;
}

mat3 quat_to_mat3(const vec4 &q){
    double x = q.x;
    double y = q.y;
    double z = q.z;
    double w = q.w;
    mat3 R{};
    R.m[0][0] = 1 - 2 * (y*y + z*z);
    R.m[0][1] = 2 * (x*y - z*w);
    R.m[0][2] = 2 * (x*z + y*w);
    R.m[1][0] = 2 * (x*y + z*w);
    R.m[1][1] = 1 - 2 * (x*x + z*z);
    R.m[1][2] = 2 * (y*z - x*w);
    R.m[2][0] = 2 * (x*z - y*w);
    R.m[2][1] = 2 * (y*z + x*w);
    R.m[2][2] = 1 - 2 * (x*x + y*y);
    return R;
}

mat4 tf_create(const vec3 &pos, const vec4 &quat){
    mat4 T = mat4_identity();
    mat3 R = quat_to_mat3(quat);
    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
            T.m[i][j] = R.m[i][j];
        }
    }
    T.m[0][3] = pos.x;
    T.m[1][3] = pos.y;
    T.m[2][3] = pos.z;
    return T;
}

mat3 tf_rotation(const mat4 &T){
    mat3 R{};
    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
            R.m[i][j] = T.m[i][j];
        }
    }
    return R;
}

vec3 tf_translation(const mat4 &T){
    return {T.m[0][3], T.m[1][3], T.m[2][3]};
}

mat4 tf_inverse(const mat4 &T){
    mat3 R = tf_rotation(T);
    vec3 t = tf_translation(T);
    mat3 Rt = mat3_transpose(R);
    vec3 new_t = mat3_vec3_mul(Rt, { -t.x, -t.y, -t.z });
    mat4 invT = mat4_identity();
    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
            invT.m[i][j] = Rt.m[i][j];
        }
    }
    invT.m[0][3] = new_t.x;
    invT.m[1][3] = new_t.y;
    invT.m[2][3] = new_t.z;
    return invT;
}

vec3 base_to_cam_pos = {0.0, 0.0, 0.15};
vec4 base_to_cam_quat = {0.0, 0.0, 0.0, 1.0};
mat4 tf_base_to_cam = tf_create(base_to_cam_pos, base_to_cam_quat);
vec3 drone1_to_drone2_pos = {0.0, -1.3, 0.0};

mat4 tf_create_drone1_to_drone2(){
    double yaw_rad = 10.0 * M_PI / 180.0;
    double c = cos(yaw_rad);
    double s = sin(yaw_rad);
    mat4 T = mat4_identity();
    T.m[0][0] = c;  T.m[0][1] = -s; T.m[0][2] = 0;
    T.m[1][0] = s;  T.m[1][1] =  c; T.m[1][2] = 0;
    T.m[2][0] = 0;  T.m[2][1] =  0; T.m[2][2] = 1;
    T.m[0][3] = drone1_to_drone2_pos.x;
    T.m[1][3] = drone1_to_drone2_pos.y;
    T.m[2][3] = drone1_to_drone2_pos.z;
    return T;
}

mat4 tf_drone1_to_drone2 = tf_create_drone1_to_drone2();

vec3 relative_pos_drone2_in_drone1(const vec3 &cam1_pos, const vec4 &cam1_quat, const vec3 &cam2_pos, const vec4 &cam2_quat){
    mat4 tf_world_to_cam1 = tf_create(cam1_pos, cam1_quat);
    mat4 tf_world_to_cam2 = tf_create(cam2_pos, cam2_quat);
    mat4 tf_cam_to_base = tf_inverse(tf_base_to_cam);
    mat4 tf_world_to_base1 = mat4_mul(tf_world_to_cam1, tf_cam_to_base);
    mat4 tf_world_to_base2 = mat4_mul(tf_world_to_cam2, tf_cam_to_base);
    mat4 tf_base1_to_world = tf_inverse(tf_world_to_base1);
    mat4 tf_final = mat4_mul(mat4_mul(tf_base1_to_world, tf_drone1_to_drone2), tf_world_to_base2);
    vec3 final_pos = tf_translation(tf_final);
    return final_pos;
}

int main(){
    vec3 cam1_pos = {0.0, 0.0, 0.0};
    vec4 cam1_quat = {0.0, 0.0, 0.0, 1.0};
    vec3 cam2_pos = {0.0, 0.0, 0.0};
    vec4 cam2_quat = {0.0, 0.0, 0.0, 1.0};
    vec3 hasil = relative_pos_drone2_in_drone1(cam1_pos, cam1_quat, cam2_pos, cam2_quat);
    cout << "Posisi relatif drone kedua terhadap drone pertama dalam sistem koordinat lokal (base_link) drone pertama:\n";
    cout << fixed << setprecision(2);
    cout << "x: " << hasil.x << endl;
    cout << "y: " << hasil.y << endl;
    cout << "z: " << hasil.z << endl;
    return 0;
}