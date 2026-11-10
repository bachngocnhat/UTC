/*
 * main.c
 * CHƯƠNG TRÌNH QUẢN LÝ CHẤM CÔNG & TÍNH LƯƠNG NHÂN VIÊN
 *
 * Biên dịch: gcc -std=c99 -Wall -o chamcong *.c
 * Chạy:      ./chamcong   (Windows: chamcong.exe)
 * Hoặc 1 lệnh gcc -std=c99 -Wall -o chamcong *.c && ./chamcong
 */
#include <stdio.h>
#include "kieudulieu.h"
#include "tienich.h"
#include "nhanvien.h"
#include "chamcong.h"
#include "luong.h"
#include "thongke.h"
#include "tepdulieu.h"

/* ================== 1. MENU NHÂN VIÊN ================== */
void menuNhanVien(DanhSachNV *d) {
    int chon;
    do {
        printf("\n========== QUAN LY NHAN VIEN ==========\n");
        printf("1. Them nhan vien\n");
        printf("2. Hien thi danh sach\n");
        printf("3. Sua thong tin nhan vien\n");
        printf("4. Xoa nhan vien\n");
        printf("5. Tim kiem nhan vien\n");
        printf("6. Sap xep danh sach\n");
        printf("0. Quay lai\n");
        chon = nhapSoNguyen("Chon: ", 0, 6);
        switch (chon) {
            case 1: themNV(d); break;
            case 2: hienThiDS(d); break;
            case 3: suaNV(d); break;
            case 4: xoaNV(d); break;
            case 5: timKiemNV(d); break;
            case 6: sapXepNV(d); break;
        }
        if (chon != 0) tamDung();
    } while (chon != 0);
}

/* ================== 2. MENU CHẤM CÔNG ================== */
void menuChamCong(DanhSachNV *d) {
    int chon;
    do {
        printf("\n============== CHAM CONG ==============\n");
        printf("1. Cham cong theo ngay\n");
        printf("2. Sua cham cong\n");
        printf("3. Xoa cham cong\n");
        printf("4. Xem lich su cham cong trong thang\n");
        printf("0. Quay lai\n");
        chon = nhapSoNguyen("Chon: ", 0, 4);
        switch (chon) {
            case 1: chamCongTheoNgay(d); break;
            case 2: suaChamCong(d); break;
            case 3: xoaChamCongNV(d); break;
            case 4: xemLichSu(d); break;
        }
        if (chon != 0) tamDung();
    } while (chon != 0);
}

/* ================== 3. MENU TÍNH LƯƠNG ================== */
void menuLuong(DanhSachNV *d) {
    int chon;
    do {
        printf("\n============== TINH LUONG =============\n");
        printf("1. Tinh luong 1 nhan vien\n");
        printf("2. Bang luong thang\n");
        printf("3. Xuat bang luong ra file CSV\n");
        printf("0. Quay lai\n");
        chon = nhapSoNguyen("Chon: ", 0, 3);
        switch (chon) {
            case 1: inLuongMotNV(d); break;
            case 2: inBangLuong(d); break;
            case 3: xuatBangLuongCSV(d); break;
        }
        if (chon != 0) tamDung();
    } while (chon != 0);
}

/* ================== 4. MENU THỐNG KÊ ================== */
void menuThongKe(DanhSachNV *d) {
    int chon;
    do {
        printf("\n=============== THONG KE ==============\n");
        printf("1. Thong ke gio cong theo thang\n");
        printf("2. Tong quy luong thang\n");
        printf("3. Danh sach nhan vien thieu cong\n");
        printf("0. Quay lai\n");
        chon = nhapSoNguyen("Chon: ", 0, 3);
        switch (chon) {
            case 1: thongKeGioCong(d); break;
            case 2: thongKeQuyLuong(d); break;
            case 3: thongKeThieuCong(d); break;
        }
        if (chon != 0) tamDung();
    } while (chon != 0);
}

/* ================== 5. MENU FILE ================== */
void menuFile(DanhSachNV *d) {
    int chon, ketQua;
    do {
        printf("\n============= TEP DU LIEU =============\n");
        printf("1. Luu du lieu ra file %s\n", TEN_FILE);
        printf("2. Doc lai du lieu tu file %s\n", TEN_FILE);
        printf("3. Nap du lieu mau (thang 10/2026)\n");
        printf("0. Quay lai\n");
        chon = nhapSoNguyen("Chon: ", 0, 3);
        switch (chon) {
            case 1:
                if (luuTep(d, TEN_FILE)) printf("=> Da luu %d nhan vien vao file %s\n", d->soLuong, TEN_FILE);
                else printf("=> Loi: khong ghi duoc file %s!\n", TEN_FILE);
                break;
            case 2:
                if (!hoiCoKhong("Du lieu chua luu se bi mat. Tiep tuc? (y/n): ")) break;
                ketQua = docTep(d, TEN_FILE);
                if (ketQua == 1) printf("=> Da doc %d nhan vien tu file %s\n", d->soLuong, TEN_FILE);
                else if (ketQua == 0) printf("=> File %s khong ton tai!\n", TEN_FILE);
                else printf("=> File %s sai dinh dang!\n", TEN_FILE);
                break;
            case 3:
                if (!hoiCoKhong("Du lieu hien tai se bi thay the. Tiep tuc? (y/n): ")) break;
                napDuLieuMau(d);
                printf("=> Da nap %d nhan vien mau. Hay xem thong ke/luong cua thang 10/2026.\n", d->soLuong);
                break;
        }
        if (chon != 0) tamDung();
    } while (chon != 0);
}

/* ================== MENU CHÍNH ================== */
int main(void) {
    DanhSachNV d;
    int chon, ketQua;

    khoiTaoDS(&d);

    /* Tự động đọc dữ liệu khi khởi động */
    ketQua = docTep(&d, TEN_FILE);
    if (ketQua == 1) printf("Da doc %d nhan vien tu file %s\n", d.soLuong, TEN_FILE);
    else if (ketQua == 0) printf("Chua co file %s, bat dau voi danh sach rong.\n", TEN_FILE);
    else printf("File %s sai dinh dang, bat dau voi danh sach rong.\n", TEN_FILE);

    do {
        printf("\n=======================================\n");
        printf("  QUAN LY CHAM CONG & TINH LUONG\n");
        printf("=======================================\n");
        printf("1. Quan ly nhan vien\n");
        printf("2. Cham cong\n");
        printf("3. Tinh luong\n");
        printf("4. Thong ke\n");
        printf("5. Tep du lieu\n");
        printf("0. Thoat\n");
        chon = nhapSoNguyen("Chon: ", 0, 5);
        switch (chon) {
            case 1: menuNhanVien(&d); break;
            case 2: menuChamCong(&d); break;
            case 3: menuLuong(&d); break;
            case 4: menuThongKe(&d); break;
            case 5: menuFile(&d); break;
        }
    } while (chon != 0);

    if (hoiCoKhong("Luu du lieu truoc khi thoat? (y/n): ")) {
        if (luuTep(&d, TEN_FILE)) printf("=> Da luu vao file %s\n", TEN_FILE);
        else printf("=> Loi: khong ghi duoc file!\n");
    }

    giaiPhongDS(&d);
    printf("Tam biet!\n");
    return 0;
}
