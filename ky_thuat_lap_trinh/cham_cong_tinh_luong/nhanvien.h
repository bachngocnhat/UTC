/*
 * nhanvien.h
 * Quản lý danh sách nhân viên (mảng động).
 */
#ifndef NHANVIEN_H
#define NHANVIEN_H

#include "kieudulieu.h"

/* Khởi tạo / giải phóng */
void khoiTaoDS(DanhSachNV *d);
void giaiPhongDS(DanhSachNV *d);
void xoaHetNV(DanhSachNV *d);

/* Hàm cơ bản */
int  timViTriNV(DanhSachNV *d, const char *ma);
int  themNVVaoDS(DanhSachNV *d, NhanVien nv);
int  chonNV(DanhSachNV *d);
void inTieuDeNV(void);
void inMotNV(int stt, NhanVien *nv);

/* Chức năng trên menu */
void themNV(DanhSachNV *d);       /* F1.1 */
void hienThiDS(DanhSachNV *d);    /* F1.2 */
void suaNV(DanhSachNV *d);        /* F1.3 */
void xoaNV(DanhSachNV *d);        /* F1.4 */
void timKiemNV(DanhSachNV *d);    /* F1.5 */
void sapXepNV(DanhSachNV *d);     /* F1.6 */

#endif
