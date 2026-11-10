/*
 * chamcong.h
 * Quản lý chấm công bằng danh sách liên kết đơn.
 */
#ifndef CHAMCONG_H
#define CHAMCONG_H

#include "kieudulieu.h"

/* Thao tác trên danh sách liên kết */
ChamCong *taoChamCong(Ngay n, int loai, int gioVao, int gioRa);
void      tinhGio(ChamCong *c);
ChamCong *timChamCong(ChamCong *head, Ngay n);
void      chenChamCong(ChamCong **head, ChamCong *moi);
int       xoaChamCong(ChamCong **head, Ngay n);
void      giaiPhongCC(ChamCong *head);
int       demBanGhi(ChamCong *head);
const char *tenLoaiNgay(int loai);

/* Chức năng trên menu */
void chamCongTheoNgay(DanhSachNV *d);   /* F2.1 */
void suaChamCong(DanhSachNV *d);        /* F2.2 */
void xoaChamCongNV(DanhSachNV *d);      /* F2.3 */
void xemLichSu(DanhSachNV *d);          /* F2.4 */

#endif
