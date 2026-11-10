/*
 * tepdulieu.c
 * Cài đặt lưu / đọc file và dữ liệu mẫu.
 *
 * Định dạng file dulieu.txt:
 *   Dòng 1: số nhân viên
 *   Mỗi nhân viên:
 *     MaNV|HoTen|PhongBan|ChucVu|LuongCoBan|PhuCap|SoBanGhiChamCong
 *     dd/mm/yyyy|loai|HH:MM|HH:MM      (lặp lại SoBanGhiChamCong dòng)
 *   Ngày nghỉ thì giờ vào/ra ghi là --:--
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
    char vao[6], ra[6];

    f = fopen(tenFile, "w");
    if (f == NULL) return 0;

    fprintf(f, "%d\n", d->soLuong);
    for (i = 0; i < d->soLuong; i++) {
        nv = &d->ds[i];
        fprintf(f, "%s|%s|%s|%s|%.0f|%.0f|%d\n",
                nv->maNV, nv->hoTen, nv->phongBan, nv->chucVu,
                nv->luongCoBan, nv->phuCap, demBanGhi(nv->dsChamCong));

        p = nv->dsChamCong;
        while (p != NULL) {
            doiGioRaChuoi(p->gioVao, vao);
            doiGioRaChuoi(p->gioRa, ra);
            fprintf(f, "%02d/%02d/%04d|%d|%s|%s\n",
                    p->ngay.ngay, p->ngay.thang, p->ngay.nam, p->loai, vao, ra);
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
    char vao[10], ra[10];
    int soNV, soBanGhi, i, j, loai, gioVao, gioRa;
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
        if (sscanf(dong, "%9[^|]|%49[^|]|%29[^|]|%29[^|]|%lf|%lf|%d",
                   nv.maNV, nv.hoTen, nv.phongBan, nv.chucVu,
                   &nv.luongCoBan, &nv.phuCap, &soBanGhi) != 7) {
            printf("Canh bao: bo qua dong loi: %s\n", dong);
            continue;
        }
        nv.dsChamCong = NULL;

        /* Đọc các dòng chấm công của nhân viên này */
        for (j = 0; j < soBanGhi; j++) {
            if (fgets(dong, sizeof(dong), f) == NULL) break;
            xoaXuongDong(dong);
            if (sscanf(dong, "%d/%d/%d|%d|%9[^|]|%9s",
                       &n.ngay, &n.thang, &n.nam, &loai, vao, ra) != 6) {
                printf("Canh bao: bo qua dong cham cong loi: %s\n", dong);
                continue;
            }
            gioVao = docGioTuChuoi(vao);
            gioRa = docGioTuChuoi(ra);

            /* Kiểm tra dữ liệu hợp lệ */
            if (!ngayHopLe(n) || loai < 0 || loai > 2) continue;
            if (loai == DI_LAM && (gioVao < 0 || gioRa <= gioVao)) continue;
            if (timChamCong(nv.dsChamCong, n) != NULL) continue;

            c = taoChamCong(n, loai, gioVao, gioRa);
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
                  const char *chucVu, double luong, double phuCap) {
    NhanVien nv;
    strcpy(nv.maNV, ma);
    strcpy(nv.hoTen, ten);
    strcpy(nv.phongBan, phongBan);
    strcpy(nv.chucVu, chucVu);
    nv.luongCoBan = luong;
    nv.phuCap = phuCap;
    nv.dsChamCong = NULL;
    return nv;
}

/* Hàm phụ: thêm 1 ngày chấm công mẫu (giờ truyền vào dạng giờ, phút) */
void themCCMau(NhanVien *nv, int ngay, int thang, int nam, int loai,
               int gioVao, int phutVao, int gioRa, int phutRa) {
    Ngay n;
    ChamCong *c;
    n.ngay = ngay;
    n.thang = thang;
    n.nam = nam;
    c = taoChamCong(n, loai, gioVao * 60 + phutVao, gioRa * 60 + phutRa);
    if (c != NULL) chenChamCong(&nv->dsChamCong, c);
}

/* ================== DỮ LIỆU MẪU THÁNG 10/2026: 15 NHÂN VIÊN ================== */
/*
 * Tháng 10/2026 có 22 ngày làm việc chuẩn (thứ 2 - thứ 6):
 *   1, 2, 5-9, 12-16, 19-23, 26-30
 * Chấm công của mỗi nhân viên được viết thành một chuỗi 22 ký tự,
 * mỗi ký tự là một ngày làm việc theo thứ tự trên:
 *   F = đi làm đủ    08:00 - 17:00 (8 giờ)
 *   O = có làm thêm  08:00 - 19:00 (8 giờ + 2 giờ OT)
 *   H = làm nửa ngày 08:00 - 12:00 (4 giờ = 0.5 công)
 *   P = nghỉ phép           (vẫn tính 1 công)
 *   K = nghỉ không phép     (0 công)
 * soNgayT7 = số ngày thứ 7 đi làm thêm (3/10, 10/10, 17/10, 24/10, 31/10),
 *            mỗi ngày đi làm đủ 8 giờ => được cộng thêm 1 công.
 */

typedef struct {
    char ma[10];
    char ten[50];
    char phongBan[30];
    char chucVu[30];
    double luong;
    double phuCap;
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
        /* ma      ho ten            phong ban     chuc vu          luong     phu cap   lich cham cong 22 ngay    T7 */
        {"NV001", "Nguyen Van An",  "Ky thuat",   "Nhan vien",      7800000,  500000, "FFOFFOFFOFFOFFOFFPFFFF", 1}, /* 23 cong, 10h OT (vi du trong bao cao) */
        {"NV002", "Tran Thi Binh",  "Ke toan",    "Truong phong",  12000000, 1000000, "FFFFFFFPFFFFOFFFFFFFFF", 0}, /* 22 cong, 2h OT   */
        {"NV003", "Le Van Cuong",   "Kinh doanh", "Nhan vien",      6500000,  300000, "FFFHFFFHFFFKFFFKFFFFFF", 0}, /* 19 cong, 2 KP    */
        {"NV004", "Pham Thi Dung",  "Hanh chinh", "Nhan vien",      7000000,  400000, "FFFFFFKFFFFFFFFFFFFFFF", 0}, /* 21 cong, 1 KP    */
        {"NV005", "Hoang Van Em",   "IT",         "Lap trinh vien", 9000000,  300000, "FFFFFFFFFFFFFFFFFFFFFF", 0}, /* 22 cong          */
        {"NV006", "Vu Thi Giang",   "Ke toan",    "Ke toan vien",   8000000,  300000, "FFFFFPFFFFFFFFFFFFFFFF", 0}, /* 22 cong, 1 phep  */
        {"NV007", "Dang Van Hai",   "Kinh doanh", "Nhan vien KD",   7000000,  500000, "FFOFFFFOFFFFFOFFFFFFFF", 2}, /* 24 cong, 6h OT   */
        {"NV008", "Bui Thi Hoa",    "Nhan su",    "Truong phong",  15000000, 2000000, "FFFFFFFFFFFFFFFFFFFFFF", 0}, /* 22 cong          */
        {"NV009", "Do Van Hung",    "Ky thuat",   "Ky su",         11000000,  700000, "FFFOFFFFOFFFFOFFFFOFFF", 3}, /* 25 cong, 8h OT   */
        {"NV010", "Ngo Thi Lan",    "Marketing",  "Nhan vien",      7500000,  400000, "FFFFFFFKFFFFFFFFFFFFKF", 0}, /* 20 cong, 2 KP    */
        {"NV011", "Duong Van Long", "Kho van",    "Thu kho",        6800000,  300000, "FHFFFFFFFHFFFFFFHFFFFF", 0}, /* 20.5 cong        */
        {"NV012", "Ly Thi Mai",     "Ke toan",    "Thu quy",        7200000,  300000, "FFFFFFFFFFFPPFFFFFFFFF", 0}, /* 22 cong, 2 phep  */
        {"NV013", "Trinh Van Nam",  "IT",         "Tester",         8500000,  300000, "FFFFFFFFFFFFFFFFFFFFFF", 1}, /* 23 cong          */
        {"NV014", "Phan Thi Oanh",  "Kinh doanh", "Nhan vien KD",   7000000,  500000, "FFKFFFFFFFHFFFFFKFFFFF", 0}, /* 19.5 cong, 2 KP  */
        {"NV015", "Mai Van Phuc",   "Ky thuat",   "Ky thuat vien",  8000000,  400000, "OFFFFOFFFFOFFFFOFFFFOF", 3}  /* 25 cong, 10h OT  */
    };

    int thang = 10, nam = 2026;
    int i, k;
    NhanVien nv;

    /* Xoá dữ liệu cũ, thay bằng dữ liệu mẫu */
    xoaHetNV(d);

    for (i = 0; i < 15; i++) {
        nv = taoNVMau(dsMau[i].ma, dsMau[i].ten, dsMau[i].phongBan,
                      dsMau[i].chucVu, dsMau[i].luong, dsMau[i].phuCap);

        /* Chấm công 22 ngày làm việc theo chuỗi lịch */
        for (k = 0; k < 22; k++) {
            switch (dsMau[i].lich[k]) {
                case 'F': themCCMau(&nv, ngayLam[k], thang, nam, DI_LAM, 8, 0, 17, 0); break;
                case 'O': themCCMau(&nv, ngayLam[k], thang, nam, DI_LAM, 8, 0, 19, 0); break;
                case 'H': themCCMau(&nv, ngayLam[k], thang, nam, DI_LAM, 8, 0, 12, 0); break;
                case 'P': themCCMau(&nv, ngayLam[k], thang, nam, NGHI_PHEP, 0, 0, 0, 0); break;
                case 'K': themCCMau(&nv, ngayLam[k], thang, nam, NGHI_KHONG_PHEP, 0, 0, 0, 0); break;
            }
        }

        /* Đi làm thêm ngày thứ 7 */
        for (k = 0; k < dsMau[i].soNgayT7; k++) {
            themCCMau(&nv, ngayT7[k], thang, nam, DI_LAM, 8, 0, 17, 0);
        }

        themNVVaoDS(d, nv);
    }
}
