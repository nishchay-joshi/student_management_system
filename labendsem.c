#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct student{
    char name[50];
    int roll;
    float cpi;
};

void lowerString(char dest[], char src[]){
    int len = strlen(src);
    for(int i = 0; i < len; i++)
        dest[i] = (src[i] >= 'A' && src[i] <= 'Z') ? src[i] + 32 : src[i];
    dest[len] = '\0';
}

int dataValidation(int roll, float cpi, char name[]){
    int flag = 1;
    for(int i = 0; i < strlen(name); i++){
        if((name[i] >= 'A' && name[i] <= 'Z') || (name[i] >= 'a' && name[i] <= 'z') || name[i] == ' ') continue;
        else{
            flag = 0;
            break;
        }
    }

    if(roll <= 0){
        printf("Invalid roll number.\n");
        return 0;
    }else if(cpi < 0.0 || cpi > 10.0){
        printf("Invalid CPI.\n");
        return 0;
    }else if(!flag){
        printf("Invalid name.\n");
        return 0;
    }

    return 1;
}

int addStudent(struct student *stdarray, int number){
    int roll;
    char name[50];
    float cpi;

    printf("Enter name: ");
    scanf(" %[^\n]", name);
    printf("Enter roll no: ");
    scanf("%d", &roll);
    printf("Enter gpa: ");
    scanf("%f", &cpi);

    if(dataValidation(roll, cpi, name)){
        if(number >= 99){
            printf("Array full.\n");
            return number;
        }else{
            for(int i = 0; i <= number; i++){
                if(roll == stdarray[i].roll){
                    printf("Roll no. already exists.\n");
                    return number;
                }
            }
            strcpy(stdarray[number + 1].name, name);
            stdarray[number + 1].roll = roll;
            stdarray[number + 1].cpi = cpi;

            printf("Student added successfully\n");
            return number + 1;
        }
    }

    return number;
}

int removeStudent(struct student *stdarray, int number){
    int roll, flag = 0, index;

    printf("Enter roll no you want to be removed: ");
    scanf("%d", &roll);

    for(int i = 0; i <= number; i++){
        if(stdarray[i].roll == roll){
            flag = 1;
            index = i;
            break;
        }
    }

    if(!flag){
        printf("Roll number doesn't exist.\n");
        return number;
    }

    for(int j = index + 1; j <= number; j++){
        struct student temp = stdarray[j - 1];
        stdarray[j - 1] = stdarray[j];
        stdarray[j] = temp;
    }

    printf("Student removed successfully\n");
    return number - 1;
}

void search(struct student *stdarray, int number){
    char name[50];
    int flag = 0;

    printf("Enter the name: ");
    scanf(" %[^\n]", name);

    char searchLower[50];
    lowerString(searchLower, name);

    for(int i = 0; i <= number; i++){
        char lowerName[50];
        lowerString(lowerName, stdarray[i].name);

        if (strcmp(searchLower, lowerName) == 0) {
            printf("Name : %s\n", stdarray[i].name);
            printf("Roll : %d\n", stdarray[i].roll);
            printf("CPI  : %.2f\n\n", stdarray[i].cpi);
            flag = 1;
        }
    }

    if (!flag) printf("Student not found.\n");
}

void sort(struct student *stdarray, int number){
    for(int i = 0; i < number; i++){
        for(int j = 0; j < number - i; j++){
            
            char name1[50];
            lowerString(name1, stdarray[j].name);
            char name2[50];
            lowerString(name2, stdarray[j + 1].name);

            if(strcmp(name1, name2) > 0){
                struct student temp = stdarray[j];
                stdarray[j] = stdarray[j+1];
                stdarray[j+1] = temp;
            }
        }
    }

    printf("Students sorted successfully\n");
}

int main(){

    struct student *stdarray = (struct student*)malloc(100 * sizeof(struct student));

    char names[5][50] = {"JOHN DOE", "Jane Doe", "John Smith", "JANE SMITH", "Joe Schmo"};
    int rolls[5] = {143, 123, 156, 319, 245};
    float cpis[5] = {8.2, 7.9, 8.2, 5.6, 7.7}; 

    for(int i = 0; i<5;i++){
        stdarray[i].roll = rolls[i];
        stdarray[i].cpi = cpis[i];
        strcpy(stdarray[i].name, names[i]);
    }

    int choice, number = 4;

    do{
        printf("\n---STUDENT MANAGMENT DATABASE---\n");
        printf("Choose from the following: \n");
        printf("1. Add student\n2. Remove student\n3. Search by name\n4. Sort by name\n0. Exit\n");
        scanf("%d", &choice);

        switch(choice){
            case 1:
                number = addStudent(stdarray, number);
                break;
            case 2:
                number = removeStudent(stdarray, number);
                break;
            case 3:
                search(stdarray, number);
                break;
            case 4:
                sort(stdarray, number);
                break;
        }
        
    }while(choice != 0);

    free(stdarray);

    return 0;
}
