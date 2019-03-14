#include <stdio.h>
#include <math.h>

void main()
{
	int memsize = 0, pgsize = 0, memaddrBits, offsetBits;
	int pgCount = 0, pgNoBits;
	int i, j, pgTable[32], logicalAddr[32]; 
	int frameNo = 0, pgNo = 0, physicalAddr = 0, offset = 0;

	printf("\nEnter memory size (as a power of 2): ");
	scanf("%d", &memaddrBits);
	printf("\nEnter page size (as a power of 2): ");
	scanf("%d", &offsetBits);

	pgNoBits = memaddrBits - offsetBits;
	memsize = pow(2, memaddrBits);
	pgsize = pow(2, offsetBits);
	pgCount = pow(2, pgNoBits);
	
	printf("\n\t\t\tNumber of Address bits");
	printf("\nMemory\t\t%d Bytes\t%d", memsize, memaddrBits);
	printf("\nPage\t\t%d Bytes\t\t%d", pgsize, pgNoBits);
	printf("\nNo. of pages:\t%d pages\t\t%d", pgCount, offsetBits);	
	
	printf("\nEnter the page table entry for %d pages:\n", pgCount);
	for (i = 0; i < pgCount; i++)
	{
		scanf("%d", &pgTable[i]);
	}
	
	printf("\nEnter logical address in binary form(%d bits): ",memaddrBits );
	for (i = 0; i < memaddrBits; i++)
	{
		scanf("%d", &logicalAddr[i]);	
	}

	for (i = (pgNoBits-1), j = 0; i >= 0; i--, j++ )
	{
		pgNo = pgNo + logicalAddr[i]*pow(2, j);
	}
	printf("\nPAGE TABLE");
	for (i = 0; i < pgCount; i++)
	{	
		printf("\n%d-%d", i, pgTable[i]);
	}

	printf("\n\nPgNo:%d", pgNo);
	frameNo = pgTable[pgNo];
	printf("\nFrame Number: %d", frameNo);
	
	for ( i = (memaddrBits - 1), j = 0; i >= pgNoBits; i--, j++)
	{
		offset = offset + logicalAddr[i]*pow(2,j);
	} 
	printf("\nOffset: %d", offset);
	physicalAddr = (frameNo * pgsize) + offset; 
	printf("\nPhysical Address: %d", physicalAddr);
}