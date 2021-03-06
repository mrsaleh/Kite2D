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
#ifndef KGEOMETRIC_H
#define KGEOMETRIC_H

#include "Kite/core/kcoredef.h"
#include "Kite/math/kmathstructs.h"
#include "Kite/math/kmathtypes.h"

namespace Kite{
	class KITE_FUNC_EXPORT KGeometric{
	public:
		// box (rectangle)
		static bool isPointIn(const KRectF32 &Box, const KVector2F32 &HitPoint);

		// box (quad)
		static bool isPointIn(const KRect2F32 &Box, const KVector2F32 &HitPoint);

		// cyrcle
		static bool isPointIn(const KVector2F32 &Center, F32 Radius, const KVector2F32 &HitPoint);

		// polygon
		static bool isPointIn(const KVector2F32 *Points, U32 Size, const KVector2F32 &HitPoint);

		// bounding box points
		static KRectF32 getBoundingBox(const KVector2F32 *Points, U32 Size);

		// bounding box rectangles
		static KRectF32 getBoundingBox(const KRectF32 *Rects, U32 Size);

		// bounding box cycles (cycles with same radius)
		static KRectF32 getBoundingBox(const KVector2F32 *Centers, F32 Radius, U32 Size);

		// get orientation of 3 points
		static KOrientationTypes getOrientation(const KVector2F32 &PointA, const KVector2F32 &PointB, const KVector2F32 &PointC);

		// get convex hull
		//  Points = an (unsorted) array of 2D points
		//  Size = the number of points in Points[]
		//  Output: ConvexHull = an array of the convex hull vertices (max is Size)
		//  Return: the number of points in ConvexHull
		static U32 getConvexHull(const KVector2F32 *Points, U32 Size, KVector2F32 *ConvexHull);

		// line intersect
		static bool isIntersect(const KVector2F32 &Line1Start, const KVector2F32 &Line1End,
			const KVector2F32 &Line2Start, const KVector2F32 &Line2End);

		// cyrcle intersect
		static bool isIntersect(const KVector2F32 &Center1, F32 Radius1, const KVector2F32 &Center2, F32 Radius2);

		// get intersect point between 2 line
		// output: IntersectPoint
		static bool getIntersectPoint(const KVector2F32 &Line1Start, const KVector2F32 &Line1End,
			const KVector2F32 &Line2Start, const KVector2F32 &Line2End, KVector2F32 &IntersectPoint);

	};
}

#endif // KGEOMETRIC_H