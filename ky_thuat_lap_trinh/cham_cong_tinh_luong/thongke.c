/*
 * thongke.c
 * Cài đặt các hàm đệ quy và chức năng thống kê giờ công theo tháng.
 *
 * Ý tưởng đệ quy trên danh sách liên kết:
 *   - Điều kiện dừng: p == NULL (hết danh sách) thì trả về 0.
 *   - Bước đệ quy:    giá trị của nút p + kết quả của phần còn lại (p->next).
 */
#include <stdio.h>
#include "thongke.h"
#include "tienich.h"

/* ================== CÁC HÀM ĐỆ QUY ================== */

/* Tổng giờ công LŨY KẾ trong tháng (giờ làm + giờ OT của các ngày trong tháng) */
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

/* Số công trong tháng: mỗi ngày được (giờ làm / 8) công.
   VD: làm 8 giờ = 1 công, làm 4 giờ = 0.5 công */
float demCongThang(ChamCong *p, int thang, int nam) {
    float cong = 0;
    if (p == NULL) return 0;
    if (p->ngay.thang == thang && p->ngay.nam == nam) {
        cong = p->gioLam / GIO_CHUAN;
    }
    return cong + demCongThang(p->next, thang, nam);
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
