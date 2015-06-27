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
#include "Kite/core/system/kcoreinstance.h"
#include "Kite/Core/system/ksystemutil.h"

namespace Kite{
	std::unordered_map<U64, const KCoreInstance *> KCoreInstance::_kinsptr;
	U32 KCoreInstance::_kinstances[12];
	KCoreInstance::KCoreInstance(KCoreInstanceTypes Type){
		_ktype = Type;
		_kid = getUniqueNumber();
		++_kinstances[Type];
		_kinsptr.insert({ _kid, this });
		int c = 0;
	}

	KCoreInstance::~KCoreInstance(){
		--_kinstances[_ktype];
		_kinsptr.erase(_kid);
	}

	U32 KCoreInstance::getInstanceCount(KCoreInstanceTypes Type) {
		return _kinstances[Type]; 
	}

	const KCoreInstance *KCoreInstance::getInstancePointer(U64 UniqueID){
		std::unordered_map<U64, const KCoreInstance *>::const_iterator got = _kinsptr.find(UniqueID);

		if (got != _kinsptr.end())
			return got->second;

		return 0;
	}

	U64 KCoreInstance::getInstanceTotalSize(){
		U64 total = 0;
		for (auto it = _kinsptr.begin(); it != _kinsptr.end(); ++it){
			total += it->second->getInstanceSize();
		}
		return total;
	}

	U64 KCoreInstance::getInstanceSize(KCoreInstanceTypes Type){
		U64 total = 0;
		for (auto it = _kinsptr.begin(); it != _kinsptr.end(); ++it){
			if (it->second->_ktype == Type)
				total += it->second->getInstanceSize();
		}

		return total;
	}
}