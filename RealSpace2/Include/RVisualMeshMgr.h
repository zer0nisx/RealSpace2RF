#pragma once

#include "RVisualMesh.h"
#include <vector>
#include <unordered_set>

_NAMESPACE_REALSPACE2_BEGIN

// Optimized container types for better cache locality and performance
typedef std::vector<RVisualMesh*>       r_vmesh_list;
typedef r_vmesh_list::iterator          r_vmesh_node;

#define MAX_VMESH_TABLE 1000

class RVisualMeshMgr {
public:

    RVisualMeshMgr();
    ~RVisualMeshMgr();

    int     Add(RMesh* pMesh);
    int     Add(RVisualMesh* pMesh);

    void    Del(int id);
    void    Del(RVisualMesh* pMesh);

    void    DelAll();

    void    Render();
    void    Render(int id);

    void    RenderFast(int id);

    void    Frame();
    void    Frame(int id);

    RVisualMesh* GetFast(int id);

    // Public for backward compatibility with existing code
    r_vmesh_list m_list;          // Optimized: vector instead of list
    int          m_id_last;

private:
    // Fast O(1) access by ID
    std::vector<RVisualMesh*> m_node_table;

    // Track free IDs for reuse (prevents unbounded growth)
    std::unordered_set<int> m_free_ids;

    // Helper function for ID management
    int AllocateId();
    void ReleaseId(int id);
};

extern bool g_bBirdRenderTest;

_NAMESPACE_REALSPACE2_END
