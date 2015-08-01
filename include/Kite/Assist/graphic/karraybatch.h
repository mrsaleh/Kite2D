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
#ifndef KARRAYBATCH_H
#define KARRAYBATCH_H

#include "Kite/Core/system/ksystemdef.h"
#include "Kite/Core/system/knoncopyable.h"
#include "Kite/Core/graphic/kgraphicstructs.h"
#include "Kite/Core/graphic/kvertexarray.h"
#include "Kite/Core/graphic/kvertexbuffer.h"
#include "Kite/Assist/graphic/kcamera.h"
#include "Kite/Assist/graphic/karraybatchobject.h"
#include <vector>

namespace Kite{
    class KITE_FUNC_EXPORT KArrayBatch : KNonCopyable{
    public:
		KArrayBatch(U32 VertexSize, const KBatchConfig Config, bool PointSprite);
		KArrayBatch(const std::vector<KArrayBatchObject *> &Objects, const KBatchConfig Config, bool PointSprite);

		inline U32 getVertexSize() const { return _kvsize; }

		inline void setCamera(const KCamera &Camera) { _kcam = &Camera; }
		inline const KCamera &getCamera() const { return *_kcam; }

		/// draw a single object
		void draw(const KArrayBatchObject *Object, const KBatchUpdate &Update);

		/// draw a vector of objects
		void draw(const std::vector<KArrayBatchObject *> &Objects, const KBatchUpdate &Update);


    private:
		void _draw(const std::vector<const KArrayBatchObject *> &Objects, U32 VSize, const KBatchUpdate &Update);
        static void _updatePos(void *Data, U32 Offset, U32 DataSize, void *Sender);
		static void _updateUV(void *Data, U32 Offset, U32 DataSize, void *Sender);
		static void _updateCol(void *Data, U32 Offset, U32 DataSize, void *Sender);
		static void _updatePar(void *Data, U32 Offset, U32 DataSize, void *Sender);
        std::vector<const KArrayBatchObject *> _kobj;
		Internal::KUpdateSender _ksender;
		const KCamera *_kcam;
		static const KCamera _kdefcam;
        KVertexArray _kvao;
		KVertexBuffer _kvboXY;		/// xy (position)
        KVertexBuffer _kvboUV;		/// uv (texture uv)
		KVertexBuffer _kvboCol;		/// rgba (color)
		KVertexBuffer _kvboPnt;		/// stride: point size and texture size (Particle)
        KBatchConfig _kconfig;
		U32 _kvsize;
		bool _kpstride;
    };
}

#endif // KARRAYBATCH_H