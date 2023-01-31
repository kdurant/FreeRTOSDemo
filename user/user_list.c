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
    struct xLIST_ITEM ListItem4;

    vListInitialise(&ListTest);
    vListInitialiseItem(&ListItem1);
    ListItem1.xItemValue = 10;

    vListInitialiseItem(&ListItem2);
    ListItem2.xItemValue = 22;

    vListInitialiseItem(&ListItem3);
    ListItem3.xItemValue = 33;

    vListInitialiseItem(&ListItem4);
    ListItem4.xItemValue = 44;

    printf("listLIST_IS_EMPTY() = %ld\n", listLIST_IS_EMPTY(&ListTest));
    // 不论后面使用 vListInsert 插入多少元素， vListInsertEnd 插入的元素都在列表的尾部
    vListInsertEnd(&ListTest, &ListItem4);
    vListInsert(&ListTest, &ListItem2);
    vListInsert(&ListTest, &ListItem1);
    vListInsert(&ListTest, &ListItem3);
    printf("listCURRENT_LIST_LENGTH() = %ld\n", listCURRENT_LIST_LENGTH(&ListTest));
    printf("the list item at the head of the list = %d\n", listGET_HEAD_ENTRY(&ListTest)->xItemValue);

    // while(listLIST_IS_EMPTY(&ListTest) == 0)
    // {
    // // struct xLIST_ITEM temp;
    // listGET_ITEM_VALUE_OF_HEAD_ENTRY(&ListTest);
    // }
    return 0;
}
