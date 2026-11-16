# GIẢI THÍCH CODE DỰ ÁN – DÀNH CHO NGƯỜI MỚI

> Mẹo đọc: mở file này trong VS Code rồi nhấn `Cmd + Shift + V` để xem dạng đẹp.
> Vừa đọc vừa mở file code tương ứng ở bên cạnh để đối chiếu.

---

## PHẦN 1. CHƯƠNG TRÌNH NÀY LÀM GÌ? (bức tranh lớn)

Hãy tưởng tượng bạn là nhân viên phòng nhân sự của một công ty nhỏ. Mỗi tháng bạn phải:

1. Giữ **sổ danh sách nhân viên** (mã, tên, phòng ban, chức vụ, lương cơ bản).
2. Mỗi ngày ghi **sổ chấm công**: hôm nay ai làm bao nhiêu giờ, có làm thêm giờ không.
3. Cuối tháng **tính lương** dựa vào số công và số giờ làm thêm.
4. Làm **báo cáo thống kê giờ công** của từng người trong tháng.
5. **Cất sổ** vào tủ (lưu file) để hôm sau mở ra dùng tiếp.

Chương trình này làm thay tất cả việc trên. Người dùng chỉ việc gõ số để chọn chức năng trên **menu** hiện ra trong cửa sổ đen (console / terminal).

```
=======================================
  QUAN LY CHAM CONG & TINH LUONG
=======================================
1. Quan ly nhan vien
2. Cham cong theo ngay
3. Tinh luong
4. Thong ke gio cong theo thang
5. Tep du lieu
0. Thoat
```

**Câu nói 1 dòng khi được hỏi "dự án của em làm gì?":**
> "Đây là chương trình C chạy trên console giúp quản lý nhân viên, chấm công theo từng ngày, tính lương theo số công và giờ làm thêm, thống kê giờ công theo tháng và lưu dữ liệu ra file."

### Danh sách chức năng (11 chức năng)

| Nhóm | Chức năng | Loại |
|---|---|---|
| Nhân viên | Thêm, Hiển thị | Bắt buộc |
| Nhân viên | Sửa, Xoá | Mở rộng |
| Chấm công | Chấm công theo ngày | Bắt buộc |
| Lương | Lương 1 nhân viên, Bảng lương tháng | Bắt buộc |
| Thống kê | Giờ công theo tháng (đệ quy) | Bắt buộc |
| File | Lưu, Đọc | Bắt buộc |
| File | Nạp dữ liệu mẫu | Mở rộng |

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
[01/10 | 8h] ──► [02/10 | 8h] ──► [05/10 | 8h + 2h OT] ──► NULL
```

- **Ưu điểm so với mảng:** thêm một toa vào giữa chỉ cần **tháo móc và móc lại**, không phải dời cả đoàn; không cần biết trước có bao nhiêu toa.
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
| `kieudulieu.h` | **Mẫu các tờ phiếu**: định nghĩa struct `Ngay`, `ChamCong`, `NhanVien`, `DanhSachNV` và các hằng số (26 công, 8 giờ, hệ số 1.5, tối đa 16 giờ OT) |
| `tienich.c/.h` | **Hộp đồ nghề**: nhập số/chữ an toàn, kiểm tra ngày hợp lệ, so sánh ngày |
| `nhanvien.c/.h` | **Sổ nhân viên**: thêm, hiển thị, sửa, xoá |
| `chamcong.c/.h` | **Sổ chấm công**: đoàn tàu chấm công của từng người, chấm công theo ngày |
| `thongke.c/.h` | **Các hàm đệ quy** tính tổng giờ, giờ OT, số công + thống kê giờ công tháng |
| `luong.c/.h` | **Phòng kế toán**: tính lương, phiếu lương, bảng lương |
| `tepdulieu.c/.h` | **Tủ hồ sơ**: lưu/đọc file `dulieu.txt`, nạp dữ liệu mẫu |
| `main.c` | **Lễ tân**: hiện menu, hỏi người dùng muốn gì rồi gọi đúng hàm |

Luồng gọi nhau:

```
main.c  ──gọi──►  nhanvien.c / chamcong.c / luong.c / thongke.c / tepdulieu.c
                         │
                         └──tất cả đều dùng──►  tienich.c (nhập liệu, ngày tháng)
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
    float gioLam;           // giờ làm chính trong ngày (0.5 - 8)
    float gioThem;          // giờ làm thêm (OT)
    struct ChamCong *next;  // cái móc nối sang toa sau
} ChamCong;

typedef struct {            // Danh sách nhân viên
    NhanVien *ds;           // địa chỉ của mảng
    int soLuong;            // đang có bao nhiêu người
    int sucChua;            // mảng chứa được tối đa bao nhiêu người
} DanhSachNV;
```

**Vì sao nhân viên dùng mảng, chấm công dùng danh sách liên kết?**
- Nhân viên: hay **tra cứu theo mã, in danh sách** → mảng tiện hơn (`ds[i]`).
- Chấm công: số ngày không biết trước, cần **chèn ngày mới vào đúng vị trí** → danh sách liên kết tiện hơn. Và đề bài yêu cầu như vậy.

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
        switch (chon) {                  // 4. Chọn số nào thì làm việc đó
            case 1: menuNhanVien(&d); break;
            case 2: chamCongTheoNgay(&d); tamDung(); break;
            case 3: menuLuong(&d); break;
            case 4: thongKeGioCong(&d); tamDung(); break;
            case 5: menuFile(&d); break;
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
- Menu 1, 3, 5 có menu con (`menuNhanVien`, `menuLuong`, `menuFile`) viết cùng kiểu `do … while` + `switch`.

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

Tương tự có `nhapSoThuc` (số thập phân trong khoảng min–max), `nhapChuoi`, `nhapNgay` (dd/mm/yyyy), `nhapThangNam`, `hoiCoKhong` (y/n).

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

### 5.5. Sửa nhân viên – `suaNV` (nhanvien.c)

- Hỏi mã NV (`chonNV`), lấy địa chỉ nhân viên đó: `nv = &d->ds[viTri];`
- Hiện một menu nhỏ: 1. họ tên, 2. phòng ban, 3. chức vụ, 4. lương cơ bản, 0. xong.
- Vì `nv` là **con trỏ** tới nhân viên thật trong mảng, gán `nv->luongCoBan = ...` là sửa luôn dữ liệu gốc.

### 5.6. Xoá nhân viên – `xoaNV` (nhanvien.c)

```c
giaiPhongCC(d->ds[viTri].dsChamCong);       // 1. trả bộ nhớ đoàn tàu chấm công
for (i = viTri; i < d->soLuong - 1; i++) {   // 2. dồn những người phía sau lên
    d->ds[i] = d->ds[i + 1];
}
d->soLuong--;                                // 3. bớt 1 người
```

Giống xếp hàng: một người rời hàng thì những người phía sau bước lên một bước. Trước khi xoá chương trình hỏi xác nhận `(y/n)`.

### 5.7. Chấm công theo ngày – `chamCongTheoNgay` (chamcong.c)

```c
n = nhapNgay("Ngay cham cong (dd/mm/yyyy): ");
if (timChamCong(nv->dsChamCong, n) != NULL) {          // đã chấm ngày này chưa?
    printf("=> Ngay nay da duoc cham cong!\n");
} else {
    gioLam = nhapSoThuc("So gio lam trong ngay (0.5 - 8): ", 0.5, GIO_CHUAN);
    gioThem = 0;
    if (gioLam == GIO_CHUAN) {                          // chỉ làm đủ 8 giờ mới hỏi OT
        gioThem = nhapSoThuc("So gio lam them (0 - 16): ", 0, GIO_OT_TOI_DA);
    }
    c = taoChamCong(n, gioLam, gioThem);                // malloc 1 toa mới
    chenChamCong(&nv->dsChamCong, c);                   // móc toa vào đúng chỗ
}
```

- Quy tắc: **chưa làm đủ 8 giờ thì không có giờ làm thêm** (hợp lý với thực tế).
- Vòng `do … while (hoiCoKhong("Cham cong tiep ..."))` cho phép chấm nhiều ngày liên tiếp cho cùng một người.

### 5.8. Chèn vào đoàn tàu đúng thứ tự – `chenChamCong` (chamcong.c)

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

### 5.9. ĐỆ QUY – tổng giờ công lũy kế trong tháng – `tongGioThang` (thongke.c)

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

**Chạy tay ví dụ** – đoàn tàu có 3 toa tháng 10: 8h, 10h (8 + 2 OT), 4h.

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

Câu nói tóm tắt: **"Tổng giờ lũy kế của cả đoàn tàu = giờ của toa đầu + tổng giờ của phần tàu còn lại. Khi hết tàu (NULL) thì tổng bằng 0."**

Hai hàm đệ quy khác trong `thongke.c` viết **cùng một khuôn**, dùng để tính lương:

| Hàm | Mỗi toa (đúng tháng) đóng góp |
|---|---|
| `tongGioThang` | giờ làm + giờ OT |
| `tongOTThang` | giờ OT |
| `demCongThang` | giờ làm / 8 (8h = 1 công, 4h = 0,5 công) |

**Thống kê giờ công tháng – `thongKeGioCong`:** hỏi tháng/năm, rồi với **mỗi nhân viên** gọi 3 hàm đệ quy trên để in một dòng: số công, giờ làm, giờ OT, tổng giờ. Cuối bảng cộng dồn thành dòng TỔNG CỘNG.

### 5.10. Tính lương – `tinhLuong` (luong.c)

```c
double donGiaNgay = nv->luongCoBan / CONG_CHUAN;   // lương 1 ngày công (chia 26)
double donGiaGio  = donGiaNgay / GIO_CHUAN;        // lương 1 giờ (chia 8)
float soCong = demCongThang(...);                  // đệ quy
float gioOT  = tongOTThang(...);                   // đệ quy
return donGiaNgay * soCong + donGiaGio * HE_SO_OT * gioOT;
```

**Ví dụ NV001** (dữ liệu mẫu tháng 10/2026): lương cơ bản 7.800.000, 23 công, 10 giờ OT.

```
donGiaNgay = 7.800.000 / 26        =   300.000
donGiaGio  =   300.000 / 8         =    37.500
Lương công = 300.000 × 23          = 6.900.000
Lương OT   = 37.500 × 1,5 × 10     =   562.500
THỰC NHẬN                          = 7.462.500 đ
```

`CONG_CHUAN`, `GIO_CHUAN`, `HE_SO_OT` là **hằng số** khai báo bằng `#define` trong `kieudulieu.h`. Muốn đổi công chuẩn từ 26 sang 22 chỉ cần sửa **1 chỗ**.

- `inLuongMotNV` (menu 3 → 1): in phiếu lương chi tiết từng dòng như ví dụ trên.
- `inBangLuong` (menu 3 → 2): in bảng lương mọi nhân viên + tổng quỹ lương cuối bảng.

### 5.11. Lưu file – `luuTep` (tepdulieu.c)

File `dulieu.txt` trông như sau:

```
15                                                  ← dòng 1: có 15 nhân viên
NV001|Nguyen Van An|Ky thuat|Nhan vien|7800000|23   ← thông tin + có 23 dòng chấm công
01/10/2026|8.00|0.00                                ← ngày | giờ làm | giờ làm thêm
02/10/2026|8.00|0.00
05/10/2026|8.00|2.00
...
NV002|Tran Thi Binh|...
```

Thuật toán: in số nhân viên → với **mỗi nhân viên**: in 1 dòng thông tin → đi dọc đoàn tàu, mỗi toa in 1 dòng.

**Vì sao dùng dấu `|` mà không dùng dấu cách?** Vì họ tên có dấu cách ("Nguyen Van An"). Cũng vì vậy khi nhập chương trình **không cho gõ ký tự `|`**.

### 5.12. Đọc file – `docTep` (tepdulieu.c)

```c
sscanf(dong, "%9[^|]|%49[^|]|%29[^|]|%29[^|]|%lf|%d",
       nv.maNV, nv.hoTen, nv.phongBan, nv.chucVu,
       &nv.luongCoBan, &soBanGhi);
```

- `%49[^|]` = "đọc tối đa 49 ký tự, đọc cho tới khi gặp dấu `|`".
- Đọc xong dòng nhân viên thì biết `soBanGhi`, đọc tiếp đúng bấy nhiêu dòng chấm công (`"%d/%d/%d|%f|%f"`), mỗi dòng tạo 1 toa và chèn vào đoàn tàu.
- Dòng nào sai định dạng, ngày không hợp lệ hoặc giờ ngoài khoảng cho phép thì **bỏ qua**, chương trình không bị sập.

### 5.13. Dữ liệu mẫu – `napDuLieuMau` (tepdulieu.c)

15 nhân viên, tháng 10/2026. Tháng này có đúng 22 ngày làm việc từ thứ 2 tới thứ 6. Mỗi nhân viên có một **chuỗi 22 ký tự**, mỗi ký tự là một ngày:

| Ký tự | Nghĩa |
|---|---|
| `F` | làm đủ 8 giờ |
| `O` | làm 8 giờ + 2 giờ làm thêm |
| `H` | làm nửa ngày (4 giờ = 0,5 công) |
| `-` | không đi làm (không tạo bản ghi) |

Thêm `soNgayT7` = số ngày thứ 7 đi làm thêm (mỗi ngày +1 công).

Ví dụ NV001: `"FFOFFOFFOFFOFFOFFFFFFF"` + 1 ngày thứ 7 → 23 công, 10 giờ OT. Code dùng `switch` theo từng ký tự để tạo toa chấm công tương ứng.

### 5.14. Giải phóng bộ nhớ – `giaiPhongCC` (chamcong.c)

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
| Giờ làm trong ngày | 0,5 – 8 giờ |
| Giờ làm thêm | 0 – 16 giờ, chỉ nhập khi làm đủ 8 giờ |
| Số công 1 ngày | giờ làm / 8 (8h = 1 công, 4h = 0,5 công) |
| Công chuẩn / tháng | 26 công |
| Hệ số OT | 1,5 |
| Lương | (LCB / 26) × số công + (LCB / 26 / 8) × 1,5 × giờ OT |
| Mỗi ngày | chỉ chấm công 1 lần cho mỗi nhân viên |

---

## PHẦN 7. CÂU HỎI THƯỜNG GẶP KHI BẢO VỆ & CÁCH TRẢ LỜI

**1. Đệ quy dùng ở đâu? Giải thích?**
> Ở `thongke.c`, hàm `tongGioThang` tính tổng giờ công lũy kế trong tháng. Điều kiện dừng: con trỏ NULL (hết danh sách) trả về 0. Bước đệ quy: lấy giờ của nút hiện tại (nếu đúng tháng) cộng với `tongGioThang(p->next)`. Ngoài ra `tongOTThang` và `demCongThang` cũng đệ quy cùng kiểu, dùng để tính lương.

**2. Đệ quy khác vòng lặp thế nào? Sao không dùng vòng lặp?**
> Kết quả như nhau. Đệ quy hợp với danh sách liên kết vì danh sách liên kết cũng có tính đệ quy: một danh sách = nút đầu + danh sách còn lại. Nhược điểm của đệ quy là tốn bộ nhớ ngăn xếp, danh sách rất dài có thể tràn ngăn xếp; với khoảng 31 ngày/tháng thì không vấn đề.

**3. Danh sách liên kết nằm ở đâu? Sao không dùng mảng cho chấm công?**
> Mỗi `NhanVien` có con trỏ `dsChamCong` trỏ tới nút đầu. Mỗi nút `ChamCong` có con trỏ `next`. Dùng danh sách liên kết vì số ngày chấm công không biết trước và cần chèn vào đúng vị trí theo ngày mà không phải dịch chuyển phần tử.

**4. Làm sao danh sách luôn theo thứ tự ngày?**
> Hàm `chenChamCong` không chèn vào cuối mà đi tìm vị trí đúng: dừng ở nút cuối cùng có ngày nhỏ hơn ngày mới rồi chèn vào sau nút đó. Nếu ngày mới nhỏ nhất thì chèn vào đầu.

**5. Tại sao `chenChamCong` dùng `ChamCong **head`?**
> Vì có trường hợp phải thay đổi nút đầu danh sách. Muốn hàm sửa được con trỏ đầu thì phải truyền địa chỉ của con trỏ đó, tức con trỏ cấp 2.

**6. Làm sao chống chấm công trùng ngày?**
> Trước khi chèn, gọi `timChamCong` duyệt danh sách xem đã có ngày đó chưa. Có rồi thì báo và không chèn nữa.

**7. Nhân viên lưu bằng gì? Nếu thêm quá nhiều thì sao?**
> Mảng động cấp phát bằng `malloc`, ban đầu chứa 10. Khi đầy thì `realloc` tăng gấp đôi, nên không giới hạn số nhân viên (chỉ phụ thuộc bộ nhớ máy).

**8. Rò rỉ bộ nhớ là gì? Chương trình xử lý thế nào?**
> Là cấp phát bộ nhớ mà không trả lại. Khi xoá nhân viên, chương trình `free` toàn bộ danh sách chấm công của người đó; khi thoát, `giaiPhongDS` trả toàn bộ bộ nhớ.

**9. Số công tính thế nào?**
> Mỗi ngày được (giờ làm / 8) công: làm 8 giờ là 1 công, làm 4 giờ là 0,5 công. Số công tháng là tổng các ngày, tính bằng hàm đệ quy `demCongThang`.

**10. Tại sao làm chưa đủ 8 giờ thì không được nhập giờ làm thêm?**
> Vì làm thêm giờ chỉ có ý nghĩa khi đã làm hết giờ chuẩn. Chương trình chỉ hỏi giờ làm thêm khi giờ làm bằng 8.

**11. Công thức lương?**
> Lương = (lương cơ bản / 26) × số công + (lương cơ bản / 26 / 8) × 1,5 × giờ OT. Ví dụ NV001 được 7.462.500 đ.

**12. Nhập chữ vào chỗ cần số thì sao?**
> Mọi chỗ nhập đều qua hàm trong `tienich.c`: đọc cả dòng bằng `fgets`, tách bằng `sscanf`. Sai thì báo lỗi và bắt nhập lại, chương trình không bị treo.

**13. Sao không dùng `scanf` trực tiếp?**
> `scanf` để lại ký tự xuống dòng trong bộ đệm, làm lần nhập sau bị bỏ qua. Dùng `fgets` đọc cả dòng rồi `sscanf` phân tích thì tránh được lỗi này và kiểm tra được dữ liệu thừa.

**14. File lưu theo định dạng gì? Sao dùng dấu `|`?**
> File văn bản `dulieu.txt`: dòng đầu là số nhân viên, mỗi nhân viên 1 dòng thông tin kèm số bản ghi, sau đó là các dòng chấm công `ngày|giờ làm|giờ OT`. Dùng `|` vì họ tên có dấu cách.

**15. Độ phức tạp của chèn chấm công và hàm đệ quy?**
> Đều là O(n) với n là số bản ghi chấm công của một nhân viên, vì phải duyệt dọc danh sách.

**16. Ngày 29/02 xử lý thế nào?**
> Hàm `laNamNhuan`: năm nhuận là năm chia hết cho 4 nhưng không chia hết cho 100, hoặc chia hết cho 400. Năm nhuận tháng 2 có 29 ngày.

**17. Vì sao chia nhiều file?**
> Mỗi file lo một nhóm việc, dễ đọc, dễ sửa, dễ tìm lỗi. File `.h` khai báo, file `.c` cài đặt. Biên dịch bằng `gcc -std=c99 -Wall -o chamcong *.c`.

**18. Nếu muốn đổi hệ số OT hay công chuẩn thì sửa ở đâu?**
> Sửa hằng số trong `kieudulieu.h` (`HE_SO_OT`, `CONG_CHUAN`, `GIO_CHUAN`), không cần sửa chỗ nào khác.

**19. Hạn chế và hướng phát triển?**
> Chưa có tìm kiếm, sắp xếp nhân viên; chưa sửa/xoá được chấm công; chưa chấm công bằng giờ vào/ra và phân loại ngày nghỉ; chưa có phụ cấp, bảo hiểm, thuế; chưa xuất bảng lương ra Excel. Đây là các hướng phát triển tiếp theo.

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
| O(n) | Thời gian chạy tăng tỉ lệ với số lượng dữ liệu |
