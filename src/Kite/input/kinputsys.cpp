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
#include "Kite/input/kinputsys.h"
#include "Kite/input/kkeyboard.h"
#include "Kite/input/kmouse.h"
#include "Kite/meta/kmetatypes.h"
#include "Kite/meta/kmetamanager.h"
#include "Kite/meta/kmetaclass.h"
#include "Kite/engine/kengine.h"
#include <luaintf/LuaIntf.h>

namespace Kite {
	bool KInputSys::update(F64 Delta, KEntityManager *EManager, KResourceManager *RManager) {
		//EDITOR_STATIC const bool isregist = EManager->isRegisteredComponent(CTypes::Input);
		LuaIntf::LuaRef ctable(_klvm, "_G.hooks.post");
		if (ctable.isFunction()) {
#ifdef KITE_DEV_DEBUG
			try {
				if (KKeyboard::isAnyKeyDown()) {
					KMessage msg("onKeyDown");
					ctable("onKeyDown", msg);
				}
				if (KMouse::isAnyKeyDown()) {
					KMessage msg("onMouseDown");
					ctable("onMouseDown", msg);
				}
				
			} catch (std::exception& e) {
				KD_FPRINT("input function failed: %s", e.what());
				return false;
			}
#else
			if (KKeyboard::isAnyKeyDown()) {
				KMessage msg("onKeyDown");
				ctable("onKeyDown", msg);
			}
			if (KMouse::isAnyKeyDown()) {
				KMessage msg("onMouseDown");
				ctable("onMouseDown", msg);
			}
#endif
		} else {
			KD_PRINT("engine hooks system is corrupted");
			return false;
		}

		return true;
	}

	bool KInputSys::inite(void *Data) {
		if (!Data) return false;
		auto engien = static_cast<KEngine *>(Data);

		if (!isInite()) {
			_klvm = static_cast<lua_State *>(engien->getLuaState());

			setInite(true);
		}
		
		return isInite();
	}

	void KInputSys::destroy() { setInite(false); }

	KMETA_KINPUTSYS_SOURCE();
}