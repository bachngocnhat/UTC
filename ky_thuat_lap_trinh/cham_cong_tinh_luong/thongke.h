/*
 * thongke.h
 * Các hàm ĐỆ QUY tính giờ công và các chức năng thống kê theo tháng.
 */
#ifndef THONGKE_H
#define THONGKE_H

#include "kieudulieu.h"

/* Hàm đệ quy duyệt danh sách liên kết chấm công */
float tongGioThang(ChamCong *p, int thang, int nam);
float tongOTThang(ChamCong *p, int thang, int nam);
float demCongThang(ChamCong *p, int thang, int nam);
int   demNghiKhongPhep(ChamCong *p, int thang, int nam);
float gioLuyKe(ChamCong *p, Ngay den);

/* Chức năng trên menu */
void thongKeGioCong(DanhSachNV *d);   /* F4.1 */
void thongKeQuyLuong(DanhSachNV *d);  /* F4.2 */
void thongKeThieuCong(DanhSachNV *d); /* F4.3 */

#endif
