/*
 * luong.c
 * Cài đặt các chức năng tính lương.
 *
 * Công thức:
 *   donGiaNgay = luongCoBan / 26
 *   donGiaGio  = donGiaNgay / 8
 *   Luong      = donGiaNgay * soCong + donGiaGio * 1.5 * gioOT + phuCap
 */
#include <stdio.h>
#include "luong.h"
#include "nhanvien.h"
#include "thongke.h"
#include "tienich.h"

/* Tính lương thực nhận của 1 nhân viên trong tháng */
double tinhLuong(NhanVien *nv, int thang, int nam) {
    double donGiaNgay = nv->luongCoBan / CONG_CHUAN;
    double donGiaGio = donGiaNgay / GIO_CHUAN;
    float soCong = demCongThang(nv->dsChamCong, thang, nam);
    float gioOT = tongOTThang(nv->dsChamCong, thang, nam);

    return donGiaNgay * soCong + donGiaGio * HE_SO_OT * gioOT + nv->phuCap;
}

/* ================== F3.1 LƯƠNG 1 NHÂN VIÊN ================== */
void inLuongMotNV(DanhSachNV *d) {
    int viTri, thang, nam;
    NhanVien *nv;
    double donGiaNgay, donGiaGio, luongCong, luongOT;
    float soCong, gioOT;

    printf("\n----- TINH LUONG 1 NHAN VIEN -----\n");
    viTri = chonNV(d);
    if (viTri == -1) return;
    nv = &d->ds[viTri];
    nhapThangNam(&thang, &nam);

    donGiaNgay = nv->luongCoBan / CONG_CHUAN;
    donGiaGio = donGiaNgay / GIO_CHUAN;
    soCong = demCongThang(nv->dsChamCong, thang, nam);
    gioOT = tongOTThang(nv->dsChamCong, thang, nam);
    luongCong = donGiaNgay * soCong;
    luongOT = donGiaGio * HE_SO_OT * gioOT;

    printf("\nPHIEU LUONG THANG %02d/%04d\n", thang, nam);
    printf("Nhan vien        : %s - %s\n", nv->maNV, nv->hoTen);
    printf("Phong ban        : %s\n", nv->phongBan);
    printf("Chuc vu          : %s\n", nv->chucVu);
    printf("----------------------------------------\n");
    printf("Luong co ban     : %15.0f VND\n", nv->luongCoBan);
    printf("Don gia ngay     : %15.0f VND (= LCB / %d)\n", donGiaNgay, CONG_CHUAN);
    printf("Don gia gio      : %15.0f VND (= don gia ngay / %d)\n", donGiaGio, GIO_CHUAN);
    printf("So cong          : %15.2f\n", soCong);
    printf("Gio lam them     : %15.2f\n", gioOT);
    printf("----------------------------------------\n");
    printf("Luong theo cong  : %15.0f VND\n", luongCong);
    printf("Luong lam them   : %15.0f VND (he so %.1f)\n", luongOT, HE_SO_OT);
    printf("Phu cap          : %15.0f VND\n", nv->phuCap);
    printf("----------------------------------------\n");
    printf("THUC NHAN        : %15.0f VND\n", luongCong + luongOT + nv->phuCap);
}

/* ================== F3.2 BẢNG LƯƠNG THÁNG ================== */
void inBangLuong(DanhSachNV *d) {
    int thang, nam, i;
    NhanVien *nv;
    double luong, tong = 0;

    printf("\n----- BANG LUONG THANG -----\n");
    if (d->soLuong == 0) {
        printf("=> Danh sach nhan vien dang rong!\n");
        return;
    }
    nhapThangNam(&thang, &nam);

    printf("\nBANG LUONG THANG %02d/%04d\n", thang, nam);
    printf("%-8s %-25s %8s %8s %12s %10s %14s\n",
           "Ma NV", "Ho ten", "So cong", "Gio OT", "Luong CB", "Phu cap", "Thuc nhan");
    printf("------------------------------------------------------------------------------------------\n");
    for (i = 0; i < d->soLuong; i++) {
        nv = &d->ds[i];
        luong = tinhLuong(nv, thang, nam);
        tong += luong;
        printf("%-8s %-25s %8.2f %8.2f %12.0f %10.0f %14.0f\n",
               nv->maNV, nv->hoTen,
               demCongThang(nv->dsChamCong, thang, nam),
               tongOTThang(nv->dsChamCong, thang, nam),
               nv->luongCoBan, nv->phuCap, luong);
    }
    printf("------------------------------------------------------------------------------------------\n");
    printf("%-77s %14.0f\n", "TONG CONG", tong);
}

/* ================== F3.3 XUẤT BẢNG LƯƠNG RA FILE CSV ================== */
void xuatBangLuongCSV(DanhSachNV *d) {
    int thang, nam, i;
    char tenFile[50];
    FILE *f;
    NhanVien *nv;
    double donGiaGio, luongOT;
    float soCong, gioOT;

    printf("\n----- XUAT BANG LUONG RA FILE CSV -----\n");
    if (d->soLuong == 0) {
        printf("=> Danh sach nhan vien dang rong!\n");
        return;
    }
    nhapThangNam(&thang, &nam);

    snprintf(tenFile, sizeof(tenFile), "bangluong_%02d_%04d.csv", thang, nam);
    f = fopen(tenFile, "w");
    if (f == NULL) {
        printf("=> Khong tao duoc file %s!\n", tenFile);
        return;
    }

    /* 3 byte BOM để Excel hiểu file là UTF-8 */
    fprintf(f, "\xEF\xBB\xBF");
    fprintf(f, "MaNV,HoTen,PhongBan,SoCong,GioOT,LuongCoBan,PhuCap,LuongOT,ThucNhan\n");
    for (i = 0; i < d->soLuong; i++) {
        nv = &d->ds[i];
        soCong = demCongThang(nv->dsChamCong, thang, nam);
        gioOT = tongOTThang(nv->dsChamCong, thang, nam);
        donGiaGio = nv->luongCoBan / CONG_CHUAN / GIO_CHUAN;
        luongOT = donGiaGio * HE_SO_OT * gioOT;
        /* Họ tên và phòng ban đặt trong dấu ngoặc kép phòng trường hợp có dấu phẩy */
        fprintf(f, "%s,\"%s\",\"%s\",%.2f,%.2f,%.0f,%.0f,%.0f,%.0f\n",
                nv->maNV, nv->hoTen, nv->phongBan, soCong, gioOT,
                nv->luongCoBan, nv->phuCap, luongOT, tinhLuong(nv, thang, nam));
    }
    fclose(f);
    printf("=> Da xuat bang luong ra file %s\n", tenFile);
}
