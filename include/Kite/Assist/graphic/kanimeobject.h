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
#ifndef KANIMEOBJECT_H
#define KANIMEOBJECT_H

#include "Kite/Core/system/ksystemdef.h"
#include "Kite/Core/graphic/kgraphicstructs.h"
#include "Kite/Core/graphic/kgraphictypes.h"
#include "Kite/Core/math/kmathstructs.h"
#include "Kite/Core/math/ktransform.h"

namespace Kite{
	class KITE_FUNC_EXPORT KAnimeObject{
		friend class KAnimeController;
	protected:
		// color
		inline const KColor &getAnimeColor() const { return _kcolor; }

		// UV
		inline const KRect2F32 &getAnimeUV() const { return _kuv; }

		// transform
		inline const KTransform &getAnimeTransform() const { return _ktransform; }

		virtual void animeUpdate(bool ColorChanged, bool UVChanged, bool TransformChanged) = 0;
	private:
		KColor _kcolor;
		KRect2F32 _kuv;
		KTransform _ktransform;
	};
}

#endif // KANIMEOBJECT_H