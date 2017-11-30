#ifndef _memory_h
#define _memory_h

#include "definitions.h"

#ifdef _WIN32
#define BAD_ALLOC 
#else
#define BAD_ALLOC std::bad_alloc
#endif

namespace pen
{
	//c 
	void*	memory_alloc( u32 size_bytes );
	void*	memory_alloc_align( u32 size_bytes, u32 alignment );
	void*	memory_realloc(void* mem, u32 size_bytes);
	void	memory_free( void* mem );
	void	memory_free_align( void* mem );
	void	memory_cpy( void* dest, const void* src, u32 size_bytes );
	void	memory_set( void* dest, u8 val, u32 size_bytes );
	void	memory_zero( void* dest, u32 size_bytes );
}

void*	operator new(size_t n) throw(BAD_ALLOC);
void	operator delete(void *p) throw();

#endif
