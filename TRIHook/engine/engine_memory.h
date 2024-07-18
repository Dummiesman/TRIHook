#pragma once
#include <framework\hook_framework.h>

#if defined(TRIHOOK_GAME_EVO)
#define TRI_ALLOCATOR   void* operator new(size_t size)                        { return hook::StaticThunk<0x5A0C50>::Call<void*>(size); } \
                        void operator delete(void * pointer)                   { hook::StaticThunk<0x5A0C93>::Call<void>(pointer);} \
                        void operator delete[](void * pointer)                 { hook::StaticThunk<0x5A0CCD>::Call<void>(pointer);} \
                        void* operator new(size_t size, void * data)           { return data; } \
                        void operator delete(void * pointer, void * place)     { (void)place; }
#elif defined(TRIHOOK_GAME_EVO2)
#define TRI_ALLOCATOR   void* operator new(size_t size)                        { return hook::StaticThunk<0x60FA90>::Call<void*>(size); } \
                        void operator delete(void * pointer)                   { hook::StaticThunk<0x60FAD3>::Call<void>(pointer);} \
                        void operator delete[](void * pointer)                 { hook::StaticThunk<0x60FB0D>::Call<void>(pointer);} \
                        void* operator new(size_t size, void * data)           { return data; } \
                        void operator delete(void * pointer, void * place)     { (void)place; }
#else
#define TRI_ALLOCATOR /* Use inbuilt allocator */
#endif