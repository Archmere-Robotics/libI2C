//TYPE should be defined
#IFNDEF HEAP_SIZE
	#DEFINE HEAP_SIZE 100
#ENDIF

static byte[HEAP_SIZE] heap;
static bool[HEAP_SIZE] alloc;
void bf_init(short init_size) {
	for(int i=0;i<HEAP_SIZE;i++) {
		alloc[i]=false;
	}
}
*byte malloc(int size) {
	//find 
}
