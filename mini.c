#include <stdio.h>
#include <string.h>
#include <stdlib.h>
int printmenu() {
	int ch;
	printf("[1].Add record of new employee\n");
	printf("[2].Show records\n");
	printf("[3].Search a record\n");
	printf("[4].Delete a record\n");
	printf("[5].Modify a record\n");
	printf("[6].Exit\n");
	printf("Enter ur choice :");
	scanf("%d", &ch);
	return ch;
}
int main(){
	typedef struct employee {
		char name[20];
		float sal;
		int id;
	}emp;
	int choice, i, id1;
	emp e;
	char nxt, *name;
	FILE *fp; 
	choice = printmenu();
	fp = fopen("EMP.DAT","rb+");
	if(fp == NULL){
		fp = fopen("EMP.DAT","wb+");
		if(fp == NULL){
			printf("Cannot open file");
			exit(1);
		}
	}
	switch(choice) {
		case 1: /*adding info of new employee*/
				printf("Enter name, id and salary\n");
				while(scanf("%s%d%f", e.name, &e.id, &e.sal) != -1);
				fseek(fp,0,SEEK_END);
				fwrite(&e, sizeof(e), 1, fp);
				fclose(fp);		
				break;
		case 2:/*display*/
			rewind(fp); ///this moves file cursor to start of the file
			printf("Name\tID\tSalary\n\n");
                	while(fread(&e, sizeof(struct employee), 1, fp) == 1){ /// read the file and fetch the record one record per fetch
                    		printf("%s\t%d\t%f\n", e.name, e.id, e.sal); /// print the name, id and salary
                	}
			break;
		case 3:/*search the record*/
			printf("(1).Search by name\n");
			printf("(2).Search by id\n");
			scanf("%d", &i);
			switch(i) {
				case 1:/*Search by name*/
					printf("*Search Employee By Name*\n");
					printf("Enter employee Name:\n");
     					scanf("%s",name);
					rewind(fp);
					while(fread(&e,sizeof(e),1,fp)==1) {
						if((strcmp(e.name, name)) == 0)
							printf("Name:%s\tID:%d\tSalary:%f\n",e.name, e.id, e.sal);
						else 
							printf("Record not found\n");
					}		
					break;
				case 2:/*Search by id*/
					printf("****Search Books By Id****");
					printf("Enter the book id:");
					scanf("%d",&id1);
					rewind(fp);
					while(fread(&e,sizeof(e),1,fp)==1) {
						if(e.id == id1)
							printf("Name:%s\tID:%d\tSalary:%f\n", e.name, e.id, e.sal);
						else 
							printf("Record not found\n");
					}	
					break;
			}
			break;

		case 4:/*delete*/
			
			break;

		case 5:/*edit*/
			printf("Enter the employee name to modify:\n");
			scanf("%s", name);
			rewind(fp);
			while(fread(&e, sizeof(e), 1, fp)==1){ /// fetch all record from file
                        	if(strcmp(e.name, name) == 0){ ///if entered name matches with that in file
                            		printf("\nEnter new name, id and salary:\n");
                           		scanf("%s%d%f", e.name, &e.id, &e.sal);
                            		fseek(fp, -sizeof(e), SEEK_CUR); /// move the cursor 1 step back from current position
                            		fwrite(&e, sizeof(e), 1, fp); /// overwrite the record
					break;
                        	}
			}
			break;

		case 6:/*Exit*/
			exit(0);
			break;
	}
	return 0;
}
