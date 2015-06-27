/*
    Kite2D Game Framework.
    Copyright (C) 2010-2015  Milad Rasaneh <milad_rasaneh2000@yahoo.com>

    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Lesser General Public
    License as published by the Free Software Foundation; either
    version 2.1 of the License, or (at your option) any later version.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public
    License along with this library; if not, write to the Free Software
    Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301
    USA
*/
#include "src/Kite/core/graphic/glcall.h"
#include "Kite/core/graphic/kgraphicutil.h"

namespace Kite{
    I32 getMaximumTextureSize(){
        GLint size;
        DGL_CALL(glGetIntegerv(GL_MAX_TEXTURE_SIZE, &size));
        return (I32)size;
    }

    I32 getMaximumTextureUnit(){
        GLint maxUnits;
        DGL_CALL(glGetIntegerv(GL_MAX_TEXTURE_IMAGE_UNITS, &maxUnits));
        return (I32)maxUnits;
    }

    I32 getMaximumVertexAttrib(){
        GLint maxVertAttr;
        DGL_CALL(glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &maxVertAttr));
        return (I32)maxVertAttr;
    }

    // not work with gl 3.3 context
//    bool isShaderAvailable(){
//        return false;
//        return GLEW_ARB_shading_language_100 &&
//               GLEW_ARB_shader_objects       &&
//               GLEW_ARB_vertex_shader        &&
//               GLEW_ARB_fragment_shader;
//    }
}
