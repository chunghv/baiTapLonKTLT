
#include <iostream>
////////10h31 26/05
#include <math.h>
#include <iomanip>
using namespace std;
long double f[100], f1[100], f2[100];  // lưu hàm f(x), f'(x), f''(x)
int bac, bacPhay, bacHaiPhay;          // bậc f(x), f'(x), f''(x)
long double a, b;                      // khai báo khoảng [a,b]
long double ETA = 0.001, STEP = 0.001; // khởi tạo eta, step trong thuật toán Gradient Descent
long double d[100]; // lưu các cực trị
int m ; // biến đếm cực trị
long double c[100];
int t;
long double a1, b1;
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
// tìm cận dưới của miền nghiệm
long double mienNghiemAm(){
     
     long double M1,m1, B1 = 0;
     int i, k1, count1 = 0;

    if(bac % 2 == 0 && f[bac] > 0){ // bậc chẵn và a(n) > 0
        t = 1;
    }
    if(bac % 2 == 0 && f[bac] < 0){
        t = 2;
    }
    if(bac % 2 == 1 && f[bac] > 0){
        t = 3;
    }
    if(bac % 2 == 1 && f[bac] < 0){
        t = 4;
    }
    switch(t){
	case 1:

		for(i = bac;i >= 0; i--){
			if((i % 2) == 1){ 
			f[i] = -f[i];
			}
        }
        break;
    
    case 2:

		for(i = bac;i >= 0; i--){
			f[i] = -f[i];
        }
        break;
    
	case 3:
		for(i = bac;i >= 0; i--){
			if((i % 2) == 0){ 
				f[i] = -f[i];
            }
        }
        break;
   
    case 4:
		for(i = bac;i >= 0; i--){
			if((i % 2) == 1){ 
				f[i] = -f[i];
            }
        }
        break;
	}

	for( i = bac-1;i >= 0; i--){
		if( f[i] < 0) {
			k1 = bac-i;
			count1++;
			break;
		}
    }
	if(count1 == 0){ 
		M1 = 0;
    }
	else {
	    for(i = bac-1;i >= 0; i--) {
		    if(f[i] < 0) {
			B1 = f[i];
            }
			for(int j = i-1;j >= 0; j--){
				if(f[j] < 0 && -f[j] > -B1){ 
					B1 = f[j];
				}
            }
        } 

	
	M1 = 1 + pow( ( (abs(B1)) / f[bac] )  , (1.0 / k1 ) );
 
    }
    if (M1 == 0){
        m1 = M1;
        
    } else { 
        m1 = -M1;
    
    }
    // Trả lại dấu biểu thức
    if ( t ==1 || t == 4){
        for(i = bac;i >= 0; i--){
			if((i % 2) == 1){ 
				f[i] = -f[i];
            }
        }
    }
    if (t == 2){
        for(i = bac;i >= 0; i--){
			f[i] = -f[i];
        }
    }
    if ( t == 3){
        for(i = bac;i >= 0; i--){
			if((i % 2) == 0){ 
				f[i] = -f[i];
            }
        }
    }
   return m1;
}
// tìm cận trên
long double mienNghiemDuong(){
    long double M2, m2, B2 = 0;
     int i, k2, count2 = 0;
    if (f[bac] < 0){
		for (i = bac; i >= 0; i--){
			f[i] = -f[i];
        }
    }
	for(i = bac - 1; i >= 0; i--){ 
		if(f[i] < 0) {
			k2 = bac-i;
			count2++;
			break;
		}
    }
	if(count2 == 0){ 
		M2 = 0;
    }
	else {
	    for(i = bac-1; i >= 0; i--) {
		    if( f[i] < 0) { 
			   B2 = f[i];
            }
			for(int j = i-1; j >= 0; j--){
				if( f[j] < 0 && - f[j]  >  -B2  ){ 
					B2 = f[j];
				}
            }
        }
    M2 = 1 + pow( ( abs(B2) / f[bac] ) , (1.0 / k2) );
    m2 = M2;
	}
    //Trả lại dấu biểu thức
    if (f[bac] < 0){
		for (i = bac; i >= 0; i--){
			f[i] = -f[i];
        }
    }	
    return m2;
}
 
// hàm sắp các cực trị tăng dần
double Sort(double long  c[100], int n) {
	int i,j, count = 0;
	
	for(i = 0; i < n - 1;i++) {
		for(j = 0; j < n - i - 1; j++) {
			if(c[ j ] > c[ j + 1 ]) {
				double long temp=c[j];
				c[ j ] = c[ j + 1 ];
				c[ j + 1 ] = temp;
				count ++;
			}
		}
		if(count == 0) {
            break;
        }
	}
	return c[100];
}
// hàm in miền phân ly bài 1
void inMienPhanLy(long double d[100], int bac){
    int count = 0;
    for(int i = 0; i < m; i++){
        for(int j = i+1; j <=m; j++){
            if((giaTriF(f,d[i],bac)) * giaTriF(f,d[j],bac) < 0){
                cout << "mien phan li nghiem la=(" <<d[i] <<"," <<d[j] <<")" <<endl;
                count++;
                }
                break;
                
            }
        }
        if(count == 0){
            cout << "mien phan li nghiem la=(" << mienNghiemAm() << "," << mienNghiemDuong() << ")" << endl;
        }
}
// hàm tìm mảng chứa các cực trị và 2 đầu mút a,b   
void  mangCucTri(long double d[100]){
    long double i = mienNghiemAm();    
    while (i < mienNghiemDuong())
    {
        i = cuctri(f,bac,ETA,i);

        if(abs( giaTriFPhay(f,i,bac) ) < 0.0001 ){
        d[m] = i; 
	    m++;
        i+=STEP;
        }    
    }
    d[m] =   mienNghiemAm();
    m++;
    d[m] =  mienNghiemDuong();
}
// hàm sử dụng phương pháp chia đôi    
long double chiaDoi( long double a, long double b){
    long double c;
    int n = 0;
    while ( abs(a - b) > 0.5 ){
        c = (a + b) / 2;
        if ( giaTriF(f,a,bac) * giaTriF(f,c,bac) < 0 ){
            a = a;
            b = c;
            n++;
        }
        else {
            a = c;
            b = b;
            n++;
        }
    }
    if (n == 0){
        cout << "!!! Khong the dung phuong phap chia doi !!!" <<endl;
        cout << "Mien nghiem la (" <<mienNghiemAm() << " , " << mienNghiemDuong() << ")" <<endl;
    } 
    else{
    cout << "khoang li nghiem (a,b) thoa man |a-b| <= 0.5 la (" << a << " , " << b << ")" <<endl;
    }
}
// chương trình 1
void chuongTrinh1(){

    cout <<  mienNghiemAm() << " < X < " << mienNghiemDuong() <<endl;

    mangCucTri(d);
    
    Sort(d,m+1);	
    
    for (int i = 1; i < m; i++){
        cout <<"cac cuc tri la ";
        cout << "d["<<i<<"] = " << d[i] <<endl;
    }
    inMienPhanLy(d, bac);
}

// chương trình 2
void chuongTrinh2(){
    int n = 0;
    int count = 0;

    mangCucTri(d);

    Sort(d,m+1);
    
    for (int i = 1; i < m; i++){ // in ra các cực trị
        cout << "d[" <<i <<"]=" << d[i] <<endl;
    }

    for(int i = 0; i < m; i++){ // tìm các miền phân li nghiệm, sau đó chia đôi
        for(int j = i+1; j <=m; j++){
            if((giaTriF(f,d[i],bac)) * giaTriF(f,d[j],bac) < 0){
               chiaDoi(d[i], d[j]);
               count ++;
               break;  
            }             
        }
    }
    if(count  == 0){
            chiaDoi(mienNghiemAm(), mienNghiemDuong());
    }    
      
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
    } while (a >= b || giaTriF(f, a, bac) * giaTriF(f, b, bac) > 0);
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
        delta1 = fabs(giaTriF(f, x, bac)) / m1;
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
    long double epsi;
    long double x, tmp, delta1, delta2, trunggian, m1, M2; // lưu nghiệm, các sai số và giá trị min|f'(x)| và max|f''(x)|
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
    if (fphay.MAX * fphay.MIN <= 0 || fhaiPhay.MAX * fhaiPhay.MIN <= 0) // kiểm tra xem f'(x) và f''(x) có giữ nguyên dấu trên [a,b] hay không
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
    // tính theo công thức sai số thứ nhất
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
    // tính theo công thức thứ hai
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
// chương trình nhập vào sai số epsi,
// đưa ra nghiệm theo đánh giá |x(n) -x(n-1)| < epsi
void chuongTrinh5()
{
    long double epsi;
    long double x, tmp, delta, trunggian, m1, M2; // lưu nghiệm, các sai số và giá trị min|f'(x)| và max|f''(x)|
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
    if (fphay.MAX * fphay.MIN <= 0 || fhaiPhay.MAX * fhaiPhay.MIN <= 0) // kiểm tra xem f'(x) và f''(x) có giữ nguyên dấu trên [a,b] hay không
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
}
// chương trình chính
int main()
{
    nhapF();
    // vd chạy ct4
    //chuongTrinh1();
    chuongTrinh1();
    
    
}


    