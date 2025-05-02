#include "hospital.h"



DiseaseMap diseaseDatabase[MAX_DISEASES] = {
  
    {"θ����", "�ڿ�-������"},
    {"θ����", "�ڿ�-������"},
    {"θ��", "�ڿ�-������"},
    {"��Ӳ��", "�ڿ�-������"},
    {"��������Ѫ", "�ڿ�-������"},
    {"���׼��ۺ���", "�ڿ�-������"},


    {"���Ĳ�", "�ڿ�-��Ѫ�ܿ�"},
    {"�Ľ�ʹ", "�ڿ�-��Ѫ�ܿ�"},
    {"�ļ�����", "�ڿ�-��Ѫ�ܿ�"},
    {"����ʧ��", "�ڿ�-��Ѫ�ܿ�"},
    {"��Ѫѹ", "�ڿ�-��Ѫ�ܿ�"},
    {"����Ӳ��", "�ڿ�-��Ѫ�ܿ�"},


    {"����", "�ڿ�-������"},
    {"����", "�ڿ�-������"},
    {"���������Էμ���", "�ڿ�-������"},
    {"�ν��", "�ڿ�-������"},
    {"������", "�ڿ�-������"},
    {"��Ĥ��", "�ڿ�-������"},

 
    {"����", "���-�ǿ�"},
    {"��������", "���-�ǿ�"},
    {"��׵����ͻ��", "���-�ǿ�"},
    {"�ؽ���", "���-�ǿ�"},
    {"������", "���-�ǿ�"},
    {"��׵��", "���-�ǿ�"},


    {"��β��", "���-�����"},
    {"����", "���-�����"},
    {"���ҽ�ʯ", "���-�����"},
    {"������", "���-�����"},
    {"���ٰ�", "���-�����"},
    {"��״�ٽ��", "���-�����"},


    {"������", "���-�����"},
    {"�Գ�Ѫ", "���-�����"},
    {"������", "���-�����"},
    {"�Ի�ˮ", "���-�����"},
    {"����ɭ��", "���-�����"},
    {"������ʹ", "���-�����"},

};

int diseaseCount = 36;  

void normalizeDepartment(const char *input, char *output) {
    char buffer[100];
    int j = 0;
    
   
    for (int i = 0; input[i] != '\0'; i++) {
        if (isalpha((unsigned char)input[i]) || 
            isdigit((unsigned char)input[i]) || 
            input[i] == ' ' || 
            input[i] == '-') {
            buffer[j++] = tolower(input[i]);
        }
    }
    buffer[j] = '\0';

 
    j = 0;
    char prev = '\0';
    for (int i = 0; buffer[i] != '\0'; i++) {
        if (buffer[i] == ' ' || buffer[i] == '_' || buffer[i] == ',') {
            if (prev != '-') {
                output[j++] = '-';
                prev = '-';
            }
        } else {
            output[j++] = buffer[i];
            prev = buffer[i];
        }
    }
    output[j] = '\0';

 
    const char *prefix = "�ڿ�";
    if (strstr(output, "���") || 
        strstr(output, "�ǿ�") || 
        strstr(output, "����") || 
        strstr(output, "�����")) {
        prefix = "���";
    }


    if (!strstr(output, "�ڿ�") && !strstr(output, "���")) {
        char temp[100];
        if (strstr(output, "����")) sprintf(temp, "%s-������", prefix);
        else if (strstr(output, "��Ѫ��")) sprintf(temp, "%s-��Ѫ�ܿ�", prefix);
        else if (strstr(output, "����")) sprintf(temp, "%s-������", prefix);
        else if (strstr(output, "�ǿ�")) strcpy(temp, "���-�ǿ�");
        else if (strstr(output, "����")) strcpy(temp, "���-�����");
        else if (strstr(output, "�����")) strcpy(temp, "���-�����");
        else {
            strcpy(temp, output); 
            return;
        }
        strcpy(output, temp);
    }


    if (output[0] == '-') memmove(output, output+1, strlen(output));
}




void diseaseManagement() {
    int choice;
    do {
        printf("\n=== ��������� ===\n");
        printf("1. ��Ӽ�����Ӧ��ϵ\n");
        printf("2. �޸����м�������\n");
        printf("3. ɾ��������Ŀ\n");
        printf("4. �鿴ȫ��������Ӧ\n");
        printf("0. �����ϼ��˵�\n");
        printf("��ѡ�����: ");
        
        if(scanf("%d", &choice) != 1) {
            while(getchar() != '\n');
            printf("������Ч��������ѡ��\n");
            continue;
        }

        switch (choice) {
            case 1: {
    char newDisease[50] = {0}, rawDept[50] = {0}, normalizedDept[50] = {0};
    
    printf("\n�����뼲�����ƣ�0���أ�: ");
    if(scanf("%49s", newDisease) != 1) {
        printf("������Ч\n");
        break;
    }
    if(strcmp(newDisease, "0") == 0) break;

    printf("�������Ӧ���ң�0���أ�: ");
    if(scanf("%49s", rawDept) != 1) {
        printf("������Ч\n");
        break;
    }
    if(strcmp(rawDept, "0") == 0) break;

    
    normalizeDepartment(rawDept, normalizedDept);
    
    int deptValid = 0;
    for(int i=0; i<departmentCount; i++){
   
        if(strstr(departments[i].name, normalizedDept) || 
           strstr(normalizedDept, departments[i].name)) {
            strcpy(normalizedDept, departments[i].name);
            deptValid = 1;
            break;
        }
    }

    if(!deptValid){
        printf("�����޷�ʶ����ҡ�%s������ʹ�ñ�׼��ʽ���磺�ڿ�-�����ƣ�\n", rawDept);
        printf("��ǰ��Ч���ң�\n");
        for(int i=0; i<departmentCount; i++){
            printf("- %s\n", departments[i].name);
        }
        break;
    }

   
    int deptDiseaseCount = 0;
    for(int i=0; i<diseaseCount; i++){
        if(strcmp(diseaseDatabase[i].department, normalizedDept) == 0){ 
            deptDiseaseCount++;
        }
    }
    if(deptDiseaseCount >= MAX_DEPT_DISEASES){
        printf("���󣺸ÿ��Ҽ��������Ѵ����ޣ�%d�֣�\n", MAX_DEPT_DISEASES);
        break;
    }

   
    strcpy(diseaseDatabase[diseaseCount].disease, newDisease);
    strcpy(diseaseDatabase[diseaseCount].department, normalizedDept);
    diseaseCount++;
    printf("��ӳɹ�����׼���������ƣ�%s\n", normalizedDept);
    break;
}
            case 2: {
                
                printf("\n=== �������Ҷ�Ӧ�� ===\n");
                char *mainDepartments[] = {
                    "�ڿ�-������", "�ڿ�-��Ѫ�ܿ�", "�ڿ�-������",
                    "���-�ǿ�", "���-�����", "���-�����"
                };
                const int deptCount = 6;

               
                int colWidths[6] = {0};
                for(int d=0; d<deptCount; d++){
                    int deptNameLen = strlen(mainDepartments[d]) * 2;
                    colWidths[d] = deptNameLen;
                    
                    for(int i=0; i<diseaseCount; i++){
                        if(strcmp(diseaseDatabase[i].department, mainDepartments[d]) == 0){
                            int diseaseLen = strlen(diseaseDatabase[i].disease) * 2;
                            if(diseaseLen > colWidths[d]){
                                colWidths[d] = diseaseLen;
                            }
                        }
                    }
                    colWidths[d] += 4;
                }

               
                for(int d=0; d<deptCount; d++){
                    printf("%-*s", colWidths[d], mainDepartments[d]);
                }
                printf("\n");

                
                struct DeptDiseases {
                    int indexes[10];
                    char diseases[10][50];
                    int count;
                } deptData[6] = {0};

                for(int d=0; d<deptCount; d++){
                    for(int i=0; i<diseaseCount; i++){
                        if(strcmp(diseaseDatabase[i].department, mainDepartments[d]) == 0){
                            strcpy(deptData[d].diseases[deptData[d].count], diseaseDatabase[i].disease);
                            deptData[d].indexes[deptData[d].count] = i;
                            deptData[d].count++;
                        }
                    }
                }

                
                int globalIndex = 1;
                for(int line=0; line<10; line++) {
                    for(int d=0; d<deptCount; d++){ 
                        if(line < deptData[d].count){
                            printf("%2d.%-*s", 
                                globalIndex++,
                                colWidths[d]-3,
                                deptData[d].diseases[line]);
                        } else {
                            printf("%-*s", colWidths[d], "");
                        }
                    }
                    printf("\n");
                }

                
                int selectedIndex;
                printf("\n��ѡ��Ҫ�޸ĵļ�����ţ�0���أ�: ");
                if(scanf("%d", &selectedIndex) != 1) {
                    while(getchar() != '\n');
                    printf("������Ч\n");
                    break;
                }
                if(selectedIndex == 0) break;

                if(selectedIndex<1 || selectedIndex>diseaseCount){
                    printf("��Ч�ı��\n");
                    break;
                }

                int originalIndex = selectedIndex - 1;
                char currentDisease[50], currentDept[50];
                strcpy(currentDisease, diseaseDatabase[originalIndex].disease);
                strcpy(currentDept, diseaseDatabase[originalIndex].department);

                
                char newDisease[50] = {0};
                printf("\n��ǰ��������: %s\n", currentDisease);
                printf("���������ƣ�ֱ�ӻس�������: ");
                getchar();
                fgets(newDisease, 50, stdin);
                newDisease[strcspn(newDisease, "\n")] = '\0';
                
                if(strlen(newDisease) > 0) {
                    
                    int exists = 0;
                    for(int i=0; i<diseaseCount; i++){
                        if(i != originalIndex && strcmp(diseaseDatabase[i].disease, newDisease) == 0){
                            exists = 1;
                            break;
                        }
                    }
                    if(exists){
                        printf("���󣺼��������Ѵ���\n");
                        break;
                    }
                    strcpy(diseaseDatabase[originalIndex].disease, newDisease);
                }

                
                char newDept[50] = {0};
                printf("\n��ǰ����: %s\n", currentDept);
                printf("�����¿��ң�ֱ�ӻس�������: ");
                fgets(newDept, 50, stdin);
                newDept[strcspn(newDept, "\n")] = '\0';

                if(strlen(newDept) > 0) {
                    
                    int deptValid = 0;
                    for(int i=0; i<departmentCount; i++){
                        if(strcmp(departments[i].name, newDept) == 0){
                            deptValid = 1;
                            break;
                        }
                    }
                    if(!deptValid){
                        printf("���󣺿��Ҳ�����\n");
                        
                        if(strlen(newDisease)>0) strcpy(diseaseDatabase[originalIndex].disease, currentDisease);
                        break;
                    }

                    
                    int deptDiseaseCount = 0;
                    for(int i=0; i<diseaseCount; i++){
                        if(strcmp(diseaseDatabase[i].department, newDept) == 0){
                            deptDiseaseCount++;
                        }
                    }
                    if(deptDiseaseCount >= 6){
                        printf("���󣺸ÿ�������6�ּ���\n");
                        
                        if(strlen(newDisease)>0) strcpy(diseaseDatabase[originalIndex].disease, currentDisease);
                        break;
                    }

                    strcpy(diseaseDatabase[originalIndex].department, newDept);
                }

                printf("�޸ĳɹ���\n");
                break;
            }

           case 3: {
    printf("\n=== �������Ҷ�Ӧ�� ===\n");
    char *mainDepartments[] = {
        "�ڿ�-������", "�ڿ�-��Ѫ�ܿ�", "�ڿ�-������",
        "���-�ǿ�", "���-�����", "���-�����"
    };
    const int deptCount = 6;

    
    int colWidths[6] = {0};
    for(int d=0; d<deptCount; d++){
        
        colWidths[d] = strlen(mainDepartments[d])*2 + 4;
        
       
        for(int i=0; i<diseaseCount; i++){
            if(strcmp(diseaseDatabase[i].department, mainDepartments[d]) == 0){
                int len = strlen(diseaseDatabase[i].disease)*2 + 4; 
                if(len > colWidths[d]) colWidths[d] = len;
            }
        }
    }

   
    for(int d=0; d<deptCount; d++){
        printf("%-*s", colWidths[d], mainDepartments[d]);
    }
    printf("\n");

   
    struct DeptDiseases {
        int indexes[10];  
        char diseases[10][50];
        int count;
    } deptData[6] = {0};

   
    for(int d=0; d<deptCount; d++){
        for(int i=0; i<diseaseCount; i++){
            if(strcmp(diseaseDatabase[i].department, mainDepartments[d]) == 0){
                strcpy(deptData[d].diseases[deptData[d].count], diseaseDatabase[i].disease);
                deptData[d].indexes[deptData[d].count] = i; 
                deptData[d].count++;
            }
        }
    }

    
    int maxLines = 0;
    for(int d=0; d<deptCount; d++){
        if(deptData[d].count > maxLines) maxLines = deptData[d].count;
    }
    
    int globalIndex = 1;
    for(int line=0; line<maxLines; line++){
        for(int d=0; d<deptCount; d++){ 
            if(line < deptData[d].count){
                printf("%2d.%-*s", 
                      globalIndex++,
                      colWidths[d]-3,
                      deptData[d].diseases[line]);
            } else {
                printf("%-*s", colWidths[d], "");
            }
        }
        printf("\n");
    }

   
    int index;
    printf("\n��ѡ��Ҫɾ������Ŀ��ţ�0���أ�: ");
                if(scanf("%d", &index) != 1) {
                    while(getchar() != '\n');
                    printf("������Ч\n");
                    break;
                }
                if(index == 0) break;

                if(index<1 || index>diseaseCount){
                    printf("��Ч�ı��\n");
                    break;
                }

                char confirm;
                printf("ȷ��ɾ����%s����(y/����ȡ��): ", diseaseDatabase[index-1].disease);
                scanf(" %c", &confirm);
                if(tolower(confirm) != 'y') {
                    printf("������ȡ��\n");
                    break;
                }

               
                for(int i=index-1; i<diseaseCount-1; i++){
                    diseaseDatabase[i] = diseaseDatabase[i+1];
                }
                diseaseCount--;
                printf("ɾ���ɹ���\n");
                break;
            }

            case 4: {
                printf("\n=== �������Ҷ�Ӧ�� ===\n");
                char *mainDepartments[] = {
                    "�ڿ�-������", "�ڿ�-��Ѫ�ܿ�", "�ڿ�-������",
                    "���-�ǿ�", "���-�����", "���-�����"
                };
                const int deptCount = 6;

            
                int colWidths[6] = {0};
                for(int d=0; d<deptCount; d++){
                    int deptNameLen = strlen(mainDepartments[d]) * 2;
                    colWidths[d] = deptNameLen;
                    
                    for(int i=0; i<diseaseCount; i++){
                        if(strcmp(diseaseDatabase[i].department, mainDepartments[d]) == 0){
                            int diseaseLen = strlen(diseaseDatabase[i].disease) * 2;
                            if(diseaseLen > colWidths[d]){
                                colWidths[d] = diseaseLen;
                            }
                        }
                    }
                    colWidths[d] += 4;
                }

                
                for(int d=0; d<deptCount; d++){
                    printf("%-*s", colWidths[d], mainDepartments[d]);
                }
                printf("\n");

                struct DeptDiseases {
                    char diseases[10][50];
                    int count;
                } deptData[6] = {0};

                for(int d=0; d<deptCount; d++){
                    for(int i=0; i<diseaseCount; i++){
                        if(strcmp(diseaseDatabase[i].department, mainDepartments[d]) == 0){
                            strcpy(deptData[d].diseases[deptData[d].count], diseaseDatabase[i].disease);
                            deptData[d].count++;
                        }
                    }
                }

                
                int maxLines = 0;
for(int d=0; d<deptCount; d++){
    if(deptData[d].count > maxLines){
        maxLines = deptData[d].count;
    }
}
for(int line=0; line<maxLines; line++){
                    for(int d=0; d<deptCount; d++){ 
                        if(line < deptData[d].count){
                            printf("%2d.%-*s", 
                                line+1,
                                colWidths[d]-3,
                                deptData[d].diseases[line]);
                        } else {
                            printf("%-*s", colWidths[d], "");
                        }
                    }
                    printf("\n");
                }

                printf("�����������...");
                getchar();
                getchar();
                break;
            }

            case 0:
                printf("�����ϼ��˵�\n");
                break;

            default:
                printf("��Ч��ѡ��\n");
                break;
        }
    } while (choice != 0);
}



void searchByDisease(int isDeveloperMode) {
    char disease[50];
    printf("\n�����뼲�����ƣ�0���أ�: ");
    scanf("%s", disease);
    
    if(strcmp(disease, "0") == 0) return;

    
    char targetDept[50] = "";
    for(int i=0; i<diseaseCount; i++){
        if(strcmp(diseaseDatabase[i].disease, disease) == 0){
            strcpy(targetDept, diseaseDatabase[i].department);
            break;
        }
    }

    if(strlen(targetDept) == 0){
        printf("δ�ҵ���ؿ�����Ϣ��������ѯ����̨\n");
        if(isDeveloperMode){
            printf("[��������ʾ] ��ǰ�������������Ӷ�Ӧ��ϵ\n");
        }
        return;
    }

 printf("\n��%s�����ڡ�%s��\n", disease, targetDept);
    
    int deptIndex = -1;
    for(int i=0; i<departmentCount; i++){
        if(strcmp(departments[i].name, targetDept) == 0){
            deptIndex = i;
            break;
        }
    }

    if(deptIndex == -1){
        printf("��ǰû�п����ר��\n");
        return;
    }

    
    Department *dept = &departments[deptIndex];
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
                  COL_WIDTH - (int)(strlen("��X��ҽ����")/3*2 + 1)*2, 
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
                  COL_WIDTH - LABEL_WIDTH - 4, "");
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

    
    if (!isDeveloperMode) {
        int docChoice;
        
        while(1){
            printf("\n��ѡ��ҽ���鿴���飨0���أ�: ");
            if(scanf("%d", &docChoice) != 1){
                printf("�����ʽ����\n");
                while(getchar() != '\n');
                continue;
            }
            if(docChoice == 0) return;
            if(docChoice<1 || docChoice>departments[deptIndex].doctorCount){
                printf("��Ч��ѡ�����������룡\n");
                continue;
            }
            break;
        }

        Doctor doc = departments[deptIndex].doctors[docChoice-1];
        
        printf("\n=== ҽ������ ===\n");
        printf("������%s\nְ�ƣ�%s\n", doc.name, doc.title);
        printf("רҵ����%s\n", doc.specialty);
        printf("�Һŷѣ�%.1fԪ\n", doc.fee);
        
        
        printf("\n��ԤԼʱ�䣺\n");
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
        if(!hasAvailable){
            printf("���ں�Դ����\n");
            return;
        }

        char confirm;
        printf("\n�Ƿ�����ԤԼ��(y/��������): ");
        scanf(" %c", &confirm);
        if(tolower(confirm) != 'y') return;

        
        char name[50], phone[20];
        printf("����������: ");
        scanf("%s", name);
        do {
    printf("��������ϵ�绰��11λ���֣�0���أ�: ");
    scanf("%s", phone);
    if(strcmp(phone, "0") == 0) return;
    
    if(strlen(phone) != 11) {
        printf("�ֻ��ű���Ϊ11λ��\n");
        continue;
    }
    
    int valid = 1;
    for(int i=0; i<11; i++){
        if(!isdigit(phone[i])){
            valid = 0;
            break;
        }
    }
    
    if(!valid){
        printf("�ֻ��ű���ȫΪ���֣�\n");
        continue;
    }
    
    break;
} while(1);

        
        int dayInput, timeInput;
        while(1){
            
            while(1){
                printf("��ѡ�����ڣ�1-7��Ӧ��һ�����գ�0���أ�: ");
                if(scanf("%d", &dayInput) != 1){
                    printf("�����ʽ�������������֣�\n");
                    while(getchar() != '\n');
                    continue;
                }
                if(dayInput == 0) return;
                if(dayInput<1 || dayInput>7){
                    printf("������1-7֮������֣�\n");
                    continue;
                }
                break;
            }

            
            while(1){
                printf("��ѡ��ʱ��Σ�����0������1���������أ�: ");
                if(scanf("%d", &timeInput) != 1){
                    printf("�����ʽ�������������֣�\n");
                    while(getchar() != '\n');
                    continue;
                }
                if(timeInput<0 || timeInput>1){
                    printf("������0��1��\n");
                    continue;
                }
                break;
            }

            
            int dayIndex = dayInput - 1;
            if(doc.appointments[dayIndex][timeInput] > 0){
                break;
            }else{
                printf("��ʱ�����޺�Դ��������ѡ��\n");
            }
        }

       
        makeAppointment(name, phone, deptIndex+1, docChoice, dayInput, timeInput);
        printf("ԤԼ�ɹ���\n");
    } else {
        
        printf("\n�����������...");
        getchar();
        getchar();
    }
}
