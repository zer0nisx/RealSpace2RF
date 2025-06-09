# Character Cloth Bugs Analysis - RealSpace2

## 🚨 Critical Issues Identified

### **Bug #1: Character cloth meshes ignore custom normals**

#### **Problem**
- **Location**: `RCharCloth.cpp` lines 172 and 683
- **Issue**: Recalculates face normals using simple cross product every frame
- **Impact**: Custom vertex normals are completely ignored, leading to poor lighting quality

#### **Current Code**
```cpp
// Line 172 and 683 in RCharCloth.cpp
CrossProduct(&n, Point[2] - Point[0], Point[2] - Point[1]);
```

#### **Root Cause**
- Cloth simulation recalculates geometry positions each frame
- Normal calculation assumes planar triangles using cross product
- Original vertex normals from modeling software are discarded
- No consideration for smooth normals or UV seams

#### **Proposed Solution**
```cpp
// Instead of recalculating from scratch, transform existing normals
void TransformVertexNormals(rvector* originalNormals, rvector* deformedPositions,
                           rvector* deformedNormals, int vertexCount) {

    for (int i = 0; i < vertexCount; i++) {
        // Calculate deformation matrix for this vertex
        rmatrix deformMatrix = CalculateLocalDeformation(i, deformedPositions);

        // Transform original normal by deformation
        deformedNormals[i] = TransformNormal(originalNormals[i], deformMatrix);
        Normalize(&deformedNormals[i]);
    }
}
```

#### **Implementation Priority**: HIGH
- Affects visual quality significantly
- Required for proper PBR lighting
- Needed for normal map compatibility

---

### **Bug #2: Character cloth meshes become unlit (sharp falloff)**

#### **Problem**
- **Location**: Lighting calculations in cloth rendering pipeline
- **Issue**: Diffuse light response falls off too sharply beyond max attenuation distance
- **Impact**: Cloth becomes completely dark, flat appearance

#### **Affected Components**
- Nearest light source calculations
- Sun/directional light source
- Both point lights and ambient lighting

#### **Evidence**
- Standard meshes have smooth falloff → copy implementation needed
- Problem occurs beyond `fAttnEnd` distance
- Different behavior compared to regular mesh lighting

#### **Investigation Required**
```cpp
// Need to locate and compare:
// 1. Standard mesh lighting calculation
// 2. Cloth mesh lighting calculation
// 3. Attenuation formula differences

// Expected in files like:
// - RBspObject.cpp (has attenuation code)
// - RMesh rendering code
// - Cloth-specific lighting in RCharCloth.cpp
```

#### **Implementation Priority**: HIGH
- Critical for visual consistency
- Affects gameplay (dark characters hard to see)

---

### **Bug #3: Character cloth ignores sub materials/material slots**

#### **Problem**
- **Location**: `RCharCloth.cpp` lines 569-571
- **Issue**: Applies base material across all geometry, ignoring material slots
- **Impact**: Multi-material clothing renders incorrectly

#### **Current Code**
```cpp
// Line 569-571 in RCharCloth.cpp
RMtrlMgr* pMtrlMgr = &mpMeshNode->m_pParentMesh->m_mtrl_list_ex;
RMtrl* pMtrl = pMtrlMgr->Get_s(mpMeshNode->m_mtrl_id, -1);
int num_mtrl = pMtrl->m_sub_mtrl_num;
```

#### **Root Cause Analysis**
- Code retrieves `num_mtrl` but doesn't iterate through sub-materials
- Missing per-face material assignment
- No material slot rendering loop

#### **Two Solution Approaches**

**Option A: Fix cloth rendering to support multiple materials**
```cpp
// Iterate through materials and render geometry per material
for (int matId = 0; matId < num_mtrl; matId++) {
    RMtrl* pSubMtrl = pMtrlMgr->Get_s(mpMeshNode->m_mtrl_id, matId);
    SetMaterial(pSubMtrl);
    RenderFacesWithMaterial(matId);
}
```

**Option B: Content creation guidelines (vanilla compatibility)**
- Consolidate textures into atlas
- Modify UVs to reference consolidated texture
- Merge materials into single material
- Separate meshes by material if needed

#### **Implementation Priority**: MEDIUM
- **Option A**: Requires significant rendering changes
- **Option B**: Content workflow changes, maintains compatibility

---

## 🔍 **Next Steps for Investigation**

### **Files to Analyze**
1. **RCharCloth.cpp** - Main cloth implementation
2. **RCloth.cpp** - Base cloth functionality
3. **RBspObject.cpp** - Standard mesh lighting (reference implementation)
4. **RMesh.cpp** - Standard mesh material handling
5. **Lighting.hlsl** - Shader-side lighting calculations

### **Code Locations to Find**
```cpp
// Lighting attenuation in standard meshes
float fIntensity = (fdistance - Light.fAttnStart) / (Light.fAttnEnd - Light.fAttnStart);

// Material slot iteration in standard rendering
for (int i = 0; i < mesh->GetMaterialCount(); i++) {
    SetMaterial(mesh->GetMaterial(i));
    RenderSubset(i);
}
```

### **Test Cases Needed**
1. Cloth with smooth normals vs recalculated normals
2. Cloth lighting vs standard mesh lighting at various distances
3. Multi-material cloth rendering vs standard multi-material mesh

---

## 📊 **Impact Assessment**

| Bug | Visual Impact | Performance Impact | Compatibility Risk |
|-----|---------------|-------------------|-------------------|
| #1 Normal | HIGH | LOW | MEDIUM |
| #2 Lighting | HIGH | NONE | LOW |
| #3 Materials | MEDIUM | NONE | HIGH (vanilla) |

**Recommended Fix Order**: #2 → #1 → #3
