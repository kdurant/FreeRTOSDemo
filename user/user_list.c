#include <stdio.h>
#include "FreeRTOS.h"
// #include "FreeRTOSConfig.h"
#include "list.h"


int main(void)
{
    xList             ListTest;
    struct xLIST_ITEM ListItem1;
    struct xLIST_ITEM ListItem2;
    struct xLIST_ITEM ListItem3;

    vListInitialise(&ListTest);
    vListInitialiseItem(&ListItem1);
    ListItem1.xItemValue = 10;

    vListInitialiseItem(&ListItem2);
    ListItem2.xItemValue = 2;

    vListInitialiseItem(&ListItem3);
    ListItem3.xItemValue = 3;

    printf("listLIST_IS_EMPTY() = %ld\n", listLIST_IS_EMPTY(&ListTest));
    vListInsert(&ListTest, &ListItem2);
    vListInsert(&ListTest, &ListItem1);
    vListInsert(&ListTest, &ListItem3);
    printf("listCURRENT_LIST_LENGTH() = %ld\n", listCURRENT_LIST_LENGTH(&ListTest));
    printf("the list item at the head of the list = %d\n", listGET_HEAD_ENTRY(&ListTest)->xItemValue);

    // while(!listLIST_IS_EMPTY())
    // {
    // // struct xLIST_ITEM temp;
    // }
    return 0;
}
