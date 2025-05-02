#include "hospital.h"



DiseaseMap diseaseDatabase[MAX_DISEASES] = {
  
    {"胃肠炎", "内科-消化科"},
    {"胃溃疡", "内科-消化科"},
    {"胃炎", "内科-消化科"},
    {"肝硬化", "内科-消化科"},
    {"消化道出血", "内科-消化科"},
    {"肠易激综合征", "内科-消化科"},


    {"冠心病", "内科-心血管科"},
    {"心绞痛", "内科-心血管科"},
    {"心肌梗死", "内科-心血管科"},
    {"心律失常", "内科-心血管科"},
    {"高血压", "内科-心血管科"},
    {"动脉硬化", "内科-心血管科"},


    {"肺炎", "内科-呼吸科"},
    {"哮喘", "内科-呼吸科"},
    {"慢性阻塞性肺疾病", "内科-呼吸科"},
    {"肺结核", "内科-呼吸科"},
    {"肺气肿", "内科-呼吸科"},
    {"胸膜炎", "内科-呼吸科"},

 
    {"骨折", "外科-骨科"},
    {"骨质疏松", "外科-骨科"},
    {"腰椎间盘突出", "外科-骨科"},
    {"关节炎", "外科-骨科"},
    {"腱鞘炎", "外科-骨科"},
    {"颈椎病", "外科-骨科"},


    {"阑尾炎", "外科-普外科"},
    {"疝气", "外科-普外科"},
    {"胆囊结石", "外科-普外科"},
    {"肠梗阻", "外科-普外科"},
    {"胰腺癌", "外科-普外科"},
    {"甲状腺结节", "外科-普外科"},


    {"脑肿瘤", "外科-神经外科"},
    {"脑出血", "外科-神经外科"},
    {"脑外伤", "外科-神经外科"},
    {"脑积水", "外科-神经外科"},
    {"帕金森病", "外科-神经外科"},
    {"三叉神经痛", "外科-神经外科"},

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

 
    const char *prefix = "内科";
    if (strstr(output, "外科") || 
        strstr(output, "骨科") || 
        strstr(output, "普外") || 
        strstr(output, "神经外科")) {
        prefix = "外科";
    }


    if (!strstr(output, "内科") && !strstr(output, "外科")) {
        char temp[100];
        if (strstr(output, "消化")) sprintf(temp, "%s-消化科", prefix);
        else if (strstr(output, "心血管")) sprintf(temp, "%s-心血管科", prefix);
        else if (strstr(output, "呼吸")) sprintf(temp, "%s-呼吸科", prefix);
        else if (strstr(output, "骨科")) strcpy(temp, "外科-骨科");
        else if (strstr(output, "普外")) strcpy(temp, "外科-普外科");
        else if (strstr(output, "神经外科")) strcpy(temp, "外科-神经外科");
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
        printf("\n=== 疾病库管理 ===\n");
        printf("1. 添加疾病对应关系\n");
        printf("2. 修改现有疾病分类\n");
        printf("3. 删除疾病条目\n");
        printf("4. 查看全部疾病对应\n");
        printf("0. 返回上级菜单\n");
        printf("请选择操作: ");
        
        if(scanf("%d", &choice) != 1) {
            while(getchar() != '\n');
            printf("输入无效，请重新选择\n");
            continue;
        }

        switch (choice) {
            case 1: {
    char newDisease[50] = {0}, rawDept[50] = {0}, normalizedDept[50] = {0};
    
    printf("\n请输入疾病名称（0返回）: ");
    if(scanf("%49s", newDisease) != 1) {
        printf("输入无效\n");
        break;
    }
    if(strcmp(newDisease, "0") == 0) break;

    printf("请输入对应科室（0返回）: ");
    if(scanf("%49s", rawDept) != 1) {
        printf("输入无效\n");
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
        printf("错误：无法识别科室「%s」，请使用标准格式（如：内科-消化科）\n", rawDept);
        printf("当前有效科室：\n");
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
        printf("错误：该科室疾病数量已达上限（%d种）\n", MAX_DEPT_DISEASES);
        break;
    }

   
    strcpy(diseaseDatabase[diseaseCount].disease, newDisease);
    strcpy(diseaseDatabase[diseaseCount].department, normalizedDept);
    diseaseCount++;
    printf("添加成功！标准化科室名称：%s\n", normalizedDept);
    break;
}
            case 2: {
                
                printf("\n=== 疾病科室对应表 ===\n");
                char *mainDepartments[] = {
                    "内科-消化科", "内科-心血管科", "内科-呼吸科",
                    "外科-骨科", "外科-普外科", "外科-神经外科"
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
                printf("\n请选择要修改的疾病编号（0返回）: ");
                if(scanf("%d", &selectedIndex) != 1) {
                    while(getchar() != '\n');
                    printf("输入无效\n");
                    break;
                }
                if(selectedIndex == 0) break;

                if(selectedIndex<1 || selectedIndex>diseaseCount){
                    printf("无效的编号\n");
                    break;
                }

                int originalIndex = selectedIndex - 1;
                char currentDisease[50], currentDept[50];
                strcpy(currentDisease, diseaseDatabase[originalIndex].disease);
                strcpy(currentDept, diseaseDatabase[originalIndex].department);

                
                char newDisease[50] = {0};
                printf("\n当前疾病名称: %s\n", currentDisease);
                printf("输入新名称（直接回车保留）: ");
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
                        printf("错误：疾病名称已存在\n");
                        break;
                    }
                    strcpy(diseaseDatabase[originalIndex].disease, newDisease);
                }

                
                char newDept[50] = {0};
                printf("\n当前科室: %s\n", currentDept);
                printf("输入新科室（直接回车保留）: ");
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
                        printf("错误：科室不存在\n");
                        
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
                        printf("错误：该科室已满6种疾病\n");
                        
                        if(strlen(newDisease)>0) strcpy(diseaseDatabase[originalIndex].disease, currentDisease);
                        break;
                    }

                    strcpy(diseaseDatabase[originalIndex].department, newDept);
                }

                printf("修改成功！\n");
                break;
            }

           case 3: {
    printf("\n=== 疾病科室对应表 ===\n");
    char *mainDepartments[] = {
        "内科-消化科", "内科-心血管科", "内科-呼吸科",
        "外科-骨科", "外科-普外科", "外科-神经外科"
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
    printf("\n请选择要删除的条目编号（0返回）: ");
                if(scanf("%d", &index) != 1) {
                    while(getchar() != '\n');
                    printf("输入无效\n");
                    break;
                }
                if(index == 0) break;

                if(index<1 || index>diseaseCount){
                    printf("无效的编号\n");
                    break;
                }

                char confirm;
                printf("确认删除「%s」吗？(y/其他取消): ", diseaseDatabase[index-1].disease);
                scanf(" %c", &confirm);
                if(tolower(confirm) != 'y') {
                    printf("操作已取消\n");
                    break;
                }

               
                for(int i=index-1; i<diseaseCount-1; i++){
                    diseaseDatabase[i] = diseaseDatabase[i+1];
                }
                diseaseCount--;
                printf("删除成功！\n");
                break;
            }

            case 4: {
                printf("\n=== 疾病科室对应表 ===\n");
                char *mainDepartments[] = {
                    "内科-消化科", "内科-心血管科", "内科-呼吸科",
                    "外科-骨科", "外科-普外科", "外科-神经外科"
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

                printf("按任意键返回...");
                getchar();
                getchar();
                break;
            }

            case 0:
                printf("返回上级菜单\n");
                break;

            default:
                printf("无效的选择\n");
                break;
        }
    } while (choice != 0);
}



void searchByDisease(int isDeveloperMode) {
    char disease[50];
    printf("\n请输入疾病名称（0返回）: ");
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
        printf("未找到相关科室信息，建议咨询导诊台\n");
        if(isDeveloperMode){
            printf("[开发者提示] 可前往疾病库管理添加对应关系\n");
        }
        return;
    }

 printf("\n【%s】属于【%s】\n", disease, targetDept);
    
    int deptIndex = -1;
    for(int i=0; i<departmentCount; i++){
        if(strcmp(departments[i].name, targetDept) == 0){
            deptIndex = i;
            break;
        }
    }

    if(deptIndex == -1){
        printf("当前没有开设该专科\n");
        return;
    }

    
    Department *dept = &departments[deptIndex];
    printf("\n=== %s专家详情 ===\n", dept->name);

   
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
            printf("【%d号医生】%-*s", 
                  j+c+1, 
                  COL_WIDTH - (int)(strlen("【X号医生】")/3*2 + 1)*2, 
                  "");
        }
        printf("\n");

        
        for(int c=0; c<validCols; c++){
            printf("姓名：%-*s", COL_WIDTH-6, docs[c]->name);
        }
        printf("\n");

       
        for(int c=0; c<validCols; c++){
            printf("职称：%-*s", COL_WIDTH-6, docs[c]->title);
        }
        printf("\n");

       
        for(int c=0; c<validCols; c++){
            printf("专业：%-*s", COL_WIDTH-6, docs[c]->specialty);
        }
        printf("\n");

        
        for(int c=0; c<validCols; c++){
            printf("挂号费：%-.1f元%-*s", 
                  docs[c]->fee,
                  COL_WIDTH - LABEL_WIDTH - 4, "");
        }
        printf("\n");

        
        char *days[] = {"周一","周二","周三","周四","周五","周六","周日"};
        char timeSlots[4][6][30];
        int slotCounts[4] = {0};
        
        for(int c=0; c<validCols; c++){
            for(int d=0; d<7 && slotCounts[c]<6; d++){
                for(int t=0; t<2; t++){
                    if(docs[c]->appointments[d][t] > 0){
                        snprintf(timeSlots[c][slotCounts[c]], 30, "%s%s 剩%2d号",
                               days[d], t==0?"上午":"下午", docs[c]->appointments[d][t]);
                        slotCounts[c]++;
                    }
                }
            }
            if(slotCounts[c] == 0){
                strcpy(timeSlots[c][0], "暂无号源");
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
            printf("\n请选择医生查看详情（0返回）: ");
            if(scanf("%d", &docChoice) != 1){
                printf("输入格式错误！\n");
                while(getchar() != '\n');
                continue;
            }
            if(docChoice == 0) return;
            if(docChoice<1 || docChoice>departments[deptIndex].doctorCount){
                printf("无效的选择，请重新输入！\n");
                continue;
            }
            break;
        }

        Doctor doc = departments[deptIndex].doctors[docChoice-1];
        
        printf("\n=== 医生详情 ===\n");
        printf("姓名：%s\n职称：%s\n", doc.name, doc.title);
        printf("专业方向：%s\n", doc.specialty);
        printf("挂号费：%.1f元\n", doc.fee);
        
        
        printf("\n可预约时间：\n");
        char *days[] = {"周一","周二","周三","周四","周五","周六","周日"};
        int hasAvailable = 0;
        for(int d=0; d<7; d++){
            for(int t=0; t<2; t++){
                if(doc.appointments[d][t] >0){
                    printf("%s %s：剩余%d号\n", 
                          days[d], 
                          t==0 ? "上午" : "下午", 
                          doc.appointments[d][t]);
                    hasAvailable = 1;
                }
            }
        }
        if(!hasAvailable){
            printf("近期号源已满\n");
            return;
        }

        char confirm;
        printf("\n是否立即预约？(y/其他返回): ");
        scanf(" %c", &confirm);
        if(tolower(confirm) != 'y') return;

        
        char name[50], phone[20];
        printf("请输入姓名: ");
        scanf("%s", name);
        do {
    printf("请输入联系电话（11位数字，0返回）: ");
    scanf("%s", phone);
    if(strcmp(phone, "0") == 0) return;
    
    if(strlen(phone) != 11) {
        printf("手机号必须为11位！\n");
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
        printf("手机号必须全为数字！\n");
        continue;
    }
    
    break;
} while(1);

        
        int dayInput, timeInput;
        while(1){
            
            while(1){
                printf("请选择星期（1-7对应周一到周日，0返回）: ");
                if(scanf("%d", &dayInput) != 1){
                    printf("输入格式错误，请输入数字！\n");
                    while(getchar() != '\n');
                    continue;
                }
                if(dayInput == 0) return;
                if(dayInput<1 || dayInput>7){
                    printf("请输入1-7之间的数字！\n");
                    continue;
                }
                break;
            }

            
            while(1){
                printf("请选择时间段（上午0，下午1，其他返回）: ");
                if(scanf("%d", &timeInput) != 1){
                    printf("输入格式错误，请输入数字！\n");
                    while(getchar() != '\n');
                    continue;
                }
                if(timeInput<0 || timeInput>1){
                    printf("请输入0或1！\n");
                    continue;
                }
                break;
            }

            
            int dayIndex = dayInput - 1;
            if(doc.appointments[dayIndex][timeInput] > 0){
                break;
            }else{
                printf("该时段已无号源，请重新选择！\n");
            }
        }

       
        makeAppointment(name, phone, deptIndex+1, docChoice, dayInput, timeInput);
        printf("预约成功！\n");
    } else {
        
        printf("\n按任意键返回...");
        getchar();
        getchar();
    }
}
