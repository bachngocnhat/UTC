/*
 * tienich.c
 * Cài đặt các hàm tiện ích.
 *
 * Lưu ý: toàn bộ chương trình chỉ dùng fgets để đọc bàn phím
 * (không dùng scanf trực tiếp) để tránh lỗi trôi lệnh do ký tự '\n'.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "tienich.h"

/* ================== XỬ LÝ CHUỖI ================== */

/* Xoá ký tự xuống dòng ở cuối chuỗi (do fgets để lại) */
void xoaXuongDong(char *s) {
    int n = strlen(s);
    if (n > 0 && s[n - 1] == '\n') {
        s[n - 1] = '\0';
        n--;
    }
    /* File tạo trên Windows có thêm '\r' */
    if (n > 0 && s[n - 1] == '\r') {
        s[n - 1] = '\0';
    }
}

/* Đổi chuỗi sang chữ HOA */
void chuHoa(char *s) {
    int i;
    for (i = 0; s[i] != '\0'; i++) {
        s[i] = toupper((unsigned char)s[i]);
    }
}

/* ================== NHẬP DỮ LIỆU ================== */

/* Đọc 1 dòng từ bàn phím vào s */
void docDong(char *s, int kichThuoc) {
    if (fgets(s, kichThuoc, stdin) == NULL) {
        /* Hết dữ liệu nhập (VD: nhấn Ctrl+D / Ctrl+Z) */
        printf("\nKhong doc duoc du lieu nhap. Thoat chuong trinh.\n");
        exit(0);
    }
    /* Nếu dòng nhập dài hơn kích thước mảng thì bỏ phần thừa */
    if (strchr(s, '\n') == NULL) {
        int c;
        while ((c = getchar()) != '\n' && c != EOF) {
            /* bỏ qua */
        }
    }
    xoaXuongDong(s);
}

/* Nhập chuỗi không được rỗng, không chứa ký tự '|' (vì '|' dùng để ngăn cách trong file) */
void nhapChuoi(const char *loiNhac, char *s, int kichThuoc) {
    while (1) {
        printf("%s", loiNhac);
        docDong(s, kichThuoc);
        if (strlen(s) == 0) {
            printf("  -> Khong duoc de trong!\n");
        } else if (strchr(s, '|') != NULL) {
            printf("  -> Khong duoc chua ky tu '|'!\n");
        } else {
            break;
        }
    }
}

/* Nhập số nguyên trong khoảng [min, max] */
int nhapSoNguyen(const char *loiNhac, int min, int max) {
    char buf[100];
    int x;
    char thua;
    while (1) {
        printf("%s", loiNhac);
        docDong(buf, sizeof(buf));
        /* sscanf trả về 1 nghĩa là chỉ đọc được đúng 1 số, không có ký tự thừa */
        if (sscanf(buf, "%d %c", &x, &thua) != 1) {
            printf("  -> Vui long nhap mot so nguyen!\n");
        } else if (x < min || x > max) {
            printf("  -> Vui long nhap so tu %d den %d!\n", min, max);
        } else {
            return x;
        }
    }
}

/* Nhập số thực trong khoảng [min, max] */
double nhapSoThuc(const char *loiNhac, double min, double max) {
    char buf[100];
    double x;
    char thua;
    while (1) {
        printf("%s", loiNhac);
        docDong(buf, sizeof(buf));
        if (sscanf(buf, "%lf %c", &x, &thua) != 1) {
            printf("  -> Vui long nhap mot so!\n");
        } else if (x < min || x > max) {
            printf("  -> Vui long nhap so tu %.0f den %.0f!\n", min, max);
        } else {
            return x;
        }
    }
}

/* Hỏi có/không. Trả về 1 nếu chọn y, 0 nếu chọn n */
int hoiCoKhong(const char *loiNhac) {
    char buf[20];
    while (1) {
        printf("%s", loiNhac);
        docDong(buf, sizeof(buf));
        if (strcmp(buf, "y") == 0 || strcmp(buf, "Y") == 0) return 1;
        if (strcmp(buf, "n") == 0 || strcmp(buf, "N") == 0) return 0;
        printf("  -> Vui long nhap y hoac n!\n");
    }
}

/* Dừng màn hình chờ người dùng nhấn Enter */
void tamDung(void) {
    char buf[10];
    printf("\nNhan Enter de tiep tuc...");
    docDong(buf, sizeof(buf));
}

/* ================== NGÀY THÁNG ================== */

int laNamNhuan(int nam) {
    return (nam % 4 == 0 && nam % 100 != 0) || (nam % 400 == 0);
}

int soNgayTrongThang(int thang, int nam) {
    switch (thang) {
        case 4: case 6: case 9: case 11:
            return 30;
        case 2:
            if (laNamNhuan(nam)) return 29;
            return 28;
        default:
            return 31;
    }
}

/* Trả về 1 nếu ngày hợp lệ */
int ngayHopLe(Ngay n) {
    if (n.nam < 1900 || n.nam > 2100) return 0;
    if (n.thang < 1 || n.thang > 12) return 0;
    if (n.ngay < 1 || n.ngay > soNgayTrongThang(n.thang, n.nam)) return 0;
    return 1;
}

/* So sánh 2 ngày: trả về -1 nếu a < b, 0 nếu bằng, 1 nếu a > b */
int soSanhNgay(Ngay a, Ngay b) {
    /* Ghép thành số dạng yyyymmdd để so sánh cho dễ */
    long giaTriA = a.nam * 10000L + a.thang * 100 + a.ngay;
    long giaTriB = b.nam * 10000L + b.thang * 100 + b.ngay;
    if (giaTriA < giaTriB) return -1;
    if (giaTriA > giaTriB) return 1;
    return 0;
}

/* Nhập ngày dạng dd/mm/yyyy, nhập lại tới khi hợp lệ */
Ngay nhapNgay(const char *loiNhac) {
    char buf[50];
    char thua;
    Ngay n;
    while (1) {
        printf("%s", loiNhac);
        docDong(buf, sizeof(buf));
        if (sscanf(buf, "%d/%d/%d %c", &n.ngay, &n.thang, &n.nam, &thua) != 3) {
            printf("  -> Sai dinh dang! Vi du dung: 05/11/2026\n");
        } else if (!ngayHopLe(n)) {
            printf("  -> Ngay khong ton tai!\n");
        } else {
            return n;
        }
    }
}

/* Nhập tháng và năm */
void nhapThangNam(int *thang, int *nam) {
    *thang = nhapSoNguyen("Nhap thang (1-12): ", 1, 12);
    *nam = nhapSoNguyen("Nhap nam: ", 1900, 2100);
}
