#include<iostream>
#include<string>
#include <fstream>
#include<string.h>

using namespace std;

struct Sinhvien{
    int id;
    char ten[30];
    char gt[5];
    int tuoi;
    float dT, dL, dA;
    float dtb;
};

typedef Sinhvien SV;

int laychuso(std::string prompt){
    int x;
    std::cout<< prompt;
    std::cin>> x;
    while (cin.fail()) {
        std::cout<< "\n-----\n";
        std::cout<< "* Nhap Sai * \nVui long nhap lai mot chu so !!!\n";
        std::cout<< "-----";
        std::cin.clear();
        std::cin.ignore(256,'\n');
        std::cout<< endl << prompt;
        std::cin>> x;
        std::cout<< endl;
    }
    return x;
}

void tinhDTB(SV &sv){
    sv.dtb = (sv.dT + sv.dL + sv.dA) / 3;
}

void nhapttSV(SV &sv, int i){
    sv.id = i + 1;
    std::cout<< "Nhap ten: "; std::cin.get(sv.ten, 30);
    getchar();
    std::cout<< "Nhap gioi tinh: "; std::cin.get(sv.gt, 5);
    getchar();
    sv.tuoi = laychuso("Nhap tuoi: ");
    std::cout<< "Nhap diem 3 mon Toan - Ly - Anh\n";
    sv.dT = laychuso("Toan: ");
    sv.dL = laychuso("Ly: ");
    sv.dA = laychuso("Anh ");
    tinhDTB(sv);
    getchar();
};

void nhapNttSV(SV a[] ,int n){
    for(int i = 0; i < n; i++){
        std::cout<< "\nNhap sinh vien thu: " << i+1 << std::endl;
        nhapttSV(a[i], i);
    }
}

void inttSV(SV &sv){
    std::cout<< "ID: " << sv.id << std::endl;
    std::cout<< "Ho ten SV: " << sv.ten << std:: endl;
    std::cout<< "Gioi tinh: " << sv.gt << std:: endl;
    std::cout<< "Tuoi: " << sv.tuoi << std:: endl;
    std::cout<< "Diem Toan - Ly - Anh: " << sv.dT << " - " << sv.dL << " - " << sv.dA << std:: endl;
    std::cout<< "Diem trung binh: " << sv.dtb << std:: endl;
}

void inNttSV(SV a[], int n){
    std::cout<< "\n-----";
    for (int i = 0; i < n; i++) {
        std::cout<<"\nThong tin cua sinh vien thu: " << i+1 << std:: endl;;
        inttSV(a[i]);
    }
    std::cout<< "-----\n";
}

void sapxepTheoDTB(SV a[], int n){
    SV max;
    for (int i = 0; i < n; i++) {
        for (int j = i+1; j < n; j++) {
            if(a[i].dtb > a[j].dtb){
                max = a[i];
                a[i] = a[j];
                a[j] = max;
            }
        }
    }
}

void sapxepTheoTen(SV a[], int n) {
    SV bien_luu_tru;
    char tenSV1[30];
    char tenSV2[30];

    for (int i = 0; i < n; i++) {
        //strcpy la ham copy du lieu sang 1 bien khac
        strcpy(tenSV1, a[i].ten);
        for (int j = i + 1; j < n; j++) {
            strcpy(tenSV2, a[j].ten);
            //strcmp la ham so sanh 2 chuoi
            //strdup la ham viet hoa
            if(strcmp(strdup(tenSV1), strdup(tenSV2)) > 0) {
                bien_luu_tru = a[i];
                a[i] = a[j];
                a[j] = bien_luu_tru;
            }
        }
    }
}

void xeploai(SV &sv){
    if (sv.dtb >= 8) {
        std::cout << "Gioi";
    }
    else if (sv.dtb >= 6.5) {
        std::cout << "Kha";
    }
    else {
        std::cout << "Trung binh";
    }
}

void xeploaiN(SV a[], int n){
    for (int i = 0; i < n; i++) {
        std::cout<< "\nSinh vien - - " << a[i].ten << " - - xep loai: ";
        xeploai(a[i]);
    }
}

void xuatFile(SV a[], int n, char Filename[]) {
    ofstream FileOut;
    FileOut.open(Filename, ios_base::out);
    FileOut << "ID" << std::setw(20) <<"Ho Ten" << std::setw(15) << "GT" << std::setw(10) << "Tuoi" << std::setw(10) << "DT" << std::setw(10) << "DL" << std::setw(10) << "DA" << std::setw(10) << "DTB" <<"\n";
    for (int i = 0; i < n; i++) {
        FileOut << a[i].id << std::setw(20) << a[i].ten << std::setw(15) << a[i].gt << std::setw(10) << a[i].tuoi << std::setw(10) << a[i].dT << std::setw(10) << a[i].dL << std::setw(10) << a[i].dA << std::setw(10) << a[i].dtb <<"\n";
    }
    FileOut.close();
}

int xoatheoID(SV a[], int n, int id, int xoa[],int biendem) {
    int found = 0;
    for (int i = 0; i < n ; i++) {
        if (a[i].id == id) {
            found = 1;
            xoa[biendem] = a[i].id;
            for (int j = i; j < n; j++) {
                a[j] = a[j+1];
            }
            std::cout<< "Da xoa sinh vien co ID: " << id;
            break;
        }
    };

    if (found==0) {
        return 0;
    }
    else {
        return 1;
    }

}

void capnhatTTSV(SV &sv) {
    int chon;
    while(true) {
        std::cout<< "\n-----\n";
        std::cout<< "1. Ten: \n";
        std::cout<< "2. Gioi tinh: \n";
        std::cout<< "3. Tuoi: \n";
        std::cout<< "0. Quay lai\n";
        chon = laychuso("CHon TT muon cap nhat(1-3): ");
        getchar();
        switch(chon) {
            case 1:
                std::cout<< "Nhap ten: ";
                std::cin.get(sv.ten, 30);
                std::cout<< "Cap nhat TTSV thanh cong!!!";
                getchar();
                return;
            case 2:
                std::cout<< "Nhap gioi tinh: ";
                std::cin.get(sv.gt, 5);
                std::cout<< "Cap nhat TTSV thanh cong!!!";
                getchar();
                return;
            case 3:
                sv.tuoi = laychuso("Nhap tuoi: ");
                std::cout<< "Cap nhat TTSV thanh cong!!!";
                getchar();
                return;
            case 0:
                std::cout<< "Ban da chon quay lai.";
                return;
            default:
                std::cout<< "\nKhong co chuc nang nay, hay thu lai!!";
                std::cout<< "\nBam phim bat ki de tiep tuc.\n";
                getchar();
                break;
        }
    }
}

void timkiemTheoTen(SV a[], char ten[], int n) {
    SV dsTimKiem[1000];
    char tenSV[30];
    int found = 0;
    for (int i = 0; i < n ; i++) {
        strcpy(tenSV, a[i].ten);
        //strstr la ham tim kiem
        if (strstr(strdup(tenSV), strdup(ten))) {
            dsTimKiem[found] = a[i];
            found++; 
        }
    }
    if (found == 0) {
        std::cout<< "\nKhong ton tai SV da nhap trong he thong\n";
    }
    else
        inNttSV(dsTimKiem, found);
}

int main() {
    int key;
    int n;
    char Filename[] = "DTN.txt";
    bool daNhap = false;
    int xoa[1000];
    int biendem = 0;

    n = laychuso("Nhap so luong SV: ");
    SV a[n];
    getchar();

    while(true){
        std::cout<< "----------------------------------------\n";
        std::cout<< "|    -CHUONG TRINH QUAN LY SINH VIEN-  |\n";
        std::cout<< "----------------------------------------\n";
        std::cout<< "|     1. Nhap du lieu                  |\n";
        std::cout<< "|     2. Hien thi DS sinh vien         |\n";
        std::cout<< "|     3. Sap xep sinh vien theo DTB    |\n";
        std::cout<< "|     4. Sap xep sinh vien theo Ten    |\n";
        std::cout<< "|     5. Xoa SV theo ID                |\n";
        std::cout<< "|     6. Xep loai sinh vien            |\n";
        std::cout<< "|     7. Cap nhat TTSV theo ID         |\n";
        std::cout<< "|     8. Xuat DS sinh vien             |\n";
        std::cout<< "|     9. Tim kiem SV theo ten          |\n";
        std::cout<< "|     0. Thoat                         |\n";
        std::cout<< "----------------------------------------\n";
        key = laychuso("---       Nhap lua chon cua ban      ---\n");
        std::cout<< "-----";
        getchar();
        switch(key){
            case 1:
                std::cout<< "\nBan da chon nhap danh sach SV: ";
                nhapNttSV(a, n);
                std::cout<< "\nNhap du lieu thanh cong!!!";
                daNhap = true;
                std::cout<< "\nBam phim bat ki de tiep tuc.\n";
                getchar();
                break;
            case 2:
                if(daNhap){
                    std::cout<< "\nBan da chon in danh sach SV: ";
                    inNttSV(a, n);}
                else {
                    std::cout<< "\nVui long nhap danh sach SV truoc!";
                }
                std::cout<< "\nBam phim bat ki de tiep tuc.\n";
                getchar();
                break;
            case 3:
                if (daNhap) {
                    std::cout<< "\nBan da chon sap xep danh sach SV: ";
                    sapxepTheoDTB(a, n);
                    inNttSV(a, n);
                }
                else {
                    std::cout<< "\nVui long nhap danh sach SV truoc!";
                }
                std::cout<< "\nBam phim bat ki de tiep tuc.\n";
                getchar();
                break;
            case 4:
                if (daNhap) {
                    std::cout<< "\nBan da chon sap xep danh sach SV theo Ten: ";
                    sapxepTheoTen(a, n);
                    inNttSV(a, n);
                }
                else {
                    std::cout<< "\nVui long nhap danh sach SV truoc!";
                }
                std::cout<< "\nBam phim bat ki de tiep tuc.\n";
                getchar();
                break;
            case 5:
                if (daNhap) {
                    int id;
                    std::cout<< "\n Ban da chon xoa SV theo ID: \n";
                    for (int i = 0; i < n; i++) {
                        std::cout<< "SV: " << a[i].ten << "  --  " << "ID: " << a[i].id << std:: endl;
                    }
                    id = laychuso("Nhap ID cua SV can xoa: ");
                    getchar();
                    if (xoatheoID(a, n , id, xoa, biendem) == 0) {
                        std::cout<< "Xoa SV that bai(ID khong ton tai)!!!";
                        getchar();
                        break;
                    }
                    else {
                        biendem++;
                        n--;
                    }
                }
                else {
                    std::cout<< "\nVui long nhap danh sach SV truoc!";
                }
                std::cout<< "\nBam phim bat ki de tiep tuc.\n";
                getchar();
                break;
            case 6:
                if (daNhap) {
                    std::cout<< "\nBan da chon xep loai SV: ";
                    xeploaiN(a, n);
                }
                else {
                    std::cout<< "\nVui long nhap danh sach SV truoc!";
                }
                std::cout<< "\nBam phim bat ki de tiep tuc.\n";
                getchar();
                break;
            case 8:
                if (daNhap) {
                    std::cout<< "\nBan da chon xuat danh sach SV ra file txt: ";
                    xuatFile(a, n, Filename);
                    std::cout<< "\nXuat DSSV thanh cong!!!";
                }
                else {
                    std::cout<< "\nVui long nhap danh sach SV truoc!";
                }
                std::cout<< "\nBam phim bat ki de tiep tuc.\n";
                getchar();
                break;
            case 7:
                if (daNhap) {
                    int chon;
                    int maxDS, minDS;

                    std::cout<< "\nBan da chon cap nhat TTSV: \n";
                    for (int i = 0; i < n; i++) {
                        std::cout<< "SV: " << a[i].ten << "  --  " << "ID: " << a[i].id << std:: endl;
                    }

                    minDS = maxDS = a[0].id;
                    for (int i = 1; i < n; i++) {
                        if(maxDS < a[i].id) {
                            maxDS = a[i].id;
                        }
                    }
                    for (int i = 1; i < n; i++) {
                        if(minDS > a[i].id) {
                            minDS = a[i].id;
                        }
                    }
                    
                    chon = laychuso("Nhap ID sinh vien muon chinh sua: ");
                    for (int i = 0; i < biendem; i++) {
                        while (chon > maxDS || chon < minDS || chon == xoa[i]) {
                            std::cout<< "ID khong ton tai hoac co the da bi xoa, vui long nhap lai!\n";
                            getchar();
                            chon = laychuso("Nhap ID sinh vien muon chinh sua: ");
                        }
                    }

                    getchar();
                    for (int i = 0; i < n; i++) {
                        if (a[i].id == chon) {
                            capnhatTTSV(a[i]);
                            break;
                        }
                    }
                }
                else {
                    std::cout<< "\nVui long nhap danh sach SV truoc!";
                }
                std::cout<< "\nBam phim bat ki de tiep tuc.\n";
                getchar();
                break;
            case 9:
                if (daNhap) {
                    std::cout<< "\nBan da chon tim kiem sinh vien theo ten: \n";
                    char strTen[30];
                    std::cout<< "Nhap ten de tim kiem: ";
                    cin.get(strTen, 30);
                    getchar();
                    timkiemTheoTen(a, strTen, n);
                }
                else {
                    std::cout<< "\nVui long nhap danh sach SV truoc!";
                }
                std::cout<< "\nBam phim bat ki de tiep tuc.\n";
                getchar();
                break;
            case 0:
                std::cout<< "\nBan da chon thoat chuong trinh!!!";
                std::cout<< "\n- - - Cam on ban da su dung - - -";
                getchar();
                return 0;
            default:
                std::cout<< "\nKhong co chuc nang nay, hay thu lai!!";
                std::cout<< "\nBam phim bat ki de tiep tuc.\n";
                getchar();
                break;
        }
    }

    return 0;
}