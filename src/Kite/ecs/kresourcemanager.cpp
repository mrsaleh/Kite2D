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
#include "Kite/ecs/kresourcemanager.h"
#include "Kite/meta/kmetamanager.h"
#include "Kite/meta/kmetaclass.h"
#include "Kite/serialization/kbinaryserial.h"
#include "Kite/serialization/types/kstdstring.h"
#include "Kite/serialization/types/kstdumap.h"
#include "Kite/serialization/types/kstdpair.h"
#include "kmeta.khgen.h"
#include <luaintf\LuaIntf.h>

namespace Kite {
	KResourceManager::KResourceManager(){
		// initialize factory array
		initeFactory();

		// register resource types and stream types
		registerRTypes(this);
	}

	KResourceManager::~KResourceManager(){
		if (!_kmap.empty()) {
			KD_PRINT("call clear() before destroing resource manager.");
		}
	}

	void KResourceManager::initeFactory() {
		for (SIZE i = 0; i < (SIZE)RTypes::maxSize; ++i) {
			_krfactory[i] = nullptr;
		}

		for (SIZE i = 0; i < (SIZE)IStreamTypes::maxSize; ++i) {
			_ksfactory[i] = nullptr;
		}
	}

	void KResourceManager::registerIStream(IStreamTypes Type, KIStream *(*Func)()) {
		auto index = (SIZE)Type;

		// check type
		if (_ksfactory[index] != nullptr) {
			KD_FPRINT("this input stream type has already been registered. type name: %s", getIStreamTypesName(Type).c_str());
			return;
		}

		_ksfactory[index] = Func;
	}

	void KResourceManager::registerResource(RTypes Type, KResource *(*Func)(const std::string &)) {
		auto index = (SIZE)Type;

		// check type
		if (_krfactory[index] != nullptr) {
			KD_FPRINT("this type has already been registered. type name: %s", getRTypesName(Type).c_str());
			return;
		}

		_krfactory[index] = Func;
	}

	KResource *KResourceManager::load(const std::string &Name){
		// checking file name
		if (Name.empty()) {
			KD_PRINT("empty name.");
			return nullptr;
		}

		// check dictionary
		auto found = _kmap.find(Name);
		if (found == _kmap.end()) {
			KD_FPRINT("There is no resource with this name. name: %s", Name.c_str());
			return nullptr;
		}

		// if resource is loaded, increase ref counter and return it
		if (found->second.res != nullptr) {
			found->second.res->incRef();
			return found->second.res;
		} 

		// else load it and return
		// create new resource and associated input stream
		auto stream = _ksfactory[(SIZE)found->second.stype]();
		if (stream == nullptr) {
			KD_FPRINT("can't create stream. stream type: %s", getIStreamTypesName(found->second.stype).c_str());
			return nullptr;
		}

		KResource *resource = _krfactory[(SIZE)found->second.rtype](Name);
		resource->setOnFly(false);

		// loading composite resources (recursive)
		if (resource->isComposite()) {
			if (!loadCompositeList(found->second.stype, resource, found->second.address)) {
				KD_FPRINT("can't load composite resource. rname: %s", Name.c_str());
				delete resource;
				delete stream;
				return nullptr;
			}
		}

		// loading resource itself
		if (!resource->_loadStream(*stream, found->second.address)) {
			KD_FPRINT("can't load resource. rname: %s", Name.c_str());
			delete resource;
			delete stream;
			return nullptr;
		}
		resource->setAddress(found->second.address);

		// stream lifetime
		std::pair<KResource *, KIStream *> pair;
		if (resource->isCatchStream()) {
			resource->setCatchStream(stream);
		} else {
			stream->close();
			delete stream;
		}

		// increment refrence count
		resource->incRef();

		// insert resource to map
		found->second.res = resource;

		// post a message about new resource
		KMessage msg;
		msg.setType("onResLoad");
		msg.setData((void *)resource, sizeof(resource));
		postMessage(&msg, MessageScope::ALL);

		return resource;
	}

	KResource *KResourceManager::getLoaded(const std::string &Name) {
		// checking file name
		if (Name.empty()) {
			KD_PRINT("empty name.");
			return nullptr;
		}

		auto found = _kmap.find(Name);
		if (found != _kmap.end()) {
			return found->second.res;
		}

		KD_FPRINT("there is no resource with this name. name: %s", Name.c_str());
		return nullptr;
	}

	bool KResourceManager::registerName(const std::string &Name, const std::string &Address, RTypes RType, IStreamTypes SType) {
		if (Name.empty() || Address.empty()) {
			KD_PRINT("empty name or addrss.");
			return false;
		}

		// check map
		auto found = _kmap.find(Name);

		// this name is not exist in the map so we insert it to the map
		if (found == _kmap.end()) {
			_kmap.insert({ Name, info(Address, RType, SType) });
			return true;
		}

		// this name is exist so we check its resource
		if (found->second.res == nullptr) {
			// overwrite infos
			found->second.address = Address;
			found->second.stype = SType;
			found->second.rtype = RType;
			return true;
		}

		// this name has an associated loaded resource so we can't overwrite it
		KD_FPRINT("this name has an associated loaded resource. name: %s", Name.c_str());
		return false;
	}

	void KResourceManager::unload(const std::string &Name, UnloadMode Mode) {
		// checking file name
		if (Name.empty()) {
			KD_PRINT("empty name entered.");
			return;
		}

		auto found = _kmap.find(Name);
		// using dictionary key
		if (found != _kmap.end()) {
			if (found->second.res != nullptr) {

				// send msg about it befor actually unload it
				KMessage msg;
				msg.setType("onResUnload");
				msg.setData((void *)found->second.res, sizeof(KResource *));
				postMessage(&msg, MessageScope::ALL);

				// checking unload mode
				if (Mode == UnloadMode::IMMEDIATELY) {
					delete found->second.res;
					found->second.res = nullptr;

				} else {
					// decrease ref count
					found->second.res->decRef();

					// delete it if ref count is 0
					if (found->second.res->getReferencesCount() <= 0) {
						delete found->second.res;
						found->second.res = nullptr;
					}
				}
			}
		}
	}

	const std::vector<KResource *> &KResourceManager::dump() {
		static std::vector<KResource *> res;
		res.clear();
		res.reserve(_kmap.size());

		for (auto it = _kmap.cbegin(); it != _kmap.cend(); ++it) {	
			if (it->second.res != nullptr) {
				res.push_back(it->second.res);
			}
		}

		return res;
	}

	bool KResourceManager::saveDictionary(KOStream &Stream, const std::string &Address) {
		KBinarySerial bserial;
		
		bserial << _kmap.size();
		for (auto it = _kmap.begin(); it != _kmap.end(); ++it) {
			bserial << it->first;
			bserial << it->second.address;
			bserial << it->second.rtype;
			bserial << it->second.stype;
		}

		if (!bserial.saveStream(Stream, Address, 0)) {
			KD_FPRINT("cant save resource dictionary. address: %s", Address.c_str());
			return false;
		}

		return true;
	}

	bool KResourceManager::loadDictionary(KIStream &Stream, const std::string &Address) {
		KBinarySerial bserial;
		if (!bserial.loadStream(Stream, Address)) {
			KD_FPRINT("cant load resource dictionary. address: %s", Address.c_str());
			return false;
		}

		// first clear manager
		clear();

		// load dictinary size
		SIZE size = 0;
		bserial >> size;

		std::string name;
		std::string address;
		RTypes rtype;
		IStreamTypes stype;
		for (auto i = 0; i < size; ++i) {
			bserial >> name;
			bserial >> address;
			bserial >> rtype;
			bserial >> stype;

			// insert data to the map
			_kmap.insert({ name, info(address, rtype, stype) });
		}

		return true;
	}

	void KResourceManager::clear() {
		for (auto it = _kmap.begin(); it != _kmap.end(); ++it) {
			// post a message about unloaded resource
			if (it->second.res != nullptr) {
				KMessage msg;
				msg.setType("onResUnload");
				msg.setData((void *)it->second.res, sizeof(it->second.res));
				postMessage(&msg, MessageScope::ALL);

				delete it->second.res;
			}
		}

		// clear map
		_kmap.clear();
	}

	bool KResourceManager::loadCompositeList(IStreamTypes SType, KResource *Res, const std::string &Address) {
		std::vector<std::string> plist;
		KBinarySerial serializer;
		auto sindex = (SIZE)SType;
		auto stream = _ksfactory[sindex]();
		if (!serializer.loadStream(*stream, Address + ".dep")) {
			KD_FPRINT("cant load resource composite list. rname: %s", Res->getName().c_str());
			delete stream;
			return false;
		}
		delete stream;

		serializer >> plist;
		Res->_kclist.clear();

		// loading composite resources
		for (auto it = plist.begin(); it != plist.end(); ++it) {

			// load composite resources based our name\address dictionary
			auto comp = load((*it));
			if (comp == nullptr) {
				KD_FPRINT("cant load dependecy. dependency name: %s", (*it).c_str());
			}
			Res->_kclist.push_back(comp);
		}

		return true;
	}

	KMETA_KRESOURCEMANAGER_SOURCE();
}