/*
 Kite2D Game Framework.
 Copyright (C) 2010-2014  Milad Rasaneh <milad_rasaneh2000@yahoo.com>

 This program is free software: you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation, either version 3 of the License, or
 any later version.

 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.

 You should have received a copy of the GNU General Public License
 along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
#ifndef KSOUNDBUFFER_H
#define KSOUNDBUFFER_H

/*! \file ksoundbuffer.h */

#include "Kite/Core/system/ksystemdef.h"
#include "Kite/Core/system/kresources.h"
#include "Kite/Core/system/kinputstream.h"
#include "Kite/Core/audio/kaudiotypes.h"
#include <string>

/*! \namespace Kite
	\brief Public namespace.
*/
namespace Kite{

	//! The KSoundBuffer class encapsulates an OpenAL buffer object with features such as reading/decoding audio formats.
	/*!
		A buffer encapsulates OpenAL state related to storing sample data.
		the application can request and release buffer objects,
		and fill them with data. Data can be supplied compressed and encoded as long as the format is supported.
		Unlike source (KSoundSource) and listener (KListener) objects,
		buffer objects can be shared among AL contexts.
		buffers are referenced by sources. a single buffer can be referred to by multiple sources.
		supported format: OGG
	*/
    class KITE_FUNC_EXPORT KSoundBuffer : public KResources{
    public:

		//! Constructs an empty buffer object.
        KSoundBuffer();

		//! Destructor
        ~KSoundBuffer();

		//! Load the sound from a file on disk
		/*!
			Supported formats: OGG

			\param FileName Address of the sound file on the disk

			\return True if loading was successful
		*/
        bool loadFile(const std::string &FileName, KAudioFileTypes Format);

		//! Load the sound from input stream
		/*!
			Supported formats: OGG

			\param InputStream Input stream

			\return True if loading was successful
		*/
		bool loadStream(KInputStream &InputStream, KAudioFileTypes Format);

		//! Get sample rate of the sound track
		/*!
			The sample rate is in samples per second

			\return Sample rate of the sound track
		*/
        inline I64 getSampleRate() const {return _ksampleRate;}

		//! Get number of channel of the sound track
		/*!
			The number of channels in the audio data. For example, Stereo 2 channels

			\return The number of channels in the sound track
		*/
        inline U16 getChannelCount() const {return _kchannelCount;}

		//! Get bits per sample of the sound track
		/*!
			\return Bits per sample of the sound track
		*/
        inline U16 getBitsPerSample() const {return _kbitsPerSample;}

		//! Get size of the buffer (in bytes)
		/*!
			\return Size of the buffer
		*/
        inline I32 getSize() const {return _ksize;}

		//! Get OpenAL ID of the buffer
		/*!
			\return OpenAL ID of the buffer
		*/
        inline U32 getALID() const {return _kID;}

		//! Get size of resource in memory
		/*!
			\return Size of resource in bytes
		*/
		U64 resGetSize() const;

    private:
        I64 _ksampleRate;
        U16 _kchannelCount;
        U16 _kbitsPerSample;
        I32 _ksize;
        U32 _kID;
    };
}

#endif // KSOUNDBUFFER_H
