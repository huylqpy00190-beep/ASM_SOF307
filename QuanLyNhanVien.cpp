#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define sl 100

// --- CAU TRUC DU LIEU ---
struct Date { 
    int ngay, thang, nam;
};

struct NhanVien {
    int msnv;
    char ho[30];
    char ten[20];
    Date namsinh;
    char noisinh[100];
    char diachi[200];
    float luong;
    Date ngayvao;
};

struct DanhSach {
    NhanVien a[sl];
    int n;           
};

void khoiTao(DanhSach &ds) {
    // Nhan vien 1
    ds.a[0].msnv = 1;
    strcpy(ds.a[0].ho, "Nguyen Van");
    strcpy(ds.a[0].ten, "An");
    ds.a[0].namsinh = {15, 5, 1995};
    strcpy(ds.a[0].noisinh, "Ha Noi");
    strcpy(ds.a[0].diachi, "123 Cau Giay");
    ds.a[0].luong = 15000000;
    ds.a[0].ngayvao = {1, 1, 2020};

    // Nhan vien 2
    ds.a[1].msnv = 2;
    strcpy(ds.a[1].ho, "Tran Thi");
    strcpy(ds.a[1].ten, "Binh");
    ds.a[1].namsinh = {20, 8, 1998};
    strcpy(ds.a[1].noisinh, "Da Nang");
    strcpy(ds.a[1].diachi, "456 Hai Chau");
    ds.a[1].luong = 18000000;
    ds.a[1].ngayvao = {15, 3, 2021};

    // Nhan vien 3
    ds.a[2].msnv = 3;
    strcpy(ds.a[2].ho, "Le Minh");
    strcpy(ds.a[2].ten, "Cuong");
    ds.a[2].namsinh = {10, 12, 1992};
    strcpy(ds.a[2].noisinh, "TP HCM");
    strcpy(ds.a[2].diachi, "789 Quan 1");
    ds.a[2].luong = 22000000;
    ds.a[2].ngayvao = {20, 5, 2019};

    ds.n = 3; 
}

// --- HAM HO TRO ---

void xoaDem() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void xoaXuongDong(char x[]) {
    size_t len = strlen(x);
    if (len > 0 && x[len-1] == '\n') x[len-1] = '\0';
}

int nhapSoNguyen(const char *prompt) {
    char s[20];
    int check;
    while (1) {
        printf("%s", prompt);
        scanf("%s", s);
        check = 1;
        for (int i = 0; i < strlen(s); i++) {
            if (s[i] < '0' || s[i] > '9') { check = 0; break; }
        }
        if (check) return atoi(s);
        else printf("[!] Loi: Vui long chi nhap SO NGUYEN!\n");
    }
}

float nhapSoThuc(const char *prompt) {
    char s[20];
    char *endptr;
    float n;
    while (1) {
        printf("%s", prompt);
        scanf("%s", s);
        n = strtof(s, &endptr);
        if (*endptr == '\0') return n;
        else printf("[!] Loi: Vui long chi nhap SO THUC (Vi du: 1500)!\n");
    }
}

int kiemTraTrungMSNV(DanhSach ds, int msnvMoi) {
    for (int i = 0; i < ds.n; i++) {
        if (ds.a[i].msnv == msnvMoi) return 1; 
    }
    return 0; 
}

void dinhDangLuong(float luong, char *ketQua) {
    char s[50];
    sprintf(s, "%lld", (long long)luong); 
    int len = strlen(s);
    int dotCount = (len - 1) / 3;
    int targetLen = len + dotCount;
    ketQua[targetLen] = '\0';
    int i = len - 1, j = targetLen - 1, count = 0;
    while (i >= 0) {
        ketQua[j--] = s[i--];
        count++;
        if (count == 3 && i >= 0) {
            ketQua[j--] = '.'; 
            count = 0;
        }
    }
}

// --- NHAP / XUAT ---

void nhap1nv(NhanVien &nv, DanhSach ds) {
    int msnvTam;
    while (1) {
        msnvTam = nhapSoNguyen("=> Nhap MSNV: ");
        if (kiemTraTrungMSNV(ds, msnvTam)) {
            printf("[!] Loi: MSNV %d da ton tai!\n", msnvTam);
        } else {
            nv.msnv = msnvTam;
            break; 
        }
    }
    xoaDem();
    printf("=> Nhap Ho: "); fgets(nv.ho, sizeof(nv.ho), stdin); xoaXuongDong(nv.ho);
    printf("=> Nhap Ten: "); fgets(nv.ten, sizeof(nv.ten), stdin); xoaXuongDong(nv.ten);
    printf("=> Ngay sinh (dd/mm/yyyy): "); scanf("%d/%d/%d", &nv.namsinh.ngay, &nv.namsinh.thang, &nv.namsinh.nam);
    xoaDem();
    printf("=> Noi sinh: "); fgets(nv.noisinh, sizeof(nv.noisinh), stdin); xoaXuongDong(nv.noisinh);
    printf("=> Dia chi: "); fgets(nv.diachi, sizeof(nv.diachi), stdin); xoaXuongDong(nv.diachi);
    nv.luong = nhapSoThuc("=> Luong: ");
    printf("=> Ngay vao lam (dd/mm/yyyy): "); scanf("%d/%d/%d", &nv.ngayvao.ngay, &nv.ngayvao.thang, &nv.ngayvao.nam);
    xoaDem();
}

void xuatTieuDe() {
    printf("\n%-5s | %-18s | %-8s | %-10s | %-15s | %-20s | %-15s | %-10s\n", 
           "MSNV", "HO", "TEN", "NGAY SINH", "NOI SINH", "DIA CHI", "LUONG (VND)", "NGAY VAO");
    printf("---------------------------------------------------------------------------------------------------------------------\n");
}

void xuat1nv(NhanVien nv) {
    char luongStr[50], ns[15], nvStr[15];
    dinhDangLuong(nv.luong, luongStr); 
    sprintf(ns, "%02d/%02d/%d", nv.namsinh.ngay, nv.namsinh.thang, nv.namsinh.nam);
    sprintf(nvStr, "%02d/%02d/%d", nv.ngayvao.ngay, nv.ngayvao.thang, nv.ngayvao.nam);

    printf("%-5d | %-18s | %-8s | %-10s | %-15s | %-20s | %-15s | %-10s\n", 
           nv.msnv, nv.ho, nv.ten, ns, nv.noisinh, nv.diachi, luongStr, nvStr);
}

// --- CHUC NANG ---

int timMSNV(DanhSach ds, int msnvCanTim) {
    for(int i = 0; i < ds.n; i++) if(ds.a[i].msnv == msnvCanTim) return i;
    return -1;
}

int timTen(DanhSach ds, char *tenCanTim) {
    for(int i = 0; i < ds.n; i++) if(strcmp(ds.a[i].ten, tenCanTim) == 0) return i;
    return -1;
}

void sua1nv(NhanVien &nv, DanhSach ds) {
    int chon;
    do {
        printf("\n========= BANG CHINH SUA =========\n");
        printf("1. Ho va Ten           2. Ngay sinh\n");
        printf("3. Noi sinh            4. Dia chi\n");
        printf("5. Luong               6. Ngay vao lam\n");
        printf("7. SUA TAT CA          0. Thoat\n");
        chon = nhapSoNguyen("Chon muc can sua: ");
        xoaDem();
        switch(chon) {
            case 1:
                printf("Ho moi: "); fgets(nv.ho, sizeof(nv.ho), stdin); xoaXuongDong(nv.ho);
                printf("Ten moi: "); fgets(nv.ten, sizeof(nv.ten), stdin); xoaXuongDong(nv.ten);
                break;
            case 2:
                printf("Ngay sinh (dd/mm/yyyy): "); scanf("%d/%d/%d", &nv.namsinh.ngay, &nv.namsinh.thang, &nv.namsinh.nam);
                break;
            case 5: nv.luong = nhapSoThuc("Luong moi: "); break;
            case 7: 
                printf("[Sua cho MSNV: %d]\n", nv.msnv);
                printf("=> Ho moi: "); fgets(nv.ho, sizeof(nv.ho), stdin); xoaXuongDong(nv.ho);
                printf("=> Ten moi: "); fgets(nv.ten, sizeof(nv.ten), stdin); xoaXuongDong(nv.ten);
                nv.luong = nhapSoThuc("=> Luong moi: ");
                break;
            case 0: break;
        }
    } while(chon != 0);
}

void xuatDanhSach(DanhSach ds) {
    if(ds.n == 0) { printf("\n(!) Danh sach trong.\n"); return; }
    xuatTieuDe(); 
    for(int i = 0; i < ds.n; i++) xuat1nv(ds.a[i]);
    printf("---------------------------------------------------------------------------------------------------------------------\n");
}

void sapXepLuong(DanhSach &ds) {
    for(int i = 0; i < ds.n - 1; i++) {
        for(int j = i + 1; j < ds.n; j++) {
            if(ds.a[i].luong < ds.a[j].luong) {
                NhanVien t = ds.a[i]; ds.a[i] = ds.a[j]; ds.a[j] = t;
            }
        }
    }
    printf("\n[OK] Da sap xep luong giam dan.\n");
}

void xoaNhanVien(DanhSach &ds) {
    if(ds.n == 0) return;
    int msnv = nhapSoNguyen("Nhap MSNV can xoa: ");
    int pos = timMSNV(ds, msnv);
    if(pos == -1) printf("[!] Khong tim thay!\n");
    else {
        for(int i = pos; i < ds.n - 1; i++) ds.a[i] = ds.a[i+1];
        ds.n--;
        printf("[OK] Da xoa thanh cong.\n");
    }
}

void hoiThoat() {
    printf("\n[1] Ve Menu | [0] Thoat: ");
    int chon = nhapSoNguyen("");
    if (chon == 0) exit(0);
}

void menu() {
    DanhSach ds; ds.n = 0;
    khoiTao(ds);
    int chon, pos, msnv;
    char ten[20];
    do {
        printf("\n********** QUAN LY NHAN VIEN **********\n");
        printf("* 1. Nhap danh sach                   *\n");
        printf("* 2. Xuat danh sach                   *\n");
        printf("* 3. Them 1 nhan vien                 *\n");
        printf("* 4. Tim MSNV & Sua                   *\n");
        printf("* 5. Tim Ten & Sua                    *\n");
        printf("* 6. Sap xep luong                    *\n");
        printf("* 7. Xoa nhan vien                    *\n");
        printf("* 0. Thoat                            *\n");
        printf("***************************************\n");
        chon = nhapSoNguyen("Chon chuc nang: ");
        switch(chon) {
            case 1:
                int soLuong;
                soLuong = nhapSoNguyen("Nhap so luong: ");
                for(int i = 0; i < soLuong; i++) {
                    if (ds.n < sl) { nhap1nv(ds.a[ds.n], ds); ds.n++; }
                }
                hoiThoat(); break;
            case 2: xuatDanhSach(ds); hoiThoat(); break;
            case 3: if(ds.n < sl) { nhap1nv(ds.a[ds.n], ds); ds.n++; } hoiThoat(); break;
            case 4:
                msnv = nhapSoNguyen("Nhap MSNV: ");
                pos = timMSNV(ds, msnv);
                if(pos != -1) { xuatTieuDe(); xuat1nv(ds.a[pos]); sua1nv(ds.a[pos], ds); }
                hoiThoat(); break;
            case 6: sapXepLuong(ds); xuatDanhSach(ds); hoiThoat(); break;
            case 7: xoaNhanVien(ds); hoiThoat(); break;
        }
    } while(chon != 0);
}

int main() {
    menu();
    return 0;
}