set(INCROOT ${PROJECT_SOURCE_DIR}/include/Kite/graphic)
set(SRCROOT ${PROJECT_SOURCE_DIR}/src/Kite/graphic)

# all source files
set(GFX_SRC
    ${SRCROOT}/tp/glew.c
    ${SRCROOT}/glcall.cpp
    ${SRCROOT}/imageio.cpp
    ${SRCROOT}/kframebuffer.cpp
    ${SRCROOT}/kgraphicstructs.cpp
    ${SRCROOT}/kimage.cpp
    ${SRCROOT}/kshader.cpp
    ${SRCROOT}/kshaderprogram.cpp
    ${SRCROOT}/ktexture.cpp
    ${SRCROOT}/kvertexarray.cpp
    ${SRCROOT}/kvertexbuffer.cpp
    ${SRCROOT}/kgraphictypes.cpp
    ${SRCROOT}/krendersys.cpp
    ${SRCROOT}/kcameracom.cpp
    ${SRCROOT}/kquadcom.cpp
    ${SRCROOT}/korthogonalmap.cpp
    ${SRCROOT}/kgcullingsys.cpp
    #${SRCROOT}/korthomapcom.cpp
    ${SRCROOT}/katlastexture.cpp
    ${SRCROOT}/katlastexturearray.cpp
    ${SRCROOT}/korthotilestamp.cpp
    #${SRCROOT}/kbitmaptextcom.cpp
    PARENT_SCOPE
)

# all header files
set(GFX_INC
    ${SRCROOT}/glcall.h
    ${SRCROOT}/imageio.h
    ${INCROOT}/kgraphic.h
    ${INCROOT}/kframebuffer.h
    ${INCROOT}/kgraphicstructs.h
    ${INCROOT}/kgraphicdef.h
    ${INCROOT}/kgraphictypes.h
    ${INCROOT}/kimage.h
    ${INCROOT}/kshader.h
    ${INCROOT}/kshaderprogram.h
    ${INCROOT}/ktexture.h
    ${INCROOT}/kvertexarray.h
    ${INCROOT}/kvertexbuffer.h
    ${INCROOT}/krendersys.h
    ${INCROOT}/krenderable.h
    ${INCROOT}/kcameracom.h
    ${INCROOT}/kquadcom.h
    ${INCROOT}/korthogonalmap.h
    ${INCROOT}/kgcullingsys.h
    #${INCROOT}/korthomapcom.h
    ${INCROOT}/katlastexture.h
    ${INCROOT}/katlastexturearray.h
    ${INCROOT}/korthotilestamp.h
    #${INCROOT}/kbitmaptextcom.h
    ${INCROOT}/kcullable.h
    PARENT_SCOPE
)

