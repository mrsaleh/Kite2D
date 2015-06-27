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
#ifndef KQUAD_H
#define KQUAD_H

#include "Kite/Core/system/ksystemdef.h"
#include "Kite/Core/graphic/kgraphicstructs.h"
#include "Kite/Core/math/kmathstructs.h"
#include "Kite/Assist/graphic/ktransformable.h"
#include "kite/Assist/graphic/kindexbatchobject.h"
#include "kite/Assist/graphic/kanimeobject.h"

namespace Kite{
    class KITE_FUNC_EXPORT KQuad : public KIndexBatchObject, public KTransformable, public KAnimeObject{
    public:
		KQuad();
		KQuad(const KRectF32 &Dimension, const KRectF32 &UV, const KColor &Color);
		KQuad(const KRect2F32 &Dimension, const KRectF32 &UV, const KColor &Color);

		void setDimension(const KRect2F32 &Dimension);
		void setDimension(const KRectF32 &Dimension);
		inline const KRect2F32 &getDimension() const { return _kdim; }

		void setUV(const KRectF32 &UV);
		inline const KRectF32 &getUV() const { return _kuv; }

		void setColor(const KColor &Color);
		inline const KColor &getColor() const { return _kcolor; }

	protected:
		// from KIndexBatchObject (output/send)
		const KTransform &getModelViewTransform() const;

		// from KAnimeObject (input/recive)
		void animeUpdate(const KAnimeValue *AnimatedValue);

    private:
		void _fillIndex();
		KRect2F32 _kdim;
		KRectF32 _kuv;
		KColor _kcolor;
		KTransform _kmodelView;
    };
}

#endif // KQUAD_H
