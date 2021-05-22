#include <iostream>
#include <math.h>
#include <iomanip>
using namespace std;
long double f[100], f1[100], f2[100];  // lưu hàm f(x), f'(x), f''(x)
int bac, bacPhay, bacHaiPhay;          // bậc f(x), f'(x), f''(x)
long double a, b;                      // khai báo khoảng [a,b]
long double ETA = 0.001, STEP = 0.001; // khởi tạo eta, step trong thuật toán Gradient Descent
struct MIN_MAX
{
    long double MIN; // kiểu dữ liệu tự định nghĩa để lưu giá trị min và max
    long double MAX; // của một hàm số trong khoảng [a,b] cho trước
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
// các phần tiếp theo phục vụ việc tìm min, max của hàm số
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
    int i, dau;                // biến 'dau' dùng để lưu dấu của f'(x0)
    long double deltaX, x_New; // deltaX dùng để xác định giá trị nhảy đến x tiếp theo
    dau = xetDau(arr, x0, BAC);
    for (i = 0; i < 400000; i++)
    {
        deltaX = eta * giaTriFPhay(arr, x0, BAC);
        if (deltaX > 0.2) // các bước hạn chế delTaX quá lớn
        {
            deltaX = 0.2;
        }
        if (deltaX < -0.2)
        {
            deltaX = -0.2;
        }
        x_New = x0 + dau * deltaX;
        if (fabs(giaTriFPhay(arr, x_New, BAC)) < (1e-20) || (x_New > b)) // nếu đã gần với cực trị với một sai số 1e-20 thì ta dừng lại
        {
            break;
        }
        // eta động
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
// hàm sau đây tìm giá trị lớn nhất và nhỏ nhất
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
// chương trình nhập vào số lượng lần lặp mà người dùng yêu cầu
// sau đó đưa ra nghiệm gần đúng, sai số theo cả hai công thức
void chuongTrinh3()
{
    int soLanLap;
    long double x, tmp, delta1, delta2, trunggian, m1, M2; // lưu nghiệm, các sai số và giá trị min|f'(x)| và max|f''(x)|
    MIN_MAX fphay, fhaiPhay;
    cout << "\nNhap vao doan [a,b] sao cho a<b va f(a)*f(b) trai dau";
    do
    {
        cout << "\na = ";
        cin >> a;
        cout << "\nb = ";
        cin >> b;
    } while (a >= b || giaTriF(f, a, bac) * giaTriF(f, b, bac) >= 0);
    if (giaTriF(f, a, bac) == 0 || giaTriF(f, b, bac) == 0)
    {
        cout << "nghiem o dau mut ";
        return;
    }
    fphay = timCacGiaTriMinVaMax(f1, bacPhay, a, b);
    fhaiPhay = timCacGiaTriMinVaMax(f2, bacHaiPhay, a, b);
    if (fphay.MAX * fphay.MIN <= 0 || fhaiPhay.MAX * fhaiPhay.MIN <= 0) // kiểm tra xem f'(x) và f''(x) có giữ nguyên dấu trên [a,b] hay không
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
        delta1 = fabs(giaTriF(f, x, bac) / m1);
        delta2 = (M2 * (x - tmp) * (x - tmp)) / (2 * m1);
    }
    cout << "\nNghiem gan dung la " << setprecision(20) << fixed << x;
    cout << "\ndelta1 = " << delta1 << "\n"
         << "delta2 = " << delta2;
}
// chương trình nhập vào sai số epsi mà người dùng yêu cầu
// đưa ra nghiệm gần đúng và sai số theo cả hai công thức
void chuongTrinh4()
{
    long double x, delta1, delta2, trunggian, m1, M2, epsi;
    MIN_MAX fphay, fhaiPhay;
    cout << "epsi = ";
    cin >> epsi;
    cout << "[a,b] = ";
    cout << "\na = ";
    cin >> a;
    cout << "\nb = ";
    cin >> b;
    if (giaTriF(f, a, bac) == 0)
    {
        cout << "nghiem la : " << a;
        return;
    }
    if (giaTriF(f, b, bac) == 0)
    {
        cout << "nghiem la : " << b;
        return;
    }
    fphay = timCacGiaTriMinVaMax(f1, bacPhay, a, b);
    fhaiPhay = timCacGiaTriMinVaMax(f2, bacHaiPhay, a, b);
    if (fphay.MAX * fphay.MIN <= 0 || fhaiPhay.MAX * fhaiPhay.MIN <= 0 || a >= b) // kiểm tra xem f'(x) và f''(x) có giữ nguyên dấu trên [a,b] hay không
    {
        cout << "[a,b] khong hop le! Thoat chuong trinh";
        return;
    }
    trunggian = (a * giaTriF(f, b, bac) - b * giaTriF(f, a, bac)) / ((giaTriF(f, b, bac)) - (giaTriF(f, a, bac)));
    m1 = min(giaTriFPhay(f, a, bac), giaTriFPhay(f, b, bac)); // min|f'(x)| trên [a,b]
    M2 = max(fabs(fhaiPhay.MAX), fabs(fhaiPhay.MIN));         // max|f''(x)| trên [a,b]
    if (giaTriF(f, trunggian, bac) * giaTriF(f, a, bac) > 0)
    {
        x = a;
    }
    else
    {
        x = b;
    }
    // tính theo công thức sai số thứ nhất
    x = x - giaTriF(f, x, bac) / giaTriFPhay(f, x, bac);
    delta1 = fabs(giaTriF(f, x, bac) / m1);
    while (delta1 > epsi)
    {
        x = x - giaTriF(f, x, bac) / giaTriFPhay(f, x, bac);
        delta1 = fabs(giaTriF(f, x, bac) / m1);
    }
    cout << "\nNghiem gan dung theo ct sai so thu 1 la ";
    cout << setprecision(20) << fixed << x;
    cout << "\ndelta1 = " << delta1;
}
// chương trình nhập vào sai số epsi,
// đưa ra nghiệm theo đánh giá |x(n) -x(n-1)| < epsi
long double chuongTrinh5(long double arr[])
{
    int epsi;
    cout << "epsi = ";
    cin >> epsi;
    cout << "[a,b] = ";
    cout << "\na = ";
    cin >> a;
    cout << "\nb = ";
    cin >> b;
}
// chương trình chính
int main()
{
    cout << "bac cua fx =  ";
    cin >> bac;
    bacPhay = bac - 1;
    bacHaiPhay = bac - 2;
    cout << "\nnhap fx";
    for (int i = 0; i <= bac; i++)
    {
        cout << "\nnhap he so cua x ^ " << i << " = ";
        cin >> f[i];
    }
    // gán các hệ số cho f'(x)
    for (int i = 0; i <= bacPhay; i++)
    {
        f1[i] = f[i + 1] * (i + 1);
    }
    // gán các hệ số cho f''(x)
    for (int i = 0; i <= bacHaiPhay; i++)
    {
        f2[i] = f1[i + 1] * (i + 1);
    }
    chuongTrinh3();
}