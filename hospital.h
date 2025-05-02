#ifndef HOSPITAL_H
#define HOSPITAL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>

#define MAX_DEPARTMENTS 20
#define MAX_DISEASES 1000
#define MAX_DEPT_DISEASES 50
#define MAX_DOCTORS 20
#define MAX_APPOINTMENTS 14
#define MAX_RECORDS 100




typedef struct {
    char disease[50];
    char department[50];
} DiseaseMap;

typedef struct {
    char name[50];
    int age;
    char title[30];
    char specialty[50];
    float fee;
    int appointments[7][2];
    char reviews[3][100];
} Doctor;

typedef struct {
    char name[50];
    Doctor doctors[MAX_DOCTORS];
    int doctorCount;
} Department;

typedef struct {
    char patientName[50];
    char phoneNumber[20];
    char docName[50];
    char deptName[50];
    int dayOfWeek;
    int timeOfDay;
} AppointmentRecord;

extern DiseaseMap diseaseDatabase[];
extern int diseaseCount;
extern Department departments[];
extern int departmentCount;
extern AppointmentRecord appointmentRecords[];
extern int recordCount;

void initDepartments();
void showMenu(int mode);
void showDepartmentsAndMakeAppointment();
void makeAppointment(char*,char*,int,int,int,int);
void cancelAppointment();
void viewAppointments();
void addDepartment();
void normalizeDepartment(const char *input, char *output);
void diseaseManagement();
void searchByDisease(int);
void addDoctor();
void deleteDoctor();
void modifyDoctor();
void searchDoctor();

#endif
