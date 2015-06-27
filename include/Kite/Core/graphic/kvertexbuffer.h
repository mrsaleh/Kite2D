/* 
 Kite2D Game Framework.
 Copyright (C) 2010-2014  Milad Rasaneh <milad_rasaneh2000@yahoo.com>

 This program is free software: you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation, either version 3 of the License, or 
 any later version.

 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.

 You should have received a copy of the GNU General Public License
 along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
#ifndef KVERTEXBUFFER_H
#define KVERTEXBUFFER_H

/*! \file kvertexbuffer.h */

#include "Kite/Core/system/ksystemdef.h"
#include "Kite/core/system/kcoreinstance.h"
#include "Kite/Core/graphic/kgraphicstructs.h"
#include "Kite/Core/graphic/kgraphictypes.h"

/*! \namespace Kite
	\brief Public namespace.
*/
namespace Kite{

	//! The KVertexArray class provides functions for creating and managing OpenGL buffer objects.
	/*!
		Buffer objects are created in the OpenGL server so that the client application 
		can avoid uploading vertices, indices, texture image data, etc every time they are needed.
	*/
    class KITE_FUNC_EXPORT KVertexBuffer : public KCoreInstance{
    public:

		//! Constructs an empty vertex buffer object (VBO).
		KVertexBuffer(KBufferTargetTypes TargetType);

		//! Destructor
        ~KVertexBuffer();

		//! Creates and initializes a buffer object's data store.
		/*!
			This function is similar to the glBufferData().

			\param Data A pointer to data that will be copied into the data store for initialization,
						or NULL if no data is to be copied.
			\param DataSize  the size in bytes of the buffer object's new data store.
						DataSize = sizeof(DataType) * DataArrayLenght
			\param BufferType A hint to the GL implementation as to how a buffer object's data store will be 
						accessed
		*/
        void fill(const void *Data, U32 DataSize, KVertexBufferTypes BufferType);

		//! Map all of a buffer object's data store into the client's address space, and send its pointer to handle function.
		/*!
			This function is similar to the glMapBuffer().
			inefficient if you have a large buffer
			and need to update a small portion of the values.

			\param Sender Opaque pointer.
		*/
        void update(void *Sender);

		//! Map a section of a buffer object's data store, and send its pointer to handle function.
		/*!
			This function is similar to the glMapBufferRange().
			best methode for streaming buffers

			\param Offset The starting offset within the buffer of the range to be mapped. Offset = sizeof(DataType) * Offset
			\param Size length of the range to be mapped. Size = sizeof(DataType) * DataArrayLenght
			\param Discarded Streaming purpose only. read document of glMapBufferRange() "access" parameter for more information.
			\param Sender Opaque pointer.
		*/
        void update(U32 Offset, U32 Size, bool Discarded, void *Sender);

		//! Updates a subset of a buffer object's data store.
		/*!
			This function is similar to the glBufferSubData().

			\param Offset The starting offset within the buffer of the range to be mapped. Offset = sizeof(DataType) * Offset
			\param Size length of the range to be mapped. Size = sizeof(DataType) * DataArrayLenght
			\param Data A pointer to the new data that will be copied into the data store.
		*/
        void update(U32 Offset, U32 Size, const void *Data);

		//! Bind the vertex buffer object.
		/*!
			This function is similar to the glBindBuffer(),
			but avoid calling that gl function several times if our VBO is currently bound.
			(automatic handle by internal render system)
		*/
        void bind() const;

		//! Unbind the vertex buffer if it is currently bound.
		/*!
			This function is similar to the glBindBuffer(0).
			unbind only if our VBO is currently bound.
		*/
        void unbind();

		//! Unbind current vertex buffer.
		/*!
			This function is similar to the glBindBuffer(0).
		*/
        static void unbindVertexBuffer();

		//! Set the function pointer for updateing buffer.
		/*!
			\param UpdateHandle Function pointer
		*/
        inline void setUpdateHandle(KCallVBUpdate *UpdateHandle) {_kupdateHnd = UpdateHandle;}

		//! Get type of buffer
		/*!
			\return Type of buffer
		*/
        inline KVertexBufferTypes getType() const {return _kbufType;}

		//! Get OpenGL ID of the vertex buffer object
		/*!
			\return OpenGL ID of vertex buffer object
		*/
		inline U32 getGLID() const { return _kbufId; }

		//! Get size of resource in memory
		/*!
			\return Size of resource in bytes
		*/
		U64 getInstanceSize() const;

    private:
        KVertexBufferTypes _kbufType;	//!< Storage state of buffer
		KBufferTargetTypes _kbufTarget;	//!< Type of buffer
        U32 _ksize;		//!< Size of buffer
        U32 _kbufId;	//!< OpenGL vbo ID
        KCallVBUpdate *_kupdateHnd;	//!< Function pointer for update
		static I32 _ktargets[2];	//!< Buffer types
        static U32 _klastBufId;		//!< Last openGL buffer ID
    };
}

#endif // KVERTEXBUFFER_H
