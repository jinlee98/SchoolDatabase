#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <conio.h>
#include <iomanip>

using namespace std;

int main()
{
    FILE *f1, *f2;
    char decision, choice;

    struct student
    {
        char first_name[25], last_name[25];
        char course[4];
        int section;
    };

    struct student s;
    char xfirst_name[25], xlast_name[25];
    long int recsize;

    f1 = fopen("students.txt","rb+");

    if (f1 == NULL) {
        f1 = fopen("students.txt","wb+");

        if (f1 == NULL) {
            puts("Cannot open file");
            return 0;
        }
    }


    recsize = sizeof(s);

    while(1) {
        system("cls");

        cout << "\t\t====== STUDENT DATABASE MANAGEMENT SYSTEM ======";
        cout <<"\n\n                                          ";
        cout << "\n\n";
        cout << "\n \t\t\t 1. Add Records";
        cout << "\n \t\t\t 2. List Records";
        cout << "\n \t\t\t 3. Modify Records";
        cout << "\n \t\t\t 4. Delete Records";
        cout << "\n \t\t\t 5. Exit Program";
        cout << "\n\n";
    
        fflush(stdin);
        choice = getche();
        switch(choice) {
        case '1' :
            fseek(f1, 0, SEEK_END);
            decision ='Y';
            while(decision == 'Y' || decision == 'y') {
                system("cls");
                cout << "Enter first name: ";
                cin >> s.first_name;
                cout << "Enter last name: ";
                cin >> s.last_name;
                cout << "Enter the course code: ";
                cin >> s.course;
                cout << "Enter the section number: ";
                cin >> s.section;
                fwrite(&s, recsize, 1, f1);
                cout << "\n Add another Record (Y/N) ";
                fflush(stdin);
                decision = getchar();
            }
            break;
        case '2':
            system("cls");
            rewind(f1);
            cout << "=== View the records in the database ===";
            cout << "\n";
            while (fread(&s, recsize, 1, f1) == 1) {
                cout << "\n";
                cout <<"\n" << s.first_name << setw(10)  << s.last_name;
                cout << "\n";
                cout <<"\n" <<s.course <<  setw(8)  << s.section;
            }
            cout << "\n\n";
            system("pause");
            break;

        case '3' :
            system("cls");
            decision = 'Y';
            while (decision == 'Y'|| decision == 'y') {
                cout << "\n Enter the last name of the student: ";
                cin >> xlast_name;

                rewind(f1);
                while (fread(&s, recsize, 1, f1) == 1) {
                    if (strcmp(s.last_name, xlast_name) == 0) {
                        cout << "Enter the new first name: ";
                        cin >> s.first_name;
                        cout << "Enter the new last name: ";
                        cin >> s.last_name;
                        cout << "Enter the new course code: ";
                        cin >> s.course;
                        cout << "Enter the new section number: ";
                        cin >> s.section;
                        fseek(f1, - recsize, SEEK_CUR);
                        fwrite(&s, recsize, 1, f1);
                        break;
                    }
                    else
                        cout<<"record not found";
                }
                cout << "\n Modify another record (Y/N) ";
                fflush(stdin);
                decision = getchar();
            }
            break;


        case '4':
            system("cls");
            decision = 'Y';
            while (decision == 'Y'|| decision == 'y') {
                cout << "\n Enter the last name of the student to delete: ";
                cin >> xlast_name;

                f2 = fopen("temp.dat", "wb");

                rewind(f1);
                while (fread (&s, recsize, 1, f1) == 1) {
                    if (strcmp(s.last_name, xlast_name) != 0) {
                        fwrite(&s, recsize, 1, f2);
                    }
                }
                fclose(f1);
                fclose(f2);
                remove("students.txt");
                rename("temp.dat", "students.txt");

                f1 = fopen("students.txt", "rb+");

                cout << "\n Delete record? (Y/N) ";
                fflush(stdin);
                decision = getchar();
            }

            break;

        case '5':
            fclose(f1);
            exit(0);
        }
    }


    system("pause");
    return 0;
}