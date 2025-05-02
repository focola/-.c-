#include "hospital.h"

AppointmentRecord appointmentRecords
[MAX_RECORDS];
int recordCount = 0;

void viewAppointments() {
    if (recordCount == 0) {
        printf("û��ԤԼ��¼��\n");
        return;
    }

    printf("\n=== ԤԼ��¼ ===\n");
    for (int i = 0; i < recordCount; i++) {
        printf("[%d] %s ԤԼ %s ҽ�� %s %s\n",
               i+1,
               appointmentRecords[i].patientName,
               appointmentRecords[i].docName,
               appointmentRecords[i].timeOfDay == 0 ? "����" : "����",
               appointmentRecords[i].deptName);
    }
}



void cancelAppointment() {
    if (recordCount == 0) {
        printf("û�п�ȡ����ԤԼ��¼��\n");
        return;
    }

  
    printf("\n=== ԤԼ��¼ ===\n");
    for (int i = 0; i < recordCount; i++) {
        printf("[%d] %s ԤԼ %s ҽ�� %s %s\n",
               i+1,
               appointmentRecords[i].patientName,
               appointmentRecords[i].docName,
               appointmentRecords[i].timeOfDay == 0 ? "����" : "����",
               appointmentRecords[i].deptName);
    }

    int choice;
    printf("\n����Ҫȡ����ԤԼ��ţ�0���أ�: ");
    if(scanf("%d", &choice) != 1) {
        while(getchar() != '\n');
        printf("������Ч\n");
        return;
    }

    if(choice == 0) return;

    if(choice <1 || choice > recordCount) {
        printf("��Ч�ı��\n");
        return;
    }

    int index = choice - 1;
    AppointmentRecord record = appointmentRecords[index];

    char confirm;
    printf("\nȷ��ȡ������ԤԼ��(y/����ȡ��)\n");
    printf("����: %s\n����: %s\nҽ��: %s\nʱ��: ����%d %s\n",
           record.patientName,
           record.deptName,
           record.docName,
           record.dayOfWeek,
           record.timeOfDay == 0 ? "����" : "����");
    printf("��ȷ��: ");
    scanf(" %c", &confirm);

    if(tolower(confirm) == 'y') {
   
        int restored = 0;
        for(int i=0; i<departmentCount; i++) {
            if(strcmp(departments[i].name, record.deptName) == 0) {
                for(int j=0; j<departments[i].doctorCount; j++) {
                    if(strcmp(departments[i].doctors[j].name, record.docName) == 0) {
                        if(record.dayOfWeek >=1 && record.dayOfWeek <=7 &&
                           record.timeOfDay >=0 && record.timeOfDay <=1) {
                            departments[i].doctors[j].appointments[record.dayOfWeek-1][record.timeOfDay]++;
                            restored = 1;
                        }
                        break;
                    }
                }
                break;
            }
        }

   
        for(int i=index; i<recordCount-1; i++) {
            appointmentRecords[i] = appointmentRecords[i+1];
        }
        recordCount--;

        if(restored) {
            printf("ȡ���ɹ�����Դ���ͷ�\n");
        } else {
            printf("ȡ����ɣ�ע��δ�ָܻ���Դ�����ܿ��һ�ҽ����Ϣ�ѱ����\n");
        }
    } else {
        printf("������ȡ��\n");
    }
}



void makeAppointment(char patientName[], char phoneNumber[], int deptChoice, int docChoice, int dayOfWeek, int timeOfDay) {
    
    if(strcmp(patientName, "0") == 0 || strcmp(phoneNumber, "0") == 0 || dayOfWeek == 0) {
        printf("��ȡ��ԤԼ\n");
        return;
    }

    
    for (int i = 0; i < recordCount; i++) {
        if (strcmp(appointmentRecords[i].patientName, patientName) == 0 &&
            strcmp(appointmentRecords[i].phoneNumber, phoneNumber) == 0 &&
            strcmp(appointmentRecords[i].deptName, departments[deptChoice-1].name) == 0 && 
            strcmp(appointmentRecords[i].docName, departments[deptChoice-1].doctors[docChoice-1].name) == 0 &&
            appointmentRecords[i].dayOfWeek == dayOfWeek &&
            appointmentRecords[i].timeOfDay == timeOfDay) 
        {
            printf("��������ԤԼ����ʱ��\n");
            return;
        }
    }

    
    if (departments[deptChoice-1].doctors[docChoice-1].appointments[dayOfWeek-1][timeOfDay] <= 0) {
        printf("��ʱ�����޺�Դ\n");
        return;
    }

    
    departments[deptChoice-1].doctors[docChoice-1].appointments[dayOfWeek-1][timeOfDay]--;

    
    if(recordCount < MAX_RECORDS){
        strcpy(appointmentRecords[recordCount].patientName, patientName);
        strcpy(appointmentRecords[recordCount].phoneNumber, phoneNumber);
        strcpy(appointmentRecords[recordCount].docName, departments[deptChoice-1].doctors[docChoice-1].name);
        strcpy(appointmentRecords[recordCount].deptName, departments[deptChoice-1].name);
        appointmentRecords[recordCount].dayOfWeek = dayOfWeek;
        appointmentRecords[recordCount].timeOfDay = timeOfDay;
        recordCount++;
        printf("ԤԼ�ɹ���\n");
    } else {
        printf("ԤԼʧ�ܣ�ԤԼ��¼����\n");
    }
}
	
	

