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
#ifndef KGRAPHICTYPES_H
#define KGRAPHICTYPES_H

#include "Kite/Core/meta/kmetadef.h"
#include "Kite/Core/meta/kmetaenum.h"
#include "Kite/Core/meta/kmetamanager.h"

/*! \file kgraphictypes.h
	\brief All core graphic types.
*/

/*! \namespace Kite
	\brief Public namespace.
*/
namespace Kite{
	/*! \enum Pixel blend
	\brief Blend types
	*/
    enum KTextureEnvMode{
        KTE_ADD = 0,
        KTE_MODULATE,
        KTE_DECAL,
        KTE_BLEND,
        KTE_REPLACE,
        KTE_COMBINE
    };

	/*! \enum KVertexBufferTypes
		\brief Performance hint for VBO to provide how the buffer object is going to be used.
	*/
    enum KVertexBufferTypes : U8{
        KVB_STATIC = 0,	//!< The data in VBO will not be changed (specified once and used many times)
        KVB_DYNAMIC,	//!< The data in VBO will be changed frequently (specified and used repeatedly)
        KVB_STREAM		//!< The data in VBO will be changed every frame (specified once and used once)
    };

	/*! \enum KBufferTargetTypes
		\brief Buffer types.
	*/
	enum KBufferTargetTypes{
		KBT_INDEX = 0,	//!< Index buffer
		KBT_VERTEX		//!< Vertex buffer
	};

	/*! \enum KMapAccessTypes */
    enum KMapAccessTypes{
        KMA_READ = 0,	//!< Reading access
        KMA_WRITE,		//!< Writing access
        KMA_RW			//!< Reading/writing access
    };

	/*! \enum KGeoPrimitiveTypes
		\brief Primitive types
	*/
    enum KGeoPrimitiveTypes{
        KGP_POINTS = 0,
        KGP_LINES,
        KGP_LINE_STRIP,
        KGP_LINE_LOOP,
        KGP_TRIANGLES,
        KGP_TRIANGLE_STRIP,
        KGP_TRIANGLE_FAN,
        KGP_LINE_STRIP_ADJACENCY,
        KGP_LINES_ADJACENCY,
        KGP_TRIANGLE_STRIP_ADJACENCY,
        KGP_TRIANGLES_ADJACENCY
    };

//    enum KFilteringDrawTypes{
//        KFD_ALIASED,
//        KFD_SMOOTH
//    };

	/*! \enum KColorTypes
		\brief Hex colors code
	*/
    enum KColorTypes{
        KC_BLACK = 0x000000,           KC_WHITE = 0xFFFFFF,
        KC_RED = 0xff0000,             KC_YELLOW = 0xffff00,
        KC_BLUE = 0x0000ff,            KC_GREEN = 0x00ff00,
        KC_CRIMSON = 0xDC143C,         KC_PINK = 0xFFC0CB,
        KC_PALEVIOLETRED = 0xDB7093,   KC_LIMEGREEN = 0x32CD32,
        KC_LAVENDERBLUSH = 0xFFF0F5,   KC_HOTPINK = 0xFF69B4,
        KC_RASPBERRY = 0x872657,       KC_COBALTGREEN = 0x3D9140,
        KC_DEEPPINK = 0xFF1493,        KC_MAROON = 0xFF34B3,
        KC_VIOLET = 0xEE82EE,          KC_MEDIUMSEAGREEN = 0x3CB371,
        KC_DARKVIOLET = 0x9400D3,      KC_ORCHID = 0xDA70D6,
        KC_THISTLE = 0xD8BFD8,         KC_CYAN = 0x00FFFF,
        KC_PLUM = 0xDDA0DD,            KC_MAGENTA  = 0xFF00FF,
        KC_BLUEVIOLET = 0x8A2BE2,      KC_POWDERBLUE = 0xB0E0E6,
        KC_PURPLE = 0x800080,          KC_GHOSTWHITE = 0xF8F8FF,
        KC_INDIGO = 0x4B0082,          KC_DODGERBLUE = 0x1E90FF,
        KC_LAVENDER = 0xE6E6FA,        KC_NAVY = 0x000080,
        KC_MIDNIGHTBLUE = 0x191970,    KC_CORNFLOWERBLUE = 0x6495ED,
        KC_COBALT = 0x3D59AB,          KC_ROYALBLUE = 0x4169E1,
        KC_LIGHTSTEELBLUE = 0xB0C4DE,  KC_SLATEGRAY = 0x708090,
        KC_SKYBLUE = 0x87CEEB,         KC_PEACOCK = 0x33A1C9,
        KC_CADETBLUE = 0x5F9EA0,       KC_AZURE = 0xF0FFFF,
        KC_COLDGREY = 0x808A87,        KC_SPRINGGREEN = 0x00FF7F,
        KC_EMERALDGREEN = 0x00C957,    KC_MINT = 0xBDFCC9,
        KC_DARKSEAGREEN = 0x8FBC8F,    KC_PALEGREEN = 0x98FB98,
        KC_FORESTGREEN = 0x228B22,     KC_LAWNGREEN = 0x7CFC00,
        KC_GREENYELLOW = 0xADFF2F,     KC_MELON = 0xE3A869,
        KC_OLIVEDRAB = 0x6B8E23,       KC_IVORY = 0xFFFFF0,
        KC_BEIGE = 0xF5F5DC,           KC_ORANGE = 0xFF8000,
        KC_OLIVE = 0x808000,           KC_DARKKHAKI = 0xBDB76B,
        KC_KHAKI = 0xF0E68C,           KC_SIENNA = 0xA0522D,
        KC_PALEGOLDENROD = 0xEEE8AA,   KC_BANANA = 0xE3CF57,
        KC_GOLD = 0xFFD700,            KC_SNOW = 0xFFFAFA,
        KC_CADMIUMYELLOW = 0xFF9912,   KC_BRICK = 0x9C661F,
        KC_ARKORANGE = 0xFF8C00,       KC_CARROT = 0xED9121,
        KC_FLESH = 0xFF7D40,           KC_CADMIUMORANGE = 0xFF6103,
        KC_CORAL = 0x8B5742,           KC_SALMON = 0xFA8072,
        KC_BROWN = 0xA52A2A,           KC_FIREBRICK = 0xB22222,
        KC_GRAY = 0x808080
    };

    /*enum KColorComponent{
        KCC_R = 0,
        KCC_G = 1,
        KCC_B = 2,
        KCC_A = 3
    };

    enum KRectComponent{
        KRC_X = 0,
        KRC_Y = 1,
        KRC_W = 2,
        KRC_H = 3
    };*/


//    enum KFontCharSetTypes{
//        KFC_ANSI,
//        KFC_ARABIC,
//        KFC_HEBREW,
//        KFC_AUTO
//    };

	/*! \enum KTextureFilterTypes
		\brief Magnification texture filtering options
	*/
    enum KTextureFilterTypes : U8{
		KTF_NEAREST = 0,	//!< Select the texel nearest the texture coordinate
        KTF_LINEAR		//!< Perform a weighted linear blend between the nearest adjacent samples
    };

	/*! \enum KTextureWrapTypes
		\brief The possible heuristic when a texture coordinate is not within the [0, 1] range
	*/
    enum KTextureWrapTypes : U8{
		KTW_REPEAT = 0,				//!< The texture coordinate wraps around the texture
        KTW_MIRRORED_REPEAT,	//!< The texture coordinate wraps around like a mirror
        KTW_CLAMP_TO_EDGE		//!< The texture coordinate is clamped to the [0, 1] range
     // KTW_CLAMP_TO_BORDER		// border not supported (see KTexture::create())
    };

	/*! \enum KShaderTypes
		\brief OpenGL shader types
	*/
    enum KShaderTypes{
        KS_VERTEX,	//!< Vertex shader
        KS_FRAGMENT,	//!< Fragment shader
		KS_GEOMETRY //!< Geometry shader
    };

//    enum KShaderTextureTypes{
//        KST_CURRENT = 0
//    };

	/*! \enum KAttributeCountTypes
		\brief Specifies the number of components per generic vertex attribute. (Internally use)
	*/
    enum KAttributeCountTypes{
        KAC_1COMPONENT = 1,
        KAC_2COMPONENT = 2,
        KAC_3COMPONENT = 3,
        KAC_4COMPONENT = 4,
    };

	/*! \enum KAttributeTypeTypes
		\brief Specifies the data type of each component in the array. (Internally use)
	*/
    enum KAttributeTypeTypes{
        KAT_BYTE = 0,
        KAT_UNSIGNED_BYTE,
        KAT_SHORT,
        KAT_UNSIGNED_SHORT,
        KAT_FIXED,
        KAT_FLOAT
    };

	enum KBuiltinShaderTypes {
		KBS_VERT,
		KBS_FRAG_COLOR,
		KBS_FRAG_TEXTURE,
		KBS_FRAG_TEXTURE_COLOR,
		KBS_VERT_POINT,
		KBS_FRAG_POINT_COLOR,
		KBS_FRAG_POINT_TEXTURE,
		KBS_FRAG_POINT_TEXTURE_COLOR,
	};

	/*! \typedef KAtlasFileTypes
	\brief Types of the atlas files
	*/
	enum KAtlasFileTypes {
		KAF_ATLAS,	//!< Default KAtlas format (compact format in speed and size)
		KAF_JSON	//!< Adobe Flash created JSON 
	};

	/*! \typedef KCallVBUpdate
		\brief Function handle for mapping and updating VBO buffers
	*/
	typedef void (KCallVBUpdate)(void *Data, U32 Offset, U32 DataSize, void *Sender);

	/*! \namespace Kite::Internal
		\brief Private namespace.
	*/
    namespace Internal{

		/*! \enum KGLBindGuardTypes
			\brief (Internal use)
		*/
		enum KGLBindGuardTypes{
			KBG_NONE = 0,	//!< None
			KBG_TEXTURE,	//!< Texture
			KBG_VBUFFER,	//!< Vertex buffer
			KBG_FBUFFER		//!< Frame buffer
		};
    }

}
#endif // KGRAPHICTYPES_H