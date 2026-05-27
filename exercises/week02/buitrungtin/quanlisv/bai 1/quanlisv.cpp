#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>

using namespace std;

struct SinhVien {
    string mssv;
    string ten;
    double diem;
};

// Quản lý danh sách sinh viên bằng mảng động
struct DanhSachSV {
    SinhVien* ds;
    int size;
    int capacity;

    void init() {
        capacity = 4;
        size = 0;
        ds = new SinhVien[capacity];
    }

    void resize(int newCapacity) {
        SinhVien* temp = new SinhVien[newCapacity];
        for (int i = 0; i < size; i++) {
            temp[i] = ds[i];
        }
        delete[] ds;
        ds = temp;
        capacity = newCapacity;
    }

    // 1. Thêm sinh viên
    void themSV(SinhVien sv) {
        if (size == capacity) {
            resize(capacity * 2);
        }
        ds[size] = sv;
        size++;
        cout << "=> Them sinh vien thanh cong!\n";
    }

    // 2. Xóa sinh viên theo MSSV
    void xoaSV(string mssv) {
        int index = -1;
        for (int i = 0; i < size; i++) {
            if (ds[i].mssv == mssv) {
                index = i;
                break;
            }
        }
        if (index == -1) {
            cout << "=> Khong tim thay sinh vien co MSSV: " << mssv << endl;
            return;
        }
        // Dịch chuyển các phần tử phía sau lên trước
        for (int i = index; i < size - 1; i++) {
            ds[i] = ds[i + 1];
        }
        size--;
        cout << "=> Xoa sinh vien thanh cong!\n";
    }

    // 3. Tìm kiếm theo tên hoặc MSSV (Linear Search)
    void timKiem(string tuKhoa) {
        bool timThay = false;
        cout << "\n" << setfill('-') << setw(60) << "-" << setfill(' ') << endl;
        cout << setw(15) << left << "MSSV" << setw(30) << left << "Ho va Ten" << setw(10) << right << "Diem" << endl;
        cout << setfill('-') << setw(60) << "-" << setfill(' ') << endl;

        for (int i = 0; i < size; i++) {
            if (ds[i].mssv == tuKhoa || ds[i].ten.find(tuKhoa) != string::npos) {
                cout << setw(15) << left << ds[i].mssv
                    << setw(30) << left << ds[i].ten
                    << setw(10) << right << fixed << setprecision(2) << ds[i].diem << endl;
                timThay = true;
            }
        }
        if (!timThay) cout << "Khong tim thay ket qua phu hop.\n";
    }

    // 4. Sắp xếp tăng dần theo điểm (Bubble Sort)
    void sapXepTheoDiem() {
        for (int i = 0; i < size - 1; i++) {
            for (int j = 0; j < size - i - 1; j++) {
                if (ds[j].diem > ds[j + 1].diem) {
                    SinhVien temp = ds[j];
                    ds[j] = ds[j + 1];
                    ds[j + 1] = temp;
                }
            }
        }
        cout << "=> Da sap xep danh sach tang dan theo diem!\n";
    }

    // 5. Thống kê điểm & Xuất báo cáo màn hình
    void xuatBaoCao() {
        if (size == 0) {
            cout << "Danh sach trong!\n";
            return;
        }

        double minDiem = ds[0].diem, maxDiem = ds[0].diem, tong = 0;
        for (int i = 0; i < size; i++) {
            if (ds[i].diem < minDiem) minDiem = ds[i].diem;
            if (ds[i].diem > maxDiem) maxDiem = ds[i].diem;
            tong += ds[i].diem;
        }

        cout << "\n" << setfill('=') << setw(60) << "=" << setfill(' ') << endl;
        cout << setw(15) << left << "MSSV" << setw(30) << left << "Ho va Ten" << setw(10) << right << "Diem" << endl;
        cout << setfill('-') << setw(60) << "-" << setfill(' ') << endl;
        for (int i = 0; i < size; i++) {
            cout << setw(15) << left << ds[i].mssv
                << setw(30) << left << ds[i].ten
                << setw(10) << right << fixed << setprecision(2) << ds[i].diem << endl;
        }
        cout << setfill('-') << setw(60) << "-" << setfill(' ') << endl;
        cout << "Tong so sinh vien: " << size << endl;
        cout << "Diem cao nhat   : " << maxDiem << endl;
        cout << "Diem thap nhat  : " << minDiem << endl;
        cout << "Diem trung binh : " << fixed << setprecision(2) << tong / size << endl;
        cout << setfill('=') << setw(60) << "=" << setfill(' ') << endl;
    }

    // Xuất danh sách ra file txt
    void xuatFile(string filename) {
        ofstream f(filename);
        if (!f.is_open()) {
            cout << "Loi mo file de ghi!\n";
            return;
        }
        f << "MSSV,HoTen,Diem\n";
        for (int i = 0; i < size; i++) {
            f << ds[i].mssv << "," << ds[i].ten << "," << ds[i].diem << "\n";
        }
        f.close();
        cout << "=> Da xuat du lieu ra file " << filename << " thanh cong!\n";
    }

    void freeMemory() {
        delete[] ds;
    }
};

int main() {
    DanhSachSV ql;
    ql.init();
    int luonChon;

    do {
        cout << "\n=== QUAN LY DIEM SINH VIEN ===\n";
        cout << "1. Them sinh vien\n";
        cout << "2. Xoa sinh vien\n";
        cout << "3. Tim kiem\n";
        cout << "4. Xep hang lop (Sap xep diem)\n";
        cout << "5. Xuat bao cao\n";
        cout << "6. Xuat ra file diem_sinhvien.txt\n";
        cout << "0. Thoat\n";
        cout << "Nhap lua chon cua ban: ";
        cin >> luonChon;
        cin.ignore(); // Xóa bộ nhớ đệm tránh trôi lệnh khi nhập chuỗi

        if (luonChon == 1) {
            SinhVien sv;
            cout << "Nhap MSSV: "; getline(cin, sv.mssv);
            cout << "Nhap ho va ten: "; getline(cin, sv.ten);
            cout << "Nhap diem: "; cin >> sv.diem;
            ql.themSV(sv);
        }
        else if (luonChon == 2) {
            string mssv;
            cout << "Nhap MSSV can xoa: "; getline(cin, mssv);
            ql.xoaSV(mssv);
        }
        else if (luonChon == 3) {
            string keyword;
            cout << "Nhap ten hoac MSSV can tim: "; getline(cin, keyword);
            ql.timKiem(keyword);
        }
        else if (luonChon == 4) {
            ql.sapXepTheoDiem();
        }
        else if (luonChon == 5) {
            ql.xuatBaoCao();
        }
        else if (luonChon == 6) {
            ql.xuatFile("diem_sinhvien.txt");
        }
    } while (luonChon != 0);

    ql.freeMemory();
    cout << "Tam biet!";
    return 0;
}