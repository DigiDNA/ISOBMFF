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
 * @file        HVCC.cpp
 * @copyright   (c) 2017, DigiDNA - www.digidna.net
 * @author      Jean-David Gadina - www.digidna.net
 */

#include <HVCC.hpp>
#include <Utils.hpp>
#include <Parser.hpp>

namespace ISOBMFF
{
    class HVCC::IMPL
    {
        public:

            IMPL();
            IMPL( const IMPL & o );
            ~IMPL();

            uint8_t                                 _configurationVersion;
            uint8_t                                 _generalProfileSpace;
            uint8_t                                 _generalTierFlag;
            uint8_t                                 _generalProfileIDC;
            uint32_t                                _generalProfileCompatibilityFlags;
            uint64_t                                _generalConstraintIndicatorFlags;
            uint8_t                                 _generalLevelIDC;
            uint16_t                                _minSpatialSegmentationIDC;
            uint8_t                                 _parallelismType;
            uint8_t                                 _chromaFormat;
            uint8_t                                 _bitDepthLumaMinus8;
            uint8_t                                 _bitDepthChromaMinus8;
            uint16_t                                _avgFrameRate;
            uint8_t                                 _constantFrameRate;
            uint8_t                                 _numTemporalLayers;
            uint8_t                                 _temporalIdNested;
            uint8_t                                 _lengthSizeMinusOne;
            std::vector< std::shared_ptr< Array > > _arrays;
    };

    HVCC::HVCC():
        Box( "hvcC" ),
        impl( std::make_unique< IMPL >() )
    {}

    HVCC::HVCC( const HVCC & o ):
        Box( o ),
        impl( std::make_unique< IMPL >( *( o.impl ) ) )
    {}

    HVCC::HVCC( HVCC && o ) noexcept:
        Box( std::move( o ) ),
        impl( std::move( o.impl ) )
    {
        o.impl = nullptr;
    }

    HVCC::~HVCC()
    {}

    HVCC & HVCC::operator =( HVCC o )
    {
        Box::operator=( o );
        swap( *( this ), o );

        return *( this );
    }

    void swap( HVCC & o1, HVCC & o2 )
    {
        using std::swap;

        swap( static_cast< Box & >( o1 ), static_cast< Box & >( o2 ) );
        swap( o1.impl, o2.impl );
    }

    void HVCC::ReadData( Parser & parser, BinaryStream & stream )
    {
        uint8_t  u8;
        uint16_t u16;
        uint32_t u32;
        uint8_t  count;
        uint8_t  i;

        ( void )parser;

        this->SetConfigurationVersion( stream.ReadUInt8() );

        u8 = stream.ReadUInt8();

        this->SetGeneralProfileSpace( u8 >> 6 );
        this->SetGeneralTierFlag( ( u8 >> 5 ) & 0x01 );
        this->SetGeneralProfileIDC( u8 & 0x1F );
        this->SetGeneralProfileCompatibilityFlags( stream.ReadBigEndianUInt32() );

        u16 = stream.ReadBigEndianUInt16();
        u32 = stream.ReadBigEndianUInt32();

        this->SetGeneralConstraintIndicatorFlags( ( static_cast< uint64_t >( u16 ) << 32 ) | static_cast< uint64_t >( u32 ) );
        this->SetGeneralLevelIDC( stream.ReadUInt8() );

        u16 = stream.ReadBigEndianUInt16();

        this->SetMinSpatialSegmentationIDC( u16 & 0x0FFF );

        u8 = stream.ReadUInt8();

        this->SetParallelismType( u8 & 0x03 );

        u8 = stream.ReadUInt8();

        this->SetChromaFormat( u8 & 0x03 );

        u8 = stream.ReadUInt8();

        this->SetBitDepthLumaMinus8( u8 & 0x07 );

        u8 = stream.ReadUInt8();

        this->SetBitDepthChromaMinus8( u8 & 0x07 );
        this->SetAvgFrameRate( stream.ReadBigEndianUInt16() );

        u8 = stream.ReadUInt8();

        this->SetConstantFrameRate( ( u8 >> 6 ) & 0x03 );
        this->SetNumTemporalLayers( ( u8 >> 3 )& 0x07 );
        this->SetTemporalIdNested( ( u8 >> 2 ) & 0x01 );
        this->SetLengthSizeMinusOne( u8 & 0x03 );

        count = stream.ReadUInt8();

        for( i = 0; i < count; i++ )
        {
            if( stream.HasBytesAvailable() == false )
            {
                /*
                 * Shouldn't happen in theory, but happens on some files...
                 * So simply don't process next arrays if we don't have any data
                 * available...
                 */
                break;
            }

            this->AddArray( std::make_shared< Array >( stream ) );
        }
    }

    void HVCC::WriteDescription( std::ostream & os, std::size_t indentLevel ) const
    {
        Box::WriteDescription( os, indentLevel );
        DisplayableObjectContainer::WriteDescription( os, indentLevel );
    }

    std::vector< std::shared_ptr< DisplayableObject > > HVCC::GetDisplayableObjects() const
    {
        auto v( this->GetArrays() );

        return std::vector< std::shared_ptr< DisplayableObject > >( v.begin(), v.end() );
    }

    std::vector< std::pair< std::string, std::string > > HVCC::GetDisplayableProperties() const
    {
        auto props( Box::GetDisplayableProperties() );

        props.push_back( { "Configuration version",               std::to_string( this->GetConfigurationVersion() ) } );
        props.push_back( { "General profile space",               std::to_string( this->GetGeneralProfileSpace() ) } );
        props.push_back( { "General tier flag",                   Utils::ToHexString( this->GetGeneralTierFlag() ) } );
        props.push_back( { "General profile IDC",                 std::to_string( this->GetGeneralProfileIDC() ) } );
        props.push_back( { "General profile compatibility flags", Utils::ToHexString( this->GetGeneralProfileCompatibilityFlags() ) } );
        props.push_back( { "General constraint indicator flags",  Utils::ToHexString( this->GetGeneralConstraintIndicatorFlags() ) } );
        props.push_back( { "General level IDC",                   std::to_string( this->GetGeneralLevelIDC() ) } );
        props.push_back( { "Min spacial segmentation IDC",        std::to_string( this->GetMinSpatialSegmentationIDC() ) } );
        props.push_back( { "Parallelism type",                    std::to_string( this->GetParallelismType() ) } );
        props.push_back( { "Chroma format",                       std::to_string( this->GetChromaFormat() ) } );
        props.push_back( { "Bit depth luma minus 8",              std::to_string( this->GetBitDepthLumaMinus8() ) } );
        props.push_back( { "Bit depth chroma minus 8",            std::to_string( this->GetBitDepthChromaMinus8() ) } );
        props.push_back( { "Avg frame rate",                      std::to_string( this->GetAvgFrameRate() ) } );
        props.push_back( { "Constant frame rate",                 std::to_string( this->GetConstantFrameRate() ) } );
        props.push_back( { "Num temporal layers",                 std::to_string( this->GetNumTemporalLayers() ) } );
        props.push_back( { "Temporal id nested",                  std::to_string( this->GetTemporalIdNested() ) } );
        props.push_back( { "Length size minus one",               std::to_string( this->GetLengthSizeMinusOne() ) } );
        props.push_back( { "Arrays",                              std::to_string( this->GetArrays().size() ) } );

        return props;
    }

    uint8_t HVCC::GetConfigurationVersion() const
    {
        return this->impl->_configurationVersion;
    }

    uint8_t HVCC::GetGeneralProfileSpace() const
    {
        return this->impl->_generalProfileSpace;
    }

    uint8_t HVCC::GetGeneralTierFlag() const
    {
        return this->impl->_generalTierFlag;
    }

    uint8_t HVCC::GetGeneralProfileIDC() const
    {
        return this->impl->_generalProfileIDC;
    }

    uint32_t HVCC::GetGeneralProfileCompatibilityFlags() const
    {
        return this->impl->_generalProfileCompatibilityFlags;
    }

    uint64_t HVCC::GetGeneralConstraintIndicatorFlags() const
    {
        return this->impl->_generalConstraintIndicatorFlags;
    }

    uint8_t HVCC::GetGeneralLevelIDC() const
    {
        return this->impl->_generalLevelIDC;
    }

    uint16_t HVCC::GetMinSpatialSegmentationIDC() const
    {
        return this->impl->_minSpatialSegmentationIDC;
    }

    uint8_t HVCC::GetParallelismType() const
    {
        return this->impl->_parallelismType;
    }

    uint8_t HVCC::GetChromaFormat() const
    {
        return this->impl->_chromaFormat;
    }

    uint8_t HVCC::GetBitDepthLumaMinus8() const
    {
        return this->impl->_bitDepthLumaMinus8;
    }

    uint8_t HVCC::GetBitDepthChromaMinus8() const
    {
        return this->impl->_bitDepthChromaMinus8;
    }

    uint16_t HVCC::GetAvgFrameRate() const
    {
        return this->impl->_avgFrameRate;
    }

    uint8_t HVCC::GetConstantFrameRate() const
    {
        return this->impl->_constantFrameRate;
    }

    uint8_t HVCC::GetNumTemporalLayers() const
    {
        return this->impl->_numTemporalLayers;
    }

    uint8_t HVCC::GetTemporalIdNested() const
    {
        return this->impl->_temporalIdNested;
    }

    uint8_t HVCC::GetLengthSizeMinusOne() const
    {
        return this->impl->_lengthSizeMinusOne;
    }

    void HVCC::SetConfigurationVersion( uint8_t value )
    {
        this->impl->_configurationVersion = value;
    }

    void HVCC::SetGeneralProfileSpace( uint8_t value )
    {
        this->impl->_generalProfileSpace = value;
    }

    void HVCC::SetGeneralTierFlag( uint8_t value )
    {
        this->impl->_generalTierFlag = value;
    }

    void HVCC::SetGeneralProfileIDC( uint8_t value )
    {
        this->impl->_generalProfileIDC = value;
    }

    void HVCC::SetGeneralProfileCompatibilityFlags( uint32_t value )
    {
        this->impl->_generalProfileCompatibilityFlags = value;
    }

    void HVCC::SetGeneralConstraintIndicatorFlags( uint64_t value )
    {
        this->impl->_generalConstraintIndicatorFlags = value;
    }

    void HVCC::SetGeneralLevelIDC( uint8_t value )
    {
        this->impl->_generalLevelIDC = value;
    }

    void HVCC::SetMinSpatialSegmentationIDC( uint16_t value )
    {
        this->impl->_minSpatialSegmentationIDC = value;
    }

    void HVCC::SetParallelismType( uint8_t value )
    {
        this->impl->_parallelismType = value;
    }

    void HVCC::SetChromaFormat( uint8_t value )
    {
        this->impl->_chromaFormat = value;
    }

    void HVCC::SetBitDepthLumaMinus8( uint8_t value )
    {
        this->impl->_bitDepthLumaMinus8 = value;
    }

    void HVCC::SetBitDepthChromaMinus8( uint8_t value )
    {
        this->impl->_bitDepthChromaMinus8 = value;
    }

    void HVCC::SetAvgFrameRate( uint16_t value )
    {
        this->impl->_avgFrameRate = value;
    }

    void HVCC::SetConstantFrameRate( uint8_t value )
    {
        this->impl->_constantFrameRate = value;
    }

    void HVCC::SetNumTemporalLayers( uint8_t value )
    {
        this->impl->_numTemporalLayers = value;
    }

    void HVCC::SetTemporalIdNested( uint8_t value )
    {
        this->impl->_temporalIdNested = value;
    }

    void HVCC::SetLengthSizeMinusOne( uint8_t value )
    {
        this->impl->_lengthSizeMinusOne = value;
    }

    std::vector< std::shared_ptr< HVCC::Array > > HVCC::GetArrays() const
    {
        return this->impl->_arrays;
    }

    void HVCC::AddArray( std::shared_ptr< Array > array )
    {
        this->impl->_arrays.push_back( array );
    }

    HVCC::IMPL::IMPL():
        _configurationVersion( 0 ),
        _generalProfileSpace( 0 ),
        _generalTierFlag( 0 ),
        _generalProfileIDC( 0 ),
        _generalProfileCompatibilityFlags( 0 ),
        _generalConstraintIndicatorFlags( 0 ),
        _generalLevelIDC( 0 ),
        _minSpatialSegmentationIDC( 0 ),
        _parallelismType( 0 ),
        _chromaFormat( 0 ),
        _bitDepthLumaMinus8( 0 ),
        _bitDepthChromaMinus8( 0 ),
        _avgFrameRate( 0 ),
        _constantFrameRate( 0 ),
        _numTemporalLayers( 0 ),
        _temporalIdNested( 0 ),
        _lengthSizeMinusOne( 0 )
    {}

    HVCC::IMPL::IMPL( const IMPL & o ):
        _configurationVersion( o._configurationVersion ),
        _generalProfileSpace( o._generalProfileSpace ),
        _generalTierFlag( o._generalTierFlag ),
        _generalProfileIDC( o._generalProfileIDC ),
        _generalProfileCompatibilityFlags( o._generalProfileCompatibilityFlags ),
        _generalConstraintIndicatorFlags( o._generalConstraintIndicatorFlags ),
        _generalLevelIDC( o._generalLevelIDC ),
        _minSpatialSegmentationIDC( o._minSpatialSegmentationIDC ),
        _parallelismType( o._parallelismType ),
        _chromaFormat( o._chromaFormat ),
        _bitDepthLumaMinus8( o._bitDepthLumaMinus8 ),
        _bitDepthChromaMinus8( o._bitDepthChromaMinus8 ),
        _avgFrameRate( o._avgFrameRate ),
        _constantFrameRate( o._constantFrameRate ),
        _numTemporalLayers( o._numTemporalLayers ),
        _temporalIdNested( o._temporalIdNested ),
        _lengthSizeMinusOne( o._lengthSizeMinusOne ),
        _arrays( o._arrays )
    {}

    HVCC::IMPL::~IMPL()
    {}
}
