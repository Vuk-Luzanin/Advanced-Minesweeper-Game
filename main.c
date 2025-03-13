#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    double x;
    double y;
    double r;
} Node;

typedef struct {
    int data[100];
    int top;
} Stack;

void initializeStack(Stack* stack) {
    stack->top = -1;
}

int isEmpty(Stack* stack) {
    return stack->top == -1;
}

void push(Stack* stack, int item) {
    stack->data[++stack->top] = item;
}

int pop(Stack* stack) {
    if (isEmpty(stack)) {
        printf("Stack underflow!\n");
        return -1;
    }
    return stack->data[stack->top--];
}

int top(Stack* stack) {
    if (isEmpty(stack)) {
        printf("Stack je prazan!\n");
        return -1;
    }
    return stack->data[stack->top];
}


int nadjiBrojCvorova(FILE* inputFile) {
    int brojCvorova;                                                                      //broj cvorova
    fscanf(inputFile, "%d", &brojCvorova);
    return brojCvorova;
}


int nadjiId(Node **nizCvorova, int brojCvorova, double x, double y, double r) {
    int id;
    for (int i = 0; i < brojCvorova; i++) {
        if (nizCvorova[i] -> x == x && nizCvorova[i] -> y == y && nizCvorova[i] -> r == r) {
            id = i;
            break;
        }
    }
    return id;
}


Node** formGraph(int brojCvorova, FILE* inputFile) {
    Node **nizCvorova = malloc(brojCvorova * sizeof(Node*));                        //niz pokazivaca na cvorove
    for (int i = 0; i < brojCvorova; i++) {
        Node *node = malloc(sizeof(Node));
        fscanf(inputFile, "%lf %lf %lf", &node->x, &node->y, &node->r);
        nizCvorova[i] = node;
    }

    for (int i = 0; i < brojCvorova; i++) {
        printf("%.2f %.2f %.2f\n", nizCvorova[i]->x, nizCvorova[i]->y, nizCvorova[i]->r);
    }
    putchar('\n');
    return nizCvorova;
}


int** formBlankMatrix(int brojCvorova) {
    int **matrix = calloc(brojCvorova, sizeof(int*));
    for (int i = 0; i < brojCvorova; i++) {
        matrix[i] = calloc(brojCvorova, sizeof(int));
        for (int j = 0; j < brojCvorova; j++) {
            matrix[i][j] = 0;
        }
    }
    return matrix;
}


int** formMatrix2(int brojCvorova, Node** nizCvorova) {
    int **matrix = calloc(brojCvorova, sizeof(int*));
    for (int i = 0; i < brojCvorova; i++) {
        matrix[i] = calloc(brojCvorova, sizeof(int));
        for (int j = 0; j < brojCvorova; j++) {
            matrix[i][j] = 0;
        }
    }
    for (int i = 0; i < brojCvorova; i++) {
        for (int j = 0; j < brojCvorova; j++) {
            if ((nizCvorova[j] -> x - nizCvorova[i] -> x) * (nizCvorova[j] -> x - nizCvorova[i] -> x) + (nizCvorova[j] -> y - nizCvorova[i] -> y) * (nizCvorova[j] -> y - nizCvorova[i] -> y) <= (nizCvorova[i] -> r)*(nizCvorova[i] -> r)) {
                matrix[i][j] = 1;
            }
        }
    }

    return matrix;
}


Node** addNodeInGraph(Node ***nizCvorova, int *brojCvorova) {                                   //menja brojCvorova
    printf("Unesite koordinate čvora i poluprečnik po formatu: x y r\n");
    *nizCvorova = realloc(*nizCvorova, ++(*brojCvorova) * sizeof(Node*));
    Node *node = malloc(sizeof(Node*));
    scanf("%lf %lf %lf", &node -> x, &node -> y, &node -> r);
    (*nizCvorova)[*brojCvorova - 1] = node;
    return *nizCvorova;
}


Node** addRocketInGraph(Node ***nizCvorova, int *brojCvorova) {                                   //menja brojCvorova
    printf("Unesite koordinate rakete i poluprečnik po formatu: x y r\n");
    *nizCvorova = realloc(*nizCvorova, ++(*brojCvorova) * sizeof(Node*));
    Node *node = malloc(sizeof(Node*));
    scanf("%lf %lf %lf", &node -> x, &node -> y, &node -> r);
    (*nizCvorova)[*brojCvorova - 1] = node;
    return *nizCvorova;
}


int** addNodeInMatrix( int ***matrix, int brojCvorova) {
    *matrix = realloc(*matrix, brojCvorova * sizeof(int*));
    (*matrix)[brojCvorova - 1] = NULL;
    for (int i = 0; i < brojCvorova; i++) {
        (*matrix)[i] = realloc((*matrix)[i], brojCvorova * sizeof(int));
    }
    return *matrix;
}


void printfMatrix(int **matrix, int brojCvorova) {
    printf("Ovako izgleda matrična reprezentacija vašeg grafa.\n");
    for (int i = 0; i < brojCvorova; i++) {
        for (int j = 0; j < brojCvorova; j++) {
            printf("%d ", matrix[i][j]);
        }
        putchar('\n');
    }
    putchar('\n');
}


void printGraph(int brojCvorova, Node **nizCvorova) {
    for (int i = 0; i < brojCvorova; i++) {
        printf("%.2f %.2f %.2f\n", nizCvorova[i]->x, nizCvorova[i]->y, nizCvorova[i]->r);
    }
    putchar('\n');
}


void freeGraph(int **matrix, Node **nizCvorova, int brojCvorova) {
    for (int i = 0; i < brojCvorova; i++) {
        free(nizCvorova[i]);
        free(matrix[i]);
    }
    free(nizCvorova);
    free(matrix);
}


Node** deleteNodeInGraph(Node ***nizCvorova, int *brojCvorova, int id) {                                //menja brojCvorova
    free((*nizCvorova)[id]);
    for (int i = id; i < *brojCvorova - 1; i++) {
        (*nizCvorova)[i] = (*nizCvorova)[i + 1];
    }
    *nizCvorova = realloc(*nizCvorova, --(*brojCvorova) * sizeof(Node*));
    return *nizCvorova;
}


int** deleteNodeInMatrix(int ***matrix, int brojCvorova, int id) {
    brojCvorova++;
    for (int i = 0; i < brojCvorova; i++) {
        for (int j = id; j < brojCvorova - 1; j++) {
            (*matrix)[i][j] = (*matrix)[i][j + 1];
        }
        (*matrix)[i] = realloc((*matrix)[i], (brojCvorova - 1) * sizeof(int));
    }
    for (int i = id; i < brojCvorova - 1; i++) {
        (*matrix)[i] = (*matrix)[i + 1];
    }
    *matrix = realloc(*matrix, (brojCvorova - 1) * sizeof(int*));
    return *matrix;
}


int findEffectivenessOfMine(Node** nizCvorova, int** matrix, int brojCvorova, int id, Stack *stack) {
    int br = 0;
    int tmp;
    int visit[brojCvorova];
    for (int i = 0; i < brojCvorova; i++) {
        visit[i] = 0;
    }
    printf("Detonirane mine su:\n");
    push(stack, id);
    while (!isEmpty(stack)) {
        tmp = pop(stack);
        if (!visit[tmp]) {
            visit[tmp] = 1;
            printf("%.2f %.2f %.2f\n", nizCvorova[tmp]->x, nizCvorova[tmp]->y, nizCvorova[tmp]->r);
            br++;
            for (int i = 0; i < brojCvorova; i++) {
                if (matrix[tmp][i] == 1) {
                    if (!visit[i]) {
                        push(stack, i);
                    }
                }
            }
        }
    }
    return br;
}


int findEffectivenessOfMineWithoutPrint(Node** nizCvorova, int** matrix, int brojCvorova, int id, Stack *stack) {
    int br = 0;
    int tmp;
    int visit[brojCvorova];
    for (int i = 0; i < brojCvorova; i++) {
        visit[i] = 0;
    }
    push(stack, id);
    while (!isEmpty(stack)) {
        tmp = pop(stack);
        if (!visit[tmp]) {
            visit[tmp] = 1;
            br++;
            for (int i = 0; i < brojCvorova; i++) {
                if (matrix[tmp][i] == 1) {
                    if (!visit[i]) {
                        push(stack, i);
                    }
                }
            }
        }
    }
    return br;
}


int* findMinesThatExplode(Node** nizCvorova, int** matrix, int brojCvorova, int id, Stack *stack) {
    int isDetonated[brojCvorova];
    for (int i = 0; i < brojCvorova; i++) {
        isDetonated[i] = 0;
    }
    int br = 0;
    int tmp;
    int visit[brojCvorova];
    for (int i = 0; i < brojCvorova; i++) {
        visit[i] = 0;
    }
    push(stack, id);
    while (!isEmpty(stack)) {
        tmp = pop(stack);
        if (!visit[tmp]) {
            visit[tmp] = 1;
            isDetonated[nadjiId(nizCvorova, brojCvorova, nizCvorova[tmp]->x, nizCvorova[tmp]->y, nizCvorova[tmp]->r)] = 1;
            for (int i = 0; i < brojCvorova; i++) {
                if (matrix[tmp][i] == 1) {
                    if (!visit[i]) {
                        push(stack, i);
                    }
                }
            }
        }
    }
    return isDetonated;
}


double findSurface(Node** nizCvorova, int** matrix, int brojCvorova, int max, Stack *stack) {
    double p = 0;
    printf("Broj detoniranih mina je: %d.\n\n", findEffectivenessOfMine(nizCvorova, matrix, brojCvorova, max, stack));
    int *isDetonated = findMinesThatExplode(nizCvorova, matrix, brojCvorova, max, stack);           //za sve koje su detonirane stoji 1
    double maxX = 0, maxY = 0;                                      //gornja desna granica
    for (int i = 0; i < brojCvorova; i++) {
        if (maxX < nizCvorova[i]->x + nizCvorova[i]->r) {
            maxX = nizCvorova[i]->x + nizCvorova[i]->r;
        }
        if (maxY < nizCvorova[i]->y + nizCvorova[i]->r) {
            maxY = nizCvorova[i]->y + nizCvorova[i]->r;
        }
    }
    for (int i = 0; i < 1000000; i++) {
        double randomX = ((double)rand() / RAND_MAX) * 2 * maxX - maxX;
        double randomY = ((double)rand() / RAND_MAX) * 2 * maxY - maxY;
        for (int j = 0; j < brojCvorova; j++) {
            if (isDetonated[j]) {
                if ((randomX - nizCvorova[j]->x) * (randomX - nizCvorova[j]->x) + (randomY - nizCvorova[j]->y) * (randomY - nizCvorova[j]->y) <= nizCvorova[j]->r * nizCvorova[j]->r) {
                    p++;
                    break;
                }
            }
        }
    }
    double Pu = 2 * maxX * 2 * maxY;
    if (Pu < 0) {
        Pu = -Pu;
    }
    p = p / 1000000*Pu;
    return p;
}


int main() {
    int zad;
    int **matrix;
    Node **nizCvorova;
    int brojCvorova;
    Stack stack;
    initializeStack(&stack);

    printf("Počeli ste igru, izaberite broj zadatka koji rešavate (1 ili 2).\n");
    printf("Igru možete inicijalizovati popunjavanje određene datoteke.\n");
    scanf("%d", &zad);
    if (zad == 1) {                                                                             //radi se prvi zadatak
        printf("Rešavate 1. zadatak, izaberite neku od sledećih stavki:\n");
        printf("1. Kreiranje prazne strukture podataka za graf zadatih dimenzija.\n");
        printf("2. Dodavanje čvora u graf i uklanjanje čvora iz grafa.\n");
        printf("3. Dodavanje i uklanjanje grane između dva čvora u grafu.\n");
        printf("4. Ispis reprezentacije grafa.\n");
        printf("5. Brisanje grafa iz memorije.\n");
        printf("6. Kraj igre.\n");
        printf("7. Ispiši graf, kao u datoteci.\n");
        int pr;
        while (1) {
            scanf("%d", &pr);
            if (pr == 1) {
                FILE *inputFile = fopen("graf1.txt", "r");
                if (inputFile == NULL) {
                    printf("DAT_GRESKA");
                    return 0;
                }
                brojCvorova = nadjiBrojCvorova(inputFile);
                nizCvorova = formGraph(brojCvorova, inputFile);
                matrix = formBlankMatrix(brojCvorova);
                fclose(inputFile);

            } else if (pr == 2) {
                int opt;
                printf("Unesite 1 ako želite da dodate čvor u graf i 2 ako želite da izbrišete.\n");
                scanf("%d", &opt);

                if (opt == 1) {
                    nizCvorova = addNodeInGraph(&nizCvorova, &brojCvorova);
                    addNodeInMatrix(&matrix, brojCvorova);

                } else if (opt == 2) {
                    printGraph(brojCvorova, nizCvorova);
                    printf("Unesite redni broj čvora koji želite da izbacite (indeks kreće od 0).\n");
                    int id;
                    scanf("%d", &id);
                    nizCvorova = deleteNodeInGraph(&nizCvorova, &brojCvorova, id);
                    deleteNodeInMatrix(&matrix, brojCvorova, id);
                }
            } else if (pr == 3) {
                int start, end;
                printf("Unesite granu koju želite da dodate/oduzmete po formatu: startNode endNode.\n");
                scanf("%d %d", &start, &end);
                int opt;
                printf("Unesite 1 ako želite da dodate granu u graf i 2 ako želite da izbrišete.\n");
                scanf("%d", &opt);

                if (opt == 1) {
                    matrix[start][end] = 1;

                } else if (opt == 2) {
                    matrix[start][end] = 0;
                }
            }
            if (pr == 4) {
                printfMatrix(matrix, brojCvorova);

            } else if (pr == 5) {
                freeGraph(matrix, nizCvorova, brojCvorova);

            } else if (pr == 6) {
                printf("Završili ste igru.");
                freeGraph(matrix, nizCvorova, brojCvorova);
                return 0;

            } else if (pr == 7) {
                printGraph(brojCvorova, nizCvorova);
            } else {
                printf("Uneli ste nekorektnu vrednost, pokušajte ponovo.\n");
            }
            printf("Rešavate 1. zadatak, izaberite neku od sledećih stavki:\n");
            printf("1. Kreiranje prazne strukture podataka za graf zadatih dimenzija.\n");
            printf("2. Dodavanje čvora u graf i uklanjanje čvora iz grafa.\n");
            printf("3. Dodavanje i uklanjanje grane između dva čvora u grafu.\n");
            printf("4. Ispis reprezentacije grafa.\n");
            printf("5. Brisanje grafa iz memorije.\n");
            printf("6. Kraj igre.\n");
            printf("7. Ispiši graf, kao u datoteci.\n");
        }
    } else if (zad == 2) {
        printf("Rešavate 2. zadatak, izaberite neku od sledećih stavki:\n");
        printf("1. Kreiranje grafa prema izabranom modelu u ulaznom fajlu.\n");
        printf("2. Pronalazak efikasnosti izabrane mine.\n");
        printf("3. Pronalaženje mine maksimalne efikasnosti.\n");
        printf("4. Eksplozija rakete na zadatom mestu.\n");
        printf("5. Pronalaženje ukupne površine koja je pokrivena eksplozijom mine maksimalne efikasnosti.\n");
        printf("6. Kraj igre.\n");
        printf("7. Ispis reprezentacije grafa.\n");
        printf("8. Ispiši graf, kao u datoteci.\n");
        printf("9. Dodavanje mine u graf i uklanjanje mine iz grafa.\n");
        printf("10. Brisanje grafa iz memorije.\n");
        int pr;
        while (1) {
            scanf("%d", &pr);
            if (pr == 1) {
                printf("Rešavate 2. zadatak, izaberite neku od sledećih stavki:\n");
                FILE *inputFile = fopen("graf1.txt", "r");
                if (inputFile == NULL) {
                    printf("DAT_GRESKA");
                    return 0;
                }
                brojCvorova = nadjiBrojCvorova(inputFile);
                nizCvorova = formGraph(brojCvorova, inputFile);
                matrix = formMatrix2(brojCvorova, nizCvorova);
                fclose(inputFile);

            } else if (pr == 2) {
                int id;
                printf("Unesite redni broj mine čiju efikasnost želite da odredite (indeks kreće od 0).\n");
                printGraph(brojCvorova, nizCvorova);
                scanf("%d", &id);
                printf("Broj detoniranih mina je: %d.\n\n",
                       findEffectivenessOfMine(nizCvorova, matrix, brojCvorova, id, &stack));

            } else if (pr == 3) {
                int all[brojCvorova];                                               //efikasnosti svih mina
                int max = 0;                                                        //redni broj najefikasnije mine
                for (int i = 0; i < brojCvorova; i++) {
                    all[i] = findEffectivenessOfMineWithoutPrint(nizCvorova, matrix, brojCvorova, i, &stack);
                }
                for (int i = 0; i < brojCvorova; i++) {
                    if (all[max] < all[i]) {
                        max = i;
                    }
                }
                printGraph(brojCvorova, nizCvorova);
                printf("Najefikasnija je mina pod rednim brojem %d, sa efikasnošću %d.\n\n", max, all[max]);

            } else if (pr == 4) {
                nizCvorova = addRocketInGraph(&nizCvorova, &brojCvorova);
                addNodeInMatrix(&matrix, brojCvorova);
                for (int i = 0; i < brojCvorova; i++) {
                    for (int j = 0; j < brojCvorova; j++) {
                        matrix[i][j] = 0;
                        if ((nizCvorova[j]->x - nizCvorova[i]->x) * (nizCvorova[j]->x - nizCvorova[i]->x) +
                            (nizCvorova[j]->y - nizCvorova[i]->y) * (nizCvorova[j]->y - nizCvorova[i]->y) <=
                            (nizCvorova[i]->r) * (nizCvorova[i]->r)) {
                            matrix[i][j] = 1;
                        }
                    }
                }
                printGraph(brojCvorova, nizCvorova);
                printf("Broj detoniranih mina (uključujući i raketu) je: %d.\n\n",
                       findEffectivenessOfMine(nizCvorova, matrix, brojCvorova, brojCvorova - 1, &stack));

            } else if (pr == 5) {
                int all[brojCvorova];                                               //efikasnosti svih mina
                int max = 0;                                                        //redni broj najefikasnije mine
                double p;
                for (int i = 0; i < brojCvorova; i++) {
                    all[i] = findEffectivenessOfMineWithoutPrint(nizCvorova, matrix, brojCvorova, i, &stack);
                }
                for (int i = 0; i < brojCvorova; i++) {
                    if (all[max] < all[i]) {
                        max = i;
                    }
                }
                printGraph(brojCvorova, nizCvorova);
                printf("Najefikasnija je mina pod rednim brojem %d.\n", max);
                p = findSurface(nizCvorova, matrix, brojCvorova, max, &stack);
                printf("Površina je %.2f.\n\n", p);

            } else if (pr == 6) {
                printf("Završili ste igru.");
                freeGraph(matrix, nizCvorova, brojCvorova);
                return 0;

            } else if (pr == 7) {
                printfMatrix(matrix, brojCvorova);

            } else if (pr == 8) {
                printGraph(brojCvorova, nizCvorova);

            } else if (pr == 9) {
                int opt;
                printf("Unesite 1 ako želite da dodate minu u graf i 2 ako želite da izbrišete.\n");
                scanf("%d", &opt);

                if (opt == 1) {
                    nizCvorova = addNodeInGraph(&nizCvorova, &brojCvorova);
                    addNodeInMatrix(&matrix, brojCvorova);
                    for (int i = 0; i < brojCvorova; i++) {
                        for (int j = 0; j < brojCvorova; j++) {
                            matrix[i][j] = 0;
                            if ((nizCvorova[j]->x - nizCvorova[i]->x) * (nizCvorova[j]->x - nizCvorova[i]->x) +
                                (nizCvorova[j]->y - nizCvorova[i]->y) * (nizCvorova[j]->y - nizCvorova[i]->y) <=
                                (nizCvorova[i]->r) * (nizCvorova[i]->r)) {
                                matrix[i][j] = 1;
                            }
                        }
                    }

                } else if (opt == 2) {
                    printGraph(brojCvorova, nizCvorova);
                    printf("Unesite redni broj mine koju želite da izbacite (indeks kreće od 0).\n");
                    int id;
                    scanf("%d", &id);
                    nizCvorova = deleteNodeInGraph(&nizCvorova, &brojCvorova, id);
                    deleteNodeInMatrix(&matrix, brojCvorova, id);
                    for (int i = 0; i < brojCvorova; i++) {
                        for (int j = 0; j < brojCvorova; j++) {
                            matrix[i][j] = 0;
                            if ((nizCvorova[j]->x - nizCvorova[i]->x) * (nizCvorova[j]->x - nizCvorova[i]->x) +
                                (nizCvorova[j]->y - nizCvorova[i]->y) * (nizCvorova[j]->y - nizCvorova[i]->y) <=
                                (nizCvorova[i]->r) * (nizCvorova[i]->r)) {
                                matrix[i][j] = 1;
                            }
                        }
                    }
                }
            } else if (pr == 10) {
                freeGraph(matrix, nizCvorova, brojCvorova);

            } else {
                printf("Uneli ste nekorektnu vrednost, pokušajte ponovo.\n");
            }
            printf("Rešavate 2. zadatak, izaberite neku od sledećih stavki:\n");
            printf("1. Kreiranje grafa prema izabranom modelu u ulaznom fajlu.\n");
            printf("2. Pronalazak efikasnosti izabrane mine.\n");
            printf("3. Pronalaženje mine maksimalne efikasnosti.\n");
            printf("4. Eksplozija rakete na zadatom mestu.\n");
            printf("5. Pronalaženje ukupne površine koja je pokrivena eksplozijom mine maksimalne efikasnosti.\n");
            printf("6. Kraj igre.\n");
            printf("7. Ispis reprezentacije grafa.\n");
            printf("8. Ispiši graf, kao u datoteci.\n");
            printf("9. Dodavanje mine u graf i uklanjanje mine iz grafa.\n");
            printf("10. Brisanje grafa iz memorije.\n");
        }
    }
    return 0;
}