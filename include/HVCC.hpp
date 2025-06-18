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
 * @header      HVCC.hpp
 * @copyright   (c) 2017, DigiDNA - www.digidna.net
 * @author      Jean-David Gadina - www.digidna.net
 */

#ifndef ISOBMFF_HVCC_HPP
#define ISOBMFF_HVCC_HPP

#include <memory>
#include <algorithm>
#include <Macros.hpp>
#include <FullBox.hpp>
#include <DisplayableObject.hpp>
#include <DisplayableObjectContainer.hpp>
#include <vector>
#include <cstdint>

namespace ISOBMFF
{
    class ISOBMFF_EXPORT HVCC: public Box, public DisplayableObjectContainer
    {
        public:

            HVCC();
            HVCC( const HVCC & o );
            HVCC( HVCC && o ) noexcept;
            virtual ~HVCC() override;

            HVCC & operator =( HVCC o );

            void ReadData( Parser & parser, BinaryStream & stream ) override;
            void WriteDescription( std::ostream & os, std::size_t indentLevel ) const override;

            virtual std::vector< std::shared_ptr< DisplayableObject > >  GetDisplayableObjects()    const override;
            virtual std::vector< std::pair< std::string, std::string > > GetDisplayableProperties() const override;

            uint8_t  GetConfigurationVersion()             const;
            uint8_t  GetGeneralProfileSpace()              const;
            uint8_t  GetGeneralTierFlag()                  const;
            uint8_t  GetGeneralProfileIDC()                const;
            uint32_t GetGeneralProfileCompatibilityFlags() const;
            uint64_t GetGeneralConstraintIndicatorFlags()  const;
            uint8_t  GetGeneralLevelIDC()                  const;
            uint16_t GetMinSpatialSegmentationIDC()        const;
            uint8_t  GetParallelismType()                  const;
            uint8_t  GetChromaFormat()                     const;
            uint8_t  GetBitDepthLumaMinus8()               const;
            uint8_t  GetBitDepthChromaMinus8()             const;
            uint16_t GetAvgFrameRate()                     const;
            uint8_t  GetConstantFrameRate()                const;
            uint8_t  GetNumTemporalLayers()                const;
            uint8_t  GetTemporalIdNested()                 const;
            uint8_t  GetLengthSizeMinusOne()               const;

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

            class ISOBMFF_EXPORT Array: public DisplayableObject, public DisplayableObjectContainer
            {
                public:

                    Array();
                    Array( BinaryStream & stream );
                    Array( const Array & o );
                    Array( Array && o ) noexcept;
                    virtual ~Array() override;

                    Array & operator =( Array o );

                    std::string GetName() const override;

                    bool    GetArrayCompleteness() const;
                    uint8_t GetNALUnitType()       const;

                    void SetArrayCompleteness( bool value );
                    void SetNALUnitType( uint8_t value );

                    void WriteDescription( std::ostream & os, std::size_t indentLevel ) const override;

                    virtual std::vector< std::shared_ptr< DisplayableObject > >  GetDisplayableObjects()    const override;
                    virtual std::vector< std::pair< std::string, std::string > > GetDisplayableProperties() const override;

                    class ISOBMFF_EXPORT NALUnit: public DisplayableObject
                    {
                        public:

                            NALUnit();
                            NALUnit( BinaryStream & stream );
                            NALUnit( const NALUnit & o );
                            NALUnit( NALUnit && o ) noexcept;
                            virtual ~NALUnit() override;

                            NALUnit & operator =( NALUnit o );

                            std::string GetName() const override;

                            std::vector< uint8_t > GetData() const;
                            void                   SetData( const std::vector< uint8_t > & value );

                            virtual std::vector< std::pair< std::string, std::string > > GetDisplayableProperties() const override;

                            ISOBMFF_EXPORT friend void swap( NALUnit & o1, NALUnit & o2 );

                        private:

                            class IMPL;

                            std::unique_ptr< IMPL > impl;
                    };

                    std::vector< std::shared_ptr< NALUnit > > GetNALUnits() const;
                    void                                      AddNALUnit( std::shared_ptr< NALUnit > unit );

                    ISOBMFF_EXPORT friend void swap( Array & o1, Array & o2 );

                private:

                    class IMPL;

                    std::unique_ptr< IMPL > impl;
            };

            std::vector< std::shared_ptr< Array > > GetArrays() const;
            void                                    AddArray( std::shared_ptr< Array > array );

            ISOBMFF_EXPORT friend void swap( HVCC & o1, HVCC & o2 );

        private:

            class IMPL;

            std::unique_ptr< IMPL > impl;
    };
}

#endif /* ISOBMFF_HVCC_HPP */
