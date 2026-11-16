/*
 * kieudulieu.h
 * Khai báo các hằng số và kiểu dữ liệu dùng chung cho cả chương trình.
 */
#ifndef KIEUDULIEU_H
#define KIEUDULIEU_H

/* ---------- Hằng số ---------- */
#define CONG_CHUAN  26        /* số công chuẩn trong 1 tháng          */
#define GIO_CHUAN   8         /* số giờ làm chuẩn trong 1 ngày        */
#define HE_SO_OT    1.5       /* hệ số lương làm thêm giờ              */
#define GIO_OT_TOI_DA 16      /* số giờ làm thêm tối đa trong 1 ngày   */

#define TEN_FILE "dulieu.txt" /* tên file lưu dữ liệu                */

/* ---------- Kiểu dữ liệu ---------- */

/* Ngày tháng năm */
typedef struct {
    int ngay;
    int thang;
    int nam;
} Ngay;

/* Một bản ghi chấm công của 1 ngày = 1 nút trong danh sách liên kết */
typedef struct ChamCong {
    Ngay  ngay;              /* ngày chấm công                    */
    float gioLam;            /* giờ làm chính trong ngày (0 - 8)  */
    float gioThem;           /* giờ làm thêm (OT)                 */
    struct ChamCong *next;   /* con trỏ tới ngày tiếp theo        */
} ChamCong;

/* Thông tin một nhân viên */
typedef struct {
    char   maNV[10];
    char   hoTen[50];
    char   phongBan[30];
    char   chucVu[30];
    double luongCoBan;       /* lương cơ bản / tháng (VND)                 */
    ChamCong *dsChamCong;    /* con trỏ đầu danh sách liên kết chấm công   */
} NhanVien;

/* Danh sách nhân viên: mảng động */
typedef struct {
    NhanVien *ds;            /* mảng nhân viên                             */
    int soLuong;             /* số nhân viên hiện có                       */
    int sucChua;             /* số phần tử tối đa của mảng hiện tại        */
} DanhSachNV;

#endif
