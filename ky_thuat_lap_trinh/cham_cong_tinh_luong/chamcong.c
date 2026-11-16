/*
 * chamcong.c
 * Cài đặt danh sách liên kết chấm công và chức năng chấm công theo ngày.
 *
 * Danh sách chấm công của mỗi nhân viên luôn được sắp TĂNG DẦN theo ngày.
 */
#include <stdio.h>
#include <stdlib.h>
#include "chamcong.h"
#include "nhanvien.h"
#include "tienich.h"

/* ================== THAO TÁC DANH SÁCH LIÊN KẾT ================== */

/* Cấp phát 1 nút chấm công mới */
ChamCong *taoChamCong(Ngay n, float gioLam, float gioThem) {
    ChamCong *c = (ChamCong *)malloc(sizeof(ChamCong));
    if (c == NULL) {
        printf("Loi: khong du bo nho!\n");
        return NULL;
    }
    c->ngay = n;
    c->gioLam = gioLam;
    c->gioThem = gioThem;
    c->next = NULL;
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

/* ================== F2.1 CHẤM CÔNG THEO NGÀY ================== */
void chamCongTheoNgay(DanhSachNV *d) {
    int viTri;
    float gioLam, gioThem;
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
            printf("=> Ngay nay da duoc cham cong!\n");
        } else {
            gioLam = nhapSoThuc("So gio lam trong ngay (0.5 - 8): ", 0.5, GIO_CHUAN);
            /* Chỉ làm đủ 8 giờ mới có giờ làm thêm */
            gioThem = 0;
            if (gioLam == GIO_CHUAN) {
                gioThem = nhapSoThuc("So gio lam them (0 - 16): ", 0, GIO_OT_TOI_DA);
            }
            c = taoChamCong(n, gioLam, gioThem);
            if (c != NULL) {
                chenChamCong(&nv->dsChamCong, c);
                printf("=> Cham cong thanh cong! (gio lam: %.2f, gio them: %.2f)\n",
                       c->gioLam, c->gioThem);
            }
        }
    } while (hoiCoKhong("Cham cong tiep cho nhan vien nay? (y/n): "));
}
