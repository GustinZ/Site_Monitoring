#include "utilities.h"
#include "stm32f4xx_hal.h"

void bubble_sort(unsigned int *table, uint8_t number)
{
    uint8_t i = 0, j = 0;
    unsigned int temp = 0;

    for (i = 0; i < number; i++)
    {
        for (j = i + 1; j < number; j++)
        {
            if (table[i] < table[j])
            {
                temp = table[j];
                table[j] = table[i];
                table[i] = temp;
            }
        }
    }
}

