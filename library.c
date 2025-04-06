#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Book {
    int id;
    char title[100];
    char author[100];
};


void addBook();
void displayBooks();
void searchBook();
void deleteBook();

int main() {
    int choice;

    while (1) {
        printf("\n====== Library Management System ======\n");
        printf("1. Add Book\n");
        printf("2. Display All Books\n");
        printf("3. Search Book by ID\n");
        printf("4. Delete Book by ID\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: addBook(); break;
            case 2: displayBooks(); break;
            case 3: searchBook(); break;
            case 4: deleteBook(); break;
            case 5: exit(0);
            default: printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}


void addBook() {
    FILE *fp = fopen("library.txt", "a");
    struct Book b;

    printf("Enter Book ID: ");
    scanf("%d", &b.id);
    getchar(); 
    printf("Enter Book Title: ");
    fgets(b.title, 100, stdin);
    b.title[strcspn(b.title, "\n")] = '\0'; 
    printf("Enter Author Name: ");
    fgets(b.author, 100, stdin);
    b.author[strcspn(b.author, "\n")] = '\0';

    fwrite(&b, sizeof(struct Book), 1, fp);
    fclose(fp);

    printf("Book added successfully!\n");
}


void displayBooks() {
    FILE *fp = fopen("library.txt", "r");
    struct Book b;

    if (fp == NULL) {
        printf("No books found!\n");
        return;
    }

    printf("\n--- List of Books ---\n");
    while (fread(&b, sizeof(struct Book), 1, fp)) {
        printf("ID: %d\nTitle: %s\nAuthor: %s\n----------------\n", b.id, b.title, b.author);
    }

    fclose(fp);
}


void searchBook() {
    FILE *fp = fopen("library.txt", "r");
    struct Book b;
    int id, found = 0;

    if (fp == NULL) {
        printf("No books found!\n");
        return;
    }

    printf("Enter Book ID to search: ");
    scanf("%d", &id);

    while (fread(&b, sizeof(struct Book), 1, fp)) {
        if (b.id == id) {
            printf("Book Found!\nID: %d\nTitle: %s\nAuthor: %s\n", b.id, b.title, b.author);
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("Book not found.\n");
    }

    fclose(fp);
}


void deleteBook() {
    FILE *fp = fopen("library.txt", "r");
    FILE *temp = fopen("temp.txt", "w");
    struct Book b;
    int id, found = 0;

    if (fp == NULL) {
        printf("No books found!\n");
        return;
    }

    printf("Enter Book ID to delete: ");
    scanf("%d", &id);

    while (fread(&b, sizeof(struct Book), 1, fp)) {
        if (b.id != id) {
            fwrite(&b, sizeof(struct Book), 1, temp);
        } else {
            found = 1;
        }
    }

    fclose(fp);
    fclose(temp);

    remove("library.txt");
    rename("temp.txt", "library.txt");

    if (found)
        printf("Book deleted successfully.\n");
    else
        printf("Book with ID %d not found.\n", id);
}
