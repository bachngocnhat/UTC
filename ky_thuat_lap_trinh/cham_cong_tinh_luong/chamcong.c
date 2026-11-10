/*
 * chamcong.c
 * Cài đặt danh sách liên kết chấm công và các chức năng chấm công.
 *
 * Danh sách chấm công của mỗi nhân viên luôn được sắp TĂNG DẦN theo ngày.
 */
#include <stdio.h>
#include <stdlib.h>
#include "chamcong.h"
#include "nhanvien.h"
#include "thongke.h"
#include "tienich.h"

/* ================== THAO TÁC DANH SÁCH LIÊN KẾT ================== */

const char *tenLoaiNgay(int loai) {
    if (loai == DI_LAM) return "Di lam";
    if (loai == NGHI_PHEP) return "Nghi phep";
    return "Nghi khong phep";
}

/* Tính giờ làm chính và giờ làm thêm từ giờ vào / giờ ra */
void tinhGio(ChamCong *c) {
    int tongPhut, batDauTrua, ketThucTrua;
    float tongGio;

    /* Ngày nghỉ thì không có giờ làm */
    if (c->loai != DI_LAM) {
        c->gioLam = 0;
        c->gioThem = 0;
        return;
    }

    tongPhut = c->gioRa - c->gioVao;

    /* Trừ thời gian nghỉ trưa 12:00 - 13:00 (720 - 780 phút)
       chỉ trừ phần thời gian nằm trong khoảng làm việc */
    batDauTrua = 12 * 60;
    ketThucTrua = 13 * 60;
    if (c->gioVao > batDauTrua) batDauTrua = c->gioVao;
    if (c->gioRa < ketThucTrua) ketThucTrua = c->gioRa;
    if (ketThucTrua > batDauTrua) {
        tongPhut = tongPhut - (ketThucTrua - batDauTrua);
    }

    tongGio = tongPhut / 60.0f;
    if (tongGio > GIO_CHUAN) {
        c->gioLam = GIO_CHUAN;
        c->gioThem = tongGio - GIO_CHUAN;
    } else {
        c->gioLam = tongGio;
        c->gioThem = 0;
    }
}

/* Cấp phát 1 nút chấm công mới */
ChamCong *taoChamCong(Ngay n, int loai, int gioVao, int gioRa) {
    ChamCong *c = (ChamCong *)malloc(sizeof(ChamCong));
    if (c == NULL) {
        printf("Loi: khong du bo nho!\n");
        return NULL;
    }
    c->ngay = n;
    c->loai = loai;
    if (loai == DI_LAM) {
        c->gioVao = gioVao;
        c->gioRa = gioRa;
    } else {
        c->gioVao = -1;
        c->gioRa = -1;
    }
    c->next = NULL;
    tinhGio(c);
    return c;
}

/* Tìm bản ghi theo ngày, không có thì trả về NULL */
ChamCong *timChamCong(ChamCong *head, Ngay n) {
    ChamCong *p = head;
    while (p != NULL) {
        if (soSanhNgay(p->ngay, n) == 0) return p;
        p = p->next;
    }
    return NULL;
}

/* Chèn nút mới vào đúng vị trí để danh sách vẫn tăng dần theo ngày.
   Dùng con trỏ cấp 2 (ChamCong **) vì có thể phải thay đổi nút đầu.
   (Hàm gọi phải kiểm tra trùng ngày trước khi chèn.) */
void chenChamCong(ChamCong **head, ChamCong *moi) {
    ChamCong *p;

    /* Trường hợp 1: danh sách rỗng hoặc ngày mới nhỏ hơn ngày đầu -> chèn đầu */
    if (*head == NULL || soSanhNgay(moi->ngay, (*head)->ngay) < 0) {
        moi->next = *head;
        *head = moi;
        return;
    }

    /* Trường hợp 2: tìm nút p đứng ngay trước vị trí cần chèn */
    p = *head;
    while (p->next != NULL && soSanhNgay(p->next->ngay, moi->ngay) < 0) {
        p = p->next;
    }
    moi->next = p->next;
    p->next = moi;
}

/* Xoá nút có ngày n. Trả về 1 nếu xoá được, 0 nếu không tìm thấy */
int xoaChamCong(ChamCong **head, Ngay n) {
    ChamCong *truoc = NULL;
    ChamCong *p = *head;

    while (p != NULL && soSanhNgay(p->ngay, n) != 0) {
        truoc = p;
        p = p->next;
    }
    if (p == NULL) return 0;

    if (truoc == NULL) {
        *head = p->next;        /* xoá nút đầu */
    } else {
        truoc->next = p->next;  /* nối nút trước với nút sau */
    }
    free(p);
    return 1;
}

/* Giải phóng toàn bộ danh sách */
void giaiPhongCC(ChamCong *head) {
    ChamCong *p;
    while (head != NULL) {
        p = head;
        head = head->next;
        free(p);
    }
}

/* Đếm số bản ghi trong danh sách */
int demBanGhi(ChamCong *head) {
    int dem = 0;
    while (head != NULL) {
        dem++;
        head = head->next;
    }
    return dem;
}

/* ================== HÀM NHẬP PHỤ ================== */

/* Chọn loại ngày, trả về DI_LAM / NGHI_PHEP / NGHI_KHONG_PHEP */
int nhapLoaiNgay(void) {
    printf("Loai ngay: 1. Di lam   2. Nghi phep   3. Nghi khong phep\n");
    return nhapSoNguyen("Chon loai: ", 1, 3) - 1;
}

/* Nhập giờ vào, giờ ra, bắt buộc giờ ra sau giờ vào */
void nhapGioVaoRa(int *gioVao, int *gioRa) {
    while (1) {
        *gioVao = nhapGio("Gio vao (HH:MM): ");
        *gioRa = nhapGio("Gio ra  (HH:MM): ");
        if (*gioRa <= *gioVao) {
            printf("  -> Gio ra phai sau gio vao! Nhap lai.\n");
        } else {
            break;
        }
    }
}

/* ================== F2.1 CHẤM CÔNG THEO NGÀY ================== */
void chamCongTheoNgay(DanhSachNV *d) {
    int viTri, loai, gioVao, gioRa;
    NhanVien *nv;
    Ngay n;
    ChamCong *c;

    printf("\n----- CHAM CONG THEO NGAY -----\n");
    viTri = chonNV(d);
    if (viTri == -1) return;
    nv = &d->ds[viTri];
    printf("Nhan vien: %s - %s\n", nv->maNV, nv->hoTen);

    do {
        n = nhapNgay("Ngay cham cong (dd/mm/yyyy): ");
        if (timChamCong(nv->dsChamCong, n) != NULL) {
            printf("=> Ngay nay da duoc cham cong! Hay dung chuc nang Sua cham cong.\n");
        } else {
            loai = nhapLoaiNgay();
            gioVao = -1;
            gioRa = -1;
            if (loai == DI_LAM) {
                nhapGioVaoRa(&gioVao, &gioRa);
            }
            c = taoChamCong(n, loai, gioVao, gioRa);
            if (c != NULL) {
                chenChamCong(&nv->dsChamCong, c);
                printf("=> Cham cong thanh cong! (%s, gio lam: %.2f, gio them: %.2f)\n",
                       tenLoaiNgay(c->loai), c->gioLam, c->gioThem);
            }
        }
    } while (hoiCoKhong("Cham cong tiep cho nhan vien nay? (y/n): "));
}

/* ================== F2.2 SỬA CHẤM CÔNG ================== */
void suaChamCong(DanhSachNV *d) {
    int viTri, gioVao, gioRa;
    NhanVien *nv;
    Ngay n;
    ChamCong *c;
    char vao[6], ra[6];

    printf("\n----- SUA CHAM CONG -----\n");
    viTri = chonNV(d);
    if (viTri == -1) return;
    nv = &d->ds[viTri];

    n = nhapNgay("Ngay can sua (dd/mm/yyyy): ");
    c = timChamCong(nv->dsChamCong, n);
    if (c == NULL) {
        printf("=> Ngay nay chua duoc cham cong!\n");
        return;
    }

    doiGioRaChuoi(c->gioVao, vao);
    doiGioRaChuoi(c->gioRa, ra);
    printf("Hien tai: %s | vao %s | ra %s | gio lam %.2f | gio them %.2f\n",
           tenLoaiNgay(c->loai), vao, ra, c->gioLam, c->gioThem);

    printf("Nhap thong tin moi:\n");
    c->loai = nhapLoaiNgay();
    if (c->loai == DI_LAM) {
        nhapGioVaoRa(&gioVao, &gioRa);
        c->gioVao = gioVao;
        c->gioRa = gioRa;
    } else {
        c->gioVao = -1;
        c->gioRa = -1;
    }
    tinhGio(c);
    printf("=> Da sua! (%s, gio lam: %.2f, gio them: %.2f)\n",
           tenLoaiNgay(c->loai), c->gioLam, c->gioThem);
}

/* ================== F2.3 XOÁ CHẤM CÔNG ================== */
void xoaChamCongNV(DanhSachNV *d) {
    int viTri;
    NhanVien *nv;
    Ngay n;

    printf("\n----- XOA CHAM CONG -----\n");
    viTri = chonNV(d);
    if (viTri == -1) return;
    nv = &d->ds[viTri];

    n = nhapNgay("Ngay can xoa (dd/mm/yyyy): ");
    if (timChamCong(nv->dsChamCong, n) == NULL) {
        printf("=> Ngay nay chua duoc cham cong!\n");
        return;
    }
    if (!hoiCoKhong("Ban chac chan muon xoa? (y/n): ")) {
        printf("=> Da huy.\n");
        return;
    }
    xoaChamCong(&nv->dsChamCong, n);
    printf("=> Da xoa ban ghi cham cong ngay %02d/%02d/%04d!\n", n.ngay, n.thang, n.nam);
}

/* ================== F2.4 XEM LỊCH SỬ CHẤM CÔNG ================== */
void xemLichSu(DanhSachNV *d) {
    int viTri, thang, nam, dem;
    NhanVien *nv;
    ChamCong *p;
    char vao[6], ra[6];

    printf("\n----- LICH SU CHAM CONG -----\n");
    viTri = chonNV(d);
    if (viTri == -1) return;
    nv = &d->ds[viTri];
    nhapThangNam(&thang, &nam);

    printf("\nBANG CHAM CONG THANG %02d/%04d - %s - %s\n", thang, nam, nv->maNV, nv->hoTen);
    printf("%-12s %-16s %-6s %-6s %8s %8s %9s\n",
           "Ngay", "Loai", "Vao", "Ra", "Gio lam", "Gio OT", "Luy ke");
    printf("---------------------------------------------------------------------\n");

    dem = 0;
    p = nv->dsChamCong;
    while (p != NULL) {
        if (p->ngay.thang == thang && p->ngay.nam == nam) {
            doiGioRaChuoi(p->gioVao, vao);
            doiGioRaChuoi(p->gioRa, ra);
            /* Cột lũy kế dùng hàm đệ quy gioLuyKe */
            printf("%02d/%02d/%04d   %-16s %-6s %-6s %8.2f %8.2f %9.2f\n",
                   p->ngay.ngay, p->ngay.thang, p->ngay.nam,
                   tenLoaiNgay(p->loai), vao, ra, p->gioLam, p->gioThem,
                   gioLuyKe(nv->dsChamCong, p->ngay));
            dem++;
        }
        p = p->next;
    }

    if (dem == 0) {
        printf("Khong co ban ghi cham cong nao trong thang nay.\n");
        return;
    }
    printf("---------------------------------------------------------------------\n");
    printf("So ngay co ban ghi : %d\n", dem);
    printf("So cong            : %.2f\n", demCongThang(nv->dsChamCong, thang, nam));
    printf("Tong gio OT        : %.2f\n", tongOTThang(nv->dsChamCong, thang, nam));
    printf("Tong gio cong      : %.2f\n", tongGioThang(nv->dsChamCong, thang, nam));
    printf("Nghi khong phep    : %d ngay\n", demNghiKhongPhep(nv->dsChamCong, thang, nam));
}
