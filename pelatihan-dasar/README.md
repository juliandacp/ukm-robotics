<div align="center">

# 🚗 Autonomous Robot Navigation System

### KPP Pelatihan Dasar

</div>

## Deskripsi Masalah

Setelah mengikuti pelatihan robotika, sebuah tim berhasil mengembangkan robot otonom yang mampu menavigasi jaringan jalan dalam suatu area. Setiap jalan memiliki panjang dasar dan kemungkinan terdapat obstacle yang menambah konsumsi energi robot saat melintasinya.

Robot harus menentukan rute dari titik awal (**S**) menuju titik tujuan (**T**) dengan **total konsumsi energi minimum**, sambil mempertimbangkan:

* Pengaruh waktu (jam ganjil/genap).
* Kemampuan menunggu pada *rest point*.
* Pengisian ulang energi pada *charging station*.
* Keterbatasan kapasitas energi maksimum.

---

## Aturan Sistem

### 1. Representasi Graf

Graf terdiri atas:

* **N** node (simpul)
* **M** edge (jalan)

Setiap edge memiliki:

| Parameter | Keterangan                   |
| --------- | ---------------------------- |
| `w`       | Panjang dasar jalan          |
| `o`       | Bobot obstacle               |
| `w + o`   | Energi dasar yang dibutuhkan |

Graf bersifat **tak berarah (undirected graph)**.

---

### 2. Pengaruh Waktu terhadap Energi

Energi aktual yang digunakan saat melewati sebuah edge bergantung pada waktu keberangkatan:

| Kondisi Waktu | Faktor Energi |
| ------------- | ------------- |
| Jam ganjil    | × 1.3         |
| Jam genap     | × 0.8         |

Sehingga:

```text
Energi Aktual = (w + o) × Faktor Waktu
```

---

### 3. Rest Point (R)

Pada node yang termasuk **Rest Point**, robot diperbolehkan:

* Menunggu sejumlah menit (integer ≥ 0).
* Menunggu dapat dilakukan berkali-kali.
* Digunakan untuk mengubah kondisi waktu dari ganjil ke genap atau sebaliknya sebelum melanjutkan perjalanan.

---

### 4. Charging Station (C)

Pada node yang termasuk **Charging Station**, robot dapat mengisi ulang energi hingga kapasitas maksimum.

```text
Energi Maksimum = 1000
```

---

### 5. Batas Energi

* Robot memulai perjalanan dengan energi penuh (`1000`).
* Energi akan berkurang sesuai energi aktual yang digunakan.
* Jika energi tidak mencukupi untuk melewati edge berikutnya dan tidak ada charging station yang dapat dicapai, maka perjalanan dinyatakan gagal.

---

### 6. Tujuan

Menentukan:

1. Jalur dari **S** ke **T**.
2. Total energi minimum yang dikonsumsi.
3. Waktu tiba pada setiap node yang dilalui.

---

## Format Input

### Baris 1

```text
N M
```

Jumlah node dan edge.

---

### M Baris Berikutnya

```text
u v w o
```

Keterangan:

* `u` = node asal
* `v` = node tujuan
* `w` = panjang dasar jalan
* `o` = bobot obstacle

---

### Baris Berikutnya

```text
S T
```

Node awal dan node tujuan.

---

### Baris Berikutnya

Daftar Rest Point:

```text
A C D
```

atau

```text
-
```

jika tidak ada.

---

### Baris Berikutnya

Daftar Charging Station:

```text
B E
```

atau

```text
-
```

---

### Baris Berikutnya

Node Mechanic:

```text
M
```

atau

```text
-
```

---

### Baris Berikutnya

Node Electrical:

```text
E
```

atau

```text
-
```

---

### Baris Terakhir

Jam awal perjalanan:

```text
1
```

Contoh:

* `1` → jam ganjil
* `2` → jam genap

---

## Format Output

### Jika Berhasil

```text
Total energi minimum: <nilai>

Jalur:
S -> ... -> T

Waktu tiba:
Node (menit x)
Node (menit y)
...
```

Contoh:

```text
Total energi minimum: 960

Jalur:
S -> A -> C -> D -> E -> T

Waktu tiba:
S (menit 0)
A (menit 2)
C (menit 4)
D (menit 6)
E (menit 8)
T (menit 10)
```

---

### Jika Gagal

```text
Robot gagal dalam mencapai tujuan :(
```

---

## Batasan

| Parameter        | Nilai   |
| ---------------- | ------- |
| N                | ≤ 200   |
| M                | ≤ 2000  |
| w                | 0 – 500 |
| o                | 0 – 500 |
| Energi Maksimum  | 1000    |
| Rest Point       | ≤ 10    |
| Charging Station | ≤ 10    |

---

# Contoh Kasus

## Sample Input 1

```text
6 7

S A 200 0
A B 300 50
A C 150 0
B D 400 100
C D 100 0
D E 250 0
E T 200 0

S T
C
E
M
-
1
```

## Sample Output 1

```text
Total energi minimum: 960

Jalur:
S -> A -> C -> D -> E -> T

Waktu tiba:
S (menit 0)
A (menit 2)
C (menit 4)
D (menit 6)
E (menit 8)
T (menit 10)
```

---

## Sample Input 2

```text
4 3

S A 600 200
A B 300 0
B T 200 0

S T
-
-
-
-
1
```

## Sample Output 2

```text
Robot gagal dalam mencapai tujuan :(
```

---
