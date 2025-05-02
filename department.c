#include "hospital.h"

Department departments
[MAX_DEPARTMENTS];
int departmentCount = 0;


void initDepartments() {
    
    char *deptNames[] = {
        "�ڿ�-������", "�ڿ�-��Ѫ�ܿ�", "�ڿ�-������",
        "���-�ǿ�", "���-�����", "���-�����"
    };
    const int initialDeptCount = sizeof(deptNames)/sizeof(deptNames[0]);

    
    char *deptDoctors[][2] = {
        {"�Ž���", "����"},    
        {"��º�", "������"},    
        {"��־ǿ", "����Ӣ"},    
        {"�ܽ���", "������"},   
        {"���ǿ", "������"},    
        {"�ｨ��", "����÷"}     
    };

    
    char *specialties[][3] = {
        {"θ��", "��Ӳ��", "����������"},
        {"���Ĳ�", "����Ӳ��", "����˥��"},
        {"����", "����", "���������Էμ���"},
        {"����", "�ؽ��û�", "�������"},
        {"��β��", "����", "θ������"},
        {"������", "��Ѫ�ܲ�", "�񾭴���"}
    };

    
    int appointmentTemplates[6][2][7][2] = {
        
        { 
            {
                {5,5}, 
                {0,0}, 
                {5,5}, 
                {0,0}, 
                {5,5}, 
                {0,0}, 
                {0,0}  
            },
            {
                {0,0}, 
                {5,5}, 
                {0,0}, 
                {5,5}, 
                {0,0}, 
                {5,5}, 
                {0,0}  
            }
        },
        
        {
            {
                {5,5}, {0,0}, {5,5}, {0,0}, {5,5}, {0,0}, {0,0}
            },
            {
                {0,0}, {5,0}, {0,0}, {5,0}, {0,0}, {0,0}, {0,0} 
            }
        },
        
        {
            {
                {0,5}, {5,0}, {0,5}, {5,0}, {0,5}, {0,0}, {0,0}
            },
            {
                {5,0}, {0,5}, {5,0}, {0,5}, {5,0}, {0,0}, {0,0}
            }
        },
        
        {
            {
                {5,0}, {5,0}, {5,0}, {0,0}, {0,0}, {0,0}, {0,0}
            },
            {
                {0,0}, {0,0}, {0,0}, {5,5}, {5,5}, {0,0}, {0,0}
            }
        },
        
        {
            {
                {0,0}, {0,0}, {0,0}, {5,5}, {5,5}, {5,5}, {0,0}
            },
            {
                {5,5}, {5,5}, {5,5}, {0,0}, {0,0}, {0,0}, {0,0}
            }
        },
        
        {
            {
                {5,0}, {5,0}, {5,0}, {5,0}, {5,0}, {0,0}, {0,0}
            },
            {
                {0,5}, {0,5}, {0,5}, {0,5}, {0,5}, {0,0}, {0,0}
            }
        }
    };

    
    char *reviewPool[] = {
        "����ϸ�£��������", "����Ч���ã��Ƽ�", "�ǳ�������",
        "��ҩ��׼�����ﰲ�ź���", "����ʱ���Գ���ֵ��", "���������ر����",
        "��齨��ǳ�רҵ", "����������������", "������úܼ�ʱ",
        "���׼ȷ����ҩ�����Ժ�ת", "�Զ�ͯ���ߺ��а취", "���Ʒ���������Ч"
    };

    srand(time(NULL));
    
    
    for (int i = 0; i < initialDeptCount; i++) {
        
        strcpy(departments[i].name, deptNames[i]);
        departments[i].doctorCount = 2;

        
        for (int j = 0; j < 2; j++) {
            Doctor *doc = &departments[i].doctors[j];
            
            
            strcpy(doc->name, deptDoctors[i][j]);
            
            
            char *titles[] = {"����ҽʦ", "������ҽʦ", "����ҽʦ"};
            int titleIndex = (j == 0) ? 0 : 1; 
            strcpy(doc->title, titles[titleIndex]);
            doc->fee = (titleIndex == 0) ? 50.0 : 30.0;
            
            
            strcpy(doc->specialty, specialties[i][j%3]);
            
           
            doc->age = (titleIndex == 0) ? 55 : 45;

           
            for(int d=0; d<7; d++){
                for(int t=0; t<2; t++){
                    doc->appointments[d][t] = appointmentTemplates[i][j][d][t];
                }
            }

            
            int used[12] = {0};
            for(int k=0; k<3; k++){
                int r;
                do { r = rand()%12; } while(used[r]);
                strcpy(doc->reviews[k], reviewPool[r]);
                used[r] = 1;
            }
        }

        
        for(int j=2; j<MAX_DOCTORS; j++){
            departments[i].doctors[j].name[0] = '\0';
        }
    }

    
    for(int i=initialDeptCount; i<MAX_DEPARTMENTS; i++){
        departments[i].name[0] = '\0';
        departments[i].doctorCount = 0;
    }

    departmentCount = initialDeptCount;
}



void showDepartmentsAndMakeAppointment() {
    printf("\n=== �����б� ===\n");
    for(int i=0; i<departmentCount; i++){ 
        printf("%d. %s", i+1, departments[i].name);
        if (departments[i].doctorCount == 0) {
            printf(" (��δ����)");
        }
        printf("\n");
    }
    
    int choice;
    printf("��ѡ����Ҳ鿴ר�ң�0���أ�: ");
    scanf("%d", &choice);
    
    if(choice == 0) return;
    
    if(choice >0 && choice <= departmentCount){
        Department *dept = &departments[choice-1];
        if(dept->doctorCount == 0) {
            printf("�ÿ�����δ���ţ�����ϵҽԺ������\n");
            return;
        }

        printf("\n=== %sר������ ===\n", dept->name);

        
        const int COL_WIDTH = 30;  
        const int LABEL_WIDTH = 8; 
        
        
        for(int j=0; j<dept->doctorCount; j+=4){ 
            Doctor *docs[4] = {0};
            int validCols = 0;
            
            
            for(int c=0; c<4; c++){
                if(j+c < dept->doctorCount){
                    docs[c] = &dept->doctors[j+c];
                    validCols++;
                }
            }

            
            for(int c=0; c<validCols; c++){
                printf("��%d��ҽ����%-*s", 
                      j+c+1, 
                      COL_WIDTH - (int)(strlen("��X��ҽ����")/3 * 2 + 1)*2, 
                      "");
            }
            printf("\n");

            
            for(int c=0; c<validCols; c++){
                printf("������%-*s", COL_WIDTH-6, docs[c]->name); 
            }
            printf("\n");

            
            for(int c=0; c<validCols; c++){
                printf("ְ�ƣ�%-*s", COL_WIDTH-6, docs[c]->title);
            }
            printf("\n");

            
            for(int c=0; c<validCols; c++){
                printf("רҵ��%-*s", COL_WIDTH-6, docs[c]->specialty);
            }
            printf("\n");

            
            for(int c=0; c<validCols; c++){
                printf("�Һŷѣ�%-.1fԪ%-*s", 
                      docs[c]->fee,
                      COL_WIDTH - LABEL_WIDTH - 4,
                      "");
            }
            printf("\n");

            
            char *days[] = {"��һ","�ܶ�","����","����","����","����","����"};
            char timeSlots[4][6][30]; 
            int slotCounts[4] = {0};
            
            
            for(int c=0; c<validCols; c++){
                for(int d=0; d<7 && slotCounts[c]<6; d++){
                    for(int t=0; t<2; t++){
                        if(docs[c]->appointments[d][t] > 0){
                            snprintf(timeSlots[c][slotCounts[c]], 30, "%s%s ʣ%2d��",
                                   days[d], t==0?"����":"����", docs[c]->appointments[d][t]);
                            slotCounts[c]++;
                        }
                    }
                }
                if(slotCounts[c] == 0){
                    strcpy(timeSlots[c][0], "���޺�Դ");
                    slotCounts[c] = 1;
                }
            }

            
            for(int line=0; line<4; line++){
                for(int c=0; c<validCols; c++){
                    if(line < slotCounts[c]){
                        printf("%-*s", COL_WIDTH, timeSlots[c][line]);
                    }else{
                        printf("%-*s", COL_WIDTH, "");
                    }
                }
                printf("\n");
            }
            printf("\n");
        }


        
        int docChoice;
        printf("\n������ҪԤԼ��ҽ����ţ�0���أ�: ");
        scanf("%d", &docChoice);
        
        if(docChoice == 0) return;
        if(docChoice <1 || docChoice > dept->doctorCount){
            printf("��Ч��ҽ�����\n");
            return;
        }

        Doctor *doc = &dept->doctors[docChoice-1];
        
        
        int dayInput, timeInput;
        printf("��ѡ�����ڣ�1-7��Ӧ��һ�����գ�0���أ�: ");
        if(scanf("%d", &dayInput) != 1 || dayInput < 0 || dayInput > 7){
            printf("������Ч\n");
            while(getchar() != '\n'); 
            return;
        }
        if(dayInput == 0) return;
        int dayIndex = dayInput - 1;

        printf("��ѡ��ʱ��Σ�����0������1���������أ�: ");
        if(scanf("%d", &timeInput) != 1 || timeInput < 0 || timeInput > 1){
            printf("������Ч\n");
            while(getchar() != '\n');
            return;
        }

       
        if(doc->appointments[dayIndex][timeInput] <= 0){
            printf("��ʱ�����޺�Դ\n");
            return;
        }

        
        char patientName[50], phoneNumber[20];
        printf("�����뻼��������0���أ�: ");
        scanf("%s", patientName);
        if(strcmp(patientName, "0") == 0) return;

       do {
    printf("��������ϵ�绰��11λ���֣�0���أ�: ");
    scanf("%s", phoneNumber);
    if(strcmp(phoneNumber, "0") == 0) return;
    
    if(strlen(phoneNumber) != 11) {
        printf("�ֻ��ű���Ϊ11λ��,�Ҿ�Ϊ����\n");
        continue;
    }
    
    int valid = 1;
    for(int i=0; i<11; i++){
        if(!isdigit(phoneNumber[i])){
            valid 
= 0;
            break;
        }
    }
    
    if(!valid){
        printf("�ֻ��ű���ȫΪ���֣�\n");
        continue;
    }
    
    break;
} while(1);

        
        char *days[] = {"��һ","�ܶ�","����","����","����","����","����"};
        printf("\nȷ��ԤԼ:\n");
        printf("ҽ��: %s (%d��ҽ��)\n", doc->name, docChoice);
        printf("ʱ��: %s %s\n", days[dayIndex], timeInput==0?"����":"����");
        printf("����: %s\n", patientName);
        printf("�绰: %s\n", phoneNumber);
        
        char confirm;
        printf("�Ƿ�ȷ�ϣ�(y/n): ");
        scanf(" %c", &confirm);
        
        if(tolower(confirm) == 'y'){
    
    makeAppointment(patientName, 
                    phoneNumber, 
                    choice,         
                    docChoice,      
                    dayIndex + 1,   
                    timeInput);     
}else{
    printf("��ȡ��ԤԼ\n");
}
    }else{
        printf("��Ч��ѡ��\n");
    }
}



	void addDepartment() {
	    if (departmentCount >= MAX_DEPARTMENTS) {
	        printf("���������Ѵ����ޣ�%d��\n", MAX_DEPARTMENTS);
	        return;
	    }
	    
	    char name[50];
	    printf("�������¿�������: ");
	    scanf("%s", name);
	    
	    
	    for (int i = 0; i < departmentCount; i++) {
	        if (strcmp(departments[i].name, name) == 0) {
	            printf("�ÿ����Ѵ���\n");
	            return;
	        }
	    }
	    
	    strcpy(departments[departmentCount].name, name);
	    departments[departmentCount].doctorCount = 0;
	    departmentCount++;
	    printf("������ӳɹ���\n");
	}
	
	
	
		void modifyDoctor() {
	    printf("\n=== �޸�ҽ����Ϣ ===\n");
	    
	    
	    printf("��ѡ����Ҫ�޸ĵ�ҽ����������:\n");
	    for (int i = 0; i < departmentCount; i++) {
	        printf("%d. %s\n", i+1, departments[i].name);
	    }
	    int deptChoice;
	    printf("������ұ�ţ�0���أ�: ");
	    scanf("%d", &deptChoice);
	    if (deptChoice < 1 || deptChoice > departmentCount) return;
	
	    Department *dept = &departments[deptChoice-1];
	    
	    
	    printf("\n=== %sר���б� ===\n", dept->name);
	    for (int j = 0; j < dept->doctorCount; j++) {
	        printf("%d. %s\n", j+1, dept->doctors[j].name);
	    }
	    int docChoice;
	    printf("����ҽ����ţ�0���أ�: ");
	    scanf("%d", &docChoice);
	    if (docChoice < 1 || docChoice > dept->doctorCount) return;
	
	    Doctor *doc = &dept->doctors[docChoice-1];
	    
	    int option;
	    do {
	        printf("\n��ѡ��Ҫ�޸ĵ���Ϣ��:\n");
	        printf("1.���� 2.���� 3.ְ�� 4.רҵ 5.�Һŷ� 6.���� 0.����\nѡ��: ");
	        scanf("%d", &option);
	
	        switch(option) {
	            case 1: {
	                printf("��ǰ����: %s\n������: ", doc->name);
	                scanf("%s", doc->name);
	                printf("�����޸ĳɹ�\n");
	                break;
	            }
	            case 2: {
	                printf("��ѡ���¿���:\n");
	                for (int i = 0; i < departmentCount; i++) {
	                    printf("%d. %s\n", i+1, departments[i].name);
	                }
	                int newDeptChoice;
	                printf("�����¿��ұ�ţ�0ȡ����: ");
	                scanf("%d", &newDeptChoice);
	                
	                if (newDeptChoice > 0 && newDeptChoice <= departmentCount) {
	                    Department *newDept = &departments[newDeptChoice-1];
	                    if (newDept->doctorCount >= MAX_DOCTORS) {
	                        printf("Ŀ���������\n");
	                        break;
	                    }
	                    
	                    
	                    newDept->doctors[newDept->doctorCount++] = *doc;
	                   
	                    for (int j = docChoice-1; j < dept->doctorCount-1; j++) {
	                        dept->doctors[j] = dept->doctors[j+1];
	                    }
	                    dept->doctorCount--;
	                    
	                    
	                    for (int i = 0; i < recordCount; i++) {
	                        if (strcmp(appointmentRecords[i].docName, doc->name) == 0) {
	                            strcpy(appointmentRecords[i].deptName, newDept->name);
	                        }
	                    }
	                    printf("�����޸ĳɹ�\n");
	                    return; 
	                }
	                break;
	            }
	            case 3: {
	                printf("��ǰְ��: %s\n��ְ��: ", doc->title);
	                scanf("%s", doc->title);
	                printf("ְ���޸ĳɹ�\n");
	                break;
	            }
	            case 4: {
	                printf("��ǰרҵ: %s\n��רҵ: ", doc->specialty);
	                scanf("%s", doc->specialty);
	                printf("רҵ�޸ĳɹ�\n");
	                break;
	            }
	            case 5: {
	                printf("��ǰ�Һŷ�: %.1f\n�¹Һŷ�: ", doc->fee);
	                scanf("%f", &doc->fee);
	                printf("�Һŷ��޸ĳɹ�\n");
	                break;
	            }
	            case 6: {
	                printf("��ǰ����:\n");
	                for (int i = 0; i < 3; i++) {
	                    printf("%d. %s\n", i+1, doc->reviews[i]);
	                }
	                int reviewChoice;
	                printf("ѡ��Ҫ�޸ĵ����ۣ�1-3, 0ȡ����: ");
	                scanf("%d", &reviewChoice);
	                
	                if (reviewChoice >= 1 && reviewChoice <= 3) {
	                    printf("����������: ");
	                    getchar(); 
	                    fgets(doc->reviews[reviewChoice-1], 100, stdin);
	                    doc->reviews[reviewChoice-1][strcspn(doc->reviews[reviewChoice-1], "\n")] = 0; 
	                    printf("�����޸ĳɹ�\n");
	                }
	                break;
	            }
	            case 0:
	                break;
	            default:
	                printf("��Ч��ѡ��\n");
	        }
	    } while (option != 0);
	}
	
	
	
		void deleteDoctor() {
	    printf("\n=== ɾ��ҽ����Ϣ ===\n");
	    for (int i = 0; i < departmentCount; i++) {
	        printf("%d. %s\n", i + 1, departments[i].name);
	    }
	    
	    int deptChoice;
	    printf("��ѡ��Ҫ�����Ŀ���(����0����): ");
	    scanf("%d", &deptChoice);
	    
	    if(deptChoice > 0 && deptChoice <= departmentCount){
	        Department *dept = &departments[deptChoice - 1];
	        
	        printf("\n=== %sר���б� ===\n", dept->name);
	        for(int j=0; j<dept->doctorCount; j++){
	            printf("%d. %s\n", j+1, dept->doctors[j].name);
	        }
	        
	        int docChoice;
	        printf("ѡ��Ҫɾ����ҽ�����: ");
	        scanf("%d", &docChoice);
	        
	        if(docChoice > 0 && docChoice <= dept->doctorCount){
	            
	            for(int i=recordCount-1; i>=0; i--){
	                if(strcmp(appointmentRecords[i].docName, dept->doctors[docChoice-1].name) == 0){
	                    
	                    for(int j=i; j<recordCount-1; j++){
	                        appointmentRecords[j] = appointmentRecords[j+1];
	                    }
	                    recordCount--;
	                }
	            }
	
	            
	            dept->doctors[docChoice-1] = dept->doctors[dept->doctorCount-1];
	            dept->doctorCount--;
	
	            printf("ҽ����Ϣɾ���ɹ���\n");
	        } else {
	            printf("��Ч��ѡ��\n");
	        }
	    }
	}
	
	
		void addDoctor() {
	    printf("\n=== ���ҽ����Ϣ ===\n");
	    for (int i = 0; i < departmentCount; i++) {
	        printf("%d. %s", i + 1, departments[i].name);
	        if (departments[i].doctorCount >= MAX_DOCTORS) {
	            printf(" (����)");
	        }
	        printf("\n");
	    }
	    
	    int deptChoice;
	    printf("��ѡ��Ҫ���ҽ���Ŀ���(����0����): ");
	    scanf("%d", &deptChoice);
	
	     if(deptChoice >0 && deptChoice <= departmentCount){
	        Department *dept = &departments[deptChoice - 1];
	        
	        if(dept->doctorCount >= MAX_DOCTORS) {
	            printf("�ÿ����Ѵ����ҽ��������%d��\n", MAX_DOCTORS);
	            return;
	        }
	        Doctor newDoc;
	        printf("������ҽ������: ");
	        scanf("%s", newDoc.name);
	        printf("������ҽ��ְ��(����ҽʦ/������ҽʦ/����ҽʦ): ");
	        scanf("%s", newDoc.title);
	        printf("������ҽ��רҵ����: ");
	        scanf("%s", newDoc.specialty);
	        printf("������Һŷ�: ");
	        scanf("%f", &newDoc.fee);
	        newDoc.age = 35 + ((strcmp(newDoc.title, "����ҽʦ") == 0) ? 0 : 
	                         (strcmp(newDoc.title, "������ҽʦ") == 0) ? 5 : 10) + rand()%5;
	
	        
	        for(int d=0; d<7; d++){
	            for(int t=0; t<2; t++){
	                newDoc.appointments[d][t] = (rand()%2 == 0) ? 5 : 0;
	            }
	        }
	
	        
	        strcpy(newDoc.reviews[0], "���޻�������");
	        strcpy(newDoc.reviews[1], "");
	        strcpy(newDoc.reviews[2], "");
	
	        dept->doctors[dept->doctorCount++] = newDoc;
	        printf("ҽ����Ϣ��ӳɹ���\n");
	    } else if(deptChoice != 0) {
	        printf("��Ч��ѡ��\n");
	    }
	}
	
	
	
	
	
	
	
void searchDoctor() {
    char name[50];
    printf("������Ҫ���ҵ�ҽ������: ");
    scanf("%s", name);
    
    int found = 0;
    for(int i=0; i<departmentCount; i++) {
        for(int j=0; j<departments[i].doctorCount; j++) {
            Doctor doc = departments[i].doctors[j];
            if(strcmp(doc.name, name) == 0) {
                printf("\n=== ҽ����ϸ��Ϣ ===\n");
                printf("��������: %s\n", departments[i].name);
                printf("����: %s\n", doc.name);
                printf("ְ��: %s\n", doc.title);
                printf("רҵ����: %s\n", doc.specialty);
                printf("�Һŷ�: %.1fԪ\n", doc.fee);
                printf("����: %d\n", doc.age);
                
                printf("\n��ԤԼʱ��:\n");
                char *days[] = {"��һ","�ܶ�","����","����","����","����","����"};
                int hasAvailable = 0;
                for(int d=0; d<7; d++){
                    for(int t=0; t<2; t++){
                        if(doc.appointments[d][t] >0){
                            printf("%s %s��ʣ��%d��\n", 
                                  days[d], 
                                  t==0 ? "����" : "����", 
                                  doc.appointments[d][t]);
                            hasAvailable = 1;
                        }
                    }
                }
                if(!hasAvailable) printf("��ǰ�޿��ú�Դ\n");
                
                printf("\n��������:\n");
                for(int k=0; k<3; k++){
                    if(strlen(doc.reviews[k]) > 0)
                        printf("%d. %s\n", k+1, doc.reviews[k]);
                }
                found = 1;
                break;
            }
        }
        if(found) break;
    }
    if(!found) {
        printf("δ�ҵ���Ϊ %s ��ҽ��\n", name);
    }
}	
	
