#include "hospital.h"

AppointmentRecord appointmentRecords
[MAX_RECORDS];
int recordCount = 0;

void viewAppointments() {
    if (recordCount == 0) {
        printf("没有预约记录。\n");
        return;
    }

    printf("\n=== 预约记录 ===\n");
    for (int i = 0; i < recordCount; i++) {
        printf("[%d] %s 预约 %s 医生 %s %s\n",
               i+1,
               appointmentRecords[i].patientName,
               appointmentRecords[i].docName,
               appointmentRecords[i].timeOfDay == 0 ? "上午" : "下午",
               appointmentRecords[i].deptName);
    }
}



void cancelAppointment() {
    if (recordCount == 0) {
        printf("没有可取消的预约记录。\n");
        return;
    }

  
    printf("\n=== 预约记录 ===\n");
    for (int i = 0; i < recordCount; i++) {
        printf("[%d] %s 预约 %s 医生 %s %s\n",
               i+1,
               appointmentRecords[i].patientName,
               appointmentRecords[i].docName,
               appointmentRecords[i].timeOfDay == 0 ? "上午" : "下午",
               appointmentRecords[i].deptName);
    }

    int choice;
    printf("\n输入要取消的预约编号（0返回）: ");
    if(scanf("%d", &choice) != 1) {
        while(getchar() != '\n');
        printf("输入无效\n");
        return;
    }

    if(choice == 0) return;

    if(choice <1 || choice > recordCount) {
        printf("无效的编号\n");
        return;
    }

    int index = choice - 1;
    AppointmentRecord record = appointmentRecords[index];

    char confirm;
    printf("\n确认取消以下预约吗？(y/其他取消)\n");
    printf("患者: %s\n科室: %s\n医生: %s\n时间: 星期%d %s\n",
           record.patientName,
           record.deptName,
           record.docName,
           record.dayOfWeek,
           record.timeOfDay == 0 ? "上午" : "下午");
    printf("请确认: ");
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
            printf("取消成功！号源已释放\n");
        } else {
            printf("取消完成（注：未能恢复号源，可能科室或医生信息已变更）\n");
        }
    } else {
        printf("操作已取消\n");
    }
}



void makeAppointment(char patientName[], char phoneNumber[], int deptChoice, int docChoice, int dayOfWeek, int timeOfDay) {
    
    if(strcmp(patientName, "0") == 0 || strcmp(phoneNumber, "0") == 0 || dayOfWeek == 0) {
        printf("已取消预约\n");
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
            printf("错误：您已预约过该时段\n");
            return;
        }
    }

    
    if (departments[deptChoice-1].doctors[docChoice-1].appointments[dayOfWeek-1][timeOfDay] <= 0) {
        printf("该时段暂无号源\n");
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
        printf("预约成功！\n");
    } else {
        printf("预约失败：预约记录已满\n");
    }
}
	
	

