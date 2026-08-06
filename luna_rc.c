/* luna_rc.c */
#include "luna_rc.h"

void *luna_rc_alloc(size_t size, void (*destroy)(void*))
{
	LUNA_ASSERT(size > 0);
	struct rc *_rc = LUNA_MALLOC(sizeof(struct rc) + size);
	LUNA_ASSERT(_rc);
	_rc->count = 0;
	_rc->destroy = destroy;
	return (_rc + 1);
}

void *luna_rc_acquire(void *data)
{
	LUNA_ASSERT(data);
	struct rc *_rc = (struct rc *)data - 1;
	_rc->count += 1;
	return (_rc + 1);
}

void luna_rc_release(void *data)
{
	LUNA_ASSERT(data);
	struct rc *_rc = (struct rc *)data - 1;
	if (_rc->count > 0) {
		if (--_rc->count == 0) {
			if (_rc->destroy) {
				_rc->destroy(data);
			}
			LUNA_FREE(_rc);
		}
	}
}
