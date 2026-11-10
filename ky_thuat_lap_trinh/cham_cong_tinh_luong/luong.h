/*
 * luong.h
 * Tính lương nhân viên.
 */
#ifndef LUONG_H
#define LUONG_H

#include "kieudulieu.h"

double tinhLuong(NhanVien *nv, int thang, int nam);

/* Chức năng trên menu */
void inLuongMotNV(DanhSachNV *d);       /* F3.1 */
void inBangLuong(DanhSachNV *d);        /* F3.2 */
void xuatBangLuongCSV(DanhSachNV *d);   /* F3.3 */

#endif
