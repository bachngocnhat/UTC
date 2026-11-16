/*
 * thongke.h
 * Các hàm ĐỆ QUY tính giờ công và thống kê giờ công theo tháng.
 */
#ifndef THONGKE_H
#define THONGKE_H

#include "kieudulieu.h"

/* Hàm đệ quy duyệt danh sách liên kết chấm công */
float tongGioThang(ChamCong *p, int thang, int nam);
float tongOTThang(ChamCong *p, int thang, int nam);
float demCongThang(ChamCong *p, int thang, int nam);

/* Chức năng trên menu */
void thongKeGioCong(DanhSachNV *d);   /* F4.1 */

#endif
