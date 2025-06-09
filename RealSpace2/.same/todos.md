# RVisualMesh Optimization TODOs

## HIGH PRIORITY (Implementar primero)
- [x] Implementar pool de objetos para RWeaponTracks
- [x] Añadir constantes nombradas para magic numbers
- [x] Implementar hash map para node lookups en animaciones
- [x] Eliminar código muerto y funciones vacías
- [x] Añadir const correctness donde sea apropiado

## MEDIUM PRIORITY
- [x] Cache de matrices con dirty flags
- [x] ✅ **COMPLETADO** - Optimizar contenedores en RVisualMeshMgr
- [ ] Mejorar LOD system
- [x] ✅ **COMPLETADO** - Smart pointers para nuevas features

## 🚨 **CLOTH BUGS IDENTIFICADOS** (Nueva alta prioridad)
- [ ] **Bug #1**: Character cloth meshes ignore custom normals
  - Problema: Recalcula face normals con cross product cada frame
  - Solución: Rotar vertex normals existentes para match deformation
  - Archivo: `RCharCloth.cpp`, `RCloth.cpp`

- [ ] **Bug #2**: Character cloth meshes become unlit (sharp falloff)
  - Problema: Diffuse light response falls off too sharply beyond max attenuation
  - Afecta: Nearest light source + sun source
  - Solución: Copy-paste smooth falloff from standard meshes
  - Archivo: Lighting calculations in cloth rendering

- [ ] **Bug #3**: Character cloth ignores sub materials/material slots
  - Problema: Applies base material across all geometry
  - Solución A: Consolidate textures + modify UVs + merge materials
  - Solución B: Separate meshes by material (vanilla client compatible)
  - Archivo: Material handling in cloth system

## LOW PRIORITY
- [ ] Threading para animaciones
- [ ] SIMD optimizations
- [ ] Async resource loading
- [ ] Batch rendering para trails

## COMPLETED
- [x] Análisis completo del código base
- [x] Identificación de problemas y mejoras
- [x] Pool de objetos para RWeaponTracks (ya estaba implementado)
- [x] Constantes nombradas para magic numbers
- [x] Hash map para node lookups en animaciones (ya estaba implementado)
- [x] Eliminar código muerto y funciones vacías (código limpio encontrado)
- [x] Añadir const correctness donde sea apropiado
- [x] Cache de matrices con dirty flags para optimización de rendering

## COMMIT INFO
**Último commit**: feat: Implement medium-priority RVisualMeshMgr optimizations
**Hash**: f5dfa9e
**Cambios subidos**: ✅ Exitosamente pusheado a origin/main

## PROGRESO ACTUAL
🎯 **ALTA PRIORIDAD: COMPLETADA** (5/5 tareas)
📊 **MEDIA PRIORIDAD: CASI COMPLETADA** (3/4 tareas completadas)
🚨 **CLOTH BUGS: PENDIENTES** (3 bugs críticos identificados)

## COMPLETADO EN ESTA SESIÓN ✅
1. **Optimizar contenedores en RVisualMeshMgr**:
   - Cambio de std::list → std::vector para mejor cache locality
   - Eliminación de búsquedas O(n) en operaciones Del()
   - Gestión inteligente de IDs con reutilización
   - Pre-allocación de vectores para mejor performance

2. **Smart pointers para nuevas features**:
   - Namespace SmartPointers con aliases type-safe
   - Factory functions para creación segura
   - Migración gradual sin breaking changes

## NUEVA INVESTIGACIÓN REQUERIDA 🔍
- Analizar `RCharCloth.cpp` y `RCloth.cpp` para entender normal calculation
- Investigar lighting falloff differences entre cloth and standard meshes
- Examinar material slot handling en cloth rendering pipeline

## PENDIENTE
- [ ] Mejorar LOD system (dejado para después según solicitud)
- [ ] **NUEVO**: Fix cloth rendering bugs (alta prioridad por compatibilidad)
