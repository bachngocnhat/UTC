/*
 * tienich.h
 * Các hàm tiện ích: nhập dữ liệu có kiểm tra, xử lý ngày tháng, chuỗi.
 */
#ifndef TIENICH_H
#define TIENICH_H

#include "kieudulieu.h"

/* Xử lý chuỗi */
void xoaXuongDong(char *s);
void chuHoa(char *s);

/* Nhập dữ liệu từ bàn phím */
void   docDong(char *s, int kichThuoc);
void   nhapChuoi(const char *loiNhac, char *s, int kichThuoc);
int    nhapSoNguyen(const char *loiNhac, int min, int max);
double nhapSoThuc(const char *loiNhac, double min, double max);
int    hoiCoKhong(const char *loiNhac);
void   tamDung(void);

/* Ngày tháng */
int  laNamNhuan(int nam);
int  soNgayTrongThang(int thang, int nam);
int  ngayHopLe(Ngay n);
int  soSanhNgay(Ngay a, Ngay b);
Ngay nhapNgay(const char *loiNhac);
void nhapThangNam(int *thang, int *nam);

#endif
