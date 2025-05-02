#include "hospital.h"

Department departments
[MAX_DEPARTMENTS];
int departmentCount = 0;


void initDepartments() {
    
    char *deptNames[] = {
        "内科-消化科", "内科-心血管科", "内科-呼吸科",
        "外科-骨科", "外科-普外科", "外科-神经外科"
    };
    const int initialDeptCount = sizeof(deptNames)/sizeof(deptNames[0]);

    
    char *deptDoctors[][2] = {
        {"张建国", "王桂芳"},    
        {"李德海", "赵丽华"},    
        {"陈志强", "刘秀英"},    
        {"周建军", "黄淑兰"},   
        {"吴国强", "徐玉兰"},    
        {"孙建华", "马晓梅"}     
    };

    
    char *specialties[][3] = {
        {"胃炎", "肝硬化", "消化道肿瘤"},
        {"冠心病", "动脉硬化", "心力衰竭"},
        {"肺炎", "哮喘", "慢性阻塞性肺疾病"},
        {"骨折", "关节置换", "脊柱外科"},
        {"阑尾炎", "疝气", "胃肠肿瘤"},
        {"脑肿瘤", "脑血管病", "神经创伤"}
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
        "问诊细致，解释清楚", "治疗效果好，推荐", "非常有耐心",
        "用药精准，复诊安排合理", "候诊时间稍长但值得", "对老年人特别关照",
        "检查建议非常专业", "会认真听患者描述", "术后随访很及时",
        "诊断准确，用药后明显好转", "对儿童患者很有办法", "治疗方案经济有效"
    };

    srand(time(NULL));
    
    
    for (int i = 0; i < initialDeptCount; i++) {
        
        strcpy(departments[i].name, deptNames[i]);
        departments[i].doctorCount = 2;

        
        for (int j = 0; j < 2; j++) {
            Doctor *doc = &departments[i].doctors[j];
            
            
            strcpy(doc->name, deptDoctors[i][j]);
            
            
            char *titles[] = {"主任医师", "副主任医师", "主治医师"};
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
    printf("\n=== 科室列表 ===\n");
    for(int i=0; i<departmentCount; i++){ 
        printf("%d. %s", i+1, departments[i].name);
        if (departments[i].doctorCount == 0) {
            printf(" (暂未开放)");
        }
        printf("\n");
    }
    
    int choice;
    printf("请选择科室查看专家（0返回）: ");
    scanf("%d", &choice);
    
    if(choice == 0) return;
    
    if(choice >0 && choice <= departmentCount){
        Department *dept = &departments[choice-1];
        if(dept->doctorCount == 0) {
            printf("该科室暂未开放，请联系医院管理部门\n");
            return;
        }

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
                      COL_WIDTH - (int)(strlen("【X号医生】")/3 * 2 + 1)*2, 
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
                      COL_WIDTH - LABEL_WIDTH - 4,
                      "");
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


        
        int docChoice;
        printf("\n请输入要预约的医生编号（0返回）: ");
        scanf("%d", &docChoice);
        
        if(docChoice == 0) return;
        if(docChoice <1 || docChoice > dept->doctorCount){
            printf("无效的医生编号\n");
            return;
        }

        Doctor *doc = &dept->doctors[docChoice-1];
        
        
        int dayInput, timeInput;
        printf("请选择星期（1-7对应周一到周日，0返回）: ");
        if(scanf("%d", &dayInput) != 1 || dayInput < 0 || dayInput > 7){
            printf("输入无效\n");
            while(getchar() != '\n'); 
            return;
        }
        if(dayInput == 0) return;
        int dayIndex = dayInput - 1;

        printf("请选择时间段（上午0，下午1，其他返回）: ");
        if(scanf("%d", &timeInput) != 1 || timeInput < 0 || timeInput > 1){
            printf("输入无效\n");
            while(getchar() != '\n');
            return;
        }

       
        if(doc->appointments[dayIndex][timeInput] <= 0){
            printf("该时段暂无号源\n");
            return;
        }

        
        char patientName[50], phoneNumber[20];
        printf("请输入患者姓名（0返回）: ");
        scanf("%s", patientName);
        if(strcmp(patientName, "0") == 0) return;

       do {
    printf("请输入联系电话（11位数字，0返回）: ");
    scanf("%s", phoneNumber);
    if(strcmp(phoneNumber, "0") == 0) return;
    
    if(strlen(phoneNumber) != 11) {
        printf("手机号必须为11位！,且均为数字\n");
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
        printf("手机号必须全为数字！\n");
        continue;
    }
    
    break;
} while(1);

        
        char *days[] = {"周一","周二","周三","周四","周五","周六","周日"};
        printf("\n确认预约:\n");
        printf("医生: %s (%d号医生)\n", doc->name, docChoice);
        printf("时间: %s %s\n", days[dayIndex], timeInput==0?"上午":"下午");
        printf("患者: %s\n", patientName);
        printf("电话: %s\n", phoneNumber);
        
        char confirm;
        printf("是否确认？(y/n): ");
        scanf(" %c", &confirm);
        
        if(tolower(confirm) == 'y'){
    
    makeAppointment(patientName, 
                    phoneNumber, 
                    choice,         
                    docChoice,      
                    dayIndex + 1,   
                    timeInput);     
}else{
    printf("已取消预约\n");
}
    }else{
        printf("无效的选择\n");
    }
}



	void addDepartment() {
	    if (departmentCount >= MAX_DEPARTMENTS) {
	        printf("科室数量已达上限（%d）\n", MAX_DEPARTMENTS);
	        return;
	    }
	    
	    char name[50];
	    printf("请输入新科室名称: ");
	    scanf("%s", name);
	    
	    
	    for (int i = 0; i < departmentCount; i++) {
	        if (strcmp(departments[i].name, name) == 0) {
	            printf("该科室已存在\n");
	            return;
	        }
	    }
	    
	    strcpy(departments[departmentCount].name, name);
	    departments[departmentCount].doctorCount = 0;
	    departmentCount++;
	    printf("科室添加成功！\n");
	}
	
	
	
		void modifyDoctor() {
	    printf("\n=== 修改医生信息 ===\n");
	    
	    
	    printf("请选择需要修改的医生所属科室:\n");
	    for (int i = 0; i < departmentCount; i++) {
	        printf("%d. %s\n", i+1, departments[i].name);
	    }
	    int deptChoice;
	    printf("输入科室编号（0返回）: ");
	    scanf("%d", &deptChoice);
	    if (deptChoice < 1 || deptChoice > departmentCount) return;
	
	    Department *dept = &departments[deptChoice-1];
	    
	    
	    printf("\n=== %s专家列表 ===\n", dept->name);
	    for (int j = 0; j < dept->doctorCount; j++) {
	        printf("%d. %s\n", j+1, dept->doctors[j].name);
	    }
	    int docChoice;
	    printf("输入医生编号（0返回）: ");
	    scanf("%d", &docChoice);
	    if (docChoice < 1 || docChoice > dept->doctorCount) return;
	
	    Doctor *doc = &dept->doctors[docChoice-1];
	    
	    int option;
	    do {
	        printf("\n请选择要修改的信息项:\n");
	        printf("1.姓名 2.科室 3.职称 4.专业 5.挂号费 6.评价 0.返回\n选择: ");
	        scanf("%d", &option);
	
	        switch(option) {
	            case 1: {
	                printf("当前姓名: %s\n新姓名: ", doc->name);
	                scanf("%s", doc->name);
	                printf("姓名修改成功\n");
	                break;
	            }
	            case 2: {
	                printf("请选择新科室:\n");
	                for (int i = 0; i < departmentCount; i++) {
	                    printf("%d. %s\n", i+1, departments[i].name);
	                }
	                int newDeptChoice;
	                printf("输入新科室编号（0取消）: ");
	                scanf("%d", &newDeptChoice);
	                
	                if (newDeptChoice > 0 && newDeptChoice <= departmentCount) {
	                    Department *newDept = &departments[newDeptChoice-1];
	                    if (newDept->doctorCount >= MAX_DOCTORS) {
	                        printf("目标科室已满\n");
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
	                    printf("科室修改成功\n");
	                    return; 
	                }
	                break;
	            }
	            case 3: {
	                printf("当前职称: %s\n新职称: ", doc->title);
	                scanf("%s", doc->title);
	                printf("职称修改成功\n");
	                break;
	            }
	            case 4: {
	                printf("当前专业: %s\n新专业: ", doc->specialty);
	                scanf("%s", doc->specialty);
	                printf("专业修改成功\n");
	                break;
	            }
	            case 5: {
	                printf("当前挂号费: %.1f\n新挂号费: ", doc->fee);
	                scanf("%f", &doc->fee);
	                printf("挂号费修改成功\n");
	                break;
	            }
	            case 6: {
	                printf("当前评价:\n");
	                for (int i = 0; i < 3; i++) {
	                    printf("%d. %s\n", i+1, doc->reviews[i]);
	                }
	                int reviewChoice;
	                printf("选择要修改的评价（1-3, 0取消）: ");
	                scanf("%d", &reviewChoice);
	                
	                if (reviewChoice >= 1 && reviewChoice <= 3) {
	                    printf("输入新评价: ");
	                    getchar(); 
	                    fgets(doc->reviews[reviewChoice-1], 100, stdin);
	                    doc->reviews[reviewChoice-1][strcspn(doc->reviews[reviewChoice-1], "\n")] = 0; 
	                    printf("评价修改成功\n");
	                }
	                break;
	            }
	            case 0:
	                break;
	            default:
	                printf("无效的选择\n");
	        }
	    } while (option != 0);
	}
	
	
	
		void deleteDoctor() {
	    printf("\n=== 删除医生信息 ===\n");
	    for (int i = 0; i < departmentCount; i++) {
	        printf("%d. %s\n", i + 1, departments[i].name);
	    }
	    
	    int deptChoice;
	    printf("请选择要操作的科室(输入0返回): ");
	    scanf("%d", &deptChoice);
	    
	    if(deptChoice > 0 && deptChoice <= departmentCount){
	        Department *dept = &departments[deptChoice - 1];
	        
	        printf("\n=== %s专家列表 ===\n", dept->name);
	        for(int j=0; j<dept->doctorCount; j++){
	            printf("%d. %s\n", j+1, dept->doctors[j].name);
	        }
	        
	        int docChoice;
	        printf("选择要删除的医生编号: ");
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
	
	            printf("医生信息删除成功。\n");
	        } else {
	            printf("无效的选择。\n");
	        }
	    }
	}
	
	
		void addDoctor() {
	    printf("\n=== 添加医生信息 ===\n");
	    for (int i = 0; i < departmentCount; i++) {
	        printf("%d. %s", i + 1, departments[i].name);
	        if (departments[i].doctorCount >= MAX_DOCTORS) {
	            printf(" (已满)");
	        }
	        printf("\n");
	    }
	    
	    int deptChoice;
	    printf("请选择要添加医生的科室(输入0返回): ");
	    scanf("%d", &deptChoice);
	
	     if(deptChoice >0 && deptChoice <= departmentCount){
	        Department *dept = &departments[deptChoice - 1];
	        
	        if(dept->doctorCount >= MAX_DOCTORS) {
	            printf("该科室已达最大医生数量（%d）\n", MAX_DOCTORS);
	            return;
	        }
	        Doctor newDoc;
	        printf("请输入医生姓名: ");
	        scanf("%s", newDoc.name);
	        printf("请输入医生职称(主任医师/副主任医师/主治医师): ");
	        scanf("%s", newDoc.title);
	        printf("请输入医生专业领域: ");
	        scanf("%s", newDoc.specialty);
	        printf("请输入挂号费: ");
	        scanf("%f", &newDoc.fee);
	        newDoc.age = 35 + ((strcmp(newDoc.title, "主任医师") == 0) ? 0 : 
	                         (strcmp(newDoc.title, "副主任医师") == 0) ? 5 : 10) + rand()%5;
	
	        
	        for(int d=0; d<7; d++){
	            for(int t=0; t<2; t++){
	                newDoc.appointments[d][t] = (rand()%2 == 0) ? 5 : 0;
	            }
	        }
	
	        
	        strcpy(newDoc.reviews[0], "暂无患者评价");
	        strcpy(newDoc.reviews[1], "");
	        strcpy(newDoc.reviews[2], "");
	
	        dept->doctors[dept->doctorCount++] = newDoc;
	        printf("医生信息添加成功。\n");
	    } else if(deptChoice != 0) {
	        printf("无效的选择。\n");
	    }
	}
	
	
	
	
	
	
	
void searchDoctor() {
    char name[50];
    printf("请输入要查找的医生姓名: ");
    scanf("%s", name);
    
    int found = 0;
    for(int i=0; i<departmentCount; i++) {
        for(int j=0; j<departments[i].doctorCount; j++) {
            Doctor doc = departments[i].doctors[j];
            if(strcmp(doc.name, name) == 0) {
                printf("\n=== 医生详细信息 ===\n");
                printf("所属科室: %s\n", departments[i].name);
                printf("姓名: %s\n", doc.name);
                printf("职称: %s\n", doc.title);
                printf("专业领域: %s\n", doc.specialty);
                printf("挂号费: %.1f元\n", doc.fee);
                printf("年龄: %d\n", doc.age);
                
                printf("\n可预约时间:\n");
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
                if(!hasAvailable) printf("当前无可用号源\n");
                
                printf("\n患者评价:\n");
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
        printf("未找到名为 %s 的医生\n", name);
    }
}	
	
