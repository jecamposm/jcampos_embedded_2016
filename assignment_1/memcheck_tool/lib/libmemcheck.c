#define _GNU_SOURCE

#include <stdio.h>
#include <dlfcn.h>
static void* (*real_malloc)(size_t)=NULL;
static void* (*real_free)(size_t)=NULL;
int memory_allocations = 0;
int memory_free = 0;

static void mtrace_init(void)
{
    real_malloc = dlsym(RTLD_NEXT, "malloc");
    if (NULL == real_malloc) {
        fprintf(stderr, "Error in `dlsym`: %s\n", dlerror());
    }
}

void *malloc(size_t size)
{
    if(real_malloc==NULL) {
        mtrace_init();
    }

    void *p = NULL;
    p = real_malloc(size);
	memory_allocations++;
    return p;
}

static void ftrace_init(void)
{
    real_free = dlsym(RTLD_NEXT, "free");
    if (NULL == real_free) {
        fprintf(stderr, "Error in `dlsym`: %s\n", dlerror());
    }
}

void *free(size_t size)
{
    if(real_free==NULL) {
        ftrace_init();
    }

    void *p = NULL;
    p = real_free(size);
	memory_free++;
    return p;
}


void report(void)
{
	fprintf(stderr, "\nAnalysis finished!\n");
	fprintf(stderr, "Memory allocations: %i\n" , memory_allocations);
	fprintf(stderr, "Memory free: %i\n" , memory_free);
	fprintf(stderr, "Total memory leaks found: %i\n\n" , memory_allocations - memory_free);
}

__attribute__ ((destructor)) void end(void)
{
	report();
}
