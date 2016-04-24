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
#include "Kite/core/kscenemanager.h"
#include "Kite/meta/kmetamanager.h"
#include "Kite/meta/kmetaclass.h"
#include <luaintf\LuaIntf.h>

namespace Kite {
	KSceneManager::KSceneManager(KResourceManager &RMan) :
		_kactive(&_kdef), _krman(&RMan), _kdef("Kite2D default") 
	{
		initeDefScene();
	}

	void KSceneManager::unloadScene(const std::string &Name) {
		KScene *scene = (KScene *)_krman->get(Name);
		if (scene == nullptr) {
			return;
		}

		// unload scene resources
		for (auto it = scene->beginResource(); it != scene->endResource(); ++it) {
			_krman->unload(it->first);
		}

		// unload scene itself
		_krman->unload(Name);
	}

	KScene *KSceneManager::getScene(const std::string &Name) {
		return (KScene *)_krman->get(Name);
	}

	void KSceneManager::initeDefScene() {
		// TODO: display Kite2D logo
	}

	KMETA_KSCENEMANAGER_SOURCE();
}