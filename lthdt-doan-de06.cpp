//DO AN MON HOC LAP TRINH HUONG DOI TUONG
//Hoc ky: 2 - Nam hoc: 2024-2025
//De: 06
//Nhom: 14

//Thanh vien:
//Le Hoang Tung - 687862 - K68CNTTA - Nhom truong
//Tran Dinh Dat - 687576 - K68CNTTA
//Nguyen Dinh Duc Son - 687791 - K68CNTTA

#include<iostream>
#include<stdio.h>
#include<fstream>
#include<string.h>

using namespace std;

//Khai bao lop SanPham
class SanPham
{
    private:
	char ten[50];
	float donGia;

    public:
	SanPham();
	SanPham(const char *t, float g);

	//Ham ban
	friend istream& operator>>(istream &cin,SanPham &sp);
	friend ostream& operator<<(ostream &cout,SanPham &sp);

	friend class SPTG;
	friend class GioHang;
};

//Khai bao lop San Pham Trong Gio
class SPTG
{
    private:
	SanPham sp;
	int soLuong;

    public:
	SPTG();
	SPTG(SanPham s, int sl);
	float tinhTien();

	friend class GioHang;
};

//Khai bao lop Gio Hang
class GioHang
{
    private:
	struct Node
	    {
		SPTG infor;
		Node *link;
	    } *F;

    public:
	GioHang();
	~GioHang();
	void themSP(SanPham sp, int sl);
	bool xoaSP(const char *ten);
	void hienThiGioHang();
	float tinhTongTien();
};

//===chuong trinh chinh===
int main()
{
    //Khai bao mang 
    SanPham ds[100];

    //Khai bao bien
    int soLuongSP = 0;
    int chon;

    //Khai bao tep dau vao
    ifstream fin("sanpham.txt");

    //Doc day so tu tep vao DSLKD
    while(fin>>ds[soLuongSP])
   {
       soLuongSP++; 
   }
    
   //Khai bao doi tuong gio hang
    GioHang gh;

    //Vong lap chon chuc nang
    do
    {
	cout<<"\n========= MENU =========\n";
	cout<<"1.Xem danh sach san pham\n";
	cout<<"2.Them san pham vao gio hang\n";
	cout<<"3.Xoa san pham khoi gio hang\n";
	cout<<"4.Xem gio hang\n";
	cout<<"5.Thoat\n";
	cout<<"Chon: ";
	cin>>chon;

	//Xu ly lua chon
	switch (chon)
	{
	 case 1:
		//Hien thi danh sach san pham
		cout<<"Danh sach san pham:\n";

		for(int i=0; i<soLuongSP; i++)
		    {
			cout<<i+1<<"."<<ds[i];
		    }
		    break;

	 case 2:
		//Nhap so luong va so luong them vao gio
		int so, sl;
		cout<<"Chon san pham so may: ";
		cin>>so;
		cout<<"Nhap so luong: ";
		cin>>sl;

		//Kiem tra san pham co ton tai ko
		if(so>=1 && so <=soLuongSP)
		{
		    gh.themSP(ds[so - 1], sl);
		    cout<<"Them thanh cong!\n";
		}
		else
		{
		    cout<<"San pham khong ton tai!\n";
		}
		break;
	

	 case 3:
	{
	    //Nhap ten san pham muon xoa
	    char ten[50];
	    cout<<"Nhap ten san pham muon xoa: ";
	    cin.ignore(); cin.getline(ten, 50);

	    //Xoa san pham trong gio
	    if(gh.xoaSP(ten))
		cout<<"Xoa san pham thanh cong!\n";
	    else
		cout<<"Khong tim thay san pham trong gio!\n";
	    break;
	}

	 case 4:
	    //Hien thi gio hang
	    gh.hienThiGioHang();
	    break;
	    
	 case 5:
	    {
		char xacNhan;
		while (true)
		{
		cout<<"Quy khach co muon thoat (C/K)? ";
		cin>>xacNhan;
		if(xacNhan == 'C' || xacNhan == 'c')
		{
		    cout<<"Tam biet quy khach!\n";
		    return 0;
		}
		else if (xacNhan == 'K' || xacNhan == 'k')
		{
		    break;
		}
		else
		{
		    cout<<"Xac nhan khong hop le. Xac nhan lai\n";
		}
	    }
	    break;
	}

	    default:
	    //Nhap sai lua chon
	    cout<<"Lua chon sai. Vui long thu lai!\n";
	    break;
	}
    }
    while (true);

    cout<<endl;
    return 0;
}

//===dinh nghia ham===
//SanPham
SanPham::SanPham()
{
    strcpy(ten, "");
    donGia = 0;
}

SanPham::SanPham(const char *t, float g)
{
    strcpy(ten, t);
    donGia = g;
}

//Ham ban
istream& operator>>(istream &cin,SanPham &sp)
{
    cin.getline(sp.ten, 50);
    cin>>sp.donGia;
    cin.ignore();
    return cin;
}

ostream& operator<<(ostream &cout,SanPham &sp)
{
    cout<<sp.ten<<" - "<<sp.donGia<<" VND "<<endl;
    return cout;
}	

//SPTG
SPTG::SPTG()
{
    soLuong = 0;
}

SPTG::SPTG(SanPham s, int sl)
{
    sp = s;
    soLuong = sl;
}

float SPTG::tinhTien()
{
    return sp.donGia * soLuong;
}

//GioHang
GioHang::GioHang()
{
    F = NULL;
}

GioHang::~GioHang()
{
    while (F)
    {
	Node *p = F;
	F = F->link;
	delete p;
    }
}

void GioHang::themSP(SanPham sp, int sl)
{
    Node *p = F;

    while(p)
    {
	if (strcasecmp(p->infor.sp.ten, sp.ten) == 0)
	{
	    p->infor.soLuong += sl;
	    return;
	}
	p = p->link;
    }

    Node *N = new Node;
    N->infor = SPTG(sp, sl);
    N->link = NULL;

    if(!F)
	F = N;
    else
    {
	p = F;
	while (p->link) p = p->link;
	p->link = N;
    }
}

bool GioHang::xoaSP(const char *ten)
{
     Node *M = F;
     Node *P = NULL;

     while (M)
     {
	if(strcasecmp(M->infor.sp.ten, ten) == 0) break;
	P = M;
	M = M->link;
     }

     if(!M) return false;

     if(M == F)
	 F = F->link;
     else
	 P->link = M->link;

     delete M;
     return true;	
}

void GioHang::hienThiGioHang()
{
    //Neu gio hang rong
    if(!F)
    {
	cout<<"Gio hang trong\n";
	return;
    }

    //In tieu de
    printf("================ GIO HANG CUA KHACH ================\n");
    printf("%-20s %-10s %-10s %-10s\n", "Ten SP", "Don gia", "So luong", "Thanh tien");
    Node *p = F;

    //In tung san pham trong gio
    while (p)
    {

    printf("%-20s %-10.0f %5d %11.0f\n", p->infor.sp.ten, p->infor.sp.donGia, p->infor.soLuong, p->infor.tinhTien());
	
	p = p->link;
    }

    //In ra tong tien cua gio hang
    printf("%43s%.0f VND\n", "Tong tien: ", tinhTongTien());
}

float GioHang::tinhTongTien()
{
    float tong = 0;
    Node *p = F;
    while (p)
    {
	tong += p->infor.tinhTien();
	p = p->link;
    }
    return tong;
}
