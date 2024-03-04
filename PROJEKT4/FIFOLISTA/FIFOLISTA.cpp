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

struct Queue {
    struct Node* front;
    struct Node* rear;
    int count;
};

enum MenuOption {
    ENQUEUE = 1,
    DEQUEUE,
    FIND,
    PRINT,
    COUNT,
    CLEAR,
    EXIT
};

struct Queue* createQueue() {
    struct Queue* queue = (struct Queue*)malloc(sizeof(struct Queue));
    queue->front = NULL;
    queue->rear = NULL;
    queue->count = 0;
    return queue;
}

void enqueue(struct Queue* queue) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    struct Student student;
    printf("Podaj imie: ");
    if (fgets(student.imie, sizeof(student.imie), stdin) == NULL) {
        printf("Bledne dane. \n");
        exit(0);
    }
    student.imie[strlen(student.imie) - 1] = '\0';
    printf("Podaj nazwisko: ");
    if (fgets(student.nazwisko, sizeof(student.nazwisko), stdin) == NULL) {
        printf("Bledne dane. \n");
        exit(0);
    }
    student.nazwisko[strlen(student.nazwisko) - 1] = '\0';
    printf("Podaj rok urodzenia: ");
    if (scanf_s("%d", &student.rok_urodzenia) != 1)
    {
        printf("Bledne dane. \n");
        exit (0);
    }
    getchar();

    newNode->data = student;
    newNode->next = NULL;
    
    if (queue->rear == NULL) {
        queue->front = newNode;
        queue->rear = newNode;
    }
    else {
        queue->rear->next = newNode;
        queue->rear = newNode;
    }
    queue->count++;
}

void dequeue(struct Queue* queue) {
    if (queue->front == NULL) {
        printf("Kolejka jest pusta. Nie mozna usunac elementu.\n");
        return;
    }

    struct Node* temp = queue->front;
    queue->front = queue->front->next;
    free(temp);
    queue->count--;
}

void find(const struct Queue* queue) {
    char nazwisko[50];
    printf("Podaj nazwisko do wyszukania: ");
    fgets(nazwisko, sizeof(nazwisko), stdin);
    nazwisko[strlen(nazwisko) - 1] = '\0';
    struct Node* current = queue->front;

    while (current != NULL) {
        if (strcmp(current->data.nazwisko, nazwisko) == 0) {
            printf("Znaleziono studenta: %s %s (Rok urodzenia: %d)\n", current->data.imie, current->data.nazwisko, current->data.rok_urodzenia);
            return;
        }
        current = current->next;
    }

    printf("Nie znaleziono studenta o nazwisku: %s\n", nazwisko);
}

void print(const struct Queue* queue) {
    struct Node* current = queue->front;

    if (current == NULL) {
        printf("Kolejka jest pusta.\n");
    }
    else {
        printf("Zawartosc kolejki:\n");
        while (current != NULL) {
            printf("%s %s (Rok urodzenia: %d)\n", current->data.imie, current->data.nazwisko, current->data.rok_urodzenia);
            current = current->next;
        }
    }
}

void count(const struct Queue* queue) {
    printf("Liczba elementow: %d\n", queue->count);
}

void clear(struct Queue* queue) {
    while (queue->front != NULL) {
        struct Node* temp = queue->front;
        queue->front = queue->front->next;
        free(temp);
    }

    queue->rear = NULL;
    printf("Wszystkie elementy zostaly usuniete.\n");
}

int main() {
    struct Queue* queue = createQueue();
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
        case ENQUEUE: {
            enqueue(queue);
            break;
        }
        case DEQUEUE: {
            dequeue(queue);
            break;
        }
        case FIND: {
            find(queue);
            break;
        }
        case PRINT: {
            print(queue);
            break;
        }
        case COUNT: {
            count(queue);
            break;
        }
        case CLEAR: {
            clear(queue);
            break;
        }
        case EXIT: {
            clear(queue);
            return 0;
        }
        default: {
            printf("Niepoprawny wybor.\n");
        }
        }
    }
    return 0;
}
