/*
 * tepdulieu.c
 * Cài đặt lưu / đọc file và dữ liệu mẫu.
 *
 * Định dạng file dulieu.txt:
 *   Dòng 1: số nhân viên
 *   Mỗi nhân viên:
 *     MaNV|HoTen|PhongBan|ChucVu|LuongCoBan|SoBanGhiChamCong
 *     dd/mm/yyyy|GioLam|GioThem        (lặp lại SoBanGhiChamCong dòng)
 */
#include <stdio.h>
#include <string.h>
#include "tepdulieu.h"
#include "nhanvien.h"
#include "chamcong.h"
#include "tienich.h"

/* ================== F5.1 LƯU FILE ================== */
/* Trả về 1 nếu lưu thành công, 0 nếu không mở được file */
int luuTep(DanhSachNV *d, const char *tenFile) {
    FILE *f;
    int i;
    NhanVien *nv;
    ChamCong *p;

    f = fopen(tenFile, "w");
    if (f == NULL) return 0;

    fprintf(f, "%d\n", d->soLuong);
    for (i = 0; i < d->soLuong; i++) {
        nv = &d->ds[i];
        fprintf(f, "%s|%s|%s|%s|%.0f|%d\n",
                nv->maNV, nv->hoTen, nv->phongBan, nv->chucVu,
                nv->luongCoBan, demBanGhi(nv->dsChamCong));

        p = nv->dsChamCong;
        while (p != NULL) {
            fprintf(f, "%02d/%02d/%04d|%.2f|%.2f\n",
                    p->ngay.ngay, p->ngay.thang, p->ngay.nam, p->gioLam, p->gioThem);
            p = p->next;
        }
    }
    fclose(f);
    return 1;
}

/* ================== F5.2 ĐỌC FILE ================== */
/* Trả về 1 nếu đọc thành công, 0 nếu file không tồn tại, -1 nếu file sai định dạng */
int docTep(DanhSachNV *d, const char *tenFile) {
    FILE *f;
    char dong[256];
    int soNV, soBanGhi, i, j;
    float gioLam, gioThem;
    NhanVien nv;
    Ngay n;
    ChamCong *c;

    f = fopen(tenFile, "r");
    if (f == NULL) return 0;

    /* Dòng đầu: số nhân viên */
    if (fgets(dong, sizeof(dong), f) == NULL || sscanf(dong, "%d", &soNV) != 1) {
        fclose(f);
        return -1;
    }

    /* Xoá dữ liệu cũ trong bộ nhớ trước khi đọc */
    xoaHetNV(d);

    for (i = 0; i < soNV; i++) {
        /* Đọc dòng thông tin nhân viên */
        if (fgets(dong, sizeof(dong), f) == NULL) break;
        xoaXuongDong(dong);
        if (sscanf(dong, "%9[^|]|%49[^|]|%29[^|]|%29[^|]|%lf|%d",
                   nv.maNV, nv.hoTen, nv.phongBan, nv.chucVu,
                   &nv.luongCoBan, &soBanGhi) != 6
            || soBanGhi < 0 || soBanGhi > 366) {
            printf("Canh bao: dong loi, dung doc file: %s\n", dong);
            break;
        }
        nv.dsChamCong = NULL;

        /* Đọc các dòng chấm công của nhân viên này */
        for (j = 0; j < soBanGhi; j++) {
            if (fgets(dong, sizeof(dong), f) == NULL) break;
            xoaXuongDong(dong);
            if (sscanf(dong, "%d/%d/%d|%f|%f",
                       &n.ngay, &n.thang, &n.nam, &gioLam, &gioThem) != 5) {
                printf("Canh bao: bo qua dong cham cong loi: %s\n", dong);
                continue;
            }

            /* Kiểm tra dữ liệu hợp lệ */
            if (!ngayHopLe(n)) continue;
            if (gioLam <= 0 || gioLam > GIO_CHUAN) continue;
            if (gioThem < 0 || gioThem > GIO_OT_TOI_DA) continue;
            if (timChamCong(nv.dsChamCong, n) != NULL) continue;

            c = taoChamCong(n, gioLam, gioThem);
            if (c != NULL) chenChamCong(&nv.dsChamCong, c);
        }

        /* Thêm vào danh sách, nếu trùng mã thì bỏ và giải phóng chấm công */
        if (!themNVVaoDS(d, nv)) {
            giaiPhongCC(nv.dsChamCong);
        }
    }
    fclose(f);
    return 1;
}

/* ================== F5.3 DỮ LIỆU MẪU ================== */

/* Hàm phụ: tạo 1 nhân viên mẫu */
NhanVien taoNVMau(const char *ma, const char *ten, const char *phongBan,
                  const char *chucVu, double luong) {
    NhanVien nv;
    strcpy(nv.maNV, ma);
    strcpy(nv.hoTen, ten);
    strcpy(nv.phongBan, phongBan);
    strcpy(nv.chucVu, chucVu);
    nv.luongCoBan = luong;
    nv.dsChamCong = NULL;
    return nv;
}

/* Hàm phụ: thêm 1 ngày chấm công mẫu */
void themCCMau(NhanVien *nv, int ngay, int thang, int nam, float gioLam, float gioThem) {
    Ngay n;
    ChamCong *c;
    n.ngay = ngay;
    n.thang = thang;
    n.nam = nam;
    c = taoChamCong(n, gioLam, gioThem);
    if (c != NULL) chenChamCong(&nv->dsChamCong, c);
}

/*
 * Dữ liệu mẫu tháng 10/2026: 15 nhân viên.
 *
 * Tháng 10/2026 có 22 ngày làm việc chuẩn (thứ 2 - thứ 6):
 *   1, 2, 5-9, 12-16, 19-23, 26-30
 * Chấm công của mỗi nhân viên được viết thành một chuỗi 22 ký tự,
 * mỗi ký tự là một ngày làm việc theo thứ tự trên:
 *   F = đi làm đủ 8 giờ
 *   O = làm 8 giờ + 2 giờ làm thêm
 *   H = làm nửa ngày (4 giờ = 0.5 công)
 *   - = không đi làm (không có bản ghi chấm công)
 * soNgayT7 = số ngày thứ 7 đi làm thêm (3/10, 10/10, 17/10, 24/10, 31/10),
 *            mỗi ngày làm đủ 8 giờ => được cộng thêm 1 công.
 */
typedef struct {
    char ma[10];
    char ten[50];
    char phongBan[30];
    char chucVu[30];
    double luong;
    char lich[23];     /* 22 ký tự + '\0' */
    int soNgayT7;
} MauNV;

void napDuLieuMau(DanhSachNV *d) {
    /* Các ngày làm việc chuẩn (thứ 2 - thứ 6) */
    int ngayLam[22] = { 1,  2,
                        5,  6,  7,  8,  9,
                       12, 13, 14, 15, 16,
                       19, 20, 21, 22, 23,
                       26, 27, 28, 29, 30 };
    int ngayT7[5] = { 3, 10, 17, 24, 31 };

    MauNV dsMau[15] = {
        /* ma      ho ten            phong ban     chuc vu          luong     lich cham cong 22 ngay    T7 */
        {"NV001", "Nguyen Van An",  "Ky thuat",   "Nhan vien",      7800000, "FFOFFOFFOFFOFFOFFFFFFF", 1}, /* 23 cong, 10h OT  */
        {"NV002", "Tran Thi Binh",  "Ke toan",    "Truong phong",  12000000, "FFFFFFFFFFFFOFFFFFFFFF", 0}, /* 22 cong, 2h OT   */
        {"NV003", "Le Van Cuong",   "Kinh doanh", "Nhan vien",      6500000, "FFFHFFFHFFF-FFF-FFFFFF", 0}, /* 19 cong          */
        {"NV004", "Pham Thi Dung",  "Hanh chinh", "Nhan vien",      7000000, "FFFFFF-FFFFFFFFFFFFFFF", 0}, /* 21 cong          */
        {"NV005", "Hoang Van Em",   "IT",         "Lap trinh vien", 9000000, "FFFFFFFFFFFFFFFFFFFFFF", 0}, /* 22 cong          */
        {"NV006", "Vu Thi Giang",   "Ke toan",    "Ke toan vien",   8000000, "FFFFF-FFFFFFFFFFFFFFFF", 0}, /* 21 cong          */
        {"NV007", "Dang Van Hai",   "Kinh doanh", "Nhan vien KD",   7000000, "FFOFFFFOFFFFFOFFFFFFFF", 2}, /* 24 cong, 6h OT   */
        {"NV008", "Bui Thi Hoa",    "Nhan su",    "Truong phong",  15000000, "FFFFFFFFFFFFFFFFFFFFFF", 0}, /* 22 cong          */
        {"NV009", "Do Van Hung",    "Ky thuat",   "Ky su",         11000000, "FFFOFFFFOFFFFOFFFFOFFF", 3}, /* 25 cong, 8h OT   */
        {"NV010", "Ngo Thi Lan",    "Marketing",  "Nhan vien",      7500000, "FFFFFFF-FFFFFFFFFFFF-F", 0}, /* 20 cong          */
        {"NV011", "Duong Van Long", "Kho van",    "Thu kho",        6800000, "FHFFFFFFFHFFFFFFHFFFFF", 0}, /* 20.5 cong        */
        {"NV012", "Ly Thi Mai",     "Ke toan",    "Thu quy",        7200000, "FFFFFFFFFFF--FFFFFFFFF", 0}, /* 20 cong          */
        {"NV013", "Trinh Van Nam",  "IT",         "Tester",         8500000, "FFFFFFFFFFFFFFFFFFFFFF", 1}, /* 23 cong          */
        {"NV014", "Phan Thi Oanh",  "Kinh doanh", "Nhan vien KD",   7000000, "FF-FFFFFFFHFFFFF-FFFFF", 0}, /* 19.5 cong        */
        {"NV015", "Mai Van Phuc",   "Ky thuat",   "Ky thuat vien",  8000000, "OFFFFOFFFFOFFFFOFFFFOF", 3}  /* 25 cong, 10h OT  */
    };

    int thang = 10, nam = 2026;
    int i, k;
    NhanVien nv;

    /* Xoá dữ liệu cũ, thay bằng dữ liệu mẫu */
    xoaHetNV(d);

    for (i = 0; i < 15; i++) {
        nv = taoNVMau(dsMau[i].ma, dsMau[i].ten, dsMau[i].phongBan,
                      dsMau[i].chucVu, dsMau[i].luong);

        /* Chấm công 22 ngày làm việc theo chuỗi lịch */
        for (k = 0; k < 22; k++) {
            switch (dsMau[i].lich[k]) {
                case 'F': themCCMau(&nv, ngayLam[k], thang, nam, 8, 0); break;
                case 'O': themCCMau(&nv, ngayLam[k], thang, nam, 8, 2); break;
                case 'H': themCCMau(&nv, ngayLam[k], thang, nam, 4, 0); break;
                /* '-' : không đi làm, không tạo bản ghi */
            }
        }

        /* Đi làm thêm ngày thứ 7 */
        for (k = 0; k < dsMau[i].soNgayT7; k++) {
            themCCMau(&nv, ngayT7[k], thang, nam, 8, 0);
        }

        themNVVaoDS(d, nv);
    }
}
