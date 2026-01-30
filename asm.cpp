#include <stdio.h>
#include <conio.h>
#include <math.h>
#include <string.h>

#define sl 100

// --- Y1: KHAI BÁO CẤU TRÚC DỮ LIỆU ---

struct Date { 
    int ngay;
    int thang;
    int nam;
};
typedef struct Date date;

struct NhanVien {
    int msnv;
    char ho[20];
    char ten[20];
    date namsinh;
    char noisinh[100];
    char diachi[200];
    float luong;
    date ngayvao;
};
typedef struct NhanVien nhanvien;

struct DanhSach {
    nhanvien a[sl];
    int n;          
};
typedef struct DanhSach danhsach;

// --- Y2: CÁC HÀM CHỨC NĂNG ---

// Hàm nhập ngày tháng
void nhapngaythang(date &ntn) {
    scanf("%d/%d/%d", &ntn.ngay, &ntn.thang, &ntn.nam);
}

// Hàm nhập 1 nhân viên
void nhap1nv(nhanvien &nv) {
    printf("Nhap MSNV: "); scanf("%d", &nv.msnv);
    fflush(stdin);
    printf("Nhap Ho: "); scanf("%s", &nv.ho); //gets(nv.ho);
    printf("Nhap Ten: "); scanf("%s", &nv.ten); //gets(nv.ten);
    printf("Nhap ngay sinh (dd/mm/yyyy): "); nhapngaythang(nv.namsinh);
    fflush(stdin);
    printf("Nhap noi sinh: ");scanf("%s", &nv.noisinh); //gets(nv.noisinh);
    printf("Nhap dia chi: ");scanf("%s", &nv.diachi); //gets(nv.diachi);
    printf("Nhap luong: "); scanf("%f", &nv.luong);
    printf("Nhap ngay vao lam (dd/mm/yyyy): "); nhapngaythang(nv.ngayvao);
    fflush(stdin);
}

// Hàm xuất 1 nhân viên
void xuat1nv(nhanvien nv) {
    printf("%-5d | %-15s | %-7s | %02d/%02d/%d | %-10.2f\n", 
           nv.msnv, nv.ho, nv.ten, nv.namsinh.ngay, nv.namsinh.thang, nv.namsinh.nam, nv.luong);
}

// Y2.2: Nhập danh sách nhân viên
void nhapdanhsach(danhsach &ds) {
    printf("Nhap so luong nhan vien: ");
    scanf("%d", &ds.n);
    for(int i = 0; i < ds.n; i++) {
        printf("Nhap nhan vien thu %d:\n", i + 1);
        nhap1nv(ds.a[i]); // Goi ham nhap 1 nhan vien
    }
}

// Y2.3: Xuất danh sách nhân viên 
void xuatdanhsach(danhsach ds) {
    printf("\n--- DANH SACH NHAN VIEN ---\n");
    for(int i = 0; i < ds.n; i++) {
        xuat1nv(ds.a[i]); // Goi ham xuat 1 nhan vien 
    }
}

// Y2.4: Tìm nhân viên theo tên (Tìm kiếm tuần tự) 
int timten(danhsach ds, char *tenCanTim) {
    for(int i = 0; i < ds.n; i++) {
        if(strcmp(ds.a[i].ten, tenCanTim) == 0) { // Su dung strcmp 
            return i; // Tra ve vi tri tim thay
        }
    }
    return -1; // Khong tim thay 
}

// Y2.5: Tìm nhân viên theo MSNV 
int timMSNV(danhsach ds, int msnvCanTim) {
    for(int i = 0; i < ds.n; i++) {
        if(ds.a[i].msnv == msnvCanTim) {
return i; // Tra ve vi tri tim thay 
        }
    }
    return -1; // Khong tim thay
}

// Y2.6: Sắp xếp danh sách theo lương giảm dần (Interchange Sort) 
void sapxep(danhsach &ds) {
    for(int i = 0; i < ds.n - 1; i++) {     // Duyet tu i=0 den n-1 
        for(int j = i + 1; j < ds.n; j++) { // Duyet tu j=i+1 den n 
            if(ds.a[i].luong < ds.a[j].luong) { // Luong i < luong j thi hoan doi 
                nhanvien temp = ds.a[i];    // Hoan doi doi tuong nhan vien 
                ds.a[i] = ds.a[j];
                ds.a[j] = temp;
            }
        }
    }
}

// Y2.7: Xóa nhân viên theo MSNV
void xoanv(danhsach &ds, int msnvXoa) {
    int pos = timMSNV(ds, msnvXoa); // Goi lai ham tim MSNV
    if(pos == -1) {
        printf("Khong tim thay nhan vien can xoa!\n"); 
    } else {
        for(int i = pos; i < ds.n - 1; i++) {
            ds.a[i] = ds.a[i+1]; // Duyet va don danh sach 
        }
        ds.n--; // Giam so luong n-1 
        printf("Da xoa nhan vien co MSNV: %d\n", msnvXoa);
    }
}

// Y2.1: Menu điều khiển 
void menu() {
    danhsach ds;
    ds.n = 0;
    int chon, msnv, pos;
    char ten[20];

    do {
        printf("\n\t\t--- MENU --- [cite: 121]");
        printf("\n\t1. Nhap danh sach nhan vien");
        printf("\n\t2. Xuat danh sach nhan vien");
        printf("\n\t3. Them vao 1 nhan vien [cite: 123]");
        printf("\n\t4. Tim nhan vien theo ma so [cite: 124]");
        printf("\n\t5. Tim nhan vien theo ten [cite: 125]");
        printf("\n\t6. Bang luong nhan vien giam dan [cite: 126]");
        printf("\n\t7. Xoa 1 nhan vien [cite: 128]");
        printf("\n\t0. Thoat");
        printf("\n\tChon chuc nang: ");
        scanf("%d", &chon);

        switch(chon) {
            case 1: nhapdanhsach(ds); break;
            case 2: xuatdanhsach(ds); break;
            case 3: 
                if(ds.n < sl) {
                    nhap1nv(ds.a[ds.n]);
                    ds.n++;
                }
                break;
            case 4:
                printf("Nhap MSNV can tim: "); scanf("%d", &msnv);
                pos = timMSNV(ds, msnv);
                if(pos != -1) xuat1nv(ds.a[pos]);
                else printf("Khong tim thay!");
                break;
            case 5:
                fflush(stdin);
                printf("Nhap ten can tim: "); gets(ten);
                pos = timten(ds, ten);
                if(pos != -1) xuat1nv(ds.a[pos]);
                else printf("Khong tim thay!");
                break;
            case 6:
                sapxep(ds);
                xuatdanhsach(ds);
                break;
            case 7:
                printf("Nhap MSNV can xoa: "); scanf("%d", &msnv);
                xoanv(ds, msnv);
                break;
        }
    } while(chon != 0);
}

int main() { 
    menu();
    return 0;
}