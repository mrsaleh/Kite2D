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
#ifndef KTRANSFORMCOM_H
#define KTRANSFORMCOM_H

#include "Kite/core/kcoredef.h"
#include "Kite/ecs/kcomponent.h"
#include "Kite/ecs/knode.h"
#include "Kite/math/kmathstructs.h"
#include "Kite/math/kmatrix3.h"
#include "Kite/meta/kmetadef.h"
#include "ktransformcom.khgen.h"

KMETA
namespace Kite{
	KM_CLASS(COMPONENT)
    class KITE_FUNC_EXPORT KTransformCom: public KComponent{
		friend class KTransformSys;
		KM_INFO(KI_NAME = "Transform");
		KTRANSFORMCOM_BODY();
    public:

        /// set position
        /// completely restore the previous position
        /// default (0, 0)
		KM_PRO_SET(KP_NAME = "position")
        void setPosition(const KVector2F32& Position);

		KM_PRO_GET(KP_NAME = "position", KP_TYPE = KVector2F32, KP_CM = "Position value")
        inline const KVector2F32 &getPosition() const {return _kposition;}

		/// set scale
		/// completely restore the previous scale
		/// default (1, 1)
		KM_PRO_SET(KP_NAME = "scale")
		void setScale(const KVector2F32 &Scale);

		KM_PRO_GET(KP_NAME = "scale", KP_TYPE = KVector2F32, KP_CM = "Scale value")
		inline const KVector2F32 &getScale() const { return _kscale; }

		/// completely restore the previous Rotation
		/// range [0, 360]
		/// default 0
		KM_PRO_SET(KP_NAME = "rotation")
			void setRotation(F32 Angle);

		KM_PRO_GET(KP_NAME = "rotation", KP_TYPE = F32, KP_CM = "Rotation value")
			inline F32 getRotation() const { return _krotation; }

		/// set center of (position, scale, rotation)
		/// relative to the top-left
		/// default (0, 0)
		KM_PRO_SET(KP_NAME = "center")
		void setCenter(const KVector2F32 &Center);

		KM_PRO_GET(KP_NAME = "center", KP_TYPE = KVector2F32, KP_CM = "Center value")
		inline const KVector2F32 &getCenter() const { return _kcenter; }

		KM_PRO_SET(KP_NAME = "parallaxIndex")
		inline void setRatioIndex(I32 Index) { _kratioIndex = Index; }

		KM_PRO_GET(KP_NAME = "parallaxIndex", KP_TYPE = I32, KP_CM = "Index of Parallax Ratio", KP_MIN = -1, KP_MAX = 127)
		inline I32 getRatioIndex() const { return _kratioIndex; }

		/// return the combined matrix
		KM_FUN()
		inline const KMatrix3 &getMatrix() const { return _kmatrix; }

		/// return the combined matrix for direct manipulation
		KM_FUN()
		inline KMatrix3 &manipulateMatrix() { return _kmatrix; }

		KM_FUN()
		void computeMatrix();

    private:

		void inite() override;

		void attached() override;

		void deattached() override;

        KM_VAR() KVector2F32 _kposition;
		KM_VAR() F32 _krotation;
		KM_VAR() I32 _kratioIndex;
		KM_VAR() KVector2F32 _kscale;
		KM_VAR() KVector2F32 _kskew;
		KM_VAR() KVector2F32 _kcenter;
		KM_VAR() KMatrix3 _kmatrix;

		bool _kcompute;
		SIZE _ksysIndex; 
    };
}

#endif // KTRANSFORMCOM_H
