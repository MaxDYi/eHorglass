#include "common.h"

/**
 * @description: ��������
 * @param {int*} a
 * @param {int*} b
 * @return {*}
 */
void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}
