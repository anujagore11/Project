#include <stdio.h>
#include <string.h>
#include <stdlib.h>
int printmenu() {
	system("clear");
	int ch;
	printf("[1].Add record of new employee\n");
	printf("[2].Show records\n");
	printf("[3].Search a record\n");
	printf("[4].Delete a record\n");
	printf("[5].Modify a record\n");
	printf("[6].Show salary slip\n");
	printf("[7].Exit\n");
	printf("Enter ur choice :");
	scanf("%d", &ch);
	return ch;
}
int main(){
	typedef struct dob {
		int dd;
		int mm;
		int yy;
	} date;

	typedef struct employee {
		char name[20];
		int basic;
		int pday;
		int id;
		date b, j;
	}emp;

	int choice, i, l, dd, mm, yy, id1, flag = 0;
	int p, b;
	long sal;
	emp e;
	char nxt, name[20], ch;
	FILE *fp, *fn, *ft; 
	
	while(1) {
fp = fopen("new.txt", "rb+");
	if(fp == NULL){
		fp = fopen("new.txt","wb+");
		if(fp == NULL){
			printf("Cannot create file");
			exit(1);
		}
	}
	else{
		fp = fopen("new.txt","ab+");
		if(fp == NULL){
			printf("Cannot OPEN file");
			exit(1);
		}
	}
	choice = printmenu();
	switch(choice) {
		case 1:
		/***adding info of new employee***/
			do {
				printf("\nEnter emp name:");
				fflush(stdin);
				scanf("%s", e.name);
				l = strlen(e.name);
				e.name[l] =  '\0';
				printf("\nEnter date of birth of emp:");
				scanf("%d%d%d", &e.b.dd, &e.b.mm, &e.b.yy);
				printf("\nEnter emp basic salary:");
				scanf("%d", &e.basic);
				printf("\nEnter present days of emp:");
				scanf("%d", &e.pday);
				printf("\nEnter emp id:");
				scanf("%d", &e.id);
				printf("\nEnter date of joining:");
				scanf("%d%d%d", &e.j.dd, &e.j.mm, &e.j.yy);
				fwrite(&e, sizeof(e), 1, fp);
				printf("\nDo u want to add another record?: y/n\n");
				fflush(stdin);
				scanf("%s", &ch);
	 		} while(ch == 'y');
			fclose(fp);
				break;
		case 2:
			/***display***/

			fseek(fp, 0, SEEK_SET); //this moves file cursor to start of the file
			printf("-------------------------------------------------------------\n");
			printf("ID\tName\t DOB\tbasic salary\tPresent Days\tJoining Date\n");
			printf("-------------------------------------------------------------\n");
                	while(fread(&e, sizeof(e), 1, fp) == 1){ // read the file and fetch the record one record per fetch
                    		printf("%d\t", e.id); 
				printf("%s\t", e.name);
				printf("%d/%d/%d\t", e.b.dd, e.b.mm, e.b.yy);
				printf("%d\t\t", e.basic);
				printf("%d\t", e.pday);
				printf("%d/%d/%d\n", e.j.dd, e.j.mm, e.j.yy);	
                	}
			break;
		case 3:
			/***search the record***/
			printf("1. Search by name\n");
			printf("2. Search by id\n");
			printf("3.Search by joining date\n");
			scanf("%d", &i);
			switch(i) {
				case 1:/***Search by name***/
					printf("-------Search Employee By Name-------\n");
					printf("Enter employee Name:\n");
     					scanf("%s",name);
					rewind(fp);
					while(fread(&e, sizeof(e), 1, fp)!=0) {
						if(strcmp(e.name, name) == 0) {
							printf("Record found:\n");
							printf("ID:%d\tName:%s\tDOB:%d/%d/%d\tbasic salary:%d\tpresent days:%d\tJoin Date:%d/%d/%d\n", e.id, e.name, e.b.dd, e.b.mm, e.b.yy, e.basic, e.pday, e.j.dd, e.j.mm, e.j.yy);
							flag = 1;
							break;
						}
					}
					fclose(fp);
					if(flag == 0) 
							printf("Record not found\n");		
					break;
				case 2:/***Search by id***/
					printf("-------Search Employee By Id-------\n");
					printf("Enter the emp id: ");
					scanf("%d", &id1);
					rewind(fp);
					while(fread(&e, sizeof(e), 1, fp) == 1) {
						if(e.id == id1) {
							printf("Record found:\n");
							printf("ID:%d\tName:%s\tDOB:%d/%d/%d\tbasic  salary:%d\t\tpresent days:%d\tJoin Date:%d/%d/%d\n", e.id, e.name, e.b.dd, e.b.mm, e.b.yy, e.basic, e.pday, e.j.dd, e.j.mm, e.j.yy);
							flag = 1;
							break;
						}
					}
					fclose(fp);
					if(flag == 0)
						printf("\nRecord not found");		
					break;
				case 3:/***Search by joining date***/
					printf("-------Search Employee By Id-------\n");
					printf("Enter the date: ");
					scanf("%d%d%d", &dd, &mm, &yy);
					rewind(fp);
					while(fread(&e, sizeof(e), 1, fp) == 1) {
						if(dd == e.j.dd && mm == e.j.mm && yy == e.j.yy) {
							printf("Record found:\n");
							printf("ID:%d\tName:%s\tDOB:%d/%d/%d\tbasic  salary:%d\tpresent days:%d\tJoin Date:%d/%d/%d\n", e.id, e.name, e.b.dd, e.b.mm, e.b.yy, e.basic, e.pday, e.j.dd, e.j.mm, e.j.yy);
							flag = 1;
							break;
						}
					}
						fclose(fp);
						if(flag == 0)
							printf("\nRecord not found");		
						break;
			}
			break;

		case 4:
			/***delete***/
			printf("Enter emp id to delete:");
			scanf("%d", &id1);
			ft = fopen("temp.txt", "ab+");
			fn = fopen("abc.txt", "wb+");
			while(fread(&e, sizeof(e), 1, fp) == 1) {
				if(e.id == id1) {
					fwrite(&e, sizeof(e), 1 , ft);
					flag = 1;
				}
				else
				fwrite(&e, sizeof(e), 1 , fn);
			}
			fclose(fp);
			fclose(fn);
			remove("new.txt");
			rename("abc.txt", "new.txt");
			if(flag == 0)
				printf("Record not found\n");
			else 
				printf("Record is deleted\n");
			break;

		case 5:
			/***Modify the record***/
			printf("Enter the employee name to modify:\n");
			scanf("%s", name);
			//rewind(fp);
			while(fread(&e, sizeof(e), 1, fp) == 1) { /// fetch all record from file
                        	if(strcmp(e.name, name) == 0) { ///if entered name matches with that in file
					printf("Existing record:\n");
                            		printf("ID:%d\tName:%s\tDOB:%d/%d/%d\tbasic  salary:%d\tpresent days:%d\tJoin Date:%d/%d/%d\n", e.id, e.name, e.b.dd, e.b.mm, e.b.yy, e.basic, e.pday, e.j.dd, e.j.mm, e.j.yy);

					printf("Update basic  salary: y / n? :");
					scanf("%s", &ch);
					if(ch == 'y') {
						printf("Enter new basic  salary:");
						scanf("%d", &e.basic);
					}
					printf("Update present days: y / n? :");
					scanf("%s", &ch);
					if(ch == 'y') {
						printf("Enter present days:");
						scanf("%d", &e.pday);
					}
					printf("Update name: y / n? :");
					scanf("%s", &ch);
					if(ch == 'y') {
						printf("Enter modified name:");
						scanf("%s", e.name);
					}
					printf("Update DOB: y / n? :");
					scanf("%s", &ch);
					if(ch == 'y') {
						printf("Enter modified date:");
						scanf("%d%d%d", &e.b.dd, &e.b.mm, &e.b.yy);
					}

					//printf("%u\n", &fp);
                            		fseek(fp, -(sizeof(e)),SEEK_CUR); /// move the cursor 1 step back from current position
					//printf("%u", &fp);
                            		fwrite(&e, sizeof(e), 1, fp); /// overwrite the record
					flag = 1;
					break;
                        	}
			}
			if(flag == 0)
				printf("Record not found\n");
			else{
				printf("Record is Updated\n");
				printf("ID:%d\tName:%s\tDOB:%d/%d/%d\tbasic salary:%d\tpresent days:%d\tJoin Date:%d/%d/%d\n", e.id, e.name, e.b.dd, e.b.mm, e.b.yy, e.basic, e.pday, e.j.dd, e.j.mm, e.j.yy);
			}
			fclose(fp);
			break;

		case 6:
			/*calculate salary slip*/
			
			printf("Enter ID of d emp: ");
			scanf("%d", &id1);
			while(fread(&e, sizeof(e), 1, fp) == 1) {
				if(id1 == e.id) {
					p = e.pday;
					b = e.basic;
					sal = p * b;
					flag = 1;
				}
			}
			if(flag == 1) {
				printf("Salary Details:\n");
				printf("ID:%d\tName:%s\tBasic:%d\tPresent Days:%d\tNet Salary:%lu\n", e.id, e.name, e.basic, e.pday, sal);
			}
			fclose(fp);
			break;
			
		case 7:
			/*Exit*/
			exit(0);
			break;
	}
	}
	return 0;
}
