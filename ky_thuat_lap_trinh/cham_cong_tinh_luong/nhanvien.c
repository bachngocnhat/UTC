/*
 * nhanvien.c
 * Cài đặt các chức năng quản lý nhân viên.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "nhanvien.h"
#include "chamcong.h"
#include "tienich.h"

/* ================== KHỞI TẠO / GIẢI PHÓNG ================== */

/* Cấp phát mảng ban đầu chứa được 10 nhân viên */
void khoiTaoDS(DanhSachNV *d) {
    d->soLuong = 0;
    d->sucChua = 10;
    d->ds = (NhanVien *)malloc(d->sucChua * sizeof(NhanVien));
    if (d->ds == NULL) {
        printf("Loi: khong du bo nho!\n");
        exit(1);
    }
}

/* Xoá hết nhân viên (giải phóng danh sách chấm công) nhưng vẫn giữ mảng */
void xoaHetNV(DanhSachNV *d) {
    int i;
    for (i = 0; i < d->soLuong; i++) {
        giaiPhongCC(d->ds[i].dsChamCong);
        d->ds[i].dsChamCong = NULL;
    }
    d->soLuong = 0;
}

/* Giải phóng toàn bộ bộ nhớ khi thoát chương trình */
void giaiPhongDS(DanhSachNV *d) {
    xoaHetNV(d);
    free(d->ds);
    d->ds = NULL;
    d->sucChua = 0;
}

/* ================== HÀM CƠ BẢN ================== */

/* Tìm vị trí nhân viên theo mã. Trả về -1 nếu không có */
int timViTriNV(DanhSachNV *d, const char *ma) {
    int i;
    for (i = 0; i < d->soLuong; i++) {
        if (strcmp(d->ds[i].maNV, ma) == 0) {
            return i;
        }
    }
    return -1;
}

/* Thêm 1 nhân viên vào cuối mảng. Mảng đầy thì tăng gấp đôi.
   Trả về 1 nếu thành công, 0 nếu trùng mã hoặc hết bộ nhớ. */
int themNVVaoDS(DanhSachNV *d, NhanVien nv) {
    if (timViTriNV(d, nv.maNV) != -1) {
        return 0;
    }
    if (d->soLuong == d->sucChua) {
        int sucChuaMoi = d->sucChua * 2;
        NhanVien *mangMoi = (NhanVien *)realloc(d->ds, sucChuaMoi * sizeof(NhanVien));
        if (mangMoi == NULL) {
            printf("Loi: khong du bo nho!\n");
            return 0;
        }
        d->ds = mangMoi;
        d->sucChua = sucChuaMoi;
    }
    d->ds[d->soLuong] = nv;
    d->soLuong++;
    return 1;
}

/* Hỏi mã nhân viên và trả về vị trí trong mảng, -1 nếu không tìm thấy */
int chonNV(DanhSachNV *d) {
    char ma[10];
    int viTri;
    if (d->soLuong == 0) {
        printf("=> Danh sach nhan vien dang rong!\n");
        return -1;
    }
    nhapChuoi("Nhap ma nhan vien: ", ma, sizeof(ma));
    chuHoa(ma);
    viTri = timViTriNV(d, ma);
    if (viTri == -1) {
        printf("=> Khong tim thay nhan vien co ma %s!\n", ma);
    }
    return viTri;
}

void inTieuDeNV(void) {
    printf("%-4s %-8s %-25s %-15s %-15s %12s\n",
           "STT", "Ma NV", "Ho ten", "Phong ban", "Chuc vu", "Luong CB");
    printf("-------------------------------------------------------------------------------------\n");
}

void inMotNV(int stt, NhanVien *nv) {
    printf("%-4d %-8s %-25s %-15s %-15s %12.0f\n",
           stt, nv->maNV, nv->hoTen, nv->phongBan, nv->chucVu, nv->luongCoBan);
}

/* ================== F1.1 THÊM NHÂN VIÊN ================== */
void themNV(DanhSachNV *d) {
    NhanVien nv;
    printf("\n----- THEM NHAN VIEN -----\n");

    /* Nhập mã, kiểm tra không trùng */
    while (1) {
        nhapChuoi("Ma nhan vien (VD: NV001): ", nv.maNV, sizeof(nv.maNV));
        chuHoa(nv.maNV);
        if (timViTriNV(d, nv.maNV) != -1) {
            printf("  -> Ma nhan vien da ton tai!\n");
        } else {
            break;
        }
    }
    nhapChuoi("Ho ten: ", nv.hoTen, sizeof(nv.hoTen));
    nhapChuoi("Phong ban: ", nv.phongBan, sizeof(nv.phongBan));
    nhapChuoi("Chuc vu: ", nv.chucVu, sizeof(nv.chucVu));
    nv.luongCoBan = nhapSoThuc("Luong co ban (VND): ", 1, 1000000000);
    nv.dsChamCong = NULL;   /* nhân viên mới chưa có chấm công */

    if (themNVVaoDS(d, nv)) {
        printf("=> Them nhan vien thanh cong!\n");
    }
}

/* ================== F1.2 HIỂN THỊ DANH SÁCH ================== */
void hienThiDS(DanhSachNV *d) {
    int i;
    printf("\n----- DANH SACH NHAN VIEN (%d nguoi) -----\n", d->soLuong);
    if (d->soLuong == 0) {
        printf("Danh sach rong.\n");
        return;
    }
    inTieuDeNV();
    for (i = 0; i < d->soLuong; i++) {
        inMotNV(i + 1, &d->ds[i]);
    }
}

/* ================== F1.3 SỬA THÔNG TIN ================== */
void suaNV(DanhSachNV *d) {
    int viTri, chon;
    NhanVien *nv;

    printf("\n----- SUA THONG TIN NHAN VIEN -----\n");
    viTri = chonNV(d);
    if (viTri == -1) return;
    nv = &d->ds[viTri];

    do {
        printf("\nThong tin hien tai:\n");
        inTieuDeNV();
        inMotNV(viTri + 1, nv);
        printf("\n1. Sua ho ten\n");
        printf("2. Sua phong ban\n");
        printf("3. Sua chuc vu\n");
        printf("4. Sua luong co ban\n");
        printf("0. Xong\n");
        chon = nhapSoNguyen("Chon: ", 0, 4);
        switch (chon) {
            case 1: nhapChuoi("Ho ten moi: ", nv->hoTen, sizeof(nv->hoTen)); break;
            case 2: nhapChuoi("Phong ban moi: ", nv->phongBan, sizeof(nv->phongBan)); break;
            case 3: nhapChuoi("Chuc vu moi: ", nv->chucVu, sizeof(nv->chucVu)); break;
            case 4: nv->luongCoBan = nhapSoThuc("Luong co ban moi: ", 1, 1000000000); break;
        }
        if (chon != 0) printf("=> Da cap nhat!\n");
    } while (chon != 0);
}

/* ================== F1.4 XOÁ NHÂN VIÊN ================== */
void xoaNV(DanhSachNV *d) {
    int viTri, i;

    printf("\n----- XOA NHAN VIEN -----\n");
    viTri = chonNV(d);
    if (viTri == -1) return;

    inTieuDeNV();
    inMotNV(viTri + 1, &d->ds[viTri]);
    if (!hoiCoKhong("Ban chac chan muon xoa nhan vien nay? (y/n): ")) {
        printf("=> Da huy.\n");
        return;
    }

    /* Giải phóng danh sách chấm công của nhân viên trước */
    giaiPhongCC(d->ds[viTri].dsChamCong);

    /* Dồn các phần tử phía sau lên 1 vị trí */
    for (i = viTri; i < d->soLuong - 1; i++) {
        d->ds[i] = d->ds[i + 1];
    }
    d->soLuong--;
    printf("=> Da xoa nhan vien!\n");
}
