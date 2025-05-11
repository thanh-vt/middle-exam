# Tin học cơ sở 2 - Bài kiểm tra cuối kỳ
## Vũ Tất Thành - K24DTCN638

- **FPLDLW25638FTP90**: In ra bảng số nhị phân từ 1 đến n.
- **FPLDLW25638FTP126**: Tìm tất cả các số nguyên tố trong mảng.
- **FPLDLW25638FTP163**: Kiểm tra xem ma trận có phải là ma trận được cấu thành bởi một ma trận đơn vị viết liền kề trước với một ma trận P không.
- **FPLDLW25638FTP197**: Sử dụng malloc để cấp phát bộ nhớ cho ma trận động, nhập giá trị và in ma trận.
- **FPLDLW25638FTP48**: Nhập giờ, phút, giây → tính tổng số giây.

### Hướng dẫn chạy chương trình
- B1: Compile file mã nguồn .c tương ứng với bài tập ở trên bằng gcc.
- B2: Copy file đầu vào của test case ngang hàng với file binary sau khi build
- B3: Chạy file binary kèm theo tham số dòng lệnh là các số thứ tự của test case cần chạy

**Note: nếu không cung cấp tham số dòng lệnh thì mặc định chương trình chạy 3 test case 1, 2 và 3.**

**VD:** Chạy chương trình bài tập FPLDLW25638FTP90 với test case 1 và 2:
- Đầu vào là 2 file FPLDLW25638FTP90IN01.txt, FPLDLW25638FTP90IN02.txt
- Đầu ra sinh ra 2 file FPLDLW25638FTP90OUT01.txt, FPLDLW25638FTP90OUT02.txt

**Windows**
```
gcc FPLDLW25638FTP90.c -o FPLDLW25638FTP90.exe
.\FPLDLW25638FTP90.exe 1 2
```

**Linux**
```
gcc FPLDLW25638FTP90.c -o FPLDLW25638FTP90
./FPLDLW25638FTP90 1 2
```

