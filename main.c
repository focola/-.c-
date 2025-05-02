#include "hospital.h"

int main() {
    int mode;
    int running = 1;
    initDepartments();

    while (running) {
        printf("\nѡ��ģʽ (0: ����ģʽ, 1: ������ģʽ, ���������˳�): ");
        int result = scanf("%d", &mode);
        if (result != 1) {
            while (getchar() != '\n');
            printf("�˳�����\n");
            break;
        }

        if (mode == 0 || mode == 1) {
            showMenu(mode);
        } else {
            printf("�˳�����\n");
            running = 0;
        }
    }
    return 0;
}

void showMenu(int mode) {
    int choice;
    do {
        printf("\n=== ���˵� ===\n");
        printf("1. �鿴���Ҳ�ԤԼ\n");
        printf("2. �鿴ԤԼ��¼\n");
        printf("3. ����ҽ��\n");
        printf("4. ���������ҿ���\n");
        printf("5. ȡ��ԤԼ\n");
        
        if(mode == 1) {
            printf("6. �޸�ҽ����Ϣ\n");
            printf("7. ɾ��ҽ����Ϣ\n");
            printf("8. ���ҽ����Ϣ\n");
            printf("9. ���������\n");
            printf("10. ��ӿ���\n");
        }
        
        printf("0. �����ϼ��˵�\n");
        printf("��ѡ�����: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: showDepartmentsAndMakeAppointment(); break;
            case 2: viewAppointments(); break;
            case 3: searchDoctor(); break;
            case 4: searchByDisease(mode); break;
            case 5: cancelAppointment(); break;
            case 6: if(mode) modifyDoctor(); else printf("��Чѡ��\n"); break;
            case 7: if(mode) deleteDoctor(); else printf("��Чѡ��\n"); break;
            case 8: if(mode) addDoctor(); else printf("��Чѡ��\n"); break;
            case 9: if(mode) diseaseManagement(); else printf("��Чѡ��\n"); break;
            case 10: if(mode) addDepartment(); else printf("��Чѡ��\n"); break;
            case 0: break;
            default: printf("��Ч��ѡ��\n");
        }
    } while (choice != 0);
}
