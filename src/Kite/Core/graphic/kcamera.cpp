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
#include "Kite/Core/graphic/kcamera.h"
#include "Kite/Core/math/kmathdef.h"
#include <cmath>

namespace Kite{
    KCamera::KCamera():
        _kcenter(0, 0),
        _krotation(0.0f),
        _kzoom(1.0f),
		_kflipy(1.0f),
		_kflipx(1.0f),
        _kneedUpdate(true),
		_ktransform(KMatrix3()) // unit
    {}

	KCamera::KCamera(const KRectI32 &Viewport) :
		_krotation(0.0f),
		_kzoom(1.0f),
		_kflipy(1.0f),
		_kflipx(1.0f),
		_kneedUpdate(true),
		_ktransform(KMatrix3()) // unit
	{
		setViewport(Viewport);
	}

	void KCamera::setViewport(const KRectI32 &Viewport){
		_kcenter.x = (Viewport.left + Viewport.right) / 2.0f;
		_kcenter.y = (Viewport.top + Viewport.bottom) / 2.0f;
		_ksize.x = Viewport.right - Viewport.left;
		_ksize.y = Viewport.top - Viewport.bottom;
	}

	const KTransform *KCamera::getTransform() const{
		// recompute the matrix if needed
		if (_kneedUpdate){
			// rotation components
			F32 angle = _krotation * KMATH_PIsub180;
			F32 cosx = (F32)(std::cos(angle));
			F32 sinx = (F32)(std::sin(angle));
			//F32 tx = -(_kviewport.right + _kviewport.left) / (_kviewport.right - _kviewport.left);
			//F32 ty = -(_kviewport.top + _kviewport.bottom) / (_kviewport.top - _kviewport.bottom);
			F32 tx = -_kcenter.x * cosx - _kcenter.y * sinx + _kcenter.x;
			F32 ty = _kcenter.x * sinx - _kcenter.y * cosx + _kcenter.y;

			// projection components
			F32 a = 2.f / (_ksize.x / _kzoom);
			F32 b = (2.f * _kflipy) / (_ksize.y / _kzoom); // -2.f for microsoft windows coordinate system
			F32 c = -a * _kcenter.x;
			F32 d = -b * _kcenter.y;

			// rebuild the projection matrix
			_ktransform = KTransform(KMatrix3(a * cosx, a * sinx, a * tx + c,
				-b * sinx, b * cosx, b * ty + d,
				0.0f, 0.0f, 1.0f));

			/*_kmatrix = KMatrix3(	a,		0.0f,	tx,
			0.0f,	b,		ty,
			0.0f,	0.0f,	1.0f);*/

			_kneedUpdate = false;
		}

		return &_ktransform;
	}

}