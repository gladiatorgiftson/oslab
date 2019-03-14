#include<stdio.h>
int frameCount, refCount, memRef[30], frames[10], frCounter[30];
int refSearch(int);
void FIFO();
void LRU();
void LFU();
void main()
{
    int i;
    printf("Enter the number of frames: ");
    scanf("%d", &frameCount);
    printf("Enter the number of memory references: ");
    scanf("%d", &refCount);
    printf("Enter the memory reference string: ");
    for ( i = 0; i < refCount; i++)
    {
        scanf("%d", &memRef[i]);
    }
    FIFO();
    LRU();
    LFU();
}
void FIFO()
{
    int i, pgFault = 0;
    int j = 0, k;
    for ( i = 0; i < frameCount; i++)
    {
        frames[i] = -1;
    }
    for (i = 0; i < refCount; i++)
    {
        if (refSearch(memRef[i]) == 0)
        {
            frames[j] = memRef[i];
            j = (j+1) % frameCount;
            pgFault++;
        }
        for ( k = 0; k < frameCount; k++)
        {
            printf("%d\t", frames[k]);
        }
        printf("\n");
    }
    printf("\nPage Fault Count: %d", pgFault);
}
void LRU()
{
    int i, j, k, pgFault = 0, searchIndex, least = 0, leastIndex = 0, clock = 0;
    for ( i = 0; i < frameCount; i++)
    {
        frames[i] = -1;
        frCounter[i] = 0;
    }
    for (i = 0; i < refCount; i++)
    {
        searchIndex = refSearch(memRef[i]);
        if (searchIndex == 0)
        {
            //Find the least value in frCounter
            least = frCounter[0];
            leastIndex = 0;
            for (j = 1; j < frameCount; j++)
            {
                if (least > frCounter[j])
                {
                    least = frCounter[j];
                    leastIndex = j;
                }
            }
            frames[leastIndex] = memRef[i];
            clock++;
            frCounter[leastIndex] = clock;
            pgFault++;
        }
        else
        {
            clock++;
            frCounter[searchIndex] = clock;
        }
        for ( k = 0; k < frameCount; k++)
        {
            printf("%d\t", frames[k]);
        }
        printf("\n");
    }
    printf("\nPage Fault Count: %d", pgFault);
}
int refSearch(int ref)
{
    int i;
    for (i = 0; i < frameCount; i++)
    {
        if (ref == frames[i])
        {
            return i;
        }
    }
return 0;
}
void LFU()
{
    int i, j, k, pgFault = 0, searchIndex, least = 0, leastIndex = 0;
    for ( i = 0; i < frameCount; i++)
    {
        frames[i] = -1;
        frCounter[i] = 0;
    }
    for (i = 0; i < refCount; i++)
    {
        searchIndex = refSearch(memRef[i]);
        if (searchIndex == 0)
        {
            //Find the least value in frCounter
            least = frCounter[0];
            leastIndex = 0;
            for (j = 1; j < frameCount; j++)
            {
                if (least > frCounter[j])
                {
                    least = frCounter[j];
                    leastIndex = j;
                }
            }
            frames[leastIndex] = memRef[i];
            frCounter[leastIndex] = 1;
            pgFault++;
        }
        else
        {
            frCounter[searchIndex]++;
        }
        for ( k = 0; k < frameCount; k++)
        {
            printf("%d\t", frames[k]);
        }
        printf("\n");
    }
    printf("\nPage Fault Count: %d\n", pgFault);
}