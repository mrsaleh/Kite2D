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
#ifndef KENTITY_H
#define KENTITY_H

#include "Kite/core/kcoredef.h"
#include "Kite/core/kcoretypes.h"
#include "Kite/core/kcorestructs.h"
#include "Kite/core/kcomponent.h"
#include "Kite/core/klistener.h"
#include "Kite/core/kmessenger.h"
#include "Kite/core/kistream.h"
#include "Kite/core/kostream.h"
#include "Kite/meta/kmetadef.h"
#include "Kite/serialization/kserialization.h"
#include "Kite/core/kcfstorage.h"
#include <unordered_map>
#include <string>
#include <vector>
#include "kentity.khgen.h"

KMETA
namespace Kite {
	class KEntityManager;
	KM_CLASS(ENTITY, SCRIPTABLE)
	class KITE_FUNC_EXPORT KEntity: public KMessenger, public KListener{
		friend class KEntityManager;
		KMETA_KENTITY_BODY();

	public:
		KEntity(const std::string &Name = "");
		virtual ~KEntity();

		/// redirect recieved message to all sub-components
		KM_FUN()
		RecieveTypes onMessage(KMessage *Message, MessageScope Scope);

		KM_PRO_GET(KP_NAME = "phandle", KP_TYPE = KHandle, KP_CM = "parent handle")
		inline KHandle getParentHandle() const { return _kphandle; }

		KM_PRO_GET(KP_NAME = "handle", KP_TYPE = KHandle, KP_CM = "entity handle")
		inline KHandle getHandle() const { return _khandle; }

		KM_PRO_GET(KP_NAME = "name", KP_TYPE = std::string, KP_CM = "entity unique name")
		inline const std::string &getName() const { return _kname; }

		KM_PRO_GET(KP_NAME = "listener", KP_TYPE = KListener, KP_CM = "entity message listener")
		inline KListener &getListener() { return *(KListener *)this; }

		KM_PRO_GET(KP_NAME = "messenger", KP_TYPE = KMessenger, KP_CM = "entity messenger")
		inline KMessenger &getMessenger() { return *(KMessenger *)this; }

		KM_PRO_GET(KP_NAME = "isActive", KP_TYPE = bool, KP_CM = "is active")
		inline bool isActive() const { return _kactive; }

		KM_PRO_SET(KP_NAME = "isActive")
		void setActive(bool Active);

		KM_PRO_GET(KP_NAME = "isPrefab", KP_TYPE = bool, KP_CM = "is prefab")
			inline bool isPrefab() const {return _kisPrefab; }

		KM_PRO_GET(KP_NAME = "envTableName", KP_TYPE = std::string, KP_CM = "entity env table name in lua")
		inline const std::string &getLuaTName() const { return _kluatable; }

		KM_PRO_GET(KP_NAME = "prefab", KP_TYPE = std::string, KP_CM = "entity prefab name")
			inline const std::string &getPrefab() const { return _kprefabName; }

		KM_FUN()
		KComponent *addComponent(const std::string &CType, const std::string &CName = "");

		KM_FUN()
		KComponent *getComponent(const std::string &CType, const KHandle &CHandle);

		KM_FUN()
		KComponent *getComponentByName(const std::string &CType, const std::string &CName);

		KM_FUN()
		void getFixedComponents(std::vector<KComponent *> &Output);

		/// return vector of KHandle to avoiding pointer dangling during update
		KM_FUN()
		void getScriptComponents(std::vector<KHandle> &Output);

		KM_FUN()
		void reorderScriptComponent(const KHandle &CHandle, U32 NewOrder);

		KM_FUN()
		void reorderScriptComponentByName(const std::string &CName, U32 NewOrder);

		KM_FUN()
		bool hasComponent(const std::string &CType, const std::string &Name);

		KM_FUN()
		bool hasComponentType(const std::string &CType);

		KM_FUN()
		KHandle getComponentHandle(const std::string &CType, const std::string &Name);

		KM_FUN()
		void removeComponent(const std::string &CType, const std::string &ComponentName = "");

		KM_FUN()
		void clearComponents();

		KM_FUN()
		void addChild(const KHandle &EHandle);

		KM_FUN()
		bool hasChild() const;

		inline const auto childList() const { return &_kchilds; }

	private:

		// internal use 
		void setComponent(const std::string &CType, const std::string &Name, KComponent *Comp);
		void remChildIndex(U32 ID);
		void setHandle(const KHandle Handle);
		
		KM_VAR() bool _kactive;											// entity actitvity state
		KM_VAR() bool _kisPrefab;
		KM_VAR() KHandle _khandle;										// entity handle in the entity manager
		KM_VAR() KHandle _kphandle;										// entity parent handle
		KM_VAR() U32 _kplistid;											// entity self id in the parent list
		KM_VAR() std::string _kprefabName;								// entity prefab name
		KM_VAR() std::string _kname;									// entity unique name
		KM_VAR() std::string _kluatable;								// entity env table name in lua
		KM_VAR() std::unordered_map<std::string, KHandle> _kfixedComp;	// fixed components slots (built-in components)
		KM_VAR() std::unordered_map<std::string, KHandle> _klogicComp;	// dynamic components (logic components)
		KM_VAR() std::vector<KHandle> _klogicOrder;						// logic components queue by order
		KM_VAR() std::vector<KHandle> _kchilds;							// children list

		// runtime variables (
		std::unordered_map<std::string, Internal::BaseCHolder<KComponent> *> *_kcstorage;
		KCFStorage<KEntity> *_kestorage;
	};
}

#endif // KENTITY_H