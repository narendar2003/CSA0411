#include <stdio.h>

struct Employee {
    int empID;
    char name[50];
    float salary;
};

int main() {
    FILE *file = fopen("employee.dat", "r+");
    if (!file) file = fopen("employee.dat", "w+");

    while (1) {
        printf("\n1. Add Employee\n2. Display All Employees\n3. Search Employee\n4. Exit\nEnter choice: ");
        int choice; scanf("%d", &choice);

        switch (choice) {
            case 1: {
                struct Employee emp;
                printf("Enter ID, Name, Salary: "); scanf("%d %s %f", &emp.empID, emp.name, &emp.salary);
                fseek(file, (emp.empID - 1) * sizeof(struct Employee), SEEK_SET);
                fwrite(&emp, sizeof(struct Employee), 1, file);
                break;
            }
            case 2: {
                struct Employee emp;
                rewind(file);
                while (fread(&emp, sizeof(struct Employee), 1, file) == 1)
                    printf("ID: %d, Name: %s, Salary: %.2f\n", emp.empID, emp.name, emp.salary);
                break;
        
            }
            case 4:
                fclose(file);
                return 0;
            default:
                printf("Invalid choice. Try again.\n");
        }
    }
}
