#pragma once
#include <trihook\trihook_util.h>

#define VERTEX_STRUCT_SIZE 32
struct VertexVNT
{
    float x, y, z;
    float nx, ny, nz;
    float u, v;
};
ASSERT_SIZEOF(VertexVNT, VERTEX_STRUCT_SIZE);

// Until otherwise confirmed
typedef VertexVNT SD3DTLVertex;
typedef VertexVNT SD3DLVertex;
typedef VertexVNT SLVertex;
typedef VertexVNT SVertex;