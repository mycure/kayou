//
// Copyright (c) 1999-2003 by Digital Mars, www.digitalmars.com
// All Rights Reserved
// Written by Walter Bright

// Exception handling support

/* ======================== linux =============================== */

#if linux

extern ClassInfo D9Exception7__ClassZ;

#define _Class_9Exception D9Exception7__ClassZ

typedef int (*fp_t)();   // function pointer in ambient memory model

struct DHandlerInfo
{
    unsigned offset;		// offset from function address to start of guarded section
    int prev_index;		// previous table index
    unsigned cioffset;		// offset to DCatchInfo data from start of table (!=0 if try-catch)
    void *finally_code;		// pointer to finally code to execute
				// (!=0 if try-finally)
};

// Address of DHandlerTable, searched for by eh_finddata()

struct DHandlerTable
{
    void *fptr;			// pointer to start of function
    unsigned espoffset;		// offset of ESP from EBP
    unsigned retoffset;		// offset from start of function to return code
    unsigned nhandlers;		// dimension of handler_info[]
    struct DHandlerInfo handler_info[1];
};

struct DCatchBlock
{
    ClassInfo *type;		// catch type
    unsigned bpoffset;		// EBP offset of catch var
    void *code;			// catch handler code
};

// Create one of these for each try-catch
struct DCatchInfo
{
    unsigned ncatches;			// number of catch blocks
    struct DCatchBlock catch_block[1];	// data for each catch block
};

// One of these is generated for each function with try-catch or try-finally

struct FuncTable
{
    void *fptr;			// pointer to start of function
    struct DHandlerTable *handlertable; // eh data for this function
    unsigned size;		// size of function in bytes
};

extern struct FuncTable *table_start;
extern struct FuncTable *table_end;

void terminate()
{
//    _asm
//    {
//	hlt
//    }
}

/*******************************************
 * Given address that is inside a function,
 * figure out which function it is in.
 * Return DHandlerTable if there is one, NULL if not.
 */

struct DHandlerTable *__eh_finddata(void *address)
{
    struct FuncTable *ft;

    for (ft = (struct FuncTable *)table_start;
	 ft < (struct FuncTable *)table_end;
	 ft++)
    {
	if (ft->fptr <= address &&
	    address < (void *)((char *)ft->fptr + ft->size))
	{
	    return ft->handlertable;
	}
    }
    return NULL;
}


/******************************
 * Given EBP, find return address to caller, and caller's EBP.
 * Input:
 *   regbp       Value of EBP for current function
 *   *pretaddr   Return address
 * Output:
 *   *pretaddr   return address to caller
 * Returns:
 *   caller's EBP
 */

unsigned __eh_find_caller(unsigned regbp, unsigned *pretaddr)
{
    unsigned bp = *(unsigned *)regbp;

    if (bp)         // if not end of call chain
    {
	// Perform sanity checks on new EBP.
	// If it is screwed up, terminate() hopefully before we do more damage.
	if (bp <= regbp) 
	    // stack should grow to smaller values
	    terminate();

        *pretaddr = *(unsigned *)(regbp + sizeof(int));
    }
    return bp;
}

/***********************************
 * Throw a D object.
 */

void __stdcall _d_throw(Object *h)
{
    unsigned regebp;

    //printf("_d_throw(h = %p, &h = %p)\n", h, &h);
    //printf("\tvptr = %p\n", *(void **)h);

    regebp = _EBP;

    while (1)		// for each function on the stack
    {
        struct DHandlerTable *handler_table;
	struct FuncTable *pfunc;
	struct DHandlerInfo *phi;
	unsigned retaddr;
        unsigned funcoffset;
	unsigned spoff;
	unsigned retoffset;
        int index;
        int dim;
	int ndx;
	int prev_ndx;

        regebp = __eh_find_caller(regebp,&retaddr);
        if (!regebp) 
            // if end of call chain
            break;
        
        handler_table = __eh_finddata((void *)retaddr);   // find static data associated with function
        if (!handler_table)         // if no static data
        {   
            continue;
        }
        funcoffset = (unsigned)handler_table->fptr;
        spoff = handler_table->espoffset;
        retoffset = handler_table->retoffset;

#ifdef DEBUG
        //printf("retaddr = x%x\n",(unsigned)retaddr);
        //printf("regebp=x%04x, funcoffset=x%04x, spoff=x%x, retoffset=x%x\n",
        //regebp,funcoffset,spoff,retoffset);
#endif

        // Find start index for retaddr in static data
        dim = handler_table->nhandlers;
        index = -1;
        for (int i = 0; i < dim; i++)
        {   
	    phi = &handler_table->handler_info[i];

            if ((unsigned)retaddr >= funcoffset + phi->offset)
                index = i;
        }

	// walk through handler table, checking each handler
	// with an index smaller than the current table_index
	for (ndx = index; ndx != -1; ndx = prev_ndx)
	{
	    phi = &handler_table->handler_info[ndx];
	    prev_ndx = phi->prev_index;
	    if (phi->cioffset)
	    {
		// this is a catch handler (no finally)
		struct DCatchInfo *pci;
		int ncatches;
		int i;

		pci = (struct DCatchInfo *)((char *)handler_table + phi->cioffset);
		ncatches = pci->ncatches;
		for (i = 0; i < ncatches; i++)
		{
		    struct DCatchBlock *pcb;
		    ClassInfo *ci = **(ClassInfo ***)h;

		    pcb = &pci->catch_block[i];

		    if (_d_isbaseof(ci, pcb->type))
		    {   // Matched the catch type, so we've found the handler.

			// Initialize catch variable
			*(void **)(regebp + (pcb->bpoffset)) = h;

			// Jump to catch block. Does not return.
			{
			    unsigned catch_esp;
			    fp_t catch_addr;

			    catch_addr = (fp_t)(pcb->code);
			    catch_esp = regebp - handler_table->espoffset - sizeof(fp_t);
			    _asm
			    {
				mov	EAX,catch_esp
				mov	ECX,catch_addr
				mov	[EAX],ECX
				mov	EBP,regebp
				mov	ESP,EAX		// reset stack
				ret			// jump to catch block
			    }
			}
		    }
		}
	    }
	    else if (phi->finally_code)
	    {	// Call finally block
		// Note that it is unnecessary to adjust the ESP, as the finally block
		// accesses all items on the stack as relative to EBP.

		void *blockaddr = phi->finally_code;

		_asm
		{
		    push	EBX
		    mov		EBX,blockaddr
		    push	EBP
		    mov		EBP,regebp
		    call	EBX
		    pop		EBP
		    pop		EBX
		}
	    }
	}
    }
}


#endif
