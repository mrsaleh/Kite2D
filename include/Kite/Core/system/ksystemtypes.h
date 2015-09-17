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
#ifndef KSYSTEMTYPES_H
#define KSYSTEMTYPES_H

namespace Kite{

	/* Power Sourece State */
	enum KPowerStateTypes{
		KPS_ACON,
		KPS_ACOFF,
		KPS_UNKNOWN
	};

	/* Battery State */
	/*enum KBatteryStateTypes{
		KBS_USING,
		KBS_CHARGING,
		KBS_NOBATTERY,
		KBS_UNKNOWN
	};*/

	enum KIOTypes{
		KIO_READ,
		KIO_WRITE,
		KIO_WRITE_APPEND
	};

	enum KVariantTypes : U8 {
		KVT_I8 = 0,
		KVT_U8,
		KVT_I16,
		KVT_U16,
		KVT_I32,
		KVT_U32,
		KVT_I64,
		KVT_U64,
		KVT_F32,
		KVT_F64,
		KVT_VPTR
	};

	enum KVectorComponentTypes{
		KVC_X = 0,
		KVC_Y = 1,
		KVC_Z = 2,
		KVC_W = 3
	};

	enum KCoreInstanceTypes : U8{
		KCI_IMAGE = 0,
		KCI_TEXTURE,
		KCI_AUDIOBUFFER,
		KCI_AUDIOSOURCE,
		KCI_VAO,
		KCI_VBO,
		KCI_IBO,
		KCI_PBO,
		KCI_FBO,
		KCI_SHADER,
		KCI_SHPROGRAM,
		KCI_WINDOW
	};

	enum KResourceTypes : U8 {
		KRT_TEXTURE = 0,
		KRT_IMAGE,
		KRT_AUDIOBUFFER,
		KRT_AUDIOSOURCE,
		KRT_SHADER,
		KRT_SHPROGRAM,
		KRT_ATLAS,
		KRT_ANIMCLIP,
		KRT_SCENE
	};

	enum KGridMapTriggerTypes {
		KST_ENTER,
		KST_LEAVE
	};

	typedef void(*KCallGridMapTrigger)(void *Data, KGridMapTriggerTypes State);

	/*typedef U64(*KCallInputStreamRead)(void *Data, U64 DataSize);
	typedef I32(*KCallInputStreamSeek)(I64 Offset, I32 Origin);
	typedef I64(*KCallInputStreamTell)();
	typedef bool(*KCallInputStreamIsOpen)();
	typedef I32(*KCallInputStreamEOF)();
	typedef I32(*KCallInputStreamClose)();*/

}
#endif // KSYSTEMTYPES_H
