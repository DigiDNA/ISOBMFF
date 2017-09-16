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
 * @header      HVCC.hpp
 * @copyright   (c) 2017, Jean-David Gadina - www.xs-labs.com / www.imazing.com
 */

#ifndef ISOBMFF_HVCC_HPP
#define ISOBMFF_HVCC_HPP

#include <XS/PIMPL/Object.hpp>
#include <ISOBMFF/Macros.hpp>
#include <ISOBMFF/FullBox.hpp>
#include <ISOBMFF/DisplayableObject.hpp>
#include <ISOBMFF/DisplayableObjectContainer.hpp>
#include <vector>
#include <cstdint>

namespace ISOBMFF
{
    class ISOBMFF_EXPORT HVCC: public Box, public XS::PIMPL::Object< HVCC >, public DisplayableObjectContainer
    {
        public:
            
            using XS::PIMPL::Object< HVCC >::impl;
            
            HVCC( void );
            
            void ReadData( Parser & parser, BinaryStream & stream ) override;
            void WriteDescription( std::ostream & os, std::size_t indentLevel ) const override;
            
            virtual std::vector< std::shared_ptr< DisplayableObject > >  GetDisplayableObjects( void )    const override;
            virtual std::vector< std::pair< std::string, std::string > > GetDisplayableProperties( void ) const override;
            
            uint8_t  GetConfigurationVersion( void )             const;
            uint8_t  GetGeneralProfileSpace( void )              const;
            uint8_t  GetGeneralTierFlag( void )                  const;
            uint8_t  GetGeneralProfileIDC( void )                const;
            uint32_t GetGeneralProfileCompatibilityFlags( void ) const;
            uint64_t GetGeneralConstraintIndicatorFlags( void )  const;
            uint8_t  GetGeneralLevelIDC( void )                  const;
            uint16_t GetMinSpatialSegmentationIDC( void )        const;
            uint8_t  GetParallelismType( void )                  const;
            uint8_t  GetChromaFormat( void )                     const;
            uint8_t  GetBitDepthLumaMinus8( void )               const;
            uint8_t  GetBitDepthChromaMinus8( void )             const;
            uint16_t GetAvgFrameRate( void )                     const;
            uint8_t  GetConstantFrameRate( void )                const;
            uint8_t  GetNumTemporalLayers( void )                const;
            uint8_t  GetTemporalIdNested( void )                 const;
            uint8_t  GetLengthSizeMinusOne( void )               const;
            
            void SetConfigurationVersion( uint8_t value );
            void SetGeneralProfileSpace( uint8_t value );
            void SetGeneralTierFlag( uint8_t value );
            void SetGeneralProfileIDC( uint8_t value );
            void SetGeneralProfileCompatibilityFlags( uint32_t value );
            void SetGeneralConstraintIndicatorFlags( uint64_t value );
            void SetGeneralLevelIDC( uint8_t value );
            void SetMinSpatialSegmentationIDC( uint16_t value );
            void SetParallelismType( uint8_t value );
            void SetChromaFormat( uint8_t value );
            void SetBitDepthLumaMinus8( uint8_t value );
            void SetBitDepthChromaMinus8( uint8_t value );
            void SetAvgFrameRate( uint16_t value );
            void SetConstantFrameRate( uint8_t value );
            void SetNumTemporalLayers( uint8_t value );
            void SetTemporalIdNested( uint8_t value );
            void SetLengthSizeMinusOne( uint8_t value );
            
            class Array: public XS::PIMPL::Object< Array >, public DisplayableObject, public DisplayableObjectContainer
            {
                public:
                    
                    using XS::PIMPL::Object< Array >::impl;
                    
                    Array( void );
                    Array( BinaryStream & stream );
                    
                    std::string GetName( void ) const override;
                    
                    bool    GetArrayCompleteness( void ) const;
                    uint8_t GetNALUnitType( void )       const;
                    
                    void SetArrayCompleteness( bool value );
                    void SetNALUnitType( uint8_t value );
                    
                    void WriteDescription( std::ostream & os, std::size_t indentLevel ) const override;
                    
                    virtual std::vector< std::shared_ptr< DisplayableObject > >  GetDisplayableObjects( void )    const override;
                    virtual std::vector< std::pair< std::string, std::string > > GetDisplayableProperties( void ) const override;
                    
                    class NALUnit: public XS::PIMPL::Object< NALUnit >, public DisplayableObject
                    {
                        public:
                            
                            using XS::PIMPL::Object< NALUnit >::impl;
                            
                            NALUnit( void );
                            NALUnit( BinaryStream & stream );
                            
                            std::string GetName( void ) const override;
                            
                            std::vector< uint8_t > GetData( void ) const;
                            void                   SetData( const std::vector< uint8_t > & value );
                            
                            virtual std::vector< std::pair< std::string, std::string > > GetDisplayableProperties( void )                               const override;
                    };
                    
                    std::vector< std::shared_ptr< NALUnit > > GetNALUnits( void ) const;
                    void                                      AddNALUnit( std::shared_ptr< NALUnit > unit );
            };
            
            std::vector< std::shared_ptr< Array > > GetArrays( void ) const;
            void                                    AddArray( std::shared_ptr< Array > array );
    };
}

#endif /* ISOBMFF_HVCC_HPP */
