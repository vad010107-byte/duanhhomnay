#include <stdio.h>
#include <string.h>

#define MAX 100

// ==============================
// 1. KHAI BÁO CẤU TRÚC
// ==============================
typedef struct
{
    char cardId[10];
    char name[50];
    char phone[15];
    double debt;
    int visitDays;
} Patient;

typedef struct
{
    char recId[20];
    char cardId[10];
    char date[20];
    char status[20];
    double cost;
} Record;

// ==============================
// 2. MẢNG LƯU DỮ LIỆU
// ==============================
Patient patients[MAX];
Record records[MAX];
int pCount = 0; // số bệnh nhân
int rCount = 0; // số record
void printfMenu(void)
{
    printf("\n+---------------------------+\n");
    printf("|         MENU CHINH        |\n");
    printf("+---------------------------+\n");
    printf("| 1. Tiep nhan benh nhan    |\n");
    printf("| 2. Cap nhat benh nhan     |\n");
    printf("| 3. Xuat vien              |\n");
    printf("| 4. Hien thi danh sach     |\n");
    printf("| 5. Tim kiem theo ten      |\n");
    printf("| 6. Sap xep theo cong no   |\n");
    printf("| 7. Ghi nhan kham benh     |\n");
    printf("| 8. Xem lich su kham benh  |\n");
    printf("| 9. Thoat                  |\n");
    printf("+---------------------------+\n");
}

void addPatient()//f01 tiep nhan benh nhan
{
    if (pCount >= MAX)
    {
        printf("Danh sach benh nhan da day!\n");
        return;
    }
    while (1)
    {
        printf("Nhap ma benh nhan: \n");
        fgets(patients[pCount].cardId, 10, stdin); // scanf
        patients[pCount].cardId[strcspn(patients[pCount].cardId, "\n")] = '\0';
        if (strlen(patients[pCount].cardId) == 0)
        {
            printf("ban chua nhap ID!\n");
            continue;
        }
        break;
    }
    // kiểm tra mã trùng
    for (int i = 0; i < pCount; i++)
    {
        if (strcmp(patients[i].cardId, patients[pCount].cardId) == 0)
        {
            printf("Ma benh nhan bi trung!\n");
            break;
        }
    }

    // Nhap ten benh nhan (khong de trong)
    while (1)
    {
        printf("Nhap ten benh nhan: \n");
        fgets(patients[pCount].name, sizeof(patients[pCount].name), stdin);
        patients[pCount].name[strcspn(patients[pCount].name, "\n")] = '\0';
        if (strlen(patients[pCount].name) == 0)
        {
            printf("khong duoc de trong!\n");
            continue;
        }
        break;
    }

    // Nhap so dien thoai va kiem tra hop le
    while (1)
    {
        printf("Nhap so dien thoai: \n");
        fgets(patients[pCount].phone, sizeof(patients[pCount].phone), stdin); // scanf
        patients[pCount].phone[strcspn(patients[pCount].phone, "\n")] = '\0';
        if (strlen(patients[pCount].phone) == 0)
        {
            printf("khong duoc de trong!\n");
            continue;
        }
        else if (strlen(patients[pCount].phone) < 9 || strlen(patients[pCount].phone) > 15)
        {
            printf("so vua nhap khong dung dinh dang.\n");
            continue;
        }
        int available = 1;
        for (int i = 0; patients[pCount].phone[i] != '\0'; i++)
        {
            if (patients[pCount].phone[i] < '0' || patients[pCount].phone[i] > '9')
            {
                available = 0;
                break;
            }
        }
        if (!available)
        {
            printf("so dien thoai chi chua so!\n");
            continue;
        }
        // valid phone
        break;
    }

    printf("Nhap cong no ban dau: ");
    while (scanf("%lf", &patients[pCount].debt) != 1)
    {
        int c;
        while ((c = getchar()) != '\n' && c != EOF)
        {
        }
        printf("Gia tri khong hop le. Nhap lai cong no ban dau: ");
    }
    getchar();

    patients[pCount].visitDays = 0; // mac dinh = 0

    pCount++;
    printf("Da them benh nhan moi!\n");
}

// ==============================
// F02 – CẬP NHẬT BỆNH NHÂN
// ==============================
void updatePatient()
{
    char id[10];
    printf("Nhap ma benh nhan can cap nhat: ");
    fgets(id, sizeof(id), stdin);
    id[strcspn(id, "\n")] = '\0';

    int pos = -1;
    for (int i = 0; i < pCount; i++)
    {
        if (strcmp(patients[i].cardId, id) == 0)
        {
            pos = i;
            break;
        }
    }

    if (pos == -1)
    {
        printf("Khong tim thay benh nhan!\n");
        return;
    }

    printf("Thong tin benh nhan can thay doi: %s - %s - SDT:%s - No:%.2lf - So lan kham:%d\n",
           patients[pos].cardId,
           patients[pos].name,
           patients[pos].phone,
           patients[pos].debt,
           patients[pos].visitDays);

    printf("Nhap ten moi: ");
    fgets(patients[pos].name, sizeof(patients[pos].name), stdin);
    patients[pos].name[strcspn(patients[pos].name, "\n")] = '\0';

    printf("Nhap SDT moi: ");
    fgets(patients[pos].phone, sizeof(patients[pos].phone), stdin);
    patients[pos].phone[strcspn(patients[pos].phone, "\n")] = '\0';

    printf("Nhap cong no moi: ");
    while (scanf("%lf", &patients[pos].debt) != 1)
    {
        int c;
        while ((c = getchar()) != '\n' && c != EOF)
        {
        }
        printf("Gia tri khong hop le. Nhap lai cong no moi: ");
    }
    getchar();

    printf("Cap nhat thanh cong!\n");
}

// ==============================
// F03 – XUẤT VIỆN (XÓA BỆNH NHÂN)
// ==============================
void deletePatient()
{
    char id[10];
    printf("Nhap ma benh nhan muon xuat vien: ");
    fgets(id, sizeof(id), stdin);
    id[strcspn(id, "\n")] = '\0';

    int pos = -1;
    for (int i = 0; i < pCount; i++)
    {
        if (strcmp(patients[i].cardId, id) == 0)
        {
            pos = i;
            break;
        }
    }

    if (pos == -1)
    {
        printf("Khong tim thay benh nhan!\n");
        return;
    }

    printf("Thong tin benh nhan can xuat vien: %s - %s - SDT:%s - No:%.2lf - So lan kham:%d\n",
           patients[pos].cardId,
           patients[pos].name,
           patients[pos].phone,
           patients[pos].debt,
           patients[pos].visitDays);

    if (patients[pos].debt > 0)
    {
        printf("CANH BAO: Benh nhan van con no %.2lf\n", patients[pos].debt);
    }

    printf("Ban co muon thanh toan cong no khong?(yes-1/no-0): ");
    int temp;
    scanf("%d", &temp);
    if (temp == 1)
    {
        for (int i = pos; i < pCount - 1; i++)
        {
            patients[i] = patients[i + 1];
        }

        pCount--;
        printf("Da xuat vien thanh cong!\n");
    }
    else
    {
        printf("Benh nhan khong the xuat vien!");
    }
}

// ==============================
// F04 – HIỂN THỊ DANH SÁCH
// ==============================
void showPatients()
{
    if (pCount == 0)
    {
        printf("Khong co benh nhan nao!\n");
        return;
    }

    printf("\n╔════╦════════════╦══════════════════════════╦══════════════╦══════════╦════════════╗\n");
    printf("║ STT║   Ma BN    ║         Ho Ten           ║    SDT       ║   No     ║ So lan kham║\n");
    printf("╠════╬════════════╬══════════════════════════╬══════════════╬══════════╬════════════╣\n");

    for (int i = 0; i < pCount; i++)
    {
        printf("║ %-2d ║ %-10s ║ %-24s ║ %-12s ║ %-8.2lf ║ %-12d ║\n",
               i + 1,
               patients[i].cardId,
               patients[i].name,
               patients[i].phone,
               patients[i].debt,
               patients[i].visitDays);
    }

    printf("╚════╩════════════╩══════════════════════════╩══════════════╩══════════╩════════════╝\n");
}


// ==============================
// F05 – TÌM KIẾM THEO TÊN
// ==============================
void searchPatient()
{
    char key[50];
    printf("Nhap ten (hoac mot phan ten): ");
    fgets(key, sizeof(key), stdin);
    key[strcspn(key, "\n")] = '\0';

    int found = 0;

    for (int i = 0; i < pCount; i++)
    {
        if (strstr(patients[i].name, key) != NULL)
        { // tìm chuỗi con
            printf("%s - %s - SDT:%s - No:%.2lf\n",
                   patients[i].cardId,
                   patients[i].name,
                   patients[i].phone,
                   patients[i].debt);
            found = 1;
        }
    }

    if (!found)
        printf("Khong tim thay benh nhan!\n");
}

// ==============================
// F06 – SẮP XẾP THEO NỢ (TĂNG DẦN)
// ==============================
void sortDebt()
{
    for (int i = 0; i < pCount - 1; i++)
    {
        for (int j = i + 1; j < pCount; j++)
        {
            if (patients[i].debt > patients[j].debt)
            {
                Patient temp = patients[i];
                patients[i] = patients[j];
                patients[j] = temp;
            }
        }
    }
    printf("Da sap xep theo cong no (tang dan)!\n");
    for (int i = 0; i < pCount; i++)
    {
        printf("%s - %s - SDT:%s - No:%.2lf\n",
               patients[i].cardId,
               patients[i].name,
               patients[i].phone,
               patients[i].debt);
    }
}

// ==============================
// F07 – GHI NHẬN KHÁM BỆNH
// ==============================
void addRecord()
{
    if (rCount >= MAX)
    {
        printf("Danh sach record da day!\n");
        return;
    }
    char id[10];
    printf("Nhap ma benh nhan: ");
    fgets(id, sizeof(id), stdin);
    id[strcspn(id, "\n")] = '\0';

    int pos = -1;
    for (int i = 0; i < pCount; i++)
    {
        if (strcmp(patients[i].cardId, id) == 0)
        {
            pos = i;
            break;
        }
    }

    if (pos == -1)
    {
        printf("Khong tim thay benh nhan!\n");
        return;
    }

    printf("Nhap ma lan kham: ");
    fgets(records[rCount].recId, sizeof(records[rCount].recId), stdin);
    records[rCount].recId[strcspn(records[rCount].recId, "\n")] = '\0';

    strcpy(records[rCount].cardId, id);

    printf("Nhap ngay kham: ");
    fgets(records[rCount].date, sizeof(records[rCount].date), stdin);
    records[rCount].date[strcspn(records[rCount].date, "\n")] = '\0';

    printf("Nhap trang thai: ");
    fgets(records[rCount].status, sizeof(records[rCount].status), stdin);
    records[rCount].status[strcspn(records[rCount].status, "\n")] = '\0';

    printf("Nhap chi phi: ");
    while (scanf("%lf", &records[rCount].cost) != 1)
    {
        int c;
        while ((c = getchar()) != '\n' && c != EOF)
        {
        }
        printf("Gia tri khong hop le. Nhap lai chi phi: ");
    }
    getchar();

    patients[pos].visitDays++;
    patients[pos].debt += records[rCount].cost;

    rCount++;
    printf("Da ghi nhan kham benh!\n");
}

// ==============================
// F08 – XEM LỊCH SỬ KHÁM
// ==============================
void showHistory()
{
    char id[10];
    printf("Nhap ma benh nhan: ");
    fgets(id, sizeof(id), stdin);
    id[strcspn(id, "\n")] = '\0';

    int found = 0;

    for (int i = 0; i < rCount; i++)
    {
        if (strcmp(records[i].cardId, id) == 0)
        {
            printf("%s - Ngay kham:%s - Trang thai:%s - Chi phi:%.2lf\n",
                   records[i].recId,
                   records[i].date,
                   records[i].status,
                   records[i].cost);
            found = 1;
        }
    }

    if (!found)
        printf("Khong co lich su kham!\n");
}

// ==============================
// F09 – THOÁT CHƯƠNG TRÌNH
// ==============================
int main(void)
{
    int choice = 0;
    do
    {
        printfMenu();
        printf("Chon chuc nang (1-9): ");
        scanf("%d", &choice);
        getchar();

        switch (choice)
        {
        case 1:
            addPatient();
            break;
        case 2:
            updatePatient();
            break;
        case 3:
            deletePatient();
            break;
        case 4:
            showPatients();
            break;
        case 5:
            searchPatient();
            break;
        case 6:
            sortDebt();
            break;
        case 7:
            addRecord();
            break;
        case 8:
            showHistory();
            break;
        case 9:
            printf("Thoat chuong trinh...\n");
            break;
        default:
            printf("Lua chon khong hop le!\n");
        }
    } while (choice != 9);
    return 0;
}

