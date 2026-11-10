# Quản lý chấm công & tính lương nhân viên

Chương trình console viết bằng ngôn ngữ C (chuẩn C99), không dùng giao diện đồ hoạ và không dùng cơ sở dữ liệu.

## Chức năng

| Nhóm | Chức năng |
|---|---|
| Nhân viên | Thêm, hiển thị, sửa, xoá, tìm kiếm (theo mã / tên), sắp xếp |
| Chấm công | Chấm công theo ngày (giờ vào/ra, nghỉ phép, nghỉ không phép), sửa, xoá, xem lịch sử tháng |
| Lương | Phiếu lương 1 nhân viên, bảng lương tháng, xuất file CSV |
| Thống kê | Giờ công theo tháng (đệ quy), tổng quỹ lương, nhân viên thiếu công |
| Tệp | Lưu / đọc `dulieu.txt`, nạp dữ liệu mẫu (15 nhân viên, tháng 10/2026) |

## Cấu trúc dữ liệu

- `DanhSachNV`: mảng động các `NhanVien` (`malloc` / `realloc`).
- Mỗi `NhanVien` có con trỏ `dsChamCong` trỏ tới **danh sách liên kết đơn** các bản ghi `ChamCong`, sắp tăng dần theo ngày.
- Tổng giờ công, giờ lũy kế, số công trong tháng được tính bằng **hàm đệ quy** trên danh sách liên kết (`thongke.c`).

## Công thức lương

```
donGiaNgay = luongCoBan / 26
donGiaGio  = donGiaNgay / 8
Luong      = donGiaNgay * soCong + donGiaGio * 1.5 * gioOT + phuCap
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
├── tienich.c/.h      Nhập liệu có kiểm tra, xử lý ngày giờ
├── nhanvien.c/.h     Quản lý nhân viên
├── chamcong.c/.h     Danh sách liên kết chấm công
├── thongke.c/.h      Hàm đệ quy, thống kê
├── luong.c/.h        Tính lương, xuất CSV
├── tepdulieu.c/.h    Lưu / đọc file, dữ liệu mẫu
└── tai_lieu/         Báo cáo (.docx) và tóm tắt đề tài
```
