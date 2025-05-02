#include "hospital.h"

int main() {
    int mode;
    int running = 1;
    initDepartments();

    while (running) {
        printf("\n选择模式 (0: 患者模式, 1: 开发者模式, 其他数字退出): ");
        int result = scanf("%d", &mode);
        if (result != 1) {
            while (getchar() != '\n');
            printf("退出程序。\n");
            break;
        }

        if (mode == 0 || mode == 1) {
            showMenu(mode);
        } else {
            printf("退出程序。\n");
            running = 0;
        }
    }
    return 0;
}

void showMenu(int mode) {
    int choice;
    do {
        printf("\n=== 主菜单 ===\n");
        printf("1. 查看科室并预约\n");
        printf("2. 查看预约记录\n");
        printf("3. 查找医生\n");
        printf("4. 按疾病查找科室\n");
        printf("5. 取消预约\n");
        
        if(mode == 1) {
            printf("6. 修改医生信息\n");
            printf("7. 删除医生信息\n");
            printf("8. 添加医生信息\n");
            printf("9. 疾病库管理\n");
            printf("10. 添加科室\n");
        }
        
        printf("0. 返回上级菜单\n");
        printf("请选择操作: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: showDepartmentsAndMakeAppointment(); break;
            case 2: viewAppointments(); break;
            case 3: searchDoctor(); break;
            case 4: searchByDisease(mode); break;
            case 5: cancelAppointment(); break;
            case 6: if(mode) modifyDoctor(); else printf("无效选择\n"); break;
            case 7: if(mode) deleteDoctor(); else printf("无效选择\n"); break;
            case 8: if(mode) addDoctor(); else printf("无效选择\n"); break;
            case 9: if(mode) diseaseManagement(); else printf("无效选择\n"); break;
            case 10: if(mode) addDepartment(); else printf("无效选择\n"); break;
            case 0: break;
            default: printf("无效的选择\n");
        }
    } while (choice != 0);
}
