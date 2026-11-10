/*
 * thongke.c
 * Cài đặt các hàm đệ quy và chức năng thống kê.
 *
 * Ý tưởng đệ quy trên danh sách liên kết:
 *   - Điều kiện dừng: p == NULL (hết danh sách) thì trả về 0.
 *   - Bước đệ quy:    giá trị của nút p + kết quả của phần còn lại (p->next).
 */
#include <stdio.h>
#include "thongke.h"
#include "luong.h"
#include "tienich.h"

/* ================== CÁC HÀM ĐỆ QUY ================== */

/* Tổng giờ công (giờ làm + giờ OT) trong tháng */
float tongGioThang(ChamCong *p, int thang, int nam) {
    float gio = 0;
    if (p == NULL) return 0;                       /* điều kiện dừng */
    if (p->ngay.thang == thang && p->ngay.nam == nam) {
        gio = p->gioLam + p->gioThem;
    }
    return gio + tongGioThang(p->next, thang, nam); /* bước đệ quy */
}

/* Tổng giờ làm thêm (OT) trong tháng */
float tongOTThang(ChamCong *p, int thang, int nam) {
    float gio = 0;
    if (p == NULL) return 0;
    if (p->ngay.thang == thang && p->ngay.nam == nam) {
        gio = p->gioThem;
    }
    return gio + tongOTThang(p->next, thang, nam);
}

/* Số công trong tháng:
   đi làm = giờ làm / 8, nghỉ phép = 1 công, nghỉ không phép = 0 công */
float demCongThang(ChamCong *p, int thang, int nam) {
    float cong = 0;
    if (p == NULL) return 0;
    if (p->ngay.thang == thang && p->ngay.nam == nam) {
        if (p->loai == DI_LAM) {
            cong = p->gioLam / GIO_CHUAN;
        } else if (p->loai == NGHI_PHEP) {
            cong = 1;
        }
    }
    return cong + demCongThang(p->next, thang, nam);
}

/* Đếm số ngày nghỉ không phép trong tháng */
int demNghiKhongPhep(ChamCong *p, int thang, int nam) {
    int dem = 0;
    if (p == NULL) return 0;
    if (p->ngay.thang == thang && p->ngay.nam == nam && p->loai == NGHI_KHONG_PHEP) {
        dem = 1;
    }
    return dem + demNghiKhongPhep(p->next, thang, nam);
}

/* Giờ công LŨY KẾ từ đầu tháng đến hết ngày 'den'.
   Vì danh sách đã sắp tăng theo ngày nên gặp ngày lớn hơn 'den' là dừng luôn. */
float gioLuyKe(ChamCong *p, Ngay den) {
    float gio = 0;
    if (p == NULL || soSanhNgay(p->ngay, den) > 0) return 0;  /* điều kiện dừng */
    if (p->ngay.thang == den.thang && p->ngay.nam == den.nam) {
        gio = p->gioLam + p->gioThem;
    }
    return gio + gioLuyKe(p->next, den);
}

/* ================== F4.1 THỐNG KÊ GIỜ CÔNG THEO THÁNG ================== */
void thongKeGioCong(DanhSachNV *d) {
    int thang, nam, i;
    float cong, gioOT, tongGio;
    float tongCongTatCa = 0, tongOTTatCa = 0, tongGioTatCa = 0;
    NhanVien *nv;

    printf("\n----- THONG KE GIO CONG THEO THANG -----\n");
    if (d->soLuong == 0) {
        printf("=> Danh sach nhan vien dang rong!\n");
        return;
    }
    nhapThangNam(&thang, &nam);

    printf("\nTHONG KE GIO CONG THANG %02d/%04d\n", thang, nam);
    printf("%-8s %-25s %8s %9s %8s %10s\n",
           "Ma NV", "Ho ten", "So cong", "Gio lam", "Gio OT", "Tong gio");
    printf("-----------------------------------------------------------------------\n");
    for (i = 0; i < d->soLuong; i++) {
        nv = &d->ds[i];
        cong = demCongThang(nv->dsChamCong, thang, nam);
        gioOT = tongOTThang(nv->dsChamCong, thang, nam);
        tongGio = tongGioThang(nv->dsChamCong, thang, nam);
        printf("%-8s %-25s %8.2f %9.2f %8.2f %10.2f\n",
               nv->maNV, nv->hoTen, cong, tongGio - gioOT, gioOT, tongGio);
        tongCongTatCa += cong;
        tongOTTatCa += gioOT;
        tongGioTatCa += tongGio;
    }
    printf("-----------------------------------------------------------------------\n");
    printf("%-8s %-25s %8.2f %9.2f %8.2f %10.2f\n", "", "TONG CONG",
           tongCongTatCa, tongGioTatCa - tongOTTatCa, tongOTTatCa, tongGioTatCa);
}

/* ================== F4.2 TỔNG QUỸ LƯƠNG ================== */
void thongKeQuyLuong(DanhSachNV *d) {
    int thang, nam, i, viTriMax, viTriMin;
    double luong, tong, luongMax, luongMin;

    printf("\n----- TONG QUY LUONG THANG -----\n");
    if (d->soLuong == 0) {
        printf("=> Danh sach nhan vien dang rong!\n");
        return;
    }
    nhapThangNam(&thang, &nam);

    tong = 0;
    viTriMax = 0;
    viTriMin = 0;
    luongMax = tinhLuong(&d->ds[0], thang, nam);
    luongMin = luongMax;
    for (i = 0; i < d->soLuong; i++) {
        luong = tinhLuong(&d->ds[i], thang, nam);
        tong += luong;
        if (luong > luongMax) {
            luongMax = luong;
            viTriMax = i;
        }
        if (luong < luongMin) {
            luongMin = luong;
            viTriMin = i;
        }
    }

    printf("\nQUY LUONG THANG %02d/%04d\n", thang, nam);
    printf("So nhan vien      : %d\n", d->soLuong);
    printf("Tong quy luong    : %.0f VND\n", tong);
    printf("Luong trung binh  : %.0f VND\n", tong / d->soLuong);
    printf("Luong cao nhat    : %.0f VND (%s - %s)\n",
           luongMax, d->ds[viTriMax].maNV, d->ds[viTriMax].hoTen);
    printf("Luong thap nhat   : %.0f VND (%s - %s)\n",
           luongMin, d->ds[viTriMin].maNV, d->ds[viTriMin].hoTen);
}

/* ================== F4.3 NHÂN VIÊN THIẾU CÔNG ================== */
void thongKeThieuCong(DanhSachNV *d) {
    int thang, nam, nguong, i, nghiKP, dem;
    float cong;
    NhanVien *nv;

    printf("\n----- NHAN VIEN THIEU CONG -----\n");
    if (d->soLuong == 0) {
        printf("=> Danh sach nhan vien dang rong!\n");
        return;
    }
    nhapThangNam(&thang, &nam);
    nguong = nhapSoNguyen("Nguong so cong toi thieu (VD: 22): ", 1, 31);

    printf("\nNHAN VIEN THIEU CONG THANG %02d/%04d (duoi %d cong hoac co nghi khong phep)\n",
           thang, nam, nguong);
    printf("%-8s %-25s %8s %16s\n", "Ma NV", "Ho ten", "So cong", "Nghi khong phep");
    printf("-------------------------------------------------------------\n");
    dem = 0;
    for (i = 0; i < d->soLuong; i++) {
        nv = &d->ds[i];
        cong = demCongThang(nv->dsChamCong, thang, nam);
        nghiKP = demNghiKhongPhep(nv->dsChamCong, thang, nam);
        if (cong < nguong || nghiKP > 0) {
            printf("%-8s %-25s %8.2f %16d\n", nv->maNV, nv->hoTen, cong, nghiKP);
            dem++;
        }
    }
    if (dem == 0) printf("Khong co nhan vien nao thieu cong.\n");
    else printf("=> Co %d nhan vien thieu cong.\n", dem);
}
