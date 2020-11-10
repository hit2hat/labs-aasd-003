#include <cstdio>
#include <cmath>

struct Node {
    double value;
    struct Node* next = nullptr;
};

/*
 * Функция выводит динамический список
 */
void printList(struct Node* head) {
    struct Node* x = head;
    while (x != nullptr) {
        printf("%g ", x->value);
        x = x->next;
    }
}

/*
 * Функция вставляет элемент в конец динамического списка
 */
void push(struct Node* *head, double newValue) {
    // Создаем новый элемент
    struct Node* newNode = new Node;
    newNode->value = newValue;
    newNode->next = nullptr;

    // Находим последний элемент списка
    if (*head == nullptr) {
        *head = newNode;
    } else {
        struct Node* x = *head;
        while (x->next != nullptr) {
            x = x->next;
        }

        x->next = newNode;
    }
}

/*
 * Создает динамический список, спрашивая у пользователя значения элементов
 */
void fillList(struct Node* *head, int count) {
    struct Node* x = *head;
    while (x != nullptr) {
        x = x->next;
    }

    for (int i = 0; i < count; i++) {
        double x;

        printf("> ");
        scanf("%lf", &x);

        push(head, x);
    }
}

/*
 * Функция вставляет элемент динамического списка с учетом его значения (по возрастанию)
 */
void sortedInsert(struct Node* *head, struct Node* newNode)
{
    if (*head == nullptr || (*head)->value >= newNode->value)
    {
        newNode->next = *head;
        *head = newNode;
    }
    else
    {
        struct Node* x = *head;
        while (x->next != nullptr && x->next->value < newNode->value)
        {
            x = x->next;
        }

        newNode->next = x->next;
        x->next = newNode;
    }
}

/*
 * Функция сортирует динамический список
 */
struct Node* sort(struct Node* head)
{
    struct Node* sorted = nullptr;
    struct Node* x = head;

    while (x != nullptr)
    {
        struct Node* newNode = new Node;
        newNode->value = x->value;
        newNode->next = nullptr;
        sortedInsert(&sorted, newNode);
        x = x->next;
    }

    return sorted;
}

/*
 * Функция считает сумму всех элементов в динамическом списке
 */
double sum(struct Node* head) {
    double result = 0;
    struct Node* x = head;

    while (x != nullptr) {
        result += x->value;
        x = x->next;
    }

    return result;
}

/*
 * Функция возвращает значение по индексу элемента динамического списка
 */
double getByIndex(struct Node* head, int index) {
    int currentIndex = 0;
    struct Node* x = head;
    while (x != nullptr && currentIndex < index) {
        x = x->next;
        currentIndex++;
    }

    return x->value;
}

/*
 * Функция находит индекс минимального элемента динамического списка
 */
int findMinIndex(struct Node* head) {
    int index = 0;
    int minIndex = 0;

    struct Node* x = head;
    double min = head->value;

    while (x != nullptr) {
        if (x->value < min) {
            min = x->value;
            minIndex = index;
        }

        x = x->next;
        index++;
    }

    return minIndex;
}

/*
 * Функция находит индекс максимального элемента динамического списка
 */
int findMaxIndex(struct Node* head) {
    int index = 0;
    int maxIndex = 0;

    struct Node* x = head;
    double max = head->value;

    while (x != nullptr) {
        if (x->value > max) {
            max = x->value;
            maxIndex = index;
        }

        x = x->next;
        index++;
    }

    return maxIndex;
}

/*
 * Функция чистит динамический список
 */
void clearList(struct Node* *head) {
    struct Node* x = *head;
    struct Node* next;

    while (x != nullptr) {
        next = x->next;
        free(x);
        x = next;
    }

    *head = nullptr;
}

int main() {
    int count = 0;
    int choice = 0;
    struct Node *list = nullptr;

    printf("Welcome to program!\n");
    while (count <= 0) {
        printf("Enter count of elements > ");
        scanf("%d", &count);
    }

    printf("Good news! Now you need to enter your values:\n");
    fillList(&list, count);

    do {
        printf("========================\n");
        printf("          Menu          \n");
        printf("========================\n");
        printf("1. Refill list\n");
        printf("2. Sum of items\n");
        printf("3. Minimal value\n");
        printf("4. Maximum value\n");
        printf("5. Sort items\n");
        printf("6. Print items\n");
        printf("0. Quit\n");
        printf("> ");
        scanf("%d", &choice);
        printf("========================\n");

        switch (choice) {
            case 1: {
                clearList(&list);

                count = 0;
                while (count <= 0) {
                    printf("Enter count of elements > ");
                    scanf("%d", &count);
                }

                printf("Good news! Now you need to enter your values:\n");
                fillList(&list, count);
                break;
            }

            case 2: {
                printf("Result: %g\n\n", sum(list));
                break;
            }

            case 3: {
                int index = findMinIndex(list);

                printf("Index: %d\n", index);
                printf("Value: %g\n\n", getByIndex(list, index));
                break;
            }

            case 4: {
                int index = findMaxIndex(list);

                printf("Index: %d\n", index);
                printf("Value: %g\n\n", getByIndex(list, index));
                break;
            }

            case 5: {
                printList(sort(list));
                printf("\n\n");
                break;
            }

            case 6: {
                printList(list);
                printf("\n\n");
                break;
            }

            case 0: {
                break;
            }

            default: {
                printf("Incorrect command\n\n");
            }
        }
    } while (choice != 0);

    return 0;
}
