#include <stdio.h>
#include <stdlib.h>

#include "list.h"
#include "test.h"

/*
* Now this is truly interesting. Instead of making linked lists that contain pointers
* to the structure, the linux kernel generalizes the linked list by making structures
* contain lists, and then by the magic of the container_of() macro (used in the definition
* of list_entry() used below), we are able to grab the struct that contains the linked
* list entry given. By this method, we can completely separate the idea of structures
* and lists.
*/
struct my_struct {
        int num;
        struct list_head list;
};

void welcome()
{
        printf(ANSI_GREEN("Welcome to the linked list tester!\n"));
}

void print_list(struct list_head *list)
{
        if (list_empty(list)) {
                printf(ANSI_YELLOW("list is empty\n"));
                printf(ANSI_RESET);
                return;
        }
        struct list_head *iterator;
        list_for_each(iterator, list) {
                printf(ANSI_MAGENTA("%d "), list_entry(iterator, struct my_struct, list)->num);
        }
        printf(ANSI_RESET);
        printf("\n");
}

void add(struct list_head *list)
{
        printf("Enter number to add to list: ");
        int n;
        scanf("%d", &n);
        struct my_struct *elem = malloc(sizeof(struct my_struct));
        elem->num = n;
        list_add(&elem->list, list);
        printf(ANSI_GREEN("Number %d added to list\n"), n);
        printf(ANSI_RESET);
}

void delete(struct list_head *list)
{
        if (!list_empty(list)) {
                int tmp = list_entry(list->next, struct my_struct, list)->num;
                list_del(list->next);
                printf(ANSI_GREEN("Deleted %d from list\n"), tmp);
        } else {
                printf(ANSI_YELLOW("List is empty, cannot delete an element\n"));
                printf(ANSI_RESET);
        }
}

int main(void)
{
        welcome();

        static LIST_HEAD(list);

        while (1) {
                printf(ANSI_CYAN("Available options:\n"));
                printf(ANSI_RESET);
                printf("0. Print list\n"
                                 "1. Add to list\n"
                                 "2. Delete from list\n"
                                 "3. Exit\n");
                printf(ANSI_RESET);

                int c;
                scanf("%d", &c);

                switch (c) {
                        case 0:
                                print_list(&list);
                                break;
                        case 1:
                                add(&list);
                                break;
                        case 2:
                                delete(&list);
                                break;
                        case 3:
                                goto end;
                        default:
                                printf(ANSI_RED("Input not recognized.\n"));
                                printf(ANSI_RESET);
                                break;
                }
        }

        /*
        * Honestly, I don't know how to properly use these goto constructs,
        * when these are used, if at all in today's program-writing methodology,
        * and if this leads to any unforseen consequences in the flow of logic.
        * Nonetheless, it is a neat feature of the C language.
        */
        end:;

        /*
        static LIST_HEAD(stat_list);
        static LIST_HEAD(dyn_list);

        // Statically made at compile-time. 
        struct my_struct s1 = {
                .num = 1,
                .list = LIST_HEAD_INIT(s1.list),
        };

        struct my_struct s2 = {
                .num = 2,
                .list = LIST_HEAD_INIT(s2.list),
        };

        struct my_struct s3 = {
                .num = 3,
                .list = LIST_HEAD_INIT(s3.list),
        };

        list_add_tail(&s1.list, &stat_list);
        list_add_tail(&s2.list, &stat_list);
        list_add_tail(&s3.list, &stat_list);

        struct list_head *iterator;

        printf("Compile-time made list: ");
        list_for_each(iterator, &stat_list) {
                printf("%d ", list_entry(iterator, struct my_struct, list)->num);
        }

        printf("\nEnter a number: ");
        int n;
        scanf("%d", &n);
        for (int i = 0; i < n; i++) {
                struct my_struct *tmp = malloc(sizeof(struct my_struct));
                scanf("%d", &tmp->num);
                INIT_LIST_HEAD(&tmp->list);
                list_add_tail(&tmp->list, &dyn_list);
        }

        iterator = dyn_list.next; 
        printf("Dynamically allocated list: ");
        while (iterator->next != iterator) {
                printf("%d ", list_entry(iterator, struct my_struct, list)->num);
                iterator = iterator->next;
                list_del(iterator->prev);
        }
        */
        return 0;
}
