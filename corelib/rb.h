#ifndef CORELIB_RB_H
#define CORELIB_RB_H
#include "stdtypes.h"

struct _RBE {
	int32			w;
	int32			r;
	uint8			d[];
};

typedef struct _RBE RB;

struct _RBME {
	RB				*rb;
	int32			sz;
};

typedef struct _RBME RBM;

/*
	the writer can write if r==w
	the writer has to wait if w < r and sz > (r - w)
    the writer has to wait if w >= r and ((mask - w) + r) < sz
	
	the reader has to wait if r == w
	the reader can read during any other condition
	
	POINTS
			- research memory barrier to prevent modification of index
			  before data is written into the buffer
			- consider two methods for sleeping.. one using a flag bit
			  for the thread/process and the other using a lock
			  
	
	[signal objects]
	- kernel objects can be created by a process that are signals
	- other processes can wait on these objects (but only the creating process can signal them)
	- object is specified with processID:signalID
*/

int rb_write_nbio(RBM *rbm, void *p, uint32 sz);
int rb_read_nbio(RBM *rbm, void *p, uint32 *sz, uint32 *advance);
int rb_read_bio(RBM *rbm, void *p, uint32 *sz, uint32 *advance, uint32 timeout);
#endif