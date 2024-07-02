#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Dovat
{
    long id_dovat;
    char ten_dovat[100];
    int gia_dovat;
    int soluong_dovat;
    int giagoc_dovat;
} Dovat;
// Nhập thông tin sản phẩm
void thongtin_dovat(Dovat *dovat)
{
    printf("ID san pham: ");
    scanf("%ld", &dovat->id_dovat);
    getchar();
    printf("Ten san pham: ");
    fgets(dovat->ten_dovat, sizeof(dovat->ten_dovat), stdin);
    dovat->ten_dovat[strcspn(dovat->ten_dovat, "\n")] = 0;
    printf("Gia san pham: ");
    scanf("%d", &dovat->gia_dovat);
    printf("So luong san pham: ");
    scanf("%d", &dovat->soluong_dovat);
    printf("Gia goc san pham: ");
    scanf("%d", &dovat->giagoc_dovat);
}
// Hiển thị thông tin sản phẩm 
void hienthi_dovat(Dovat *dovat)
{
    printf("%ld%20s%20d%20d%20d\n", dovat->id_dovat, dovat->ten_dovat, dovat->gia_dovat, dovat->soluong_dovat, dovat->giagoc_dovat);
}
// Ghi vào file 
void ghifile(FILE *file, Dovat *dovat)
{
    fprintf(file, "%ld%20s%20d%20d%20d\n", dovat->id_dovat, dovat->ten_dovat, dovat->gia_dovat, dovat->soluong_dovat, dovat->giagoc_dovat);
}
// Đọc file 
void docfile(FILE *file, Dovat *dovat)
{
    fscanf(file, "%ld", &dovat->id_dovat);
    fscanf(file, "%s", dovat->ten_dovat);
    fscanf(file, "%d", &dovat->gia_dovat);
    fscanf(file, "%d", &dovat->soluong_dovat);
    fscanf(file, "%d", &dovat->giagoc_dovat);
}
// Lấy thông tin sản phẩm
long get_id(Dovat *dovat)
{
    return dovat->id_dovat;
}

char *get_ten(Dovat *dovat)
{
    return dovat->ten_dovat;
}

int get_gia(Dovat *dovat)
{
    return dovat->gia_dovat;
}

int get_soluong(Dovat *dovat)
{
    return dovat->soluong_dovat;
}

int get_giagoc(Dovat *dovat)
{
    return dovat->giagoc_dovat;
}
// Đặt lại thông tin sản phẩm 
void set_id(Dovat *dovat, long id)
{
    dovat->id_dovat = id;
}

void set_ten(Dovat *dovat, char *ten)
{
    strcpy(dovat->ten_dovat, ten);
}

void set_gia(Dovat *dovat, int gia)
{
    dovat->gia_dovat = gia;
}

void set_soluong(Dovat *dovat, int soluong)
{
    dovat->soluong_dovat = soluong;
}

void set_giagoc(Dovat *dovat, int giagoc)
{
    dovat->giagoc_dovat = giagoc;
}
// Them bớt số lượng 
void cong_soluong(Dovat *dovat, int soluong)
{
    dovat->soluong_dovat += soluong;
}

void tru_soluong(Dovat *dovat, int soluong)
{
    dovat->soluong_dovat -= soluong;
}

typedef struct quanli_cuahang
{
    Dovat *danhsach_dovat;
    Dovat *danhsach_daban;
    int size;
    int size_daban;
} quanli_cuahang;
// Đọc danh sách sản phẩm 
void doc_danhsach(FILE *file, quanli_cuahang *cuahang)
{
    fseek(file, 15, SEEK_SET);
    fscanf(file, "%d", &cuahang->size);
    printf("Tong san pham: %d\n", cuahang->size);
    fseek(file, 79, SEEK_CUR);
    cuahang->danhsach_dovat = (Dovat *)malloc(cuahang->size * sizeof(Dovat));
    for (int i = 0; i < cuahang->size; i++)
    {
        docfile(file, &cuahang->danhsach_dovat[i]);
    }
    hienthi_danhsach(cuahang);
}

void hienthi_danhsach(quanli_cuahang *cuahang)
{
    printf("\t\t******Thong tin san pham******\n");
    printf("ID%20s%20s%20s%20s\n", "Ten", "Gia", "So luong", "Gia goc");
    for (int i = 0; i < cuahang->size; i++)
    {
        hienthi_dovat(&cuahang->danhsach_dovat[i]);
    }
}
// Thêm sản phẩm vào danh sách
void them_dovat(quanli_cuahang *cuahang)
{
    int n;
    printf("Them so luong san pham: ");
    scanf("%d", &n);
    cuahang->size += n;
    cuahang->danhsach_dovat = (Dovat *)realloc(cuahang->danhsach_dovat, cuahang->size * sizeof(Dovat));
    for (int i = (cuahang->size - n); i < cuahang->size; i++)
    {
        printf("San pham %d\n", i + 1);
        thongtin_dovat(&cuahang->danhsach_dovat[i]);
    }
}
// Xóa đồ vặt khỏi danh sách
void xoa_dovat(quanli_cuahang *cuahang)
{
    int found = 0;
    long ID;
    printf("Nhap ID san pham ban muon xoa: ");
    scanf("%ld", &ID);
    for (int i = 0; i < cuahang->size; i++)
    {
        if (ID == get_id(&cuahang->danhsach_dovat[i]))
        {
            found++;
            cuahang->size--;
            for (int j = i; j < cuahang->size; j++)
            {
                cuahang->danhsach_dovat[j] = cuahang->danhsach_dovat[j + 1];
            }
            printf("Da xoa san pham voi ID %ld\n", ID);
        }
    }
    cuahang->danhsach_dovat = (Dovat *)realloc(cuahang->danhsach_dovat, cuahang->size * sizeof(Dovat));
    if (found == 0)
        printf("Khong co san pham voi ID: %ld\n", ID);
}
// Thêm số lượng sản phẩm 
void them_soluong(quanli_cuahang *cuahang)
{
    long ID;
    int them_soluong;
    printf("ID san pham: ");
    scanf("%ld", &ID);
    printf("So luong them: ");
    scanf("%d", &them_soluong);
    for (int i = 0; i < cuahang->size; i++)
    {
        if (ID == get_id(&cuahang->danhsach_dovat[i]))
        {
            cong_soluong(&cuahang->danhsach_dovat[i], them_soluong);
            break;
        }
    }
}
// Giảm số lượng sản phẩm 
void giam_soluong(quanli_cuahang *cuahang)
{
    long ID;
    int giam_soluong;
    printf("ID san pham: ");
    scanf("%ld", &ID);
    printf("So luong giam: ");
    scanf("%d", &giam_soluong);
    for (int i = 0; i < cuahang->size; i++)
    {
        if (ID == get_id(&cuahang->danhsach_dovat[i]))
        {
            tru_soluong(&cuahang->danhsach_dovat[i], giam_soluong);
            break;
        }
    }
}
// Thay đổi ID sản phẩm 
void doi_id(quanli_cuahang *cuahang, int i)
{
    long doi_id;
    printf("ID moi cua san pham: ");
    scanf("%ld", &doi_id);
    set_id(&cuahang->danhsach_dovat[i], doi_id);
}
// Thay đổi tên sản phẩm 
void doi_ten(quanli_cuahang *cuahang, int i)
{
    char ten[100];
    printf("Ten moi cua san pham: ");
    scanf("%s", ten);
    set_ten(&cuahang->danhsach_dovat[i], ten);
}
// Thay đổi giá sản phẩm 
void doi_gia(quanli_cuahang *cuahang, int i)
{
    int doi_gia;
    printf("Nhap gia moi cua san pham: ");
    scanf("%d", &doi_gia);
    set_gia(&cuahang->danhsach_dovat[i], doi_gia);
}
// Thay đổi giá gốc sản phẩm
void doi_giagoc(quanli_cuahang *cuahang, int i)
{
    int doi_giagoc;
    printf("Gia goc moi la: ");
    scanf("%d", &doi_giagoc);
    set_giagoc(&cuahang->danhsach_dovat[i], doi_giagoc);
}
// Thay đổi thông tin sản phẩm
void doi_thongtin(quanli_cuahang *cuahang)
{
    long ID;
    int select;
    printf("ID san pham: ");
    scanf("%ld", &ID);
    for (int i = 0; i < cuahang->size; i++)
    {
        if (ID == get_id(&cuahang->danhsach_dovat[i]))
        {
            do
            {
                printf("\t*********Menu Thay Doi**********\n");
                printf("\t1.Thay doi ID san pham\n");
                printf("\t2.Thay doi ten san pham\n");
                printf("\t3.Thay doi gia san pham\n");
                printf("\t4.Thay doi gia goc san pham\n");
                printf("\t5.Quay lai\n");
                printf("Lua chon cua ban: ");
                scanf("%d", &select);

                switch (select)
                {
                case 1:
                    doi_id(cuahang, i);
                    break;
                case 2:
                    doi_ten(cuahang, i);
                    break;
                case 3:
                    doi_gia(cuahang, i);
                    break;
                case 4:
                    doi_giagoc(cuahang, i);
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
void xuatfile(quanli_cuahang *cuahang)
{
    FILE *file;
    file = fopen("Danh_sach_san_pham.txt", "w");
    fprintf(file, "Tong san pham: %d\n", cuahang->size);
    if (file != NULL)
    {
        fprintf(file, "ID%20s%20s%20s%20s\n", "Ten", "Gia", "So luong", "Gia goc");
        for (int i = 0; i < cuahang->size; i++)
        {
            ghifile(file, &cuahang->danhsach_dovat[i]);
        }
        fclose(file);
    }
    else
    {
        printf("Khong the mo file!");
    }
    printf("File da duoc xuat ra!!\n");
}
// Đọc file danh sách đã bán
void doc_daban(FILE *file, quanli_cuahang *cuahang)
{
    fseek(file, 20, SEEK_SET);
    fscanf(file, "%d", &cuahang->size_daban);
    printf("Tong san pham da ban: %d\n", cuahang->size_daban);
    fseek(file, 79, SEEK_CUR);
    cuahang->danhsach_daban = (Dovat *)malloc(cuahang->size_daban * sizeof(Dovat));
    for (int i = 0; i < cuahang->size_daban; i++)
    {
        docfile(file, &cuahang->danhsach_daban[i]);
    }
    hienthi_daban(cuahang);
}
// Nhập danh sách sản phẩm đã bán
void thongtin_daban(quanli_cuahang *cuahang)
{
    int n;
    printf("So luong san pham da ban: ");
    scanf("%d", &n);
    cuahang->size_daban += n;
    cuahang->danhsach_daban = (Dovat *)realloc(cuahang->danhsach_daban, cuahang->size_daban * sizeof(Dovat));
    long ID_daban;
    int soluong_daban;
    for (int i = (cuahang->size_daban - n); i < cuahang->size_daban; i++)
    {
        printf("San pham da ban %d\n", i + 1);
        printf("ID san pham da ban: ");
        scanf("%ld", &ID_daban);
        printf("So luong san pham da ban: ");
        scanf("%d", &soluong_daban);
        for (int j = 0; j < cuahang->size; j++)
        {
            if (ID_daban == get_id(&cuahang->danhsach_dovat[j]))
            {
                if (soluong_daban > get_soluong(&cuahang->danhsach_dovat[j]))
                {
                    printf("%s khong du so luong de ban !!!\n", get_ten(&cuahang->danhsach_dovat[j]));
                    cuahang->size_daban--;
                    i--;
                    cuahang->danhsach_daban = (Dovat *)realloc(cuahang->danhsach_daban, cuahang->size_daban * sizeof(Dovat));
                }
                else
                {
                    int x = 0;
                    for (int k = 0; k < cuahang->size_daban; k++)
                    {
                        if (ID_daban == get_id(&cuahang->danhsach_daban[k]))
                        {
                            cong_soluong(&cuahang->danhsach_daban[k], soluong_daban);
                            x++;
                            cuahang->size_daban--;
                            i--;
                            cuahang->danhsach_daban = (Dovat *)realloc(cuahang->danhsach_daban, cuahang->size_daban * sizeof(Dovat));
                        }
                    }
                    if (x == 0)
                    {
                        set_id(&cuahang->danhsach_daban[i], ID_daban);
                        set_ten(&cuahang->danhsach_daban[i], get_ten(&cuahang->danhsach_dovat[j]));
                        set_gia(&cuahang->danhsach_daban[i], get_gia(&cuahang->danhsach_dovat[j]));
                        set_soluong(&cuahang->danhsach_daban[i], soluong_daban);
                        set_giagoc(&cuahang->danhsach_daban[i], get_giagoc(&cuahang->danhsach_dovat[j]));
                    }
                    tru_soluong(&cuahang->danhsach_dovat[j], soluong_daban);
                }
            }
        }
    }
    printf("Da cap nhat danh sach san pham\n");
    hienthi_danhsach(cuahang);
    printf("Da cap nhat danh sach san pham da ban\n");
    hienthi_daban(cuahang);
}
// Hiển thị danh sách sản phẩm đã bán
void hienthi_daban(quanli_cuahang *cuahang)
{
    printf("\t\t******Thong tin san pham da ban******\n");
    printf("ID%20s%20s%20s%20s\n", "Ten", "Gia", "So luong", "Gia goc");

    for (int i = 0; i < cuahang->size_daban; i++)
    {
        hienthi_dovat(&cuahang->danhsach_daban[i]);
    }
}
// Xuất file sản phẩm đã bán
void xuat_daban(quanli_cuahang *cuahang)
{
    FILE *file;
    file = fopen("Danh_sach_san_pham_da_ban.txt", "w");
    fprintf(file, "Tong san pham da ban: %d\n", cuahang->size_daban);
    if (file != NULL)
    {
        fprintf(file, "ID%20s%20s%20s%20s\n", "Ten", "Gia", "So luong", "Gia goc");
        for (int i = 0; i < cuahang->size_daban; i++)
        {
            ghifile(file, &cuahang->danhsach_daban[i]);
        }
        fclose(file);
    }
    else
    {
        printf("Khong the mo file!");
    }
    printf("File da duoc xuat ra!!\n");
}
// Menu sản phẩm 
void menu_danhsach(quanli_cuahang *cuahang)
{
    int select;
    do
    {
        printf("\t*********Menu**********\n");
        printf("\t1.Hien thi san pham\n");
        printf("\t2.Them so luong san pham\n");
        printf("\t3.Giam so luong san pham\n");
        printf("\t4.Thay doi thong tin san pham\n");
        printf("\t5.Them san pham\n");
        printf("\t6.Xoa san pham\n");
        printf("\t7.Xuat file\n");
        printf("\t8.Quay lai\n");
        printf("Lua chon cua ban: ");
        scanf("%d", &select);

        switch (select)
        {
        case 1:
            hienthi_danhsach(cuahang);
            break;
        case 2:
            them_soluong(cuahang);
            break;
        case 3:
            giam_soluong(cuahang);
            break;
        case 4:
            doi_thongtin(cuahang);
            break;
        case 5:
            them_dovat(cuahang);
            break;
        case 6:
            xoa_dovat(cuahang);
            break;
        case 7:
            xuatfile(cuahang);
            break;
        default:
            break;
        }
    } while (select != 8);
}
// Menu sản phẩm đã bán 
void menu_daban(quanli_cuahang *cuahang)
{
    int select;
    do
    {
        printf("\t*********Menu**********\n");
        printf("\t1.Them thong tin san pham da ban\n");
        printf("\t2.Hien thi san pham da ban\n");
        printf("\t3.Xuat file\n");
        printf("\t4.Quay lai\n");
        printf("Lua chon cua ban:\n ");
        scanf("%d", &select);

        switch (select)
        {
        case 1:
            thongtin_daban(cuahang);
            break;
        case 2:
            hienthi_daban(cuahang);
            break;
        case 3:
            xuat_daban(cuahang);
            break;
        default:
            break;
        }
    } while (select != 4);
}
// Tính tiền lãi
void tienlai(quanli_cuahang *cuahang)
{
    int gia_goc = 0;
    int gia_ban = 0;
    for (int i = 0; i < cuahang->size_daban; i++)
    {
        gia_ban = gia_ban + get_gia(&cuahang->danhsach_daban[i]) * get_soluong(&cuahang->danhsach_daban[i]);
        gia_goc = gia_goc + get_giagoc(&cuahang->danhsach_daban[i]) * get_soluong(&cuahang->danhsach_daban[i]);
    }
    printf("Tien lai la: %d\n", gia_ban - gia_goc); // hiển thị tiền lãi
}

// in file quản lí cửa hàng 
void xuat_lai(quanli_cuahang *cuahang)
{
    FILE *file;
    file = fopen("Quan_li_cua_hang.txt", "w");
    fprintf(file, "Tong san pham: %d\n", cuahang->size);
    if (file != NULL)
    {
        fprintf(file, "\t\t**********Danh sach san pham**********\n");
        fprintf(file, "ID%20s%20s%20s%20s\n", "Ten", "Gia", "So luong", "Gia goc");
        for (int i = 0; i < cuahang->size; i++)
        {
            ghifile(file, &cuahang->danhsach_dovat[i]);
        }
        fprintf(file, "\t\t*********Danh sach san pham da ban*********\n");
        fprintf(file, "ID%20s%20s%20s%20s\n", "Ten", "Gia", "So luong", "Gia goc");
        for (int i = 0; i < cuahang->size_daban; i++)
        {
            ghifile(file, &cuahang->danhsach_daban[i]);
        }
        tienlai(cuahang);
        fclose(file);
    }
    else
    {
        printf("Khong the mo file!");
    }
    printf("File da duoc xuat ra!!\n");
}
// Menu 
void Menu()
{
    quanli_cuahang *cuahang = (quanli_cuahang *)malloc(sizeof(quanli_cuahang));

    FILE *filei;
    filei = fopen("Danh_sach_san_pham.txt", "r");
    doc_danhsach(filei, cuahang);
    fclose(filei);

    FILE *fileis;
    fileis = fopen("Danh_sach_san_pham_da_ban.txt", "r");
    doc_daban(fileis, cuahang);
    fclose(fileis);

    int select_List;

    do
    {
        printf("\t*********Menu**********\n");
        printf("\t1.Thong tin danh sach san pham\n");
        printf("\t2.Thong tin danh sach san pham da ban\n");
        printf("\t3.Xuat file va tinh lai\n");
        printf("\t4.Thoat\n");
        printf("Lua chon cua ban: ");
        scanf("%d", &select_List);

        switch (select_List)
        {
        case 1:
            menu_danhsach(cuahang);
            break;
        case 2:
            menu_daban(cuahang);
            break;
        case 3:
            xuat_lai(cuahang);
            break;
        default:
            break;
        }
    } while (select_List != 4);

    free(cuahang->danhsach_dovat);
    free(cuahang->danhsach_daban);
    free(cuahang);
}

int main()
{
    Menu();

    return 0;
}
