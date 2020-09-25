#include <stdio.h>
#include <stdlib.h>
#include "todo.h"
#include "useful_strings.h"

// things you need to do: create the data structure with the file func
// exit if the file doesn't exist
// all the menu methods

int main(int argc, const char* argv[]) {
	FILE *fin;
	int fileNF = 0;
	if (argc > 2) {
		printf("%s", ERROR_USAGE);
		return 1;
	} else {
		if (argc > 1) {
			fin = fopen(argv[1], "r");
			//this is where you call the file read in method
			if (fin == NULL) {
				printf("ERROR: File, %s, does not exist!\n", argv[1]);
				return 1;
			}
			if (fileNF == 0) {
				int check = 0;
				do
				 {
				 	check = read_todo_list_item(fin);
				 } while (check == 1); 
				 fclose(fin);
			}
			if (Todo_list_length == 0) {
				printf("ERROR: File, %s, does not exist!\n", argv[1]);
				return 1;
			}
		}
	}
	if (fileNF == 0) {
		int quit = 0;
		do {
			printf("%s", MAIN_MENU_HEADER);
			printf("%s", QUERY);
			printf("%s", OPTIONS_LIST);
			printf("%s", GRAB_INPUT);

			char ar[3];
			fgets_no_newline(ar, 3, stdin);
			int a = atoi(ar);
			if (a == 1) {
				printf("%s", TODO_LIST_HEADER);
				for (int i = 0; i < Todo_list_length; i++) {
					printf("%s\n\n", Todo_list[i].title);
					if (Todo_list[i].is_done == 0) {
						printf("Due: %02d/%02d/%04d\n", Todo_list[i].due_month, Todo_list[i].due_day, Todo_list[i].due_year);
					} else {
						printf("Completed!\n");
					}
					printf("Description: %s\n", Todo_list[i].description);
					printf("%s", LINE_BREAK);
				}
			} else if (a == 2) {
				printf("%s", ADD_TO_LIST_HEADER);
				if (Todo_list_length == 100) {
					printf("%s", LIST_MAX);
				} else {
					printf("%s", ADD_TO_LIST);
					fgets_no_newline(Todo_list[Todo_list_length].title, TITLE_LENGTH_MAX, stdin);
					fgets_no_newline(Todo_list[Todo_list_length].description, DESCRIPTION_LENGTH_MAX, stdin);
					char bqf[64];
					fgets_no_newline(bqf, 64, stdin);
					Todo_list[Todo_list_length].is_done = atoi(bqf);
					char bdf[64];
					fgets_no_newline(bdf, 64, stdin);
					Todo_list[Todo_list_length].due_day = atoi(bdf);
					char bff[64];
					fgets_no_newline(bff, 64, stdin);
					Todo_list[Todo_list_length].due_month = atoi(bff);
					char bhf[64];
					fgets_no_newline(bhf, 64, stdin);
					Todo_list[Todo_list_length].due_year = atoi(bhf);
					Todo_list_length++;
				}
			} else if (a == 3) {
				printf("%s", MARK_ITEM_COMPLETED_HEADER);
				printf("%s", MARK_ITEM_USER_INPUT);
				printf("%s", GRAB_INPUT);
				char buf[3];
				fgets_no_newline(buf, 3, stdin);
				Todo_list[atoi(buf)].is_done = 1;
			} else if (a == 4) {
				printf("%s", REMOVE_ITEM_HEADER);
				int pos = 0;
				struct todo_list_item_t holder[TODO_LIST_MAX];
				int count = 0;
				for (int i = 0; i < Todo_list_length; i++) {
					if (Todo_list[i].is_done == 1) {
						count++;
					} else {
						strcpy(holder[pos].title, Todo_list[i].title);
						strcpy(holder[pos].description, Todo_list[i].description);
						holder[pos].is_done = 0;
						holder[pos].due_month = Todo_list[i].due_month;
						holder[pos].due_day = Todo_list[i].due_day;
						holder[pos].due_year = Todo_list[i].due_year;
						pos++;
					}
				}
				Todo_list_length = pos;
				for (int i = 0; i < pos; i++) {
					strcpy(Todo_list[i].title, holder[i].title);
					strcpy(Todo_list[i].description, holder[i].description);
					Todo_list[i].is_done = 0;
					Todo_list[i].due_month = holder[i].due_month;
					Todo_list[i].due_year = holder[i].due_year;
					Todo_list[i].due_day = holder[i].due_day;
				}
				printf("Success! %d items removed!\n", count);
			} else if (a == 5) {
				printf("%s", SAVE_FILE_HEADER);
				printf("%s", INPUT_FILE_NAME);
				printf("%s", GRAB_INPUT);
				char baf[130];
				fgets_no_newline(baf, 130, stdin);
				fin = fopen(baf, "w");
				int check = 0;

				while (check != Todo_list_length) {
					fprintf(fin, "%s\n", Todo_list[check].title);
					fprintf(fin, "%s\n", Todo_list[check].description);
					fprintf(fin, "%d\n", Todo_list[check].is_done);
					fprintf(fin, "%d\n", Todo_list[check].due_day);
					fprintf(fin, "%d\n", Todo_list[check].due_month);
					fprintf(fin, "%d\n", Todo_list[check].due_year);
					check++;
				}
				fclose(fin);

			} else if (a == 6) {
				quit = 1;
			} else {
				printf("%s", INVALID_CHOICE);
			}
		} while(quit != 1);
	} else {
		return 1;
	}
	return 0;
}