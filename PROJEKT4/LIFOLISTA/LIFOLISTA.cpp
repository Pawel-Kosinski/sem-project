#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Student {
    char imie[50];
    char nazwisko[50];
    int rok_urodzenia;
};

struct Node {
    struct Student data;
    struct Node* next;
};

struct Stack {
    struct Node* top;
};

enum Menu {
    PUSH = 1,
    POP,
    FIND,
    PRINT,
    COUNT,
    CLEAR,
    EXIT
};

void push(struct Stack* stack) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    struct Student student;

    printf("Podaj imie: ");
    if (fgets(student.imie, sizeof(student.imie), stdin) == NULL)
    {
        printf("Bledne dane. \n");
        exit(0);
    }
    student.imie[strlen(student.imie) - 1] = '\0';
    printf("Podaj nazwisko: ");
    if (fgets(student.nazwisko, sizeof(student.nazwisko), stdin) == NULL)
    {
        printf("Bledne dane. \n");
        exit(0);
    }
    student.nazwisko[strlen(student.nazwisko) - 1] = '\0';
    printf("Podaj rok urodzenia: ");
    if (scanf_s("%d", &student.rok_urodzenia)!=1)
    {
        printf("Bledne dane. \n");
        exit(0);
    }
    getchar();

    if (newNode == NULL) {
        printf("Blad alokacji pamieci.\n");
        return;
    }

    newNode->data = student;
    newNode->next = stack->top;
    stack->top = newNode;
}

void pop(struct Stack* stack) {
    if (stack->top == NULL) {
        printf("Stos jest pusty.\n");
        return;
    }

    struct Node* temp = stack->top;
    stack->top = stack->top->next;
    free(temp);
}

void find(const struct Stack* stack) {
    struct Node* current = stack->top;
    char nazwisko[50];
    printf("Podaj nazwisko do wyszukania: ");
    fgets(nazwisko, sizeof(nazwisko), stdin);
    nazwisko[strlen(nazwisko) - 1] = '\0';
    while (current != NULL) {
        if (strcmp(current->data.nazwisko, nazwisko) == 0) {
            printf("Znaleziono studenta: %s %s (Rok urodzenia: %d)\n", current->data.imie, current->data.nazwisko, current->data.rok_urodzenia);
            return;
        }
        current = current->next;
    }
    printf("Nie znaleziono studenta o nazwisku: %s\n", nazwisko);
}

void print(const struct Stack* stack) {
    struct Node* current = stack->top;
    if (current == NULL) {
        printf("Stos jest pusty.\n");
        return;
    }

    printf("Zawartosc stosu:\n");
    while (current != NULL) {
        printf("%s %s (Rok urodzenia: %d)\n", current->data.imie, current->data.nazwisko, current->data.rok_urodzenia);
        current = current->next;
    }
}

void count(const struct Stack* stack) {
    int count = 0;
    struct Node* current = stack->top;
    while (current != NULL) {
        count++;
        current = current->next;
    }
    printf("Liczba elementow: %d\n", count);
}

void clear(struct Stack* stack) {
    while (stack->top != NULL) {
        struct Node* temp = stack->top;
        stack->top = stack->top->next;
        free(temp);
    }
}

int main() {
    struct Stack stack;
    stack.top = NULL;
    int choice;

    while (1) {
        printf("Wybierz opcje:\n");
        printf("1. Dodaj element\n");
        printf("2. Usun element\n");
        printf("3. Wyszukaj element po nazwisku\n");
        printf("4. Wypisz wszystkie elementy\n");
        printf("5. Sprawdz liczbe elementow\n");
        printf("6. Usun wszystkie elementy\n");
        printf("7. Zakoncz program\n");
        scanf_s("%d", &choice);
        getchar();  

        switch (choice) {
        case PUSH: {
            push(&stack);
            break;
        }
        case POP: {
            pop(&stack);
            break;
        }
        case FIND: {
            find(&stack);
            break;
        }
        case PRINT: {
            print(&stack);
            break;
        }
        case COUNT: {
            count(&stack);
            break;
        }
        case CLEAR: {
            clear(&stack);
            break;
        }
        case EXIT: {
            clear(&stack);
            return 0;
        }
        default: {
            printf("Niepoprawny wybor.\n");
        }
        }
    }
    return 0;
}
