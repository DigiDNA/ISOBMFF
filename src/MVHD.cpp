/*******************************************************************************
 * The MIT License (MIT)
 *
 * Copyright (c) 2017 DigiDNA - www.digidna.net
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 ******************************************************************************/

/*!
 * @file        MVHD.cpp
 * @copyright   (c) 2017, DigiDNA - www.digidna.net
 * @author      Jean-David Gadina - www.digidna.net
 */

#include <MVHD.hpp>
#include <cstring>

namespace ISOBMFF
{
    class MVHD::IMPL
    {
        public:

            IMPL();
            IMPL( const IMPL & o );
            ~IMPL();

            uint64_t _creationTime;
            uint64_t _modificationTime;
            uint32_t _timescale;
            uint64_t _duration;
            uint32_t _rate;
            uint16_t _volume;
            uint16_t _reserved1;
            uint32_t _reserved2[ 2 ];
            Matrix   _matrix;
            uint32_t _predefined[ 6 ];
            uint32_t _nextTrackID;
    };

    MVHD::MVHD():
        FullBox( "mvhd" ),
        impl( std::make_unique< IMPL >() )
    {}

    MVHD::MVHD( const MVHD & o ):
        FullBox( o ),
        impl( std::make_unique< IMPL >( *( o.impl ) ) )
    {}

    MVHD::MVHD( MVHD && o ) noexcept:
        FullBox( std::move( o ) ),
        impl( std::move( o.impl ) )
    {
        o.impl = nullptr;
    }

    MVHD::~MVHD()
    {}

    MVHD & MVHD::operator =( MVHD o )
    {
        FullBox::operator=( o );
        swap( *( this ), o );

        return *( this );
    }

    void swap( MVHD & o1, MVHD & o2 )
    {
        using std::swap;

        swap( static_cast< FullBox & >( o1 ), static_cast< FullBox & >( o2 ) );
        swap( o1.impl, o2.impl );
    }

    void MVHD::ReadData( Parser & parser, BinaryStream & stream )
    {
        FullBox::ReadData( parser, stream );

        if( this->GetVersion() == 1 )
        {
            this->SetCreationTime( stream.ReadBigEndianUInt64() );
            this->SetModificationTime( stream.ReadBigEndianUInt64() );
            this->SetTimescale( stream.ReadBigEndianUInt32() );
            this->SetDuration( stream.ReadBigEndianUInt64() );
        }
        else
        {
            this->SetCreationTime( stream.ReadBigEndianUInt32() );
            this->SetModificationTime( stream.ReadBigEndianUInt32() );
            this->SetTimescale( stream.ReadBigEndianUInt32() );
            this->SetDuration( stream.ReadBigEndianUInt32() );
        }

        this->SetRate( stream.ReadBigEndianUInt32() );
        this->SetVolume( stream.ReadBigEndianUInt16() );

        this->impl->_reserved1      = stream.ReadBigEndianUInt16();
        this->impl->_reserved2[ 0 ] = stream.ReadBigEndianUInt32();
        this->impl->_reserved2[ 1 ] = stream.ReadBigEndianUInt32();

        this->SetMatrix( stream.ReadMatrix() );

        this->impl->_predefined[ 0 ] = stream.ReadBigEndianUInt32();
        this->impl->_predefined[ 1 ] = stream.ReadBigEndianUInt32();
        this->impl->_predefined[ 2 ] = stream.ReadBigEndianUInt32();
        this->impl->_predefined[ 3 ] = stream.ReadBigEndianUInt32();
        this->impl->_predefined[ 4 ] = stream.ReadBigEndianUInt32();
        this->impl->_predefined[ 5 ] = stream.ReadBigEndianUInt32();

        this->SetNextTrackID( stream.ReadBigEndianUInt32() );
    }

    std::vector< std::pair< std::string, std::string > > MVHD::GetDisplayableProperties() const
    {
        auto props( FullBox::GetDisplayableProperties() );

        props.push_back( { "Creation time",     std::to_string( this->GetCreationTime() ) } );
        props.push_back( { "Modification time", std::to_string( this->GetModificationTime() ) } );
        props.push_back( { "Timescale",         std::to_string( this->GetTimescale() ) } );
        props.push_back( { "Duration",          std::to_string( this->GetDuration() ) } );
        props.push_back( { "Rate",              std::to_string( this->GetRate() ) } );
        props.push_back( { "Volume",            std::to_string( this->GetVolume() ) } );
        props.push_back( { "Matrix",            this->GetMatrix().ToString() } );
        props.push_back( { "Next track ID",     std::to_string( this->GetNextTrackID() ) } );

        return props;
    }

    uint64_t MVHD::GetCreationTime() const
    {
        return this->impl->_creationTime;
    }

    uint64_t MVHD::GetModificationTime() const
    {
        return this->impl->_modificationTime;
    }

    uint32_t MVHD::GetTimescale() const
    {
        return this->impl->_timescale;
    }

    uint64_t MVHD::GetDuration() const
    {
        return this->impl->_duration;
    }

    uint32_t MVHD::GetRate() const
    {
        return this->impl->_rate;
    }

    uint16_t MVHD::GetVolume() const
    {
        return this->impl->_volume;
    }

    Matrix MVHD::GetMatrix() const
    {
        return this->impl->_matrix;
    }

    uint32_t MVHD::GetNextTrackID() const
    {
        return this->impl->_nextTrackID;
    }

    void MVHD::SetCreationTime( uint64_t value )
    {
        this->impl->_creationTime = value;
    }

    void MVHD::SetModificationTime( uint64_t value )
    {
        this->impl->_modificationTime = value;
    }

    void MVHD::SetTimescale( uint32_t value )
    {
        this->impl->_timescale = value;
    }

    void MVHD::SetDuration( uint64_t value )
    {
        this->impl->_duration = value;
    }

    void MVHD::SetRate( uint32_t value )
    {
        this->impl->_rate = value;
    }

    void MVHD::SetVolume( uint16_t value )
    {
        this->impl->_volume = value;
    }

    void MVHD::SetMatrix( const Matrix & value )
    {
        this->impl->_matrix = value;
    }

    void MVHD::SetNextTrackID( uint32_t value )
    {
        this->impl->_nextTrackID = value;
    }

    MVHD::IMPL::IMPL():
        _creationTime( 0 ),
        _modificationTime( 0 ),
        _timescale( 0 ),
        _duration( 0 ),
        _rate( 0 ),
        _volume( 0 ),
        _reserved1( 0 ),
        _nextTrackID( 0 )
    {
        memset( this->_reserved2,  0, sizeof( this->_reserved2 ) );
        memset( this->_predefined, 0, sizeof( this->_predefined ) );
    }

    MVHD::IMPL::IMPL( const IMPL & o ):
        _creationTime( o._creationTime ),
        _modificationTime( o._modificationTime ),
        _timescale( o._timescale ),
        _duration( o._duration ),
        _rate( o._rate ),
        _volume( o._volume ),
        _reserved1( o._reserved1 ),
        _matrix( o._matrix ),
        _nextTrackID( o._nextTrackID )
    {
        memcpy( this->_reserved2,  o._reserved2,  sizeof( this->_reserved2 ) );
        memcpy( this->_predefined, o._predefined, sizeof( this->_predefined ) );
    }

    MVHD::IMPL::~IMPL()
    {}
}
