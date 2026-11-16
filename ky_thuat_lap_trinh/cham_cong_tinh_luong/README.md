# Quản lý chấm công & tính lương nhân viên

Chương trình console viết bằng ngôn ngữ C (chuẩn C99), không dùng giao diện đồ hoạ và không dùng cơ sở dữ liệu.

## Chức năng

| Nhóm | Chức năng |
|---|---|
| Nhân viên | Thêm, hiển thị, sửa, xoá |
| Chấm công | Chấm công theo ngày (số giờ làm, số giờ làm thêm) |
| Lương | Phiếu lương 1 nhân viên, bảng lương tháng |
| Thống kê | Giờ công theo tháng (tính bằng đệ quy) |
| Tệp | Lưu / đọc `dulieu.txt`, nạp dữ liệu mẫu (15 nhân viên, tháng 10/2026) |

## Cấu trúc dữ liệu

- `DanhSachNV`: mảng động các `NhanVien` (`malloc` / `realloc`).
- Mỗi `NhanVien` có con trỏ `dsChamCong` trỏ tới **danh sách liên kết đơn** các bản ghi `ChamCong`, sắp tăng dần theo ngày.
- Tổng giờ công lũy kế, giờ làm thêm, số công trong tháng được tính bằng **hàm đệ quy** trên danh sách liên kết (`thongke.c`).

## Công thức lương

```
donGiaNgay = luongCoBan / 26
donGiaGio  = donGiaNgay / 8
soCong     = tổng (gioLam / 8) của các ngày trong tháng
Luong      = donGiaNgay * soCong + donGiaGio * 1.5 * gioOT
```

## Biên dịch và chạy

```bash
cd ky_thuat_lap_trinh/cham_cong_tinh_luong
gcc -std=c99 -Wall -o chamcong *.c
./chamcong          # Windows: chamcong.exe
```

Lần đầu chạy: vào menu **5 → 3** để nạp dữ liệu mẫu, sau đó xem lương / thống kê của **tháng 10/2026**.

## Cấu trúc thư mục

```
cham_cong_tinh_luong/
├── main.c            Menu chính
├── kieudulieu.h      Struct, hằng số
├── tienich.c/.h      Nhập liệu có kiểm tra, xử lý ngày tháng
├── nhanvien.c/.h     Quản lý nhân viên
├── chamcong.c/.h     Danh sách liên kết chấm công
├── thongke.c/.h      Hàm đệ quy, thống kê giờ công
├── luong.c/.h        Tính lương
├── tepdulieu.c/.h    Lưu / đọc file, dữ liệu mẫu
└── tai_lieu/         Báo cáo (.docx), tóm tắt đề tài, giải thích code
```
