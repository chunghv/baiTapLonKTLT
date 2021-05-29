#include <fstream>
#include <iostream>
#include <windows.h>
#include <conio.h>
#include <math.h>
#include <iomanip>
using namespace std;
long double f[100], f1[100], f2[100];  // luu hàm f(x), f'(x), f''(x)
int bac, bacPhay, bacHaiPhay;          // bậc f(x), f'(x), f''(x)
long double a, b;                      // khai báo khoảng [a,b]
long double ETA = 0.001, STEP = 0.001; // khởi tạo eta, step trong thuật toán Gradient Descent
long double d[100];                    // lưu các các trị
int m;                                 // biến đếm các trị
long double c[100];
int t;
int soChuSoSauDauPhay;                                  //số chữ số thập phân sau dấu phẩy
string h = "D:\\kyThuatLapTrinh\\baiTapLon\\chung.txt"; // địa chỉ file text ghi lại quá trình thực hiện chương trình
long double a1, b1;
ofstream output; // biến để ghi quá trình thực hiện chương trình vào file
struct MIN_MAX
{
    long double MIN; // ki?u d? li?u t? d?nh nghia d? luu giá tr? min và max
    long double MAX; // c?a m?t hàm s? trong kho?ng [a,b] cho tru?c
};
//tính giá trị của f(x) tại giá trị x0
long double giaTriF(long double arr[], long double x0, int BAC)
{
    int i;
    long double Fx0 = 0;
    for (i = 0; i <= BAC; i++)
    {
        Fx0 = Fx0 + arr[i] * pow(x0, i);
    }
    return Fx0;
}
//tính giá trị của f'(x) tại giá trị x0
long double giaTriFPhay(long double arr[], long double x0, int BAC)
{
    int i;
    long double Fphay = 0;
    for (i = 1; i <= BAC; i++)
    {
        Fphay = Fphay + arr[i] * i * pow(x0, (i - 1));
    }
    return Fphay;
}

int xetDau(long double arr[], long double x0, int BAC) // hàm xét dấu f'(x)
{
    if (giaTriFPhay(arr, x0, BAC) == 0)
    {
        return 0;
    }
    if (giaTriFPhay(arr, x0, BAC) > 0)
    {
        return 1;
    }
    else
    {
        return -1;
    }
}
// thuật toán Gradient Descent với eta động
long double cuctri(long double arr[], int BAC, long double eta, long double x0) // tìm cực trị địa phương
{
    int i, dau;                // bi?n 'dau' dùng d? luu d?u c?a f'(x0)
    long double deltaX, x_New; // deltaX dùng d? xác d?nh giá tr? nh?y d?n x ti?p theo
    dau = xetDau(arr, x0, BAC);
    for (i = 0; i < 400000; i++)
    {
        deltaX = eta * giaTriFPhay(arr, x0, BAC);
        if (deltaX > 0.2) // các bu?c h?n ch? delTaX quá l?n
        {
            deltaX = 0.2;
        }
        if (deltaX < -0.2)
        {
            deltaX = -0.2;
        }
        x_New = x0 + dau * deltaX;
        if (fabs(giaTriFPhay(arr, x_New, BAC)) < (1e-20) || (x_New > b)) // n?u dã g?n v?i c?c tr? v?i m?t sai s? 1e-20 thì ta d?ng l?i
        {
            break;
        }
        // eta d?ng
        if (giaTriFPhay(arr, x_New, BAC) * giaTriFPhay(arr, x0, BAC))
        {
            eta = eta * 2;
        }
        if (giaTriFPhay(arr, x_New, BAC) * giaTriFPhay(arr, x0, BAC) < 0)
        {
            eta = eta / 4;
        }

        x0 = x_New;
    }

    return x_New;
}
// hàm sau dây tìm giá trị lớn nhất và nhỏ nhất
MIN_MAX timCacGiaTriMinVaMax(long double arr[], int BAC, long double a, long double b) // truyền vào hàm số và khoảng [a,b]
{
    MIN_MAX fx;
    long double x0 = a;
    long double x;
    if (giaTriF(arr, a, BAC) < giaTriF(arr, b, BAC))
    {
        fx.MIN = giaTriF(arr, a, BAC);
        fx.MAX = giaTriF(arr, b, BAC);
    }
    else
    {
        fx.MIN = giaTriF(arr, b, BAC);
        fx.MAX = giaTriF(arr, a, BAC);
    }
    x = cuctri(arr, BAC, ETA, x0);
    while (x <= b && x0 <= b)
    {
        if (giaTriF(arr, x, BAC) < fx.MIN)
        {
            fx.MIN = giaTriF(arr, x, BAC);
        }
        if (giaTriF(arr, x, BAC) > fx.MAX)
        {
            fx.MAX = giaTriF(arr, x, BAC);
        }
        x0 = x + STEP;
        x = cuctri(arr, BAC, ETA, x0);
    }
    return fx;
}
// tìm cận duới của miền nghiệm
long double mienNghiemAm()
{

    long double M1, m1, B1 = 0;
    int i, k1, count1 = 0;

    if (bac % 2 == 0 && f[bac] > 0)
    { // b?c ch?n và a(n) > 0
        t = 1;
    }
    if (bac % 2 == 0 && f[bac] < 0)
    {
        t = 2;
    }
    if (bac % 2 == 1 && f[bac] > 0)
    {
        t = 3;
    }
    if (bac % 2 == 1 && f[bac] < 0)
    {
        t = 4;
    }
    switch (t)
    {
    case 1:

        for (i = bac; i >= 0; i--)
        {
            if ((i % 2) == 1)
            {
                f[i] = -f[i];
            }
        }
        break;

    case 2:

        for (i = bac; i >= 0; i--)
        {
            f[i] = -f[i];
        }
        break;

    case 3:
        for (i = bac; i >= 0; i--)
        {
            if ((i % 2) == 0)
            {
                f[i] = -f[i];
            }
        }
        break;

    case 4:
        for (i = bac; i >= 0; i--)
        {
            if ((i % 2) == 1)
            {
                f[i] = -f[i];
            }
        }
        break;
    }

    for (i = bac - 1; i >= 0; i--)
    {
        if (f[i] < 0)
        {
            k1 = bac - i;
            count1++;
            break;
        }
    }
    if (count1 == 0)
    {
        M1 = 0;
    }
    else
    {
        for (i = bac - 1; i >= 0; i--)
        {
            if (f[i] < 0)
            {
                B1 = f[i];
            }
            for (int j = i - 1; j >= 0; j--)
            {
                if (f[j] < 0 && -f[j] > -B1)
                {
                    B1 = f[j];
                }
            }
        }

        M1 = 1 + pow(((abs(B1)) / f[bac]), (1.0 / k1));
    }
    if (M1 == 0)
    {
        m1 = M1;
    }
    else
    {
        m1 = -M1;
    }
    // Tr? l?i d?u bi?u th?c
    if (t == 1 || t == 4)
    {
        for (i = bac; i >= 0; i--)
        {
            if ((i % 2) == 1)
            {
                f[i] = -f[i];
            }
        }
    }
    if (t == 2)
    {
        for (i = bac; i >= 0; i--)
        {
            f[i] = -f[i];
        }
    }
    if (t == 3)
    {
        for (i = bac; i >= 0; i--)
        {
            if ((i % 2) == 0)
            {
                f[i] = -f[i];
            }
        }
    }
    return m1;
}
// tìm cận trên
long double mienNghiemDuong()
{
    long double M2, m2, B2 = 0;
    int i, k2, count2 = 0;
    if (f[bac] < 0)
    {
        for (i = bac; i >= 0; i--)
        {
            f[i] = -f[i];
        }
    }
    for (i = bac - 1; i >= 0; i--)
    {
        if (f[i] < 0)
        {
            k2 = bac - i;
            count2++;
            break;
        }
    }
    if (count2 == 0)
    {
        M2 = 0;
    }
    else
    {
        for (i = bac - 1; i >= 0; i--)
        {
            if (f[i] < 0)
            {
                B2 = f[i];
            }
            for (int j = i - 1; j >= 0; j--)
            {
                if (f[j] < 0 && -f[j] > -B2)
                {
                    B2 = f[j];
                }
            }
        }
        M2 = 1 + pow((abs(B2) / f[bac]), (1.0 / k2));
        m2 = M2;
    }
    //Tr? l?i d?u bi?u th?c
    if (f[bac] < 0)
    {
        for (i = bac; i >= 0; i--)
        {
            f[i] = -f[i];
        }
    }
    return m2;
}

// hàm sắp các cực trị tăng dần
double Sort(double long c[100], int n)
{
    int i, j, count = 0;

    for (i = 0; i < n - 1; i++)
    {
        for (j = 0; j < n - i - 1; j++)
        {
            if (c[j] > c[j + 1])
            {
                double long temp = c[j];
                c[j] = c[j + 1];
                c[j + 1] = temp;
                count++;
            }
        }
        if (count == 0)
        {
            break;
        }
    }
    return c[100];
}
// hàm in miền phân ly bài 1
void inMienPhanLy(long double d[100], int bac)
{

    int count = 0;
    for (int i = 0; i < m; i++)
    {
        for (int j = i + 1; j <= m; j++)
        {
            if ((giaTriF(f, d[i], bac)) * giaTriF(f, d[j], bac) <= 0)
            {
                cout << "mien phan li nghiem la=(" << setprecision(soChuSoSauDauPhay) << fixed << d[i] << "," << d[j] << ")" << endl;
                output << "khoang phan ly nghiem: ";
                output << "(" << d[i] << "," << d[j] << ")"
                       << "\n";
                count++;
            }
            break;
        }
    }
    if (count == 0)
    {
        cout << "mien phan li nghiem la=(" << setprecision(soChuSoSauDauPhay) << fixed << mienNghiemAm() << "," << mienNghiemDuong() << ")" << endl;
        output << "mien phan li nghiem la (" << mienNghiemAm() << ", " << mienNghiemDuong() << ")" << endl;
    }
}
// hàm tìm miền chứa các cực trị và 2 đầu mút a,b
void mangCucTri(long double d[100])
{
    long double i = mienNghiemAm();
    while (i < mienNghiemDuong())
    {
        i = cuctri(f, bac, ETA, i);

        if (abs(giaTriFPhay(f, i, bac)) < 0.0001)
        {
            d[m] = i;
            m++;
            i += STEP;
        }
    }
    d[m] = mienNghiemAm();
    m++;
    d[m] = mienNghiemDuong();
}
// hàm sử dụng phuong pháp chia dôi
void chiaDoi(long double a, long double b)
{
    long double c;
    int n = 0;
    while (abs(a - b) > 0.5)
    {
        c = (a + b) / 2;
        if (giaTriF(f, a, bac) * giaTriF(f, c, bac) < 0)
        {
            a = a;
            b = c;
            n++;
        }
        else
        {
            a = c;
            b = b;
            n++;
        }
    }
    if (n == 0)
    {
        cout << "!!! Khong the dung phuong phap chia doi !!!" << endl;
        output << "!KHong the dùng phuong phap chia doi ";
        cout << "Mien nghiem la (" << setprecision(soChuSoSauDauPhay) << fixed << mienNghiemAm() << " , " << mienNghiemDuong() << ")" << endl;
        output << "\nMien nghiem la"
               << "(" << mienNghiemAm() << ", " << mienNghiemDuong() << ")" << endl;
    }
    else
    {
        cout << "khoang li nghiem (a,b) thoa man |a-b| <= 0.5 la (" << setprecision(soChuSoSauDauPhay) << fixed << a << " , " << b << ")" << endl;
        output << "khoang li nghiem (a,b) thoa man |a-b| <= 0.5 la (" << a << " , " << b << ")" << endl;
    }
}
// chuong trình 1
void chuongTrinh1()
{
    output.open(h, ios::app);
    cout << "Ban chon chuong trinh 1" << endl;
    output << "Ban vua chon chuong trinh 1 \n";
    cout << mienNghiemAm() << " < X < " << mienNghiemDuong() << endl;
    output << "Khoang chua cac nghiem neu co: "
           << "[" << mienNghiemAm() << "," << mienNghiemDuong() << "] \n";
    mangCucTri(d);
    Sort(d, m + 1);
    inMienPhanLy(d, bac);
    output.close();
}

// chuong trình 2
void chuongTrinh2()
{
    output.open(h, ios::app);
    cout << "Ban chon chuong trinh 2" << endl;
    output << "Ban vua chon chuong trinh 2\n";
    int n = 0;
    int count = 0;
    mangCucTri(d);
    Sort(d, m + 1);
    for (int i = 0; i < m; i++)
    { // tìm các miền phân ly nghiệm sau đó chia đôi
        for (int j = i + 1; j <= m; j++)
        {
            if ((giaTriF(f, d[i], bac)) * giaTriF(f, d[j], bac) < 0)
            {
                chiaDoi(d[i], d[j]);
                count++;
                break;
            }
        }
    }
    if (count == 0)
    {
        chiaDoi(mienNghiemAm(), mienNghiemDuong());
    }
    output.close();
}

//chương trình 3
void chuongTrinh3()
{
    output.open(h, ios::app);
    int soLanLap;
    long double x, tmp, delta1, delta2, trunggian, m1, M2; // luu nghi?m, các sai s? và giá tr? min|f'(x)| và max|f''(x)|
    MIN_MAX fphay, fhaiPhay;
    cout << "Ban vua chon chuong trinh 3" << endl;
    output << "Ban vua chon chuong trinh 3 \n";
    cout << "Nhap vao doan [a,b] sao cho a<b va f(a)*f(b) trai dau" << endl;
    do
    {
        cout << "[a,b] = ";
        cin >> a >> b;

    } while (a >= b || giaTriF(f, a, bac) * giaTriF(f, b, bac) > 0);
    output << "Khoang [a,b] ban nhap la: "
           << "[" << a << "," << b << "]\n";
    if (giaTriF(f, a, bac) == 0 || giaTriF(f, b, bac) == 0)
    {
        cout << "Nghiem o dau mut ";
        output << "Khoang [a,b] ban nhap co nghiem o dau mut, Thoat chuong trinh 3!";
        return;
    }
    fphay = timCacGiaTriMinVaMax(f1, bacPhay, a, b);
    fhaiPhay = timCacGiaTriMinVaMax(f2, bacHaiPhay, a, b);
    if (fphay.MAX * fphay.MIN <= 0 || fhaiPhay.MAX * fhaiPhay.MIN <= 0) // ki?m tra xem f'(x) và f''(x) có gi? nguyên d?u trên [a,b] hay không
    {
        cout << "[a,b] khong hop le! Co f'(x) hoac f''(x) da doi dau tren [a,b]! "
             << " Thoat chuong trinh!";
        output << "[a,b] Khong hop le! Co f'(x) hoac f''(x) doi dau tren [a,b]";
        output << " Thoat chuong trinh 3!";
        return;
    }
    cout << "SO LAN LAP = ";
    cin >> soLanLap;
    output << "So lan lap ban nhap  = " << soLanLap << endl;
    trunggian = (a * giaTriF(f, b, bac) - b * giaTriF(f, a, bac)) / ((giaTriF(f, b, bac)) - (giaTriF(f, a, bac)));
    m1 = min(fabs(fphay.MAX), fabs(fphay.MIN));       // min|f'(x)| trên [a,b]
    M2 = max(fabs(fhaiPhay.MAX), fabs(fhaiPhay.MIN)); // max|f''(x)| trên [a,b]
    if (giaTriF(f, trunggian, bac) * giaTriF(f, a, bac) > 0)
    {
        x = a;
        output << "Diem bat dau lap = " << x << endl;
    }
    else
    {
        x = b;
        output << "Diem bat dau lap = " << x << endl;
    }
    for (int i = 1; (i <= soLanLap); i++)
    {
        tmp = x;
        x = x - (giaTriF(f, x, bac) / giaTriFPhay(f, x, bac));
        delta1 = fabs(giaTriF(f, x, bac)) / m1;
        delta2 = (M2 * (x - tmp) * (x - tmp)) / (2 * m1);
        output << "       Lap lan " << i << ": x = " << x << "           ||delta1 = " << delta1 << "           ||delta2 = " << delta2 << endl;
    }
    cout << "Nghiem gan dung la " << setprecision(soChuSoSauDauPhay) << fixed << x << endl;
    cout << "delta1 = " << delta1 << " ; "
         << "delta2 = " << delta2 << endl;
    output << "Thoat chuong trinh 3!\n";
    output.close();
}
//chương trình 4
void chuongTrinh4()
{
    output.open(h, ios::app);
    long double epsi;
    long double x, tmp, delta1, delta2, trunggian, m1, M2; // luu nghi?m, các sai s? và giá tr? min|f'(x)| và max|f''(x)|
    MIN_MAX fphay, fhaiPhay;
    cout << "Ban vua chon chuong trinh 4, Tim gan dung nghiem theo ca hai cong thuc sai so voi epsi cho truoc" << endl;
    output << "Ban vua chon chuong trinh 4\n";
    cout << "Nhap vao doan [a,b] sao cho a<b va f(a)*f(b) trai dau" << endl;
    do
    {
        cout << "[a,b] =  ";
        cin >> a >> b;

    } while (a >= b || giaTriF(f, a, bac) * giaTriF(f, b, bac) > 0);
    output << "Khoang [a,b] ban nhap la: "
           << "[" << a << "," << b << "]\n";
    if (giaTriF(f, a, bac) == 0 || giaTriF(f, b, bac) == 0)
    {
        cout << "nghiem o dau mut ";
        output << "Khoang [a,b] ban nhap co nghiem o dau mut, Thoat chuong trinh 4!";
        return;
    }
    fphay = timCacGiaTriMinVaMax(f1, bacPhay, a, b);
    fhaiPhay = timCacGiaTriMinVaMax(f2, bacHaiPhay, a, b);
    if (fphay.MAX * fphay.MIN <= 0 || fhaiPhay.MAX * fhaiPhay.MIN <= 0) // ki?m tra xem f'(x) và f''(x) có gi? nguyên d?u trên [a,b] hay không
    {
        cout << "[a,b] khong hop le! Co f'(x) hoac f''(x) da doi dau tren [a,b]! "
             << " Thoat chuong trinh!";
        output << "[a,b] Khong hop le! Co f'(x) hoac f''(x) doi dau tren [a,b]";
        output << " Thoat chuong trinh 4!\n";
        return;
    }
    cout << "epsi = ";
    cin >> epsi;
    output << "Epsilon = " << epsi << endl;
    trunggian = (a * giaTriF(f, b, bac) - b * giaTriF(f, a, bac)) / ((giaTriF(f, b, bac)) - (giaTriF(f, a, bac)));
    m1 = min(fabs(fphay.MAX), fabs(fphay.MIN));       // min|f'(x)| trên [a,b]
    M2 = max(fabs(fhaiPhay.MAX), fabs(fhaiPhay.MIN)); // max|f''(x)| trên [a,b]
    if (giaTriF(f, trunggian, bac) * giaTriF(f, a, bac) > 0)
    {
        x = a;
        output << "Diem bat dau lap = " << x << endl;
    }
    else
    {
        x = b;
        output << "Diem bat dau lap = " << x << endl;
    }
    // tính theo công th?c sai s? th? nh?t
    output << "Tinh theo cong thuc sai so thu nhat \n";
    tmp = x;
    tmp = tmp - (giaTriF(f, tmp, bac) / giaTriFPhay(f, tmp, bac));
    delta1 = fabs(giaTriF(f, tmp, bac)) / m1;
    output << "       x = " << tmp << "    || delta1 = " << delta1 << endl;
    while (delta1 > epsi)
    {
        tmp = tmp - (giaTriF(f, tmp, bac) / giaTriFPhay(f, tmp, bac));
        delta1 = fabs(giaTriF(f, tmp, bac)) / m1;
        output << "       x = " << tmp << "    || delta1 = " << delta1 << endl;
    }
    cout << "Theo CT sai so I, x =  " << setprecision(soChuSoSauDauPhay) << fixed << tmp << " ; delta1 = " << delta1 << endl;
    output << "Tinh theo cong thuc sai so thu hai \n";
    // tính theo công th?c th? hai
    tmp = x;
    x = x - (giaTriF(f, x, bac) / giaTriFPhay(f, x, bac));
    delta2 = (M2 * (x - tmp) * (x - tmp)) / (2 * m1);
    output << "       x = " << x << "    || delta2 = " << delta2 << endl;
    while (delta2 > epsi)
    {
        tmp = x;
        x = x - (giaTriF(f, x, bac) / giaTriFPhay(f, x, bac));
        delta2 = (M2 * (x - tmp) * (x - tmp)) / (2 * m1);
        output << "       x = " << x << "    || delta2 = " << delta2 << endl;
    }
    cout << "Theo CT sai so II, x =  " << setprecision(soChuSoSauDauPhay) << fixed << x << " ; delta2 = " << delta2 << endl;
    output << "Thoat chuong trinh 4!\n";
    output.close();
}
//chương trình 5
void chuongTrinh5()
{
    output.open(h, ios::app);
    output << "Ban vua chon chuong trinh 5: tim nghiem gan dung theo cong thuc sai so  |x(n) - x(n-1)| < epsi\n";
    long double epsi;
    long double x, tmp, delta, trunggian, m1, M2; // luu nghi?m, các sai s? và giá tr? min|f'(x)| và max|f''(x)|
    MIN_MAX fphay, fhaiPhay;
    cout << "Ban chon chuong trinh 5" << endl;
    cout << "Nhap vao doan [a,b] sao cho a<b va f(a)*f(b) trai dau" << endl;
    do
    {
        cout << "[a,b] =  ";
        cin >> a >> b;

    } while (a >= b || giaTriF(f, a, bac) * giaTriF(f, b, bac) > 0);
    output << "Khoang [a,b] ban nhap la: "
           << "[" << a << "," << b << "]\n";
    if (giaTriF(f, a, bac) == 0 || giaTriF(f, b, bac) == 0)
    {
        cout << "nghiem o dau mut ";
        output << "Khoang [a,b] ban nhap co nghiem o dau mut, Thoat chuong trinh 4!";
        return;
    }
    fphay = timCacGiaTriMinVaMax(f1, bacPhay, a, b);
    fhaiPhay = timCacGiaTriMinVaMax(f2, bacHaiPhay, a, b);
    if (fphay.MAX * fphay.MIN <= 0 || fhaiPhay.MAX * fhaiPhay.MIN <= 0) // ki?m tra xem f'(x) và f''(x) có gi? nguyên d?u trên [a,b] hay không
    {
        cout << "[a,b] khong hop le! Co f'(x) hoac f''(x) da doi dau tren [a,b]! "
             << " Thoat chuong trinh!";
        output << "[a,b] Khong hop le! Co f'(x) hoac f''(x) doi dau tren [a,b]";
        output << " Thoat chuong trinh 5!\n";
        return;
    }
    cout << "epsi = ";
    cin >> epsi;
    trunggian = (a * giaTriF(f, b, bac) - b * giaTriF(f, a, bac)) / ((giaTriF(f, b, bac)) - (giaTriF(f, a, bac)));
    m1 = min(fabs(fphay.MAX), fabs(fphay.MIN));       // min|f'(x)| trên [a,b]
    M2 = max(fabs(fhaiPhay.MAX), fabs(fhaiPhay.MIN)); // max|f''(x)| trên [a,b]
    if (giaTriF(f, trunggian, bac) * giaTriF(f, a, bac) > 0)
    {
        x = a;
        output << "Diem bat dau lap = " << x << endl;
    }
    else
    {
        x = b;
        output << "Diem bat dau lap = " << x << endl;
    }
    tmp = x;
    x = x - (giaTriF(f, x, bac) / giaTriFPhay(f, x, bac));
    delta = fabs(x - tmp);
    output << "       x = " << x << "    || delta = " << delta << endl;
    while (delta > epsi)
    {
        tmp = x;
        x = x - (giaTriF(f, x, bac) / giaTriFPhay(f, x, bac));
        delta = fabs(x - tmp);
        output << "       x = " << x << "    || delta = " << delta << endl;
    }
    cout << "Theo CT sai so |x(n) - x(n-1)| < epsi , x =  " << setprecision(soChuSoSauDauPhay) << fixed << tmp << " ; delta = " << delta << endl;
    output << "Thoat chuong trinh 5! \n";
    output.close();
}
// hàm nhập f
void nhapF()
{
    output.open(h, ios::app);
    output << "NOTE: delta1 la sai so theo cong thuc dung min|f'(x)| \n"
           << "delta2 laf sai so theo cong thuc dung min|f'(x)| va max|f''(x)|\n";
    cout << "bac cua fx =  ";
    cin >> bac;
    cout << endl;
    bacPhay = bac - 1;
    bacHaiPhay = bac - 2;

    for (int i = 0; i <= bac; i++)
    {
        cout << "nhap he so cua x ^ " << i << " = ";
        cin >> f[i];
        cout << endl;
    }
    output << "Phuong trinh vua nhap la :  ";
    for (int i = 0; i <= bac; i++)
    {

        if (f[i] > 0 && i > 0)
        {
            output << " + " << f[i] << "X^" << i;
        }
        else
        {
            output << " " << f[i] << "X^" << i;
        }
    }
    output << endl;
    // gán các hệ số cho f'(x)
    for (int i = 0; i <= bacPhay; i++) // ghi vào file hàm f(x)
    {
        f1[i] = f[i + 1] * (i + 1);
    }
    // gán các hệ số cho f''(x)
    for (int i = 0; i <= bacHaiPhay; i++)
    {
        f2[i] = f1[i + 1] * (i + 1);
    }
    output.close();
}
//hàm in màu chữ
void color(int color)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

//di chuyển con trỏ (x,y)
void gotoxy(int x, int y)
{
    COORD c;
    c.X = x;
    c.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}
// hàm tạo menu
void MENU()
{

    int Set[] = {7, 7, 7, 7, 7, 7, 7, 7, 7}; // in mac chu ban dau mau trang (ma cua màu trang la 7)
    int counter = 7;
    char key;
    for (int i = 0;;)
    {
        gotoxy(0, 0); // di chuyen con tro den toa do
        color(Set[0]);
        cout << "Phuong trinh vua nhap la :  ";
        for (int i = 0; i <= bac; i++)
        {

            if (f[i] > 0 && i > 0)
            {
                cout << " + " << f[i] << "X^" << i;
            }
            else
            {
                cout << " " << f[i] << "X^" << i;
            }
        }

        gotoxy(0, 1); // di chuyen con tro den toa do
        color(Set[1]);
        cout << "Moi ban chon chuong trinh( nhan ESC de chon chuong trinh khac  )";

        gotoxy(0, 2);  // di chuyen con tro den toa do
        color(Set[2]); // in mau cua dong
        cout << "Chuong trinh 1";

        gotoxy(0, 3);
        color(Set[3]);
        cout << "Chuong trinh 2";

        gotoxy(0, 4);
        color(Set[4]);
        cout << "Chuong trinh 3";

        gotoxy(0, 5);
        color(Set[5]);
        cout << "Chuong trinh 4";

        gotoxy(0, 6);
        color(Set[6]);
        cout << "Chuong trinh 5";

        gotoxy(0, 7);
        color(Set[7]);
        cout << "Exit";

        gotoxy(0, 8);

        key = _getch();

        if (key == 72 && (counter >= 4 && counter <= 8)) // UP (mã ASCII cua  len la 72)
        {
            counter--;
        }
        if (key == 80 && (counter >= 3 && counter <= 7)) //DOWN (mã ASCII cua xuong la 80)
        {
            counter++;
        }

        if (key == 13) //ma ASCII cua ENTER
        {
            if (counter == 3)
            {
                cout << endl;
                gotoxy(0, 8);
                chuongTrinh1();
                break;
            }
            if (counter == 4)
            {
                cout << endl;
                gotoxy(0, 8);
                chuongTrinh2();
                break;
            }
            if (counter == 5)
            {
                cout << endl;
                gotoxy(0, 8);
                chuongTrinh3();
                break;
            }
            if (counter == 6)
            {
                cout << endl;
                gotoxy(0, 8);
                chuongTrinh4();
                break;
            }
            if (counter == 7)
            {
                cout << endl;
                gotoxy(0, 8);
                chuongTrinh5();
                break;
            }
            if (counter == 8)
            {

                exit(1);
            }
        }
        if (key == 27)
        {
            system("cls");
        }
        Set[0] = 7; // dat mac dinh mau chu ban dau o cac dong la trang ( ma mau trang = 7)
        Set[1] = 7;
        Set[2] = 7;
        Set[3] = 7;
        Set[4] = 7;
        Set[5] = 7;
        Set[6] = 7;
        Set[7] = 7;
        Set[8] = 7;
        if (counter == 3)
        {
            Set[2] = 2; // dat lai mau xanh duong (ma mau xanh duong la 1)
        }
        if (counter == 4)
        {
            Set[3] = 2;
        }
        if (counter == 5)
        {
            Set[4] = 2;
        }
        if (counter == 6)
        {
            Set[5] = 2;
        }
        if (counter == 7)
        {
            Set[6] = 2;
        }
        if (counter == 8)
        {
            Set[7] = 2;
        }
    }
}
// chương trình chính
int main()
{
    nhapF();
    cout << "nhap so chu so muon hien thi sau dau phay: ";
    cin >> soChuSoSauDauPhay;
    system("cls");
    cout << endl;
    while (1)
    {
        MENU();
    }
}
