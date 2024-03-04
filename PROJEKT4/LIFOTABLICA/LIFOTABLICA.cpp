#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Student {
    char imie[50];
    char nazwisko[50];
    int rok_urodzenia;
};

const int MAX_SIZE = 100;  

struct Stack {
    struct Student data[100];
    int size;
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
    struct Student student;
    printf("Podaj imie: ");
    if(fgets(student.imie, sizeof(student.imie), stdin) == NULL)
    {
        printf("Bledne dane. \n");
        exit(0);
    }
    student.imie[strlen(student.imie) - 1] = '\0';
    printf("Podaj nazwisko: ");
    if(fgets(student.nazwisko, sizeof(student.nazwisko), stdin) == NULL)
    {
        printf("Bledne dane. \n");
        exit(0);
    }
    student.nazwisko[strlen(student.nazwisko) - 1] = '\0';
    printf("Podaj rok urodzenia: ");
    if (scanf_s("%d", &student.rok_urodzenia) !=1)
    {
        printf("Bledne dane. \n");
        exit(0);
    }
    getchar();
    if (stack->size < MAX_SIZE) {
        stack->data[stack->size] = student;
        stack->size++;
    }
    else {
        printf("Stos jest pelny.\n");
    }
}

void pop(struct Stack* stack) {
    if (stack->size > 0) {
        stack->size--;
        printf("Usunieto element: %s %s\n", stack->data[stack->size].imie, stack->data[stack->size].nazwisko);
    }
    else {
        printf("Stos jest pusty.\n");
    }
}

void find(const struct Stack* stack) {
    char nazwisko[50];
    printf("Podaj nazwisko do wyszukania: ");
    fgets(nazwisko, sizeof(nazwisko), stdin);
    nazwisko[strlen(nazwisko) - 1] = '\0';
    for (int i = stack->size - 1; i >= 0; i--) {
        if (strcmp(stack->data[i].nazwisko, nazwisko) == 0) {
            printf("Znaleziono studenta: %s %s (Rok urodzenia: %d)\n", stack->data[i].imie, stack->data[i].nazwisko, stack->data[i].rok_urodzenia);
            return;
        }
    }
    printf("Nie znaleziono studenta o nazwisku: %s\n", nazwisko);
}

void print(const struct Stack* stack) {
    if (stack->size == 0) {
        printf("Stos jest pusty.\n");
    }
    else {
        printf("Zawartosc stosu:\n");
        for (int i = stack->size - 1; i >= 0; i--) {
            printf("%s %s (Rok urodzenia: %d)\n", stack->data[i].imie, stack->data[i].nazwisko, stack->data[i].rok_urodzenia);
        }
    }
}

void count(const struct Stack* stack) {
    printf("Liczba elementow: %d\n", stack->size);
}

void clear(struct Stack* stack) {
    stack->size = 0;
    printf("Wszystkie elementy zostaly usuniete.\n");
}

int main() {
    struct Stack stack;
    stack.size = 0;
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
