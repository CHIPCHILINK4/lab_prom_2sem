#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

//Все базовые операции над списками
//0. PRINTIIIIIIIIIIII
//1. Добавление после заданного элемента
//2. Удаление «головы»
//3. Удаление «хвоста»
//4. Удаление элемента перед заданным элементом
//5. Удаление элемента после заданного элемента
//6. Удаление в заданной позиции
//7. упорядочевание списка по значению х
//8. проверка функций

struct point {
    int x;
    int y;
    struct point* next;
};



//0. PRINTIIIIIIIIIIII
void countttttttttttttt(struct point* list, size_t* count);

void printi(struct point* list) {
    if (list)
    {
        struct point* ptrIx = NULL;
        ptrIx = list;
        size_t count = 0;
        //size_t a = 0;
        //countttttttttttttt(list, &a);
        //printf("%zu\n", a);
        for (; ptrIx; ptrIx = ptrIx->next) {
            printf("x = %d; y = %d;\n", ptrIx->x, ptrIx->y);
            count += 1;
        }
        printf("%zu\n", count);
        printf("\n");
    }
    else {
        printf("ERR: list is not find\n");
    }
}

void countttttttttttttt(struct point* list, size_t* count) {
    if (list) {
        struct point* ptrIx = list;
        for (; ptrIx; ptrIx = ptrIx->next) {
            *count += 1;
        }
    }
}

void create_list(struct point** list, size_t count) {
    if (list) {
        struct point* el_a = (struct point*)calloc(1, sizeof(struct point));
        (*list) = el_a;
        if (*list) {
            size_t i = 0;
            for (struct point* ptrIx = *list; i < count; ptrIx = ptrIx->next) {
                ptrIx->next = (struct point*)calloc(1, sizeof(struct point));
                ptrIx->x = i;
                ptrIx->y = i + 1;

                i++;
                if (i == count) {
                    free(ptrIx->next);
                    ptrIx->next = NULL;
                }
            }
        }
    }
}

void free_list(struct point** list) {
    if ((*list) && (list)) {
        struct point* ptrIx = *list;
        struct point* ptr = NULL;
        for (; ptrIx; ptrIx = ptr) {
            ptr = ptrIx->next;
            free(ptrIx);
        }
        *list = NULL;
    }
}

//1.Добавление после заданного элемента
struct point* addBefore_Bez_ficthead(struct point** list, int x, int y, int goalX, int goalY) {
    if ((*list) && (list)) {
        struct point* newEl = (struct point*)calloc(1, sizeof(struct point));
        if (!newEl) {
            return NULL;
        }

        newEl->x = x;
        newEl->y = y;
        newEl->next = NULL;

        if (*list == NULL || ((*list)->x == goalX && (*list)->y == goalY)) {
            newEl->next = *list;
            *list = newEl;
            return newEl;
        }

        struct point* ptrIx = *list;

        for (; ptrIx->next && (ptrIx->next->x != goalX || ptrIx->next->y != goalY); ptrIx = ptrIx->next);

        if (ptrIx->next == NULL) {
            free(newEl);
            return NULL;
        }

        newEl->next = ptrIx->next;
        ptrIx->next = newEl;
        return newEl;
    }
    return NULL;
}

struct point* addBefore_C_ficthead(struct point** list, int x, int y, int goalX, int goalY) {
    if ((*list) && (list)) {
        struct point* fict_head = (struct point*)calloc(1, sizeof(struct point));
        if (!fict_head) {
            return NULL;
        }
        fict_head->next = *list;

        struct point* newEl = (struct point*)calloc(1, sizeof(struct point));
        if (!newEl) {
            free(fict_head);
            return NULL;
        }

        newEl->x = x;
        newEl->y = y;
        newEl->next = NULL;

        struct point* ptrIx = fict_head;

        for (; ptrIx->next && (ptrIx->next->x != goalX || ptrIx->next->y != goalY); ptrIx = ptrIx->next);

        if (ptrIx->next == NULL) {
            free(newEl);
            free(fict_head);
            return NULL;
        }

        newEl->next = ptrIx->next;
        ptrIx->next = newEl;

        *list = fict_head->next;

        free(fict_head);
        return newEl;
    }
    return NULL;
}


//2. Удаление «головы»
struct point* delHead(struct point** list) {
    if ((list) && (*list)) {
        struct point* ptrIx = *list;

        *list = (*list)->next;
        free(ptrIx);
        return *list;
    }
    return NULL;
}

//3. Удаление «хвоста»
struct point* delTail(struct point** list) {
    if ((list) && (*list)) {

        if (!((*list)->next)) {               // Список из одного элемента
            free(*list);
            *list = NULL;
            return NULL;
        }

        struct point* ptrIx = *list;
        for (; (ptrIx->next) && (ptrIx->next->next); ptrIx = ptrIx->next);
        free(ptrIx->next);
        ptrIx->next = NULL;
        return ptrIx;
    }
    return NULL;
}

//4. Удаление элемента после заданного элемента
struct point* delAfter(struct point** list, int goalX, int goalY) {
    if ((*list) && (list) && ((*list)->next)) {

        struct point* ptrIx = *list;

        for (; ptrIx && (ptrIx->x != goalX || ptrIx->y != goalY); ptrIx = ptrIx->next);

        if (ptrIx == NULL) {

            return NULL;
        }

        struct point* ptr = ptrIx->next;

        ptrIx->next = ptrIx->next->next;
        free(ptr);
        return ptrIx;
    }
    return NULL;
}

//5.  Удаление элемента перед заданным элементом
struct point* delBefore(struct point** list, int goalX, int goalY) {
    if ((*list) && (list)) {

        if ((*list)->x == goalX && (*list)->y == goalY) {
            return NULL;
        }

        if ((*list)->next && (*list)->next->x == goalX && (*list)->next->y == goalY) {
            struct point* ptr = *list;
            *list = ptr->next;
            free(ptr);
            return *list;
        }

        struct point* ptrIx = *list;
        for (; ptrIx->next && ptrIx->next->next && (ptrIx->next->next->x != goalX || ptrIx->next->next->y != goalY); ptrIx = ptrIx->next);

        if (ptrIx->next == NULL) {
            return NULL;
        }

        struct point* ptr = ptrIx->next;
        if (ptrIx->next && ptrIx->next->next && ptrIx->next->next->next) {
            ptrIx->next = ptrIx->next->next->next;
        }
        else {
            ptrIx->next = NULL;
        }
        free(ptr);

        return ptrIx;
    }
    return NULL;
}


//6. Удаление в заданной позиции
struct point* delEl(struct point** list, int goalX, int goalY) {
    if ((*list) && (list)) {


        if ((*list)->x == goalX && (*list)->y == goalY) {
            struct point* ptr = *list;
            *list = (*list)->next;
            free(ptr);
            return *list;
        }

        struct point* ptrIx = *list;
        for (; ptrIx->next && (ptrIx->next->x != goalX || ptrIx->next->y != goalY); ptrIx = ptrIx->next);

        if (ptrIx->next == NULL) {
            return NULL;
        }

        if (ptrIx->next->next) {
            struct point* ptr = ptrIx->next;
            ptrIx->next = ptrIx->next->next;
            free(ptr);
        }
        else {
            free(ptrIx->next);
            ptrIx->next = NULL;
        }

        return ptrIx;
    }
    return NULL;
}

//7. упорядочевание списка по значению х
struct point* sortListX(struct point** list) {
    if ((*list) && (list)) {
        struct point* fict_head = (struct point*)calloc(1, sizeof(struct point));
        fict_head->next = *list;
        struct point* ptrIx = (*list)->next;
        (*list)->next = NULL;
        struct point* ptrnx = NULL;

        for (; ptrIx; ptrIx = ptrnx) {
            ptrnx = ptrIx->next;
            ptrIx->next = NULL;
            struct point* ptrJx = fict_head;
            for (; ptrJx->next && (ptrIx->x > ptrJx->next->x); ptrJx = ptrJx->next);

            ptrIx->next = ptrJx->next;
            ptrJx->next = ptrIx;
        }

        *list = fict_head->next;
        free(fict_head);
        return *list;
    }
    return NULL;
}

//8. проверка функций
//9.проверка функций
//ФУУУУУУУУУУУУУУУУУУУУУУУУУУУУУУУУУУУУУУУУУУУУУУУУУУУУУУУУУУУУУУУУУУУУУУУУУУУУУУУУУУУУУУУНКЦИИ
void addToHead1(struct point* list, int x, int y)//не работает тк нужен двойной указатель
{
    struct point* PtrIx = (struct point*)malloc(sizeof(struct point));
    if (PtrIx)
    {
        PtrIx->x = x;
        PtrIx->y = y;
        PtrIx->next = NULL;
        if (list == NULL)
            list = PtrIx;
        else
        {
            PtrIx->next = list;
            list = PtrIx;
        }
    }
}

struct point* addToHead2(struct point* list, int x, int y)
{
    struct point* PtrIx = (struct point*)malloc(sizeof(struct point));
    if (PtrIx)
    {
        PtrIx->x = x;
        PtrIx->y = y;
        PtrIx->next = NULL;
        if (list == NULL)
            list = PtrIx;
        else
        {
            PtrIx->next = list;
            list = PtrIx;
        }
        return PtrIx;
    }
    return NULL;
}

bool addToHead3(struct point** list, int x, int y)
{
    struct point* PtrIx = (struct point*)malloc(sizeof(struct point));
    if (PtrIx)
    {
        PtrIx->x = x;
        PtrIx->y = y;
        PtrIx->next = NULL;
        if (*list == NULL)
            *list = PtrIx;
        else
        {
            PtrIx->next = *list;
            *list = PtrIx;
        }
        return true;
    }
    return false;
}

struct point* addToHead4(struct point** list, int x, int y)
{
    struct point* PtrIx = (struct point*)malloc(sizeof(struct point));
    if (PtrIx)
    {
        PtrIx->x = x;
        PtrIx->y = y;
        PtrIx->next = NULL;
        if (*list == NULL)
            *list = PtrIx;
        else
        {
            PtrIx->next = *list;
            *list = PtrIx;
        }
        return PtrIx;
    }
    return NULL;
}
//фууууууууууууууууууууууууууууууууууууууууууууууууууууункции


int main() {
    /*clock_t tic, toc;
    tic = clock();
    some_function();
    toc = clock();

    printf("%f seconds!\n\n", (double)(toc - tic) / CLOCKS_PER_SEC);*/

    struct point* head = NULL;//по поводу хвоста я подумал что он не нужен
    size_t count = 10;

    create_list(&head, count);


    printi(head);

    delHead(&head);
    printi(head);

    addBefore_Bez_ficthead(&head, 12, 13, 6, 7);
    printi(head);

    addBefore_C_ficthead(&head, 13, 14, 4, 5);
    printi(head);

    delEl(&head, 12, 13);
    delTail(&head);
    printi(head);

    //9.проверка функций
    //ФУУУУУУУУУУУУУУУУУУУУУУУУУУУУУУУУУУУУУУУУУУУУУУУУУУУУУУУУУУУУУУУУУУУУУУУУУУУУУУУУУУУУУУУНКЦИИ
    addToHead1(head, 17, 15);
    head = addToHead2(head, 20, 15);
    addToHead3(&head, 30, 15);
    addToHead4(&head, 400, 15);
    printi(head);
    //фууууууууууууууууууууууууууууууууууууууууууууууууууууункции

    sortListX(&head);
    printi(head);


    free_list(&head);
    printf("%p\n", head);

    return 0;
}


