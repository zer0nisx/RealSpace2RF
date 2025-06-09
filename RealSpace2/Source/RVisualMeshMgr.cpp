#include "stdafx.h"
#include "RMeshMgr.h"
#include "RVisualMeshMgr.h"
#include "MDebug.h"
#include "RealSpace2.h"

#include "MProfiler.h"
#include "RBspObject.h"
#include <algorithm>

_USING_NAMESPACE_REALSPACE2

_NAMESPACE_REALSPACE2_BEGIN

RVisualMeshMgr::RVisualMeshMgr() {
    m_id_last = 0;
    m_node_table.reserve(MAX_VMESH_TABLE);
    m_list.reserve(MAX_VMESH_TABLE); // Pre-allocate for better performance
}

RVisualMeshMgr::~RVisualMeshMgr() {
    DelAll();
}

int RVisualMeshMgr::AllocateId() {
    // Reuse free IDs first to prevent unbounded growth
    if (!m_free_ids.empty()) {
        int id = *m_free_ids.begin();
        m_free_ids.erase(m_free_ids.begin());
        return id;
    }
    return m_id_last++;
}

void RVisualMeshMgr::ReleaseId(int id) {
    m_free_ids.insert(id);
}

int RVisualMeshMgr::Add(RMesh* pMesh)
{
    if(!pMesh) {
        mlog("VisualMesh Create failure (pMesh==NULL) !!!\n");
        return -1;
    }

    RVisualMesh* node;
    node = new RVisualMesh;

    if (!node->Create(pMesh)) {
        mlog("VisualMesh Create failure !!!\n");
        delete node;
        return -1;
    }

    int id = AllocateId();
    node->m_id = id;

    // Ensure node_table is large enough
    if (id >= static_cast<int>(m_node_table.size())) {
        m_node_table.resize(id + 1, nullptr);
    }

    m_node_table[id] = node;
    m_list.push_back(node);

    return id;
}

int RVisualMeshMgr::Add(RVisualMesh* node)
{
    if(!node) {
        mlog("VisualMesh Create failure (pMesh==NULL) !!!\n");
        return -1;
    }

    int id = AllocateId();
    node->m_id = id;

    // Ensure node_table is large enough
    if (id >= static_cast<int>(m_node_table.size())) {
        m_node_table.resize(id + 1, nullptr);
    }

    m_node_table[id] = node;
    m_list.push_back(node);

    return id;
}

void RVisualMeshMgr::Del(int id) {
    if (id < 0 || id >= static_cast<int>(m_node_table.size()) || !m_node_table[id]) {
        return;
    }

    RVisualMesh* mesh = m_node_table[id];

    // Remove from vector (O(n) but maintains order)
    auto it = std::find(m_list.begin(), m_list.end(), mesh);
    if (it != m_list.end()) {
        m_list.erase(it);
    }

    // Clear from node table
    m_node_table[id] = nullptr;
    ReleaseId(id);

    delete mesh;
}

void RVisualMeshMgr::Del(RVisualMesh* pVMesh) {
    if (!pVMesh) return;

    int id = pVMesh->m_id;
    Del(id); // Use the optimized Del(int id) version
}

void RVisualMeshMgr::DelAll() {
    // Delete all meshes
    for (RVisualMesh* mesh : m_list) {
        delete mesh;
    }

    m_list.clear();
    m_node_table.clear();
    m_free_ids.clear();
    m_id_last = 0;
}

void RVisualMeshMgr::Render() {
    // Optimized: vector iteration has better cache locality than list
    for (RVisualMesh* mesh : m_list) {
        if (mesh) { // Safety check for null pointers
            mesh->Render();
        }
    }
}

void RVisualMeshMgr::Render(int id) {
    // Use fast access via node table instead of linear search
    RVisualMesh* mesh = GetFast(id);
    if (mesh) {
        mesh->Render();
    }
}

void RVisualMeshMgr::RenderFast(int id) {
    if(id == -1) return;
    if (id >= 0 && id < static_cast<int>(m_node_table.size()) && m_node_table[id]) {
        m_node_table[id]->Render();
    }
}

void RVisualMeshMgr::Frame() {
    // Optimized: vector iteration has better cache locality than list
    for (RVisualMesh* mesh : m_list) {
        if (mesh) { // Safety check for null pointers
            mesh->Frame();
        }
    }
}

void RVisualMeshMgr::Frame(int id) {
    // Use fast access via node table instead of linear search
    RVisualMesh* mesh = GetFast(id);
    if (mesh) {
        mesh->Frame();
    }
}

RVisualMesh* RVisualMeshMgr::GetFast(int id) {
    if (id < 0 || id >= static_cast<int>(m_node_table.size())) {
        return nullptr;
    }
    return m_node_table[id];
}

_NAMESPACE_REALSPACE2_END
