/*
 * Placed into the Public Domain
 * written by Walter Bright, Digital Mars
 * www.digitalmars.com
 */

/* ================================= linux ============================ */

#if linux

#include "../system/system.h"

/******************************************
 * Enter/exit critical section.
 */

/* We don't initialize critical sections unless we actually need them.
 * So keep a linked list of the ones we do use, and in the static destructor
 * code, walk the list and release them.
 */

typedef struct D_CRITICAL_SECTION
{
    struct D_CRITICAL_SECTION *next;
    pthread_mutex_t cs;
} D_CRITICAL_SECTION;

static D_CRITICAL_SECTION *dcs_list;
static D_CRITICAL_SECTION critical_section;
static pthread_mutexattr_t _criticals_attr;

void _STI_critical_init(void);
void _STD_critical_term(void);

void _d_criticalenter(D_CRITICAL_SECTION *dcs)
{
    if (!dcs_list)
    {	_STI_critical_init();
	atexit(_STD_critical_term);
    }
    //printf("_d_criticalenter(dcs = x%x)\n", dcs);
    if (!dcs->next)
    {
	pthread_mutex_lock(&critical_section.cs);
	if (!dcs->next)	// if, in the meantime, another thread didn't set it
	{
	    dcs->next = dcs_list;
	    dcs_list = dcs;
	    pthread_mutex_init(&dcs->cs, &_criticals_attr);
	}
	pthread_mutex_unlock(&critical_section.cs);
    }
    pthread_mutex_lock(&dcs->cs);
}

void _d_criticalexit(D_CRITICAL_SECTION *dcs)
{
    //printf("_d_criticalexit(dcs = x%x)\n", dcs);
    pthread_mutex_unlock(&dcs->cs);
}

void _STI_critical_init()
{
    if (!dcs_list)
    {	//printf("_STI_critical_init()\n");
	pthread_mutexattr_init(&_criticals_attr);
	pthread_mutexattr_settype(&_criticals_attr, PTHREAD_MUTEX_RECURSIVE_NP);

	// The global critical section doesn't need to be recursive
	pthread_mutex_init(&critical_section.cs, 0);
	dcs_list = &critical_section;
    }
}

void _STD_critical_term()
{
    if (dcs_list)
    {	//printf("_STI_critical_term()\n");
	while (dcs_list)
	{
	    //printf("\tlooping... %x\n", dcs_list);
	    pthread_mutex_destroy(&dcs_list->cs);
	    dcs_list = dcs_list->next;
	}
    }
}

#endif
