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
 * @file        AVC1.cpp
 * @copyright   (c) 2017, DigiDNA - www.digidna.net
 * @author      Jean-David Gadina - www.digidna.net
 */

#include <AVC1.hpp>
#include <ContainerBox.hpp>

namespace ISOBMFF
{
    class AVC1::IMPL
    {
        public:

            IMPL();
            IMPL( const IMPL & o );
            ~IMPL();

            uint16_t _data_reference_index;
            uint16_t _width;
            uint16_t _height;
            uint32_t _horizresolution;
            uint32_t _vertresolution;
            uint16_t _frame_count;
            std::string _compressorname;
            uint16_t _depth;

            std::vector< std::shared_ptr< Box > > _boxes;
    };

    AVC1::AVC1():
        FullBox( "avc1" ),
        impl( std::make_unique< IMPL >() )
    {}

    AVC1::AVC1( const AVC1 & o ):
        FullBox( o ),
        impl( std::make_unique< IMPL >( *( o.impl ) ) )
    {}

    AVC1::AVC1( AVC1 && o ) noexcept:
        FullBox( std::move( o ) ),
        impl( std::move( o.impl ) )
    {
        o.impl = nullptr;
    }

    AVC1::~AVC1()
    {}

    AVC1 & AVC1::operator =( AVC1 o )
    {
        FullBox::operator=( o );
        swap( *( this ), o );

        return *( this );
    }

    void swap( AVC1 & o1, AVC1 & o2 )
    {
        using std::swap;

        swap( static_cast< FullBox & >( o1 ), static_cast< FullBox & >( o2 ) );
        swap( o1.impl, o2.impl );
    }

    void AVC1::ReadData( Parser & parser, BinaryStream & stream )
    {
        ContainerBox container( "????" );

        // SampleEntry
        // reserved[]
        stream.ReadUInt8();
        stream.ReadUInt8();
        stream.ReadUInt8();
        stream.ReadUInt8();
        stream.ReadUInt8();
        stream.ReadUInt8();
        // data_reference_index
        this->SetDataReferenceIndex( stream.ReadBigEndianUInt16() );
        // VisualSampleEntry
        // pre_defined1
        stream.ReadBigEndianUInt16();
        // reserved1
        stream.ReadBigEndianUInt16();
        // pre_defined2
        stream.ReadBigEndianUInt32();
        stream.ReadBigEndianUInt32();
        stream.ReadBigEndianUInt32();
        this->SetWidth( stream.ReadBigEndianUInt16() );
        this->SetHeight( stream.ReadBigEndianUInt16() );
        this->SetHorizResolution( stream.ReadBigEndianUInt32() );
        this->SetVertResolution( stream.ReadBigEndianUInt32() );
        // reserved2
        stream.ReadBigEndianUInt32();
        this->SetFrameCount( stream.ReadBigEndianUInt16() );
        this->SetCompressorName( stream.ReadString(32) );
        this->SetDepth( stream.ReadBigEndianUInt16() );
        // pre_defined3
        stream.ReadBigEndianUInt16();

        container.ReadData( parser, stream );

        this->impl->_boxes = container.GetBoxes();
    }

    std::vector< std::pair< std::string, std::string > > AVC1::GetDisplayableProperties() const
    {
        auto props( FullBox::GetDisplayableProperties() );

        props.push_back( { "Data Reference Index",             std::to_string( this->GetDataReferenceIndex() ) } );
        props.push_back( { "Width",             std::to_string( this->GetWidth() ) } );
        props.push_back( { "Height",            std::to_string( this->GetHeight() ) } );
        props.push_back( { "Horizontal Resolution",            std::to_string( this->GetHorizResolution() ) } );
        props.push_back( { "Vertical Resolution",            std::to_string( this->GetVertResolution() ) } );
        props.push_back( { "Frame Count",            std::to_string( this->GetFrameCount() ) } );
        props.push_back( { "Compressor Name",         this->GetCompressorName() } );
        props.push_back( { "Depth",            std::to_string( this->GetDepth() ) } );

        return props;
    }

    void AVC1::WriteDescription( std::ostream & os, std::size_t indentLevel ) const
    {
        FullBox::WriteDescription( os, indentLevel );
        Container::WriteBoxes( os, indentLevel );
    }

    uint16_t AVC1::GetDataReferenceIndex() const
    {
        return this->impl->_data_reference_index;
    }

    uint16_t AVC1::GetWidth() const
    {
        return this->impl->_width;
    }

    uint16_t AVC1::GetHeight() const
    {
        return this->impl->_height;
    }

    uint32_t AVC1::GetHorizResolution() const
    {
        return this->impl->_horizresolution;
    }

    uint32_t AVC1::GetVertResolution() const
    {
        return this->impl->_vertresolution;
    }

    uint16_t AVC1::GetFrameCount() const
    {
        return this->impl->_frame_count;
    }

    std::string AVC1::GetCompressorName() const
    {
        return this->impl->_compressorname;
    }

    uint16_t AVC1::GetDepth() const
    {
        return this->impl->_depth;
    }


    void AVC1::SetDataReferenceIndex( uint16_t value )
    {
        this->impl->_data_reference_index = value;
    }

    void AVC1::SetWidth( uint16_t value )
    {
        this->impl->_width = value;
    }

    void AVC1::SetHeight( uint16_t value )
    {
        this->impl->_height = value;
    }

    void AVC1::SetHorizResolution( uint32_t value )
    {
        this->impl->_horizresolution = value;
    }

    void AVC1::SetVertResolution( uint32_t value )
    {
        this->impl->_vertresolution = value;
    }

    void AVC1::SetFrameCount( uint16_t value )
    {
        this->impl->_frame_count = value;
    }

    void AVC1::SetCompressorName( std::string value )
    {
        this->impl->_compressorname = value;
    }

    void AVC1::SetDepth( uint16_t value )
    {
        this->impl->_depth = value;
    }

    void AVC1::AddBox( std::shared_ptr< Box > box )
    {
        if( box != nullptr )
        {
            this->impl->_boxes.push_back( box );
        }
    }

    std::vector< std::shared_ptr< Box > > AVC1::GetBoxes() const
    {
        return this->impl->_boxes;
    }

    AVC1::IMPL::IMPL():
        _data_reference_index( 0 ),
        _width( 0 ),
        _height( 0 ),
        _horizresolution( 0 ),
        _vertresolution( 0 ),
        _frame_count( 0 ),
        _compressorname( "" ),
        _depth( 0 )
    {}

    AVC1::IMPL::IMPL( const IMPL & o ):
        _data_reference_index( o._data_reference_index ),
        _width( o._width ),
        _height( o._height ),
        _horizresolution( o._horizresolution ),
        _vertresolution( o._vertresolution ),
        _frame_count( o._frame_count ),
        _compressorname( o._compressorname ),
        _depth( o._depth ),
        _boxes( o._boxes )
    {}

    AVC1::IMPL::~IMPL()
    {}
}
