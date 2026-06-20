<div align="center">

# 🔌 Challenge Half Bridge Motor Driver

### KPP RIVAL

</div>

## Deskripsi

Challenge ini bertujuan untuk mengendalikan sebuah motor DC menggunakan konfigurasi **Half Bridge Driver** yang terdiri dari transistor **PMOS** dan **NMOS**. Arduino digunakan untuk memberikan sinyal PWM sehingga motor dapat dinyalakan dan dimatikan secara terkontrol.

Pada implementasi ini, motor berputar selama beberapa detik, kemudian berhenti, dan proses tersebut berulang secara terus-menerus.

---

## Link Simulasi

🚀 Tinkercad Simulation:
https://www.tinkercad.com/things/c6zIlPzez4n-challenge-half-bridge?sharecode=Iv-Ujf5mcbh1ShYDkds73ZkJLht0G9oMdZ8eLBzQHVk

---

## Program Arduino

```cpp
#define M1_0 3
#define M1_1 5

int setPWM = 255;

void setup() {
  pinMode(M1_0, OUTPUT);
  pinMode(M1_1, OUTPUT);
}

void loop() {
  analogWrite(M1_0, 0);
  analogWrite(M1_1, setPWM);
  delay(3000);

  analogWrite(M1_0, 0);
  analogWrite(M1_1, 0);
  delay(3000);
}
```