#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const int MAX_SIZE = 100;

struct Student {
    char imie[50];
    char nazwisko[50];
    int rok_urodzenia;
};

struct Queue {
    struct Student data[100];
    int front;  
    int rear;   
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

void enqueue(struct Queue* queue) {
    if (queue->rear == MAX_SIZE - 1) {
        printf("Kolejka jest pelna.\n");
        return;
    }
    else {
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
        if (scanf_s("%d", &student.rok_urodzenia) != 1)
        {
            printf("Bledne dane. \n");
            exit(0);
        }

        getchar();
        queue->rear++;
        queue->data[queue->rear] = student;
    }
}

void dequeue(struct Queue* queue) {
    if (queue->front > queue->rear) {
        printf("Kolejka jest pusta.\n");
        return;
    }
    printf("Usunieto element: %s %s\n", queue->data[queue->front].imie, queue->data[queue->front].nazwisko);
    queue->front++;
}

void find(const struct Queue* queue) {
    char nazwisko[50];
    printf("Podaj nazwisko do wyszukania: ");
    fgets(nazwisko, sizeof(nazwisko), stdin);
    nazwisko[strlen(nazwisko) - 1] = '\0';
    for (int i = queue->front; i <= queue->rear; i++) {
        if (strcmp(queue->data[i].nazwisko, nazwisko) == 0) {
            printf("Znaleziono studenta: %s %s (Rok urodzenia: %d)\n", queue->data[i].imie, queue->data[i].nazwisko, queue->data[i].rok_urodzenia);
            return;
        }
    }
    printf("Nie znaleziono studenta o nazwisku: %s\n", nazwisko);
}

void print(const struct Queue* queue) {
    if (queue->front > queue->rear) {
        printf("Kolejka jest pusta.\n");
    }
    else {
        printf("Zawartosc kolejki:\n");
        for (int i = queue->front; i <= queue->rear; i++) {
            printf("%s %s (Rok urodzenia: %d)\n", queue->data[i].imie, queue->data[i].nazwisko, queue->data[i].rok_urodzenia);
        }
    }
}

int count(const struct Queue* queue) {
    printf("Liczba elementow: %d\n", queue->rear - queue->front + 1);
}

void clear(struct Queue* queue) {
    queue->front = 0;
    queue->rear = -1;
    printf("Wszystkie elementy zostały usunięte.\n");
}

int main() {
    struct Queue queue;
    queue.front = 0;
    queue.rear = -1;
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
            enqueue(&queue);
            break;
        }
        case DEQUEUE: {
            dequeue(&queue);
            break;
        }
        case FIND: {
            find(&queue);
            break;
        }
        case PRINT: {
            print(&queue);
            break;
        }
        case COUNT: {
            count(&queue);
            break;
        }
        case CLEAR: {
            clear(&queue);
            break;
        }
        case EXIT: {
            clear(&queue);
            return 0;
        }
        default: {
            printf("Niepoprawny wybor.\n");
        }
        }
    }
    return 0;
}
