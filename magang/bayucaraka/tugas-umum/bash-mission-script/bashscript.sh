#!/bin/env bash
#Author: Julianda Caesar Prakoso
#Deskripsi: Script Bash untuk otomatisasi tugas dasar programmer pemula

PROJECT_DIR="$HOME"

show_menu() {
    echo "================================================="
    echo "              Bash Script Automation"
    echo "================================================="
    echo "1. Buat project folder baru"
    echo "2. Inisialisasi Git repository"
    echo "3. Buat struktur file dasar (src, docs, README)"
    echo "4. Compile & Run program C++"
    echo "5. Run program Python"
    echo "6. Backup folder project ke .zip"
    echo "7. Update sistem (apt update & upgrade)"
    echo "8. Keluar"
    echo "================================================="
}

create_project() {
    read -p "Masukkan nama project: " pname
    mkdir -p "$PROJECT_DIR/$pname"
    echo "Project dibuat di: $PROJECT_DIR/$pname"
}

init_git() {
    read -p "Masukkan nama folder project: " pname
    cd "$PROJECT_DIR/$pname" 2>/dev/null || { echo "Folder tidak ditemukan!"; return; }
    git init
    echo "Git repository berhasil diinisialisasi."
}

create_structure() {
    read -p "Masukkan nama folder project: " pname
    cd "$PROJECT_DIR/$pname" 2>/dev/null || { echo "Folder tidak ditemukan!"; return; }

    mkdir -p src docs
    touch README.md src/main.cpp src/main.py

    echo "# $pname" > README.md
    echo "Project created using DevHelper script." >> README.md

    echo "Struktur project berhasil dibuat:"
    tree -a 2>/dev/null || ls -R
}

run_cpp() {
    read -p "Masukkan nama folder project: " pname
    cd "$PROJECT_DIR/$pname" 2>/dev/null || { echo "Folder tidak ditemukan!"; return; }

    read -p "Masukkan file C++ (contoh: src/main.cpp): " cppfile

    if [ ! -f "$cppfile" ]; then
        echo "File tidak ditemukan!"
        return
    fi

    g++ "$cppfile" -o output
    if [ $? -eq 0 ]; then
        echo "Compile sukses, menjalankan program..."
        ./output
    else
        echo "Compile gagal!"
    fi
}

run_python() {
    read -p "Masukkan nama folder project: " pname
    cd "$PROJECT_DIR/$pname" 2>/dev/null || { echo "Folder tidak ditemukan!"; return; }

    read -p "Masukkan file Python (contoh: src/main.py): " pyfile

    if [ ! -f "$pyfile" ]; then
        echo "File tidak ditemukan!"
        return
    fi

    python3 "$pyfile"
}

backup_project() {
    read -p "Masukkan nama folder project: " pname
    cd "$PROJECT_DIR" 2>/dev/null || { echo "Folder Projects tidak ditemukan!"; return; }

    if [ ! -d "$pname" ]; then
        echo "Project tidak ditemukan!"
        return
    fi

    zip -r "${pname}_backup.zip" "$pname" >/dev/null
    echo "Backup berhasil dibuat: $PROJECT_DIR/${pname}_backup.zip"
}

update_system() {
    echo "Menjalankan apt update dan apt upgrade..."
    sudo apt update && sudo apt upgrade -y
}

while true; do
    show_menu
    read -p "Pilih menu [1-8]: " choice

    case $choice in
        1) create_project ;;
        2) init_git ;;
        3) create_structure ;;
        4) run_cpp ;;
        5) run_python ;;
        6) backup_project ;;
        7) update_system ;;
        8) echo "Keluar dari program..."; exit 0 ;;
        *) echo "Pilihan tidak valid!" ;;
    esac

    echo ""
    read -p "Tekan Enter untuk lanjut..."
    clear
done
