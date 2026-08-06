/* luna_rc.h */
#ifndef LUNA_RC_H
#define LUNA_RC_H

#include <stdint.h>

#ifndef LUNA_ASSERT
#include <assert.h>
#define LUNA_ASSERT	assert
#endif

#ifndef LUNA_MALLOC
#include <stdlib.h>
#define LUNA_MALLOC	malloc
#endif

#ifndef LUNA_FREE
#include <stdlib.h>
#define LUNA_FREE	free
#endif

struct rc {
	uint32_t count;
	void (*destroy)(void *data);
};

void *luna_rc_alloc(size_t size, void (*destroy)(void*));
void *luna_rc_acquire(void *data);
void luna_rc_release(void *data);

#endif
