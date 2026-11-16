/*
 * chamcong.h
 * Quản lý chấm công bằng danh sách liên kết đơn.
 */
#ifndef CHAMCONG_H
#define CHAMCONG_H

#include "kieudulieu.h"

/* Thao tác trên danh sách liên kết */
ChamCong *taoChamCong(Ngay n, float gioLam, float gioThem);
ChamCong *timChamCong(ChamCong *head, Ngay n);
void      chenChamCong(ChamCong **head, ChamCong *moi);
void      giaiPhongCC(ChamCong *head);
int       demBanGhi(ChamCong *head);

/* Chức năng trên menu */
void chamCongTheoNgay(DanhSachNV *d);   /* F2.1 */

#endif
