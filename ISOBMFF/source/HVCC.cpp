/*******************************************************************************
 * The MIT License (MIT)
 * 
 * Copyright (c) 2017 Jean-David Gadina - www.xs-labs.com / www.imazing.com
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
 * @file        HVCC.hpp
 * @copyright   (c) 2017, Jean-David Gadina - www.xs-labs.com / www.imazing.com
 */

#include <ISOBMFF/HVCC.hpp>

template<>
class XS::PIMPL::Object< ISOBMFF::HVCC >::IMPL
{
    public:
        
        IMPL( void );
        IMPL( const IMPL & o );
        ~IMPL( void );
        
        uint8_t                           _configurationVersion;
        uint8_t                           _generalProfileSpace;
        uint8_t                           _generalTierFlag;
        uint8_t                           _generalProfileIDC;
        uint32_t                          _generalProfileCompatibilityFlags;
        uint64_t                          _generalConstraintIndicatorFlags;
        uint8_t                           _generalLevelIDC;
        uint16_t                          _minSpatialSegmentationIDC;
        uint8_t                           _parallelismType;
        uint8_t                           _chromaFormat;
        uint8_t                           _bitDepthLumaMinus8;
        uint8_t                           _bitDepthChromaMinus8;
        uint16_t                          _avgFrameRate;
        uint8_t                           _constantFrameRate;
        uint8_t                           _numTemporalLayers;
        uint8_t                           _temporalIdNested;
        uint8_t                           _lengthSizeMinusOne;
        std::vector< ISOBMFF::HVCC::Array > _arrays;
};

#define XS_PIMPL_CLASS ISOBMFF::HVCC
#include <XS/PIMPL/Object-IMPL.hpp>

namespace ISOBMFF
{
    HVCC::HVCC( void ): ISOBMFF::Box( "hvcC" )
    {}
    
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
            this->AddArray( Array( stream ) );
        }
    }
    
    void HVCC::WriteDescription( std::ostream & os, std::size_t indentLevel ) const
    {
        std::vector< Array > arrays;
        std::string          i( ( indentLevel + 1 ) * 4, ' ' );
        
        Box::WriteDescription( os, indentLevel );
        
        arrays = this->GetArrays();
        
        os << std::endl
           << i << "- Configuration version:               " << static_cast< uint32_t >( this->GetConfigurationVersion() ) << std::endl
           << i << "- General profile space:               " << static_cast< uint32_t >( this->GetGeneralProfileSpace() ) << std::endl
           << i << "- General tier flag:                   " << static_cast< uint32_t >( this->GetGeneralTierFlag() ) << std::endl
           << i << "- General profile IDC:                 " << static_cast< uint32_t >( this->GetGeneralProfileIDC() ) << std::endl
           << i << "- General profile compatibility flags: " << this->GetGeneralProfileCompatibilityFlags() << std::endl
           << i << "- General constraint indicator flags:  " << this->GetGeneralConstraintIndicatorFlags() << std::endl
           << i << "- General level IDC:                   " << static_cast< uint32_t >( this->GetGeneralLevelIDC() ) << std::endl
           << i << "- Min spacial segmentation IDC:        " << this->GetMinSpatialSegmentationIDC() << std::endl
           << i << "- Parallelism type:                    " << static_cast< uint32_t >( this->GetParallelismType() ) << std::endl
           << i << "- Chroma format:                       " << static_cast< uint32_t >( this->GetChromaFormat() ) << std::endl
           << i << "- Bit depth luma minus 8:              " << static_cast< uint32_t >( this->GetBitDepthLumaMinus8() ) << std::endl
           << i << "- Bit depth chroma minus 8:            " << static_cast< uint32_t >( this->GetBitDepthChromaMinus8() ) << std::endl
           << i << "- Avg frame rate:                      " << this->GetAvgFrameRate() << std::endl
           << i << "- Constant frame rate:                 " << static_cast< uint32_t >( this->GetConstantFrameRate() ) << std::endl
           << i << "- Num temporal layers:                 " << static_cast< uint32_t >( this->GetNumTemporalLayers() ) << std::endl
           << i << "- Temporal id nested:                  " << static_cast< uint32_t >( this->GetTemporalIdNested() ) << std::endl
           << i << "- Length size minus one:               " << static_cast< uint32_t >( this->GetLengthSizeMinusOne() ) << std::endl
           << i << "- Arrays:                              " << arrays.size();
        
        if( arrays.size() > 0 )
        {
            os << std::endl
               << i
               << "{"
               << std::endl;
            
            for( const auto & array: arrays )
            {
                array.WriteDescription( os, indentLevel + 2 );
                
                os << std::endl;
            }
            
            os << i
               << "}";
        }
    }
    
    uint8_t HVCC::GetConfigurationVersion( void ) const
    {
        return this->impl->_configurationVersion;
    }
    
    uint8_t HVCC::GetGeneralProfileSpace( void ) const
    {
        return this->impl->_generalProfileSpace;
    }
    
    uint8_t HVCC::GetGeneralTierFlag( void ) const
    {
        return this->impl->_generalTierFlag;
    }
    
    uint8_t HVCC::GetGeneralProfileIDC( void ) const
    {
        return this->impl->_generalProfileIDC;
    }
    
    uint32_t HVCC::GetGeneralProfileCompatibilityFlags( void ) const
    {
        return this->impl->_generalProfileCompatibilityFlags;
    }
    
    uint64_t HVCC::GetGeneralConstraintIndicatorFlags( void ) const
    {
        return this->impl->_generalConstraintIndicatorFlags;
    }
    
    uint8_t HVCC::GetGeneralLevelIDC( void ) const
    {
        return this->impl->_generalLevelIDC;
    }
    
    uint16_t HVCC::GetMinSpatialSegmentationIDC( void ) const
    {
        return this->impl->_minSpatialSegmentationIDC;
    }
    
    uint8_t HVCC::GetParallelismType( void ) const
    {
        return this->impl->_parallelismType;
    }
    
    uint8_t HVCC::GetChromaFormat( void ) const
    {
        return this->impl->_chromaFormat;
    }
    
    uint8_t HVCC::GetBitDepthLumaMinus8( void ) const
    {
        return this->impl->_bitDepthLumaMinus8;
    }
    
    uint8_t HVCC::GetBitDepthChromaMinus8( void ) const
    {
        return this->impl->_bitDepthChromaMinus8;
    }
    
    uint16_t HVCC::GetAvgFrameRate( void ) const
    {
        return this->impl->_avgFrameRate;
    }
    
    uint8_t HVCC::GetConstantFrameRate( void ) const
    {
        return this->impl->_constantFrameRate;
    }
    
    uint8_t HVCC::GetNumTemporalLayers( void ) const
    {
        return this->impl->_numTemporalLayers;
    }
    
    uint8_t HVCC::GetTemporalIdNested( void ) const
    {
        return this->impl->_temporalIdNested;
    }
    
    uint8_t HVCC::GetLengthSizeMinusOne( void ) const
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
    
    std::vector< HVCC::Array > HVCC::GetArrays( void ) const
    {
        return this->impl->_arrays;
    }
    
    void HVCC::AddArray( const Array & array )
    {
        this->impl->_arrays.push_back( array );
    }
}

XS::PIMPL::Object< ISOBMFF::HVCC >::IMPL::IMPL( void ):
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

XS::PIMPL::Object< ISOBMFF::HVCC >::IMPL::IMPL( const IMPL & o ):
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

XS::PIMPL::Object< ISOBMFF::HVCC >::IMPL::~IMPL( void )
{}

