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
#ifndef KRENDERCOM_H
#define KRENDERCOM_H

#include "Kite/core/kcoredef.h"
#include "Kite/ecs/kcomponent.h"
#include "Kite/graphic/krenderable.h"
#include "Kite/meta/kmetadef.h"
#include <cstring>
#include "krendercom.khgen.h"

KMETA
namespace Kite{
	KM_CLASS(COMPONENT)
	class KITE_FUNC_EXPORT KRenderCom : public KComponent{
		friend class KRenderSys;
		KM_INFO(KI_SHOW = false);
		KM_INFO(KI_NAME = "RenderInstance");
		KMETA_KRENDERCOM_BODY();
    public:
		// array rendering (without index)
		KRenderCom(const std::string &Name = "");

		void attached(KNode *Entity) override;

		void deattached(KNode *Entity) override;

		RecieveTypes onMessage(KMessage *Message, MessageScope Scope) override;

		template<typename T>
		bool registerInterface(T *Component) {
			static_assert(std::is_base_of<KComponent, T>::value, "T must be a drived class from KComponent");
			static_assert(std::is_base_of<KRenderable, T>::value, "T must be a drived class from KRenderable");

			if (_kihandle.getCType() == Component->getType()) return true;
			if (_kihandle.getCType() != CTypes::maxSize) {
				KD_PRINT("override interface detected");
				return false;
			}
			if (Component->getOwnerNode() != getOwnerNode()) {
				KD_PRINT("owner missmatch");
				return false;
			}
			_kihandle = Component->getHandle();
			return true;
		}

		template<typename T>
		bool unregisterInterface(T *Component) {
			static_assert(std::is_base_of<KComponent, T>::value, "T must be a drived class from KComponent");
			static_assert(std::is_base_of<KRenderable, T>::value, "T must be a drived class from KRenderable");

			if (_kihandle.getCType() == CTypes::maxSize) return true;
			if (Component->getOwnerNode() != getOwnerNode()) {
				KD_PRINT("owner missmatch");
				return false;
			}
			if (_kihandle.getCType() != Component->getType()) {
				KD_PRINT("component type missmatch");
				return false;
			} 

			_kihandle = KHandle();
			return true;
		}

		KM_PRO_GET(KP_NAME = "interfaceType", KP_TYPE = KHandle)
		inline const KHandle &getInterfaceHandle() const { return _kihandle; }

	private:
		KM_VAR() KHandle _kihandle; // order of deserialization components is random so we must save this value
    };
}

#endif // KRENDERCOM_H
