/*
 * tepdulieu.h
 * Lưu / đọc dữ liệu ra file văn bản, nạp dữ liệu mẫu.
 */
#ifndef TEPDULIEU_H
#define TEPDULIEU_H

#include "kieudulieu.h"

int  luuTep(DanhSachNV *d, const char *tenFile);   /* F5.1 */
int  docTep(DanhSachNV *d, const char *tenFile);   /* F5.2 */
void napDuLieuMau(DanhSachNV *d);                  /* F5.3 */
#endif
