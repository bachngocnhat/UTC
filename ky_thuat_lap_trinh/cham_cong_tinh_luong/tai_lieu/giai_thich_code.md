# GIẢI THÍCH CODE DỰ ÁN – DÀNH CHO NGƯỜI MỚI

> Mẹo đọc: mở file này trong VS Code rồi nhấn `Cmd + Shift + V` để xem dạng đẹp.
> Vừa đọc vừa mở file code tương ứng ở bên cạnh để đối chiếu.

---

## PHẦN 1. CHƯƠNG TRÌNH NÀY LÀM GÌ? (bức tranh lớn)

Hãy tưởng tượng bạn là nhân viên phòng nhân sự của một công ty nhỏ. Mỗi tháng bạn phải:

1. Giữ **sổ danh sách nhân viên** (mã, tên, phòng ban, lương cơ bản, phụ cấp).
2. Mỗi ngày ghi **sổ chấm công**: ai đi làm, giờ vào, giờ ra, ai nghỉ phép, ai nghỉ không phép.
3. Cuối tháng **tính lương** dựa vào số ngày công và số giờ làm thêm.
4. Làm **báo cáo thống kê**: ai làm nhiều, ai thiếu công, công ty phải trả tổng bao nhiêu tiền lương.
5. **Cất sổ** vào tủ (lưu file) để hôm sau mở ra dùng tiếp.

Chương trình này làm thay tất cả việc trên. Người dùng chỉ việc gõ số để chọn chức năng trên **menu** hiện ra trong cửa sổ đen (console / terminal).

```
=======================================
  QUAN LY CHAM CONG & TINH LUONG
=======================================
1. Quan ly nhan vien
2. Cham cong
3. Tinh luong
4. Thong ke
5. Tep du lieu
0. Thoat
```

**Câu nói 1 dòng khi được hỏi "dự án của em làm gì?":**
> "Đây là chương trình C chạy trên console giúp quản lý nhân viên, chấm công theo từng ngày, tự tính giờ làm, giờ làm thêm, tính lương cuối tháng, thống kê và lưu dữ liệu ra file."

---

## PHẦN 2. KIẾN THỨC C TỐI THIỂU CẦN HIỂU

Phần này giải thích các khái niệm bằng ví dụ đời thường. Hiểu phần này là hiểu được 80% dự án.

### 2.1. Biến và kiểu dữ liệu – "cái hộp có dán nhãn"

Biến là một cái hộp để chứa dữ liệu. Mỗi hộp chỉ chứa được một loại đồ:

| Kiểu | Chứa gì | Ví dụ trong dự án |
|---|---|---|
| `int` | số nguyên | `int thang = 10;` |
| `float` | số thập phân (độ chính xác vừa) | `float gioLam = 7.5;` |
| `double` | số thập phân (chính xác hơn, dùng cho tiền) | `double luongCoBan = 7800000;` |
| `char[50]` | chuỗi chữ tối đa 49 ký tự | `char hoTen[50];` |

### 2.2. Hàm – "một công thức nấu ăn"

Hàm là một đoạn code có tên, làm một việc cụ thể. Gọi tên hàm là nó chạy.

```c
int laNamNhuan(int nam) {
    return (nam % 4 == 0 && nam % 100 != 0) || (nam % 400 == 0);
}
```

- `int` đầu tiên: hàm **trả về** một số nguyên (1 = đúng, 0 = sai).
- `(int nam)`: hàm **nhận vào** một số năm.
- `%` là phép chia lấy dư: `2028 % 4 = 0` nghĩa là 2028 chia hết cho 4.

### 2.3. File `.h` và `.c` – "mục lục và nội dung"

Dự án chia thành nhiều file cho dễ quản lý, giống một cuốn sách chia chương:

- File **`.h`** (header) = **mục lục**: chỉ liệt kê tên các hàm có trong chương.
- File **`.c`** = **nội dung**: viết chi tiết từng hàm làm gì.
- `#include "nhanvien.h"` = "tôi muốn dùng các hàm trong chương nhân viên".

Vì có nhiều file `.c` nên khi biên dịch phải dùng `*.c` (tất cả file) – đây chính là lý do nút ▷ Run của VS Code bị lỗi.

### 2.4. `struct` – "một tờ phiếu có nhiều ô"

`struct` gom nhiều thông tin thành một khối. Giống một tờ phiếu hồ sơ nhân viên có nhiều ô để điền:

```c
typedef struct {
    char   maNV[10];       // ô "Mã nhân viên"
    char   hoTen[50];      // ô "Họ tên"
    char   phongBan[30];
    char   chucVu[30];
    double luongCoBan;
    double phuCap;
    ChamCong *dsChamCong;  // "sợi dây" nối tới sổ chấm công của người này
} NhanVien;
```

Truy cập một ô: `nv.hoTen` (nếu có tờ phiếu) hoặc `nv->hoTen` (nếu chỉ có **địa chỉ** của tờ phiếu – xem con trỏ bên dưới).

### 2.5. Mảng – "một dãy tủ đánh số"

Mảng là nhiều hộp cùng loại xếp liền nhau, đánh số từ 0: `ds[0]`, `ds[1]`, `ds[2]`...

### 2.6. Con trỏ – "địa chỉ nhà"

Mỗi dữ liệu trong máy tính nằm ở một **địa chỉ** trong bộ nhớ. **Con trỏ là biến lưu địa chỉ**, không lưu dữ liệu.

- Giống như thay vì bê cả ngôi nhà đi, ta chỉ cần đưa **tờ giấy ghi địa chỉ nhà**.
- `NhanVien *nv` = "nv là địa chỉ của một nhân viên".
- `nv->hoTen` = "đi tới địa chỉ nv, lấy ô họ tên".
- `NULL` = "địa chỉ rỗng", nghĩa là không trỏ tới đâu cả.

**Vì sao cần con trỏ?** Khi truyền con trỏ vào hàm, hàm sửa được dữ liệu gốc. Nếu truyền bản sao thì hàm chỉ sửa bản sao, dữ liệu gốc không đổi.

### 2.7. Cấp phát động `malloc` / `realloc` / `free` – "thuê kho"

Lúc viết code ta không biết công ty sẽ có bao nhiêu nhân viên. Nên chương trình **thuê thêm bộ nhớ khi cần** lúc đang chạy:

| Hàm | Ý nghĩa đời thường |
|---|---|
| `malloc` | thuê một kho mới |
| `realloc` | đổi sang kho to hơn, đồ cũ được chuyển sang |
| `free` | trả kho khi không dùng nữa (nếu quên trả = **rò rỉ bộ nhớ**) |

### 2.8. Danh sách liên kết – "đoàn tàu"

Mỗi ngày chấm công là **một toa tàu**. Mỗi toa chứa thông tin ngày đó và **một cái móc** (`next`) nối sang toa sau. Toa cuối có móc rỗng (`NULL`).

```
dsChamCong
    │
    ▼
[01/10 | 8h] ──► [02/10 | 8h] ──► [05/10 | 10h] ──► NULL
```

- **Ưu điểm so với mảng:** thêm hay bớt một toa ở giữa chỉ cần **tháo móc và móc lại**, không phải dời cả đoàn.
- **Nhược điểm:** muốn tới toa thứ 10 phải đi qua 9 toa trước (không nhảy thẳng như mảng).

### 2.9. Đệ quy – "hàm tự gọi lại chính nó"

Ví dụ đời thường: bạn đứng cuối một hàng người, muốn biết tổng số tiền cả hàng có. Bạn hỏi người phía trước:

> "Tổng tiền từ anh tới đầu hàng là bao nhiêu?"

Người đó lại hỏi người phía trước nữa... cho tới **người đầu hàng** (không còn ai để hỏi) thì trả lời ngay số tiền của mình. Sau đó câu trả lời được cộng dồn ngược lại.

Mọi hàm đệ quy có **2 phần bắt buộc**:
1. **Điều kiện dừng** – trường hợp trả lời được ngay (hết người để hỏi).
2. **Bước đệ quy** – xử lý phần của mình + gọi lại chính hàm đó cho phần còn lại.

Thiếu điều kiện dừng thì hàm gọi mãi không dừng và chương trình bị treo/sập.

### 2.10. File – "cất sổ vào tủ"

Dữ liệu trong bộ nhớ sẽ **mất khi tắt chương trình**. Muốn giữ lại phải ghi ra file trên ổ cứng:

| Hàm | Ý nghĩa |
|---|---|
| `fopen(ten, "w")` | mở file để **ghi** (ghi đè) |
| `fopen(ten, "r")` | mở file để **đọc** |
| `fprintf(f, ...)` | ghi chữ vào file |
| `fgets(dong, ..., f)` | đọc 1 dòng từ file |
| `fclose(f)` | đóng file |

---

## PHẦN 3. DỰ ÁN GỒM NHỮNG FILE NÀO?

| File | Vai trò (ví dụ đời thường) |
|---|---|
| `kieudulieu.h` | **Mẫu các tờ phiếu**: định nghĩa struct `Ngay`, `ChamCong`, `NhanVien`, `DanhSachNV` và các hằng số (26 công, 8 giờ, hệ số 1.5) |
| `tienich.c/.h` | **Hộp đồ nghề**: nhập số/chữ an toàn, kiểm tra ngày hợp lệ, đổi giờ HH:MM ↔ phút |
| `nhanvien.c/.h` | **Sổ nhân viên**: thêm, hiển thị, sửa, xoá, tìm, sắp xếp |
| `chamcong.c/.h` | **Sổ chấm công**: đoàn tàu chấm công của từng người, tính giờ làm |
| `thongke.c/.h` | **Các hàm đệ quy** tính tổng giờ, số công + báo cáo thống kê |
| `luong.c/.h` | **Phòng kế toán**: tính lương, in bảng lương, xuất file CSV |
| `tepdulieu.c/.h` | **Tủ hồ sơ**: lưu/đọc file `dulieu.txt`, nạp dữ liệu mẫu |
| `main.c` | **Lễ tân**: hiện menu, hỏi người dùng muốn gì rồi gọi đúng hàm |

Luồng gọi nhau:

```
main.c  ──gọi──►  nhanvien.c / chamcong.c / luong.c / thongke.c / tepdulieu.c
                         │
                         └──tất cả đều dùng──►  tienich.c (nhập liệu, ngày giờ)
```

---

## PHẦN 4. DỮ LIỆU ĐƯỢC SẮP XẾP THẾ NÀO? (quan trọng nhất)

Đề bài yêu cầu: *"struct NhanVien liên kết danh sách chấm công theo ngày"*. Dự án làm như sau:

```
DanhSachNV  (mảng động)
 ├─ ds[0]: NV001 | Nguyen Van An | ... | dsChamCong ─► [01/10] ─► [02/10] ─► ... ─► NULL
 ├─ ds[1]: NV002 | Tran Thi Binh | ... | dsChamCong ─► [01/10] ─► [02/10] ─► ... ─► NULL
 └─ ds[2]: NV003 | Le Van Cuong  | ... | dsChamCong ─► NULL   (chưa chấm công ngày nào)
```

- **Tầng 1 – nhân viên:** một **mảng động** (`DanhSachNV`). Mảng đầy thì `realloc` gấp đôi.
- **Tầng 2 – chấm công:** mỗi nhân viên có **một đoàn tàu riêng** (danh sách liên kết). Đoàn tàu luôn **xếp theo ngày tăng dần**.

### Từng struct (trong `kieudulieu.h`)

```c
typedef struct {            // Một ngày
    int ngay, thang, nam;
} Ngay;

typedef struct ChamCong {   // Một toa tàu = một ngày chấm công
    Ngay  ngay;
    int   loai;             // 0 = đi làm, 1 = nghỉ phép, 2 = nghỉ không phép
    int   gioVao;           // lưu bằng SỐ PHÚT tính từ 0h. VD 08:30 = 510
    int   gioRa;            // -1 nếu là ngày nghỉ
    float gioLam;           // giờ làm chính, tối đa 8
    float gioThem;          // giờ làm thêm (OT)
    struct ChamCong *next;  // cái móc nối sang toa sau
} ChamCong;

typedef struct {            // Danh sách nhân viên
    NhanVien *ds;           // địa chỉ của mảng
    int soLuong;            // đang có bao nhiêu người
    int sucChua;            // mảng chứa được tối đa bao nhiêu người
} DanhSachNV;
```

**Vì sao giờ lưu bằng số phút?** Vì trừ hai số nguyên rất dễ: ra 17:00 (1020) – vào 08:00 (480) = 540 phút = 9 giờ. Nếu lưu dạng chữ "08:00" thì không trừ được.

**Vì sao nhân viên dùng mảng, chấm công dùng danh sách liên kết?**
- Nhân viên: hay **tra cứu, sắp xếp, in danh sách** → mảng tiện hơn (`ds[i]`).
- Chấm công: hay **chèn ngày mới vào giữa, xoá một ngày** → danh sách liên kết tiện hơn. Và đề bài yêu cầu như vậy.

---

## PHẦN 5. ĐI THEO TỪNG CHỨC NĂNG – GIẢI THÍCH CODE

### 5.1. Chương trình bắt đầu chạy – hàm `main` (main.c)

```c
int main(void) {
    DanhSachNV d;
    khoiTaoDS(&d);                       // 1. Thuê kho chứa 10 nhân viên
    ketQua = docTep(&d, TEN_FILE);       // 2. Đọc dữ liệu cũ từ dulieu.txt (nếu có)
    do {
        // 3. In menu, hỏi người dùng chọn số
        chon = nhapSoNguyen("Chon: ", 0, 5);
        switch (chon) {                  // 4. Chọn số nào thì vào menu con đó
            case 1: menuNhanVien(&d); break;
            ...
        }
    } while (chon != 0);                 // 5. Lặp lại cho tới khi chọn 0
    if (hoiCoKhong("Luu du lieu ...")) luuTep(&d, TEN_FILE); // 6. Hỏi lưu
    giaiPhongDS(&d);                     // 7. Trả lại toàn bộ bộ nhớ
    return 0;
}
```

- `do { ... } while (chon != 0);` = "làm ít nhất 1 lần, rồi lặp lại khi chưa chọn 0".
- `switch` = "rẽ nhánh theo giá trị": chọn 1 đi đường 1, chọn 2 đi đường 2...
- `&d` = **địa chỉ** của d, để các hàm con sửa được danh sách thật.

### 5.2. Nhập liệu an toàn – `nhapSoNguyen` (tienich.c)

Người dùng có thể gõ sai (gõ chữ vào chỗ cần số). Hàm này **hỏi đi hỏi lại cho tới khi đúng**:

```c
int nhapSoNguyen(const char *loiNhac, int min, int max) {
    char buf[100]; int x; char thua;
    while (1) {                                   // lặp mãi cho tới khi return
        printf("%s", loiNhac);
        docDong(buf, sizeof(buf));                // đọc cả dòng người dùng gõ
        if (sscanf(buf, "%d %c", &x, &thua) != 1) // tách số ra khỏi dòng
            printf("  -> Vui long nhap mot so nguyen!\n");
        else if (x < min || x > max)
            printf("  -> Vui long nhap so tu %d den %d!\n", min, max);
        else
            return x;                             // đúng thì trả về, thoát vòng lặp
    }
}
```

- `sscanf(buf, "%d %c", ...)` cố đọc **1 số rồi 1 ký tự**. Nếu chỉ đọc được đúng 1 thứ (là số) thì dòng nhập sạch. Nếu gõ `12abc` thì đọc được 2 thứ → báo lỗi. Gõ `abc` thì đọc được 0 thứ → báo lỗi.
- **Vì sao dùng `fgets` (trong `docDong`) mà không dùng `scanf`?** `scanf` để lại ký tự Enter trong bộ đệm, làm lần nhập sau bị "trôi" (bỏ qua). `fgets` đọc trọn cả dòng nên không bị lỗi này.

Tương tự có `nhapSoThuc`, `nhapChuoi`, `nhapNgay` (dd/mm/yyyy), `nhapGio` (HH:MM), `hoiCoKhong` (y/n).

### 5.3. Kiểm tra ngày hợp lệ – `ngayHopLe` (tienich.c)

```c
int soNgayTrongThang(int thang, int nam) {
    switch (thang) {
        case 4: case 6: case 9: case 11: return 30;
        case 2: if (laNamNhuan(nam)) return 29; return 28;
        default: return 31;
    }
}
```

`ngayHopLe` kiểm tra: tháng từ 1–12, ngày từ 1 tới số ngày của tháng đó. Nhờ vậy `31/04` hoặc `29/02/2025` bị từ chối, còn `29/02/2028` (năm nhuận) được chấp nhận.

**So sánh 2 ngày – `soSanhNgay`:** ghép ngày thành một số `yyyymmdd`. Ví dụ 05/10/2026 → `20261005`. Rồi so sánh hai số như bình thường. Mẹo này giúp so sánh ngày chỉ bằng một phép so sánh.

### 5.4. Thêm nhân viên – `themNVVaoDS` (nhanvien.c)

```c
int themNVVaoDS(DanhSachNV *d, NhanVien nv) {
    if (timViTriNV(d, nv.maNV) != -1) return 0;   // trùng mã thì không thêm
    if (d->soLuong == d->sucChua) {               // kho đầy?
        int sucChuaMoi = d->sucChua * 2;          // thuê kho gấp đôi
        NhanVien *mangMoi = realloc(d->ds, sucChuaMoi * sizeof(NhanVien));
        if (mangMoi == NULL) return 0;            // hết bộ nhớ
        d->ds = mangMoi;
        d->sucChua = sucChuaMoi;
    }
    d->ds[d->soLuong] = nv;                       // đặt vào ô trống cuối cùng
    d->soLuong++;                                 // tăng số người lên 1
    return 1;
}
```

- `timViTriNV` duyệt từng người, so mã bằng `strcmp` (so sánh 2 chuỗi, bằng nhau trả về 0). Không thấy trả về `-1`.
- `sizeof(NhanVien)` = một nhân viên chiếm bao nhiêu byte bộ nhớ.
- Mã NV được đổi sang **chữ hoa** (`chuHoa`) nên gõ `nv001` hay `NV001` đều như nhau.

### 5.5. Xoá nhân viên – `xoaNV` (nhanvien.c)

```c
giaiPhongCC(d->ds[viTri].dsChamCong);       // 1. trả bộ nhớ đoàn tàu chấm công
for (i = viTri; i < d->soLuong - 1; i++) {   // 2. dồn những người phía sau lên
    d->ds[i] = d->ds[i + 1];
}
d->soLuong--;                                // 3. bớt 1 người
```

Giống xếp hàng: một người rời hàng thì những người phía sau bước lên một bước.

### 5.6. Tìm kiếm theo tên – `timKiemNV` (nhanvien.c)

- Đổi cả **tên** và **từ khoá** về chữ thường (`chuThuong`) để `"AN"` và `"an"` như nhau.
- `strstr(ten, tuKhoa)` = "trong tên có chứa từ khoá không?". Có thì trả về vị trí, không thì `NULL`.
- Ví dụ tìm `van` sẽ ra Nguyen **Van** An, Le **Van** Cuong...

### 5.7. Sắp xếp – sắp xếp nổi bọt (bubble sort) trong `sapXepNV`

```c
for (i = 0; i < n - 1; i++)
    for (j = 0; j < n - 1 - i; j++)
        if (canDoiCho(&ds[j], &ds[j + 1], tieuChi)) {
            tam = ds[j]; ds[j] = ds[j + 1]; ds[j + 1] = tam;   // đổi chỗ
        }
```

**Ý tưởng:** đi từ đầu tới cuối, so **hai người đứng cạnh nhau**, ai lớn hơn thì đổi chỗ ra sau. Sau mỗi lượt, người lớn nhất "nổi" về cuối hàng (như bọt khí nổi lên mặt nước). Lặp lại cho tới khi cả hàng đúng thứ tự.

- `tam` là biến tạm: muốn đổi nước 2 cốc phải có cốc thứ 3.
- Khi đổi chỗ cả struct, con trỏ `dsChamCong` đi theo nên sổ chấm công không bị lẫn.
- `canDoiCho` quyết định tiêu chí: theo mã, theo tên (`strcmp`), hay theo lương.

### 5.8. Tính giờ làm 1 ngày – `tinhGio` (chamcong.c)

```c
tongPhut = gioRa - gioVao;                    // VD: 1020 - 480 = 540 phút

// Trừ giờ nghỉ trưa 12:00-13:00, chỉ trừ phần nằm trong giờ làm
batDauTrua = 720;  ketThucTrua = 780;          // 12:00 và 13:00 tính bằng phút
if (gioVao > batDauTrua) batDauTrua = gioVao;
if (gioRa  < ketThucTrua) ketThucTrua = gioRa;
if (ketThucTrua > batDauTrua) tongPhut -= (ketThucTrua - batDauTrua);

tongGio = tongPhut / 60.0;                    // 480 / 60 = 8 giờ
if (tongGio > 8) { gioLam = 8; gioThem = tongGio - 8; }
else             { gioLam = tongGio; gioThem = 0; }
```

Ví dụ:

| Vào – Ra | Có mặt | Trừ trưa | Giờ làm | Giờ OT |
|---|---|---|---|---|
| 08:00 – 17:00 | 9h | 1h | 8 | 0 |
| 08:00 – 19:00 | 11h | 1h | 8 | 2 |
| 08:00 – 12:00 | 4h | 0h (không qua trưa) | 4 | 0 |
| 13:30 – 17:00 | 3.5h | 0h | 3.5 | 0 |

`60.0` (có `.0`) để phép chia ra số thập phân. Nếu viết `60` thì `450/60 = 7` (mất phần lẻ).

### 5.9. Chấm công – chèn vào đoàn tàu đúng thứ tự – `chenChamCong` (chamcong.c)

```c
void chenChamCong(ChamCong **head, ChamCong *moi) {
    // TH1: tàu rỗng, hoặc ngày mới nhỏ hơn toa đầu -> gắn vào ĐẦU tàu
    if (*head == NULL || soSanhNgay(moi->ngay, (*head)->ngay) < 0) {
        moi->next = *head;
        *head = moi;
        return;
    }
    // TH2: đi dọc đoàn tàu, tìm toa p đứng ngay TRƯỚC chỗ cần chèn
    ChamCong *p = *head;
    while (p->next != NULL && soSanhNgay(p->next->ngay, moi->ngay) < 0)
        p = p->next;
    moi->next = p->next;   // toa mới móc vào toa sau p
    p->next = moi;         // p móc vào toa mới
}
```

Minh hoạ chèn ngày 03 vào giữa 02 và 05:

```
Trước:  [02] ──► [05] ──► NULL
             p
Bước 1: [03].next = [05]          [03] ──► [05]
Bước 2: [02].next = [03]   [02] ──► [03] ──► [05] ──► NULL
```

**Thứ tự 2 bước rất quan trọng:** nếu làm bước 2 trước thì mất dấu toa [05] (đứt tàu).

**Vì sao `ChamCong **head` (hai dấu sao)?** Ở TH1 ta phải **đổi toa đầu tàu**. Muốn hàm sửa được biến `dsChamCong` của nhân viên thì phải đưa **địa chỉ của biến đó** – tức là "địa chỉ của một địa chỉ" → hai dấu sao.

Trước khi chèn, hàm `chamCongTheoNgay` đã dùng `timChamCong` kiểm tra ngày đó đã chấm chưa, nên không bao giờ có 2 toa cùng ngày.

### 5.10. Xoá một ngày chấm công – `xoaChamCong` (chamcong.c)

```c
ChamCong *truoc = NULL, *p = *head;
while (p != NULL && soSanhNgay(p->ngay, n) != 0) {  // tìm toa cần xoá
    truoc = p;
    p = p->next;
}
if (p == NULL) return 0;                 // không tìm thấy
if (truoc == NULL) *head = p->next;      // xoá toa đầu
else truoc->next = p->next;              // toa trước móc thẳng sang toa sau
free(p);                                 // trả bộ nhớ toa bị xoá
```

```
Xoá [03]:   [02] ──► [03] ──► [05]
            truoc     p
Sau:        [02] ─────────► [05]        (free [03])
```

### 5.11. ĐỆ QUY – tổng giờ công trong tháng – `tongGioThang` (thongke.c)

Đây là phần đề bài **bắt buộc**, rất hay bị hỏi.

```c
float tongGioThang(ChamCong *p, int thang, int nam) {
    float gio = 0;
    if (p == NULL) return 0;                          // ĐIỀU KIỆN DỪNG: hết tàu
    if (p->ngay.thang == thang && p->ngay.nam == nam) // toa này đúng tháng cần tính?
        gio = p->gioLam + p->gioThem;
    return gio + tongGioThang(p->next, thang, nam);   // BƯỚC ĐỆ QUY: + phần còn lại
}
```

**Chạy tay ví dụ** – đoàn tàu có 3 toa tháng 10: 8h, 10h, 4h.

```
tongGioThang([8h])
 = 8  + tongGioThang([10h])
        = 10 + tongGioThang([4h])
               = 4 + tongGioThang(NULL)
                     = 0                  ← điều kiện dừng
               = 4 + 0  = 4
        = 10 + 4 = 14
 = 8  + 14 = 22 giờ
```

Câu nói tóm tắt: **"Tổng giờ của cả đoàn tàu = giờ của toa đầu + tổng giờ của phần tàu còn lại. Khi hết tàu (NULL) thì tổng bằng 0."**

Các hàm đệ quy khác trong `thongke.c` viết **cùng một khuôn**:

| Hàm | Mỗi toa đóng góp |
|---|---|
| `tongGioThang` | giờ làm + giờ OT |
| `tongOTThang` | giờ OT |
| `demCongThang` | đi làm: giờ làm / 8; nghỉ phép: 1; nghỉ không phép: 0 |
| `demNghiKhongPhep` | 1 nếu là ngày nghỉ không phép |
| `gioLuyKe` | giống `tongGioThang` nhưng **dừng sớm** khi gặp ngày lớn hơn ngày cần tính |

**`gioLuyKe` – "lũy kế":** tổng giờ từ đầu tháng **tới một ngày nào đó**. Dùng để in cột "Luy ke" trong bảng lịch sử chấm công. Vì đoàn tàu xếp theo ngày tăng dần, gặp toa có ngày lớn hơn là biết các toa sau cũng lớn hơn → dừng luôn:

```c
if (p == NULL || soSanhNgay(p->ngay, den) > 0) return 0;   // hai điều kiện dừng
```

### 5.12. Tính lương – `tinhLuong` (luong.c)

```c
double donGiaNgay = nv->luongCoBan / CONG_CHUAN;   // lương 1 ngày công (chia 26)
double donGiaGio  = donGiaNgay / GIO_CHUAN;        // lương 1 giờ (chia 8)
float soCong = demCongThang(...);                  // đệ quy
float gioOT  = tongOTThang(...);                   // đệ quy
return donGiaNgay * soCong + donGiaGio * HE_SO_OT * gioOT + nv->phuCap;
```

**Ví dụ NV001** (dữ liệu mẫu tháng 10/2026): lương cơ bản 7.800.000, phụ cấp 500.000, 23 công, 10 giờ OT.

```
donGiaNgay = 7.800.000 / 26        =   300.000
donGiaGio  =   300.000 / 8         =    37.500
Lương công = 300.000 × 23          = 6.900.000
Lương OT   = 37.500 × 1,5 × 10     =   562.500
Phụ cấp                            =   500.000
THỰC NHẬN                          = 7.962.500 đ
```

`CONG_CHUAN`, `GIO_CHUAN`, `HE_SO_OT` là **hằng số** khai báo bằng `#define` trong `kieudulieu.h`. Muốn đổi công chuẩn từ 26 sang 22 chỉ cần sửa **1 chỗ**.

### 5.13. Xuất bảng lương CSV – `xuatBangLuongCSV` (luong.c)

- CSV là file chữ, các cột cách nhau bằng dấu phẩy, mở được bằng Excel.
- Tên file tạo theo tháng: `bangluong_10_2026.csv` (dùng `snprintf` để ghép chuỗi).
- 3 byte `\xEF\xBB\xBF` ở đầu file (BOM) báo cho Excel biết file dùng mã UTF-8.

### 5.14. Lưu file – `luuTep` (tepdulieu.c)

File `dulieu.txt` trông như sau:

```
15                                                  ← dòng 1: có 15 nhân viên
NV001|Nguyen Van An|Ky thuat|Nhan vien|7800000|500000|23   ← thông tin + có 23 dòng chấm công
01/10/2026|0|08:00|17:00                            ← ngày | loại | giờ vào | giờ ra
02/10/2026|0|08:00|17:00
...
NV002|Tran Thi Binh|...
```

Thuật toán: in số nhân viên → với **mỗi nhân viên**: in 1 dòng thông tin → đi dọc đoàn tàu, mỗi toa in 1 dòng.

**Vì sao dùng dấu `|` mà không dùng dấu cách?** Vì họ tên có dấu cách ("Nguyen Van An"). Cũng vì vậy khi nhập chương trình **không cho gõ ký tự `|`**.

### 5.15. Đọc file – `docTep` (tepdulieu.c)

```c
sscanf(dong, "%9[^|]|%49[^|]|%29[^|]|%29[^|]|%lf|%lf|%d",
       nv.maNV, nv.hoTen, nv.phongBan, nv.chucVu,
       &nv.luongCoBan, &nv.phuCap, &soBanGhi);
```

- `%49[^|]` = "đọc tối đa 49 ký tự, đọc cho tới khi gặp dấu `|`".
- Đọc xong dòng nhân viên thì biết `soBanGhi`, đọc tiếp đúng bấy nhiêu dòng chấm công, mỗi dòng tạo 1 toa và chèn vào đoàn tàu.
- Giờ làm và giờ OT **không lưu** trong file mà được **tính lại** từ giờ vào/ra → tránh dữ liệu bị lệch.
- Dòng nào sai định dạng hoặc ngày không hợp lệ thì **bỏ qua** và in cảnh báo, chương trình không bị sập.

### 5.16. Dữ liệu mẫu – `napDuLieuMau` (tepdulieu.c)

Mỗi nhân viên mẫu có một **chuỗi 22 ký tự** tương ứng 22 ngày làm việc (thứ 2 – thứ 6) của tháng 10/2026:

| Ký tự | Nghĩa |
|---|---|
| `F` | đi làm đủ 08:00 – 17:00 |
| `O` | làm thêm 08:00 – 19:00 (2h OT) |
| `H` | nửa ngày 08:00 – 12:00 |
| `P` | nghỉ phép |
| `K` | nghỉ không phép |

Ví dụ NV001: `"FFOFFOFFOFFOFFOFFPFFFF"` + 1 ngày thứ 7 → 23 công, 10 giờ OT. Code dùng `switch` theo từng ký tự để tạo toa chấm công tương ứng.

### 5.17. Giải phóng bộ nhớ – `giaiPhongCC` (chamcong.c)

```c
while (head != NULL) {
    p = head;            // giữ toa hiện tại
    head = head->next;   // nhớ toa sau TRƯỚC khi xoá
    free(p);             // xoá toa hiện tại
}
```

Phải nhớ toa sau trước khi `free`, vì `free` xong thì toa đó không còn, không đọc được `next` nữa.

---

## PHẦN 6. CÁC QUY TẮC NGHIỆP VỤ (nhớ để trả lời)

| Quy tắc | Giá trị |
|---|---|
| Giờ làm chuẩn / ngày | 8 giờ |
| Nghỉ trưa | 12:00 – 13:00, chỉ trừ phần nằm trong giờ làm |
| Phần vượt 8 giờ | tính là giờ làm thêm (OT) |
| Công chuẩn / tháng | 26 công |
| Hệ số OT | 1,5 |
| Nghỉ phép | vẫn tính 1 công |
| Nghỉ không phép | 0 công |
| Làm nửa ngày (4h) | 0,5 công |
| Thiếu công | số công < ngưỡng nhập vào (VD 22) **hoặc** có ngày nghỉ không phép |

---

## PHẦN 7. CÂU HỎI THƯỜNG GẶP KHI BẢO VỆ & CÁCH TRẢ LỜI

**1. Đệ quy dùng ở đâu? Giải thích?**
> Ở `thongke.c`, hàm `tongGioThang`. Điều kiện dừng: con trỏ NULL (hết danh sách) trả về 0. Bước đệ quy: lấy giờ của nút hiện tại (nếu đúng tháng) cộng với `tongGioThang(p->next)`. Ngoài ra còn `gioLuyKe`, `demCongThang`, `tongOTThang`, `demNghiKhongPhep` cùng kiểu.

**2. Đệ quy khác vòng lặp thế nào? Sao không dùng vòng lặp?**
> Kết quả như nhau. Đệ quy hợp với danh sách liên kết vì danh sách liên kết cũng có tính đệ quy: một danh sách = nút đầu + danh sách còn lại. Nhược điểm của đệ quy là tốn bộ nhớ ngăn xếp, danh sách rất dài có thể tràn ngăn xếp; với ~31 ngày/tháng thì không vấn đề.

**3. Danh sách liên kết nằm ở đâu? Sao không dùng mảng cho chấm công?**
> Mỗi `NhanVien` có con trỏ `dsChamCong` trỏ tới nút đầu. Mỗi nút `ChamCong` có con trỏ `next`. Dùng danh sách liên kết vì số ngày chấm công không biết trước và cần chèn/xoá ở giữa mà không phải dịch chuyển phần tử.

**4. Làm sao danh sách luôn theo thứ tự ngày?**
> Hàm `chenChamCong` không chèn vào cuối mà đi tìm vị trí đúng: dừng ở nút cuối cùng có ngày nhỏ hơn ngày mới rồi chèn vào sau nút đó. Nếu ngày mới nhỏ nhất thì chèn vào đầu.

**5. Tại sao `chenChamCong` dùng `ChamCong **head`?**
> Vì có trường hợp phải thay đổi nút đầu danh sách. Muốn hàm sửa được con trỏ đầu thì phải truyền địa chỉ của con trỏ đó, tức con trỏ cấp 2.

**6. Làm sao chống chấm công trùng ngày?**
> Trước khi chèn, gọi `timChamCong` duyệt danh sách xem đã có ngày đó chưa. Có rồi thì báo và yêu cầu dùng chức năng Sửa.

**7. Nhân viên lưu bằng gì? Nếu thêm quá nhiều thì sao?**
> Mảng động cấp phát bằng `malloc`, ban đầu chứa 10. Khi đầy thì `realloc` tăng gấp đôi, nên không giới hạn số nhân viên (chỉ phụ thuộc bộ nhớ máy).

**8. Rò rỉ bộ nhớ là gì? Chương trình xử lý thế nào?**
> Là cấp phát bộ nhớ mà không trả lại. Chương trình `free` từng nút khi xoá một ngày, `free` cả danh sách chấm công khi xoá nhân viên, và `giaiPhongDS` trả toàn bộ bộ nhớ khi thoát.

**9. Giờ làm và giờ OT tính thế nào?**
> Giờ ra trừ giờ vào, trừ phần trùng với giờ nghỉ trưa 12–13h. Phần ≤ 8 giờ là giờ làm chính, phần vượt 8 giờ là OT. Giờ lưu bằng số phút để trừ cho dễ.

**10. Công thức lương?**
> Lương = (lương cơ bản / 26) × số công + (lương cơ bản / 26 / 8) × 1,5 × giờ OT + phụ cấp. Ví dụ NV001 được 7.962.500 đ.

**11. Nhập chữ vào chỗ cần số thì sao?**
> Mọi chỗ nhập đều qua hàm trong `tienich.c`: đọc cả dòng bằng `fgets`, tách bằng `sscanf`. Sai thì báo lỗi và bắt nhập lại, chương trình không bị treo.

**12. Sao không dùng `scanf` trực tiếp?**
> `scanf` để lại ký tự xuống dòng trong bộ đệm, làm lần nhập sau bị bỏ qua. Dùng `fgets` đọc cả dòng rồi `sscanf` phân tích thì tránh được lỗi này và kiểm tra được dữ liệu thừa.

**13. File lưu theo định dạng gì? Sao dùng dấu `|`?**
> File văn bản `dulieu.txt`: dòng đầu là số nhân viên, mỗi nhân viên 1 dòng thông tin kèm số bản ghi, sau đó là các dòng chấm công. Dùng `|` vì họ tên có dấu cách.

**14. Sắp xếp dùng thuật toán gì? Độ phức tạp?**
> Sắp xếp nổi bọt: so sánh 2 phần tử kề nhau, sai thứ tự thì đổi chỗ. Độ phức tạp O(n²), đủ nhanh với số nhân viên của công ty nhỏ.

**15. Độ phức tạp của chèn chấm công và hàm đệ quy?**
> Đều là O(n) với n là số bản ghi chấm công của một nhân viên, vì phải duyệt dọc danh sách.

**16. Ngày 29/02 xử lý thế nào?**
> Hàm `laNamNhuan`: năm nhuận là năm chia hết cho 4 nhưng không chia hết cho 100, hoặc chia hết cho 400. Năm nhuận tháng 2 có 29 ngày.

**17. Vì sao chia nhiều file?**
> Mỗi file lo một nhóm việc, dễ đọc, dễ sửa, dễ tìm lỗi. File `.h` khai báo, file `.c` cài đặt. Biên dịch bằng `gcc -std=c99 -Wall -o chamcong *.c`.

**18. Nếu muốn đổi hệ số OT hay công chuẩn thì sửa ở đâu?**
> Sửa hằng số trong `kieudulieu.h` (`HE_SO_OT`, `CONG_CHUAN`, `GIO_CHUAN`), không cần sửa chỗ nào khác.

**19. Hạn chế và hướng phát triển?**
> Chưa có hệ số OT ngày lễ/cuối tuần, chưa trừ bảo hiểm, thuế; chưa có đăng nhập. Có thể phát triển thêm các phần đó, nhập dữ liệu từ máy chấm công, dùng cơ sở dữ liệu hoặc giao diện đồ hoạ.

---

## PHẦN 8. BẢNG THUẬT NGỮ NHANH

| Thuật ngữ | Nghĩa ngắn gọn |
|---|---|
| Biên dịch (compile) | Dịch code C thành chương trình máy chạy được (`gcc`) |
| Console / Terminal | Cửa sổ chữ để gõ lệnh và chạy chương trình |
| Hàm (function) | Đoạn code có tên, làm một việc |
| Tham số | Dữ liệu đưa vào hàm |
| Giá trị trả về | Kết quả hàm đưa ra (`return`) |
| struct | Kiểu dữ liệu gom nhiều trường |
| Con trỏ (pointer) | Biến chứa địa chỉ bộ nhớ |
| `NULL` | Con trỏ không trỏ đi đâu |
| `->` | Lấy trường của struct thông qua con trỏ |
| `&x` | Lấy địa chỉ của biến x |
| Cấp phát động | Xin bộ nhớ lúc chương trình đang chạy (`malloc`) |
| Rò rỉ bộ nhớ | Xin bộ nhớ mà quên trả (`free`) |
| Danh sách liên kết | Các nút nối nhau bằng con trỏ `next` |
| Nút (node) | Một phần tử của danh sách liên kết |
| Đệ quy | Hàm tự gọi lại chính nó |
| Điều kiện dừng | Trường hợp đệ quy trả lời ngay, không gọi tiếp |
| Hằng số `#define` | Giá trị cố định đặt tên, sửa 1 chỗ đổi mọi nơi |
| O(n), O(n²) | Cách đo thời gian chạy tăng theo số lượng dữ liệu |
