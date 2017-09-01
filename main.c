#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define FILTER_SIZE 30
#define NUM_HASHES 3

unsigned int FNV_Hash(unsigned char *str, unsigned int length)
{
   const unsigned int fnv_prime = 0x811C9DC5;
   unsigned int hash      = 0;
   unsigned int i         = 0;

   for(i = 0; i < length; str++, i++)
   {
      hash = hash * fnv_prime;
      hash = hash ^ (*str);
   }


   return hash;
}

unsigned int RS_Hash(const char* str, unsigned int length)
{
   unsigned int b    = 378551;
   unsigned int a    = 63689;
   unsigned int hash = 0;
   unsigned int i    = 0;

   for (i = 0; i < length; ++str, ++i)
   {
      hash = hash * a + (*str);
      a    = a * b;
   }

   return hash;
}

unsigned int JS_Hash(const char* str, unsigned int length)
{
   unsigned int hash = 1315423911;
   unsigned int i    = 0;

   for (i = 0; i < length; ++str, ++i)
   {
      hash ^= ((hash << 5) + (*str) + (hash >> 2));
   }

   return hash;
}

void hashes_function(unsigned int hash_k[], char *st)
{
	unsigned char *str = (unsigned char *)st;
	int pos;
	for(pos = 0; str[pos] != '\0'; ++pos);
	hash_k[0] = RS_Hash  (str, pos);
	hash_k[1] = JS_Hash (str, pos);
	hash_k[2] = FNV_Hash (str, pos);

}

void insert_element(unsigned char bloom_filter[], char *str)
{
	unsigned int hash_k[NUM_HASHES];
	int i;

	hashes_function(hash_k, str);

	for (i = 0; i < NUM_HASHES; i++)
	{

		hash_k[i] = hash_k[i] % FILTER_SIZE;

		/* set the bit in the filter */
		bloom_filter[hash_k[i]] = 1;
	}
}


int search_element(unsigned char bloom_filter[], char *str)
{
	unsigned int hash_k[NUM_HASHES];
	int i;

	hashes_function(hash_k, str);

	for (i = 0; i < NUM_HASHES; i++)
	{
		hash_k[i] = hash_k[i] % FILTER_SIZE;

		if (!(bloom_filter[hash_k[i]] & 1))
			return 0;
	}

	return 1;
}


void main(void)
{
	char ch,p[10];
	unsigned char bloom_filter[FILTER_SIZE];
	int i,n,t;
	for (i = 0; i < FILTER_SIZE; i++)
	{
		bloom_filter[i] = 0;
	}

	do
	{
		printf("\n====Bloom Filter Implementation in C====\n");
		printf("\nEnter 1 to insert element=\n");
		printf("\nEnter 2 to search element=\n");
		scanf("%d",&n);
		switch(n)
		{

			case 1:
				printf("\nEnter element to insert=\n");
				scanf("%s",p);
				insert_element(bloom_filter,p);
				break;
			case 2:
				printf("\nEnter element to search=\n");
				scanf("%s",p);
				t=search_element(bloom_filter,p);
				if(t==1)
					printf("\n Yes. It is in a set.\n");
				else
					printf("\n No. It is not in a set.\n");
				break;
			default:
				printf("\nWorng Entry");
		}

		printf("\nDo you want to continue=\n");
		getchar();
		scanf("%c",&ch);
	}while(ch=='y'||ch=='Y');
}
