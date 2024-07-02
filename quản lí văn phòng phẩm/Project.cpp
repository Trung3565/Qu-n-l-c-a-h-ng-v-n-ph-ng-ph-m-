#include <bits/stdc++.h>

using namespace std;

class Dovat
{
private:
    long id_dovat;
    string ten_dovat;
    int gia_dovat;
    int soluong_dovat;
    int giagoc_dovat;

public:
    // Nhập thông tin sản phẩm
    void thongtin_dovat()
    {
        cout << "ID san pham: ";
        cin >> id_dovat;
        cin.ignore();
        cout << "Ten san pham: ";
        getline(cin, ten_dovat);
        cout << "Gia san pham: ";
        cin >> gia_dovat;
        cout << "So luong san pham: ";
        cin >> soluong_dovat;
        cout << "Gia goc san pham: ";
        cin >> giagoc_dovat;
    }
    // Hiện thị thông tin sản phẩm
    void hienthi_dovat()
    {
        cout << id_dovat << setw(20) << ten_dovat << setw(20) << gia_dovat << setw(20) << soluong_dovat << setw(20) << giagoc_dovat << endl;
    }
    // Ghi vào file
    void ghifile(ofstream &file)
    {
        file << id_dovat << setw(20) << ten_dovat << setw(20) << gia_dovat << setw(20) << soluong_dovat << setw(20) << giagoc_dovat << endl;
    }
    // Đọc file
    void docfile(ifstream &file)
    {
        file >> id_dovat;
        file >> ten_dovat;
        file >> gia_dovat;
        file >> soluong_dovat;
        file >> giagoc_dovat;
    }
    // Lấy thông tin sản phẩm
    long get_id()
    {
        return this->id_dovat;
    }
    string get_ten()
    {
        return this->ten_dovat;
    }
    int get_gia()
    {
        return this->gia_dovat;
    }
    int get_soluong()
    {
        return this->soluong_dovat;
    }
    int get_giagoc()
    {
        return this->giagoc_dovat;
    }
    // Đặt lại thông tin sản phẩm
    void set_id(long id)
    {
        this->id_dovat = id;
    }
    void set_ten(string ten)
    {
        this->ten_dovat = ten;
    }
    void set_gia(int gia)
    {
        this->gia_dovat = gia;
    }
    void set_soluong(int soluong)
    {
        this->soluong_dovat = soluong;
    }
    void set_giagoc(int giagoc)
    {
        this->giagoc_dovat = giagoc;
    }
    // Thêm bớt số lượng
    void cong_soluong(int soluong)
    {
        soluong_dovat += soluong;
    }
    void tru_soluong(int soluong)
    {
        soluong_dovat -= soluong;
    }
    friend istream &operator>>(istream &is, Dovat &DV)
    {
        DV.thongtin_dovat();
        return is;
    }
    friend ostream &operator<<(ostream &os, Dovat &DV)
    {
        DV.hienthi_dovat();
        return os;
    }
};

class quanli_cuahang
{
private:
    vector<Dovat> danhsach_dovat;
    vector<Dovat> danhsach_daban;
    int size;
    int size_daban;

public:
    // Đọc danh sách sản phẩm
    void doc_danhsach(ifstream &file)
    {
        file.seekg(15, ios_base::beg);
        file >> size;
        cout << "Tong san pham: " << size << endl;
        file.seekg(79, ios_base::cur);
        danhsach_dovat.resize(size);
        for (int i = 0; i < size; i++)
        {
            Dovat dovat;
            danhsach_dovat[i].docfile(file);
        }
        hienthi_danhsach();
    }

    void hienthi_danhsach()
    {
        cout << "\t\t******Thong tin san pham******" << endl;
        cout << "ID" << setw(20) << "Ten" << setw(20) << "Gia" << setw(20) << "So luong" << setw(20) << "Gia goc" << endl;
        for (int i = 0; i < danhsach_dovat.size(); i++)
        {
            cout << danhsach_dovat[i];
        }
    }
    // Thêm sản phẩm vào danh sách
    void them_dovat()
    {
        int n;
        cout << "Them so luong san pham: ";
        cin >> n;
        size = size + n;
        danhsach_dovat.resize(size);
        for (int i = (size - n); i < size; i++)
        {
            cout << "San pham " << i + 1 << endl;
            Dovat dovat;
            cin >> dovat;
            danhsach_dovat[i] = dovat;
        }
    }
    // Xóa sản phẩm khỏi danh sách
    void xoa_dovat()
    {
        int found = 0;
        long ID;
        cout << "Nhap ID san pham ban muon xoa: ";
        cin >> ID;
        for (int i = 0; i < danhsach_dovat.size(); i++)
        {
            if (ID == danhsach_dovat[i].get_id())
            {
                found++;
                size--;
                danhsach_dovat.erase(danhsach_dovat.begin() + i);
                cout << "Da xoa san pham voi ID " << ID << endl;
            }
        }
        danhsach_dovat.resize(size);
        if (found == 0)
            cout << "Khong co san pham voi ID: " << ID << endl;
    }
    // Thêm số lượng sản phẩm
    void them_soluong()
    {
        long ID;
        int them_soluong;
        cout << "ID san pham: ";
        cin >> ID;
        cout << "So luong them: ";
        cin >> them_soluong;
        for (int i = 0; i < danhsach_dovat.size(); i++)
        {
            if (ID == danhsach_dovat[i].get_id())
            {
                danhsach_dovat[i].cong_soluong(them_soluong);
                break;
            }
        }
    }
    // Bớt số lượng sản phẩm
    void giam_soluong()
    {
        long ID;
        int giam_soluong;
        cout << "ID san pham: ";
        cin >> ID;
        cout << "So luong giam: ";
        cin >> giam_soluong;
        for (int i = 0; i < danhsach_dovat.size(); i++)
        {
            if (ID == danhsach_dovat[i].get_id())
            {
                danhsach_dovat[i].tru_soluong(giam_soluong);
                break;
            }
        }
    }
    // Thay đổi ID sản phẩm
    void doi_id(int i)
    {
        int doi_id;
        cout << "ID moi cua san pham: ";
        cin >> doi_id;
        danhsach_dovat[i].set_id(doi_id);
    }
    // Thay đổi tên sản phẩm
    void doi_ten(int i)
    {
        string ten;
        cout << "Ten moi cua san pham: ";
        cin >> ten;
        danhsach_dovat[i].set_ten(ten);
    }
    // Thay đổi giá sản phẩm
    void doi_gia(int i)
    {
        int doi_gia;
        cout << "Nhap gia moi cua san pham: ";
        cin >> doi_gia;
        danhsach_dovat[i].set_gia(doi_gia);
    }
    // Thay đổi giá gốc sản phẩm
    void doi_giagoc(int i)
    {
        int doi_giagoc;
        cout << "Gia goc moi la: ";
        cin >> doi_giagoc;
        danhsach_dovat[i].set_giagoc(doi_giagoc);
    }
    // Thay đổi thông tin sản phẩm
    void doi_thongtin()
    {
        long ID;
        int select;
        cout << "ID san pham: ";
        cin >> ID;
        for (int i = 0; i < danhsach_dovat.size(); i++)
        {
            if (ID == danhsach_dovat[i].get_id())
            {
                do
                {
                    cout << "\t*********Menu Thay Doi**********" << endl;
                    cout << "\t1.Thay doi ID san pham" << endl;
                    cout << "\t2.Thay doi ten san pham" << endl;
                    cout << "\t3.Thay doi gia san pham" << endl;
                    cout << "\t4.Thay doi gia goc san pham" << endl;
                    cout << "\t5.Quay lai" << endl;
                    cout << "Lua chon cua ban: ";
                    cin >> select;

                    switch (select)
                    {
                    case 1:
                        doi_id(i);
                        break;
                    case 2:
                        doi_ten(i);
                        break;
                    case 3:
                        doi_gia(i);
                        break;
                    case 4:
                        doi_giagoc(i);
                        break;
                    default:
                        break;
                    }
                } while (select != 5);
                break;
            }
        }
    }
    // In file danh sách sản phẩm
    void xuatfile()
    {
        ofstream file;
        file.open("Danh_sach_san_pham.txt");
        file << "Tong san pham: " << size << endl;
        if (file.is_open())
        {
            file << "ID" << setw(20) << "Ten" << setw(20) << "Gia" << setw(20) << "So luong" << setw(20) << "Gia goc" << endl;
            for (int i = 0; i < danhsach_dovat.size(); i++)
            {
                danhsach_dovat[i].ghifile(file);
            }
            file.close();
        }
        else
        {
            cout << "Khong the mo file!";
        }
        cout << "File da duoc xuat ra!!" << endl;
    }
    // Đọc file danh sách đã bán
    void doc_daban(ifstream &file)
    {
        file.seekg(20, ios_base::beg);
        file >> size_daban;
        cout << "Tong san pham da ban: " << size_daban << endl;
        file.seekg(79, ios_base::cur);
        danhsach_daban.resize(size_daban);
        for (int i = 0; i < size_daban; i++)
        {
            Dovat dovat;
            danhsach_daban[i].docfile(file);
        }
        hienthi_daban();
    }
    // Nhập danh sách sản phẩm đã bán
    void thongtin_daban()
    {
        int n;
        cout << "So luong san pham da ban: ";
        cin >> n;
        size_daban = size_daban + n;
        danhsach_daban.resize(size_daban);
        long ID_daban;
        int soluong_daban;
        for (int i = (size_daban - n); i < size_daban; i++)
        {
            cout << "San pham da ban " << i + 1 << endl;
            cout << "ID san pham da ban: ";
            cin >> ID_daban;
            cout << "So luong san pham da ban: ";
            cin >> soluong_daban;
            for (int j = 0; j < danhsach_dovat.size(); j++)
            {
                if (ID_daban == danhsach_dovat[j].get_id())
                {
                    if (soluong_daban > danhsach_dovat[j].get_soluong())
                    {
                        cout << danhsach_dovat[j].get_ten() << " khong du so luong de ban !!!" << endl;
                        size_daban--;
                        i--;
                        danhsach_daban.resize(size_daban);
                    }
                    else
                    {
                        int x = 0;
                        for (int k = 0; k < danhsach_daban.size(); k++)
                        {
                            if (ID_daban == danhsach_daban[k].get_id())
                            {
                                danhsach_daban[k].cong_soluong(soluong_daban);
                                x++;
                                size_daban--;
                                i--;
                                danhsach_daban.resize(size_daban);
                            }
                        }
                        if (x == 0)
                        {
                            danhsach_daban[i].set_id(ID_daban);
                            danhsach_daban[i].set_ten(danhsach_dovat[j].get_ten());
                            danhsach_daban[i].set_gia(danhsach_dovat[j].get_gia());
                            danhsach_daban[i].set_soluong(soluong_daban);
                            danhsach_daban[i].set_giagoc(danhsach_dovat[j].get_giagoc());
                        }
                        danhsach_dovat[j].tru_soluong(soluong_daban);
                    }
                }
            }
        }
        cout << "Da cap nhat danh sach san pham" << endl;
        hienthi_danhsach();
        cout << "Da cap nhat danh sach san pham da ban" << endl;
        hienthi_daban();
    }
    // Hiển thị danh sách sản phẩm đã bán
    void hienthi_daban()
    {
        cout << "\t\t******Thong tin san pham da ban******" << endl;
        cout << "ID" << setw(20) << "Ten" << setw(20) << "Gia" << setw(20) << "So luong" << setw(20) << "Gia goc" << endl;

        for (int i = 0; i < danhsach_daban.size(); i++)
        {
            cout << danhsach_daban[i];
        }
    }
    // Xuất file danh sách sản phẩm đã bán
    void xuat_daban()
    {
        ofstream file;
        file.open("Danh_sach_san_pham_da_ban.txt");
        file << "Tong san pham da ban: " << size_daban << endl;
        if (file.is_open())
        {
            file << "ID" << setw(20) << "Ten" << setw(20) << "Gia" << setw(20) << "So luong" << setw(20) << "Gia goc" << endl;
            for (int i = 0; i < danhsach_daban.size(); i++)
            {
                danhsach_daban[i].ghifile(file);
            }
            file.close();
        }
        else
        {
            cout << "Khong the mo file!";
        }
        cout << "File da duoc xuat ra!!" << endl;
    }
    // Menu sản phẩm
    void menu_danhsach()
    {
        int select;
        do
        {
            cout << "\t*********Menu**********" << endl;
            cout << "\t1.Hien thi san pham" << endl;
            cout << "\t2.Them so luong san pham" << endl;
            cout << "\t3.Giam so luong san pham" << endl;
            cout << "\t4.Thay doi thong tin san pham" << endl;
            cout << "\t5.Them san pham" << endl;
            cout << "\t6.Xoa san pham" << endl;
            cout << "\t7.Xuat file" << endl;
            cout << "\t8.Quay lai" << endl;
            cout << "Lua chon cua ban: ";
            cin >> select;

            switch (select)
            {
            case 1:
                hienthi_danhsach();
                break;
            case 2:
                them_soluong();
                break;
            case 3:
                giam_soluong();
                break;
            case 4:
                doi_thongtin();
                break;
            case 5:
                them_dovat();
                break;
            case 6:
                xoa_dovat();
                break;
            case 7:
                xuatfile();
                break;
            default:
                break;
            }
        } while (select != 8);
    }
    // Menu sản phẩm đã bán
    void menu_daban()
    {
        int select;
        do
        {
            cout << "\t*********Menu**********" << endl;
            cout << "\t1.Them thong tin san pham da ban" << endl;
            cout << "\t2.Hien thi san pham da ban" << endl;
            cout << "\t3.Xuat file" << endl;
            cout << "\t4.Quay lai" << endl;
            cout << "Lua chon cua ban: ";
            cin >> select;

            switch (select)
            {
            case 1:
                thongtin_daban();
                break;
            case 2:
                hienthi_daban();
                break;
            case 3:
                xuat_daban();
                break;
            default:
                break;
            }
        } while (select != 4);
    }
    Dovat get_daban(int i)
    {
        return this->danhsach_daban[i];
    }
    Dovat get_danhsach(int i)
    {
        return this->danhsach_dovat[i];
    }
    int get_size_daban()
    {
        return this->size_daban;
    }
    int get_size()
    {
        return this->size;
    }
};

class tienlai : public quanli_cuahang
{
private:
    int gia_goc;
    int gia_ban;

public:
    // Tính tiền lãi
    void lai()
    {
        gia_goc = 0;
        gia_ban = 0;
        for (int i = 0; i < get_size_daban(); i++)
        {
            gia_ban = gia_ban + get_daban(i).get_gia() * get_daban(i).get_soluong();
            gia_goc = gia_goc + get_daban(i).get_giagoc() * get_daban(i).get_soluong();
        }
    }
    // Hiển thị tiền lãi
    void hienthi_lai()
    {
        cout << "Tien lai la: " << gia_ban - gia_goc << endl;
    }
    // in file quan ly cua hang
    void xuat_lai()
    {
        ofstream file;
        file.open("Quan_li_cua_hang.txt");
        file << "Tong san pham: " << get_size() << endl;
        if (file.is_open())
        {
            file << "\t\t**********Danh sach san pham**********" << endl;
            file << "ID" << setw(20) << "Ten" << setw(20) << "Gia" << setw(20) << "So luong" << setw(20) << "Gia goc" << endl;
            for (int i = 0; i < get_size(); i++)
            {
                get_danhsach(i).ghifile(file);
            }
            file << "\t\t*********Danh sach san pham da ban*********" << endl;
            file << "ID" << setw(20) << "Ten" << setw(20) << "Gia" << setw(20) << "So luong" << setw(20) << "Gia goc" << endl;
            for (int i = 0; i < get_size_daban(); i++)
            {
                get_daban(i).ghifile(file);
            }
            file << "Tien lai la: " << gia_ban - gia_goc << endl;
            file.close();
        }
        else
        {
            cout << "Khong the mo file!";
        }
        cout << "File da duoc xuat ra!!" << endl;
    }
    // Menu
    void Menu()
    {
        ifstream filei;
        filei.open("Danh_sach_san_pham.txt", ios_base ::in);
        doc_danhsach(filei);
        filei.close();
        ifstream fileis;
        fileis.open("Danh_sach_san_pham_da_ban.txt", ios_base ::in);
        doc_daban(fileis);
        fileis.close();
        int select_List;

        do
        {
            cout << "\t*********Menu**********" << endl;
            cout << "\t1.Thong tin danh sach san pham" << endl;
            cout << "\t2.Thong tin danh sach san pham da ban" << endl;
            cout << "\t3.Xuat file va tinh lai" << endl;
            cout << "\t4.Thoat" << endl;
            cout << "Lua chon cua ban: ";
            cin >> select_List;

            switch (select_List)
            {
            case 1:
                menu_danhsach();
                break;
            case 2:
                menu_daban();
                break;
            case 3:
                lai();
                xuat_lai();
                hienthi_lai();
                break;
            default:
                break;
            }
        } while (select_List != 4);
    }
};

int main()
{
    tienlai *cuahang = new tienlai();

    cuahang->Menu();
    delete cuahang;

    return 0;
}