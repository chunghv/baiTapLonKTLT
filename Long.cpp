
////////22h51 26/05
#include <iostream>
#include <windows.h>
#include <conio.h>
#include <math.h>
#include <iomanip>
using namespace std;
long double f[100], f1[100], f2[100];  // luu hàm f(x), f'(x), f''(x)
int bac, bacPhay, bacHaiPhay;          // b?c f(x), f'(x), f''(x)
long double a, b;                      // khai báo kho?ng [a,b]
long double ETA = 0.001, STEP = 0.001; // kh?i t?o eta, step trong thu?t toán Gradient Descent
long double d[100];                    // luu các c?c tr?
int m;                                 // bi?n d?m c?c tr?
long double c[100];
int t;
long double a1, b1;
struct MIN_MAX
{
    long double MIN; // ki?u d? li?u t? d?nh nghia d? luu giá tr? min và max
    long double MAX; // c?a m?t hàm s? trong kho?ng [a,b] cho tru?c
};
//tính giá tr? c?a f(x) t?i giá tr? x0
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
//tính giá tr? c?a f'(x) t?i giá tr? x0
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
// các ph?n ti?p theo ph?c v? vi?c tìm min, max c?a hàm s?
int xetDau(long double arr[], long double x0, int BAC) // hàm xét d?u f'(x)
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
// thu?t toán Gradient Descent v?i eta d?ng
long double cuctri(long double arr[], int BAC, long double eta, long double x0) // tìm c?c tr? d?a phuong
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
// hàm sau dây tìm giá tr? l?n nh?t và nh? nh?t
MIN_MAX timCacGiaTriMinVaMax(long double arr[], int BAC, long double a, long double b) // truy?n vào hàm s? và kho?ng [a,b]
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
// tìm c?n du?i c?a mi?n nghi?m
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
// tìm c?n trên
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

// hàm s?p các c?c tr? tang d?n
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
// hàm in mi?n phân ly bài 1
void inMienPhanLy(long double d[100], int bac)
{
    int count = 0;
    for (int i = 0; i < m; i++)
    {
        for (int j = i + 1; j <= m; j++)
        {
            if ((giaTriF(f, d[i], bac)) * giaTriF(f, d[j], bac) < 0)
            {
                cout << "mien phan li nghiem la=(" << d[i] << "," << d[j] << ")" << endl;
                count++;
            }
            break;
        }
    }
    if (count == 0)
    {
        cout << "mien phan li nghiem la=(" << mienNghiemAm() << "," << mienNghiemDuong() << ")" << endl;
    }
}
// hàm tìm m?ng ch?a các c?c tr? và 2 d?u mút a,b
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
// hàm s? d?ng phuong pháp chia dôi
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
        cout << "Mien nghiem la (" << mienNghiemAm() << " , " << mienNghiemDuong() << ")" << endl;
    }
    else
    {
        cout << "khoang li nghiem (a,b) thoa man |a-b| <= 0.5 la (" << a << " , " << b << ")" << endl;
    }
}
// chuong trình 1
void chuongTrinh1()
{

    cout << mienNghiemAm() << " < X < " << mienNghiemDuong() << endl;

    mangCucTri(d);

    Sort(d, m + 1);

    for (int i = 1; i < m; i++)
    {
        cout << "//cac cuc tri la //";
        cout << "d[" << i << "] = " << d[i] << endl;
    }
    inMienPhanLy(d, bac);
}

// chuong trình 2
void chuongTrinh2()
{
    int n = 0;
    int count = 0;

    mangCucTri(d);

    Sort(d, m + 1);

    for (int i = 1; i < m; i++)
    { // in ra các c?c tr?
        cout << "d[" << i << "]=" << d[i] << endl;
    }

    for (int i = 0; i < m; i++)
    { // tìm các mi?n phân li nghi?m, sau dó chia dôi
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
}

// chuong trình nh?p vào s? lu?ng l?n l?p mà ngu?i dùng yêu c?u
// sau dó dua ra nghi?m g?n dúng, sai s? theo c? hai công th?c
void chuongTrinh3()
{
    int soLanLap;
    long double x, tmp, delta1, delta2, trunggian, m1, M2; // luu nghi?m, các sai s? và giá tr? min|f'(x)| và max|f''(x)|
    MIN_MAX fphay, fhaiPhay;
    cout << "\nNhap vao doan [a,b] sao cho a<b va f(a)*f(b) trai dau";
    do
    {
        cout << "\na = ";
        cin >> a;
        cout << "\nb = ";
        cin >> b;
    } while (a >= b || giaTriF(f, a, bac) * giaTriF(f, b, bac) > 0);
    if (giaTriF(f, a, bac) == 0 || giaTriF(f, b, bac) == 0)
    {
        cout << "nghiem o dau mut ";
        return;
    }
    fphay = timCacGiaTriMinVaMax(f1, bacPhay, a, b);
    fhaiPhay = timCacGiaTriMinVaMax(f2, bacHaiPhay, a, b);
    if (fphay.MAX * fphay.MIN <= 0 || fhaiPhay.MAX * fhaiPhay.MIN <= 0) // ki?m tra xem f'(x) và f''(x) có gi? nguyên d?u trên [a,b] hay không
    {
        cout << "[a,b] khong hop le! Co f'(x) hoac f''(x) da doi dau tren [a,b]! "
             << " Thoat chuong trinh!";
        return;
    }
    cout << "SO LAN LAP = ";
    cin >> soLanLap;
    trunggian = (a * giaTriF(f, b, bac) - b * giaTriF(f, a, bac)) / ((giaTriF(f, b, bac)) - (giaTriF(f, a, bac)));
    m1 = min(fabs(fphay.MAX), fabs(fphay.MIN));       // min|f'(x)| trên [a,b]
    M2 = max(fabs(fhaiPhay.MAX), fabs(fhaiPhay.MIN)); // max|f''(x)| trên [a,b]
    if (giaTriF(f, trunggian, bac) * giaTriF(f, a, bac) > 0)
    {
        x = a;
    }
    else
    {
        x = b;
    }
    for (int i = 1; (i <= soLanLap); i++)
    {
        tmp = x;
        x = x - (giaTriF(f, x, bac) / giaTriFPhay(f, x, bac));
        delta1 = fabs(giaTriF(f, x, bac)) / m1;
        delta2 = (M2 * (x - tmp) * (x - tmp)) / (2 * m1);
    }
    cout << "\nNghiem gan dung la " << setprecision(20) << fixed << x;
    cout << "\ndelta1 = " << delta1 << "\n"
         << "delta2 = " << delta2;
}
// chuong trình nh?p vào sai s? epsi mà ngu?i dùng yêu c?u
// dua ra nghi?m g?n dúng và sai s? theo c? hai công th?c
void chuongTrinh4()
{
    long double epsi;
    long double x, tmp, delta1, delta2, trunggian, m1, M2; // luu nghi?m, các sai s? và giá tr? min|f'(x)| và max|f''(x)|
    MIN_MAX fphay, fhaiPhay;
    cout << "\nNhap vao doan [a,b] sao cho a<b va f(a)*f(b) trai dau";
    do
    {
        cout << "\na = ";
        cin >> a;
        cout << "\nb = ";
        cin >> b;
    } while (a >= b || giaTriF(f, a, bac) * giaTriF(f, b, bac) > 0);
    if (giaTriF(f, a, bac) == 0 || giaTriF(f, b, bac) == 0)
    {
        cout << "nghiem o dau mut ";
        return;
    }
    fphay = timCacGiaTriMinVaMax(f1, bacPhay, a, b);
    fhaiPhay = timCacGiaTriMinVaMax(f2, bacHaiPhay, a, b);
    if (fphay.MAX * fphay.MIN <= 0 || fhaiPhay.MAX * fhaiPhay.MIN <= 0) // ki?m tra xem f'(x) và f''(x) có gi? nguyên d?u trên [a,b] hay không
    {
        cout << "[a,b] khong hop le! Co f'(x) hoac f''(x) da doi dau tren [a,b]! "
             << " Thoat chuong trinh!";
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
    }
    else
    {
        x = b;
    }
    // tính theo công th?c sai s? th? nh?t
    tmp = x;
    tmp = tmp - (giaTriF(f, tmp, bac) / giaTriFPhay(f, tmp, bac));
    delta1 = fabs(giaTriF(f, tmp, bac)) / m1;
    while (delta1 > epsi)
    {
        tmp = tmp - (giaTriF(f, tmp, bac) / giaTriFPhay(f, tmp, bac));
        delta1 = fabs(giaTriF(f, tmp, bac)) / m1;
    }
    cout << "\nTheo CT sai so I, x =  " << setprecision(20) << fixed << tmp;
    cout << "\ndelta1 = " << delta1;
    // tính theo công th?c th? hai
    tmp = x;
    x = x - (giaTriF(f, x, bac) / giaTriFPhay(f, x, bac));
    delta2 = (M2 * (x - tmp) * (x - tmp)) / (2 * m1);
    while (delta2 > epsi)
    {
        tmp = x;
        x = x - (giaTriF(f, x, bac) / giaTriFPhay(f, x, bac));
        delta2 = (M2 * (x - tmp) * (x - tmp)) / (2 * m1);
    }
    cout << "\nTheo CT sai so II, x =  " << setprecision(20) << fixed << x;
    cout << "\ndelta2 = " << delta2;
}
// chuong trình nh?p vào sai s? epsi,
// dua ra nghi?m theo dánh giá |x(n) -x(n-1)| < epsi
void chuongTrinh5()
{
    long double epsi;
    long double x, tmp, delta, trunggian, m1, M2; // luu nghi?m, các sai s? và giá tr? min|f'(x)| và max|f''(x)|
    MIN_MAX fphay, fhaiPhay;
    cout << "\nNhap vao doan [a,b] sao cho a<b va f(a)*f(b) trai dau";
    do
    {
        cout << "\na = ";
        cin >> a;
        cout << "\nb = ";
        cin >> b;
    } while (a >= b || giaTriF(f, a, bac) * giaTriF(f, b, bac) > 0);
    if (giaTriF(f, a, bac) == 0 || giaTriF(f, b, bac) == 0)
    {
        cout << "nghiem o dau mut ";
        return;
    }
    fphay = timCacGiaTriMinVaMax(f1, bacPhay, a, b);
    fhaiPhay = timCacGiaTriMinVaMax(f2, bacHaiPhay, a, b);
    if (fphay.MAX * fphay.MIN <= 0 || fhaiPhay.MAX * fhaiPhay.MIN <= 0) // ki?m tra xem f'(x) và f''(x) có gi? nguyên d?u trên [a,b] hay không
    {
        cout << "[a,b] khong hop le! Co f'(x) hoac f''(x) da doi dau tren [a,b]! "
             << " Thoat chuong trinh!";
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
    }
    else
    {
        x = b;
    }
    tmp = x;
    x = x - (giaTriF(f, x, bac) / giaTriFPhay(f, x, bac));
    delta = fabs(x - tmp);
    while (delta > epsi)
    {
        tmp = x;
        x = x - (giaTriF(f, x, bac) / giaTriFPhay(f, x, bac));
        delta = fabs(x - tmp);
    }
    cout << "\nTheo CT sai so |x(n) - x(n-1)| < epsi , x =  " << setprecision(20) << fixed << tmp;
    cout << "\ndelta = " << delta;
}
void nhapF()
{
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
    // gán các h? s? cho f'(x)
    for (int i = 0; i <= bacPhay; i++)
    {
        f1[i] = f[i + 1] * (i + 1);
    }
    // gán các h? s? cho f''(x)
    for (int i = 0; i <= bacHaiPhay; i++)
    {
        f2[i] = f1[i + 1] * (i + 1);
    }
}
//in mau chu
void color(int color)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

//di chuyen con tro den toa do (x,y)
void gotoxy(int x, int y)
{
    COORD c;
    c.X = x;
    c.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}

void MENU()
{

    int Set[] = {7, 7, 7, 7, 7}; // in mac chu ban dau mau trang (ma cua màu trang la 7)
    int counter = 3;
    char key;
    for (int i = 0;;)
    {
        gotoxy(5, 14); // di chuyen con tro den toa do
        color(Set[0]); // in mau cua dong
        cout << "Bai 1";

        gotoxy(5, 15);
        color(Set[1]);
        cout << "Bai 2";

        gotoxy(5, 16);
        color(Set[2]);
        cout << "Bai 3";

        gotoxy(5, 17);
        color(Set[3]);
        cout << "Bai 4";

        gotoxy(5, 18);
        color(Set[4]);
        cout << "Bai 5";

        key = _getch();

        if (key == 72 && (counter >= 2 && counter <= 5)) // UP (mã ASCII cua  len la 72)
        {
            counter--;
        }
        if (key == 80 && (counter >= 1 && counter <= 4)) //DOWN (mã ASCII cua xuong la 80)
        {
            counter++;
        }
        if (key == 13) //ma ASCII cua ENTER
        {
            if (counter == 1)
            {
                cout << endl;
                cout << "Ban chon chuong trinh 1" << endl;
                chuongTrinh1();
                break;
            }
            if (counter == 2)
            {
                cout << endl;
                cout << "Ban chon chuong trinh 2" << endl;
                chuongTrinh2();
                break;
            }
            if (counter == 3)
            {
                cout << endl;
                cout << "Ban chon chuong trinh 3" << endl;
                chuongTrinh3();
                break;
            }
            if (counter == 4)
            {
                cout << endl;
                cout << "Ban chon chuong trinh 4" << endl;
                chuongTrinh4();
                break;
            }
            if (counter == 5)
            {
                cout << endl;
                cout << "Ban chon chuong trinh 5" << endl;
                chuongTrinh5();
                break;
            }
        }

        Set[0] = 7; // dat mac dinh mau chu ban dau o cac dong la trang ( ma mau trang = 7)
        Set[1] = 7;
        Set[2] = 7;
        Set[3] = 7;
        Set[4] = 7;

        if (counter == 1)
        {
            Set[0] = 2; // dat lai mau xanh duong (ma mau xanh duong la 1)
        }
        if (counter == 2)
        {
            Set[1] = 2;
        }
        if (counter == 3)
        {
            Set[2] = 2;
        }
        if (counter == 4)
        {
            Set[3] = 2;
        }
        if (counter == 5)
        {
            Set[4] = 2;
        }
    }
}

// chuong trình chính
int main()
{
    nhapF();

    MENU();
}
