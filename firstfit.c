# include <stdio.h>
# include <stdlib.h>

int g = 1, k = 1; 

struct free { 
	int tag; 
	int size; 
	struct free* next; 
}* free_head = NULL, *prev_free = NULL; 

struct alloc { 
	int block_id; 
	int tag; 
	int size; 
	struct alloc* next; 
}* alloc_head = NULL, *prev_alloc = NULL; 


void create_free(int c) 
{ 
	struct free* p = (struct free*) 
		malloc(sizeof(struct free)); 
	p->size = c; 
	p->tag = g; 
	p->next = NULL; 
	if (free_head == NULL) 
		free_head = p; 
	else
		prev_free->next = p; 
	prev_free = p; 
	g++; 
} 


void print_alloc() 
{ 
	struct alloc* p = alloc_head; 
	printf("\nProcess ID\tBlock ID\tSize\n"); 
	while (p != NULL) { 
    printf("%d\t \t %d\t\t%d\n", p->tag, p->block_id, p->size);
		p = p->next; 
	} 
} 


void first(int c) 
{ 

	struct alloc* q = (struct alloc*) 
		malloc(sizeof(struct alloc)); 
	q->size = c; 
	q->tag = k; 
	q->next = NULL; 
	struct free* p = free_head; 


	while (p != NULL) { 
		if (q->size <= p->size) 
			break; 
		p = p->next; 
	} 


	if (p != NULL) { 

		q->block_id = p->tag; 
		p->size -= q->size; 
		if (alloc_head == NULL) 
			alloc_head = q; 
		else { 
			prev_alloc = alloc_head; 
			while (prev_alloc->next != NULL) 
				prev_alloc = prev_alloc->next; 
			prev_alloc->next = q; 
		} 
		k++; 
	} 
	else 
    	printf("\nProcess of size %d cannot be allocated\n", c);
} 
 

int main() 
{ 
	int blockSize[] = { 100, 500, 200, 300, 600 }; 
	int processSize[] = { 212, 417, 112, 426 }; 
	int m = 5; 
	int n = 4; 
	int i;
	printf("\nBlock size: ");
	for(i=0;i<m;i++)
		printf("%d  ", blockSize[i]);
	printf("\nProcess size: ");
	for(i=0;i<n;i++)
		printf("%d  ", processSize[i]);	
	for (i = 0; i < m; i++) 
		create_free(blockSize[i]);
	for (i = 0; i < n; i++) 
		first(processSize[i]); 

	print_alloc(); 
} 

