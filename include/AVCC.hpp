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
 * @header      AVCC.hpp
 * @copyright   (c) 2017, DigiDNA - www.digidna.net
 * @author      Jean-David Gadina - www.digidna.net
 */

#ifndef ISOBMFF_AVCC_HPP
#define ISOBMFF_AVCC_HPP

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
    class ISOBMFF_EXPORT AVCC: public Box, public DisplayableObjectContainer
    {
        public:

            AVCC();
            AVCC( const AVCC & o );
            AVCC( AVCC && o ) noexcept;
            virtual ~AVCC() override;

            AVCC & operator =( AVCC o );

            void ReadData( Parser & parser, BinaryStream & stream ) override;
            void WriteDescription( std::ostream & os, std::size_t indentLevel ) const override;

            virtual std::vector< std::shared_ptr< DisplayableObject > >  GetDisplayableObjects()    const override;
            virtual std::vector< std::pair< std::string, std::string > > GetDisplayableProperties() const override;

            uint8_t  GetConfigurationVersion()             const;
            uint8_t  GetAVCProfileIndication()             const;
            uint8_t  GetProfileCompatibility()             const;
            uint8_t  GetAVCLevelIndication()              const;
            uint8_t  GetLengthSizeMinusOne()               const;
            uint8_t  GetNumOfSequenceParameterSets()       const;
            uint8_t  GetNumOfPictureParameterSets()        const;

            void SetConfigurationVersion( uint8_t value );
            void SetAVCProfileIndication( uint8_t value );
            void SetProfileCompatibility( uint8_t value );
            void SetAVCLevelIndication( uint8_t value );
            void SetLengthSizeMinusOne( uint8_t value );
            void SetNumOfSequenceParameterSets( uint8_t value );
            void SetNumOfPictureParameterSets( uint8_t value );


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


            std::vector< std::shared_ptr< NALUnit > > GetSequenceParameterSetNALUnits() const;
            void                                    AddSequenceParameterSetNALUnit( std::shared_ptr< NALUnit > nal_unit );

            std::vector< std::shared_ptr< NALUnit > > GetPictureParameterSetNALUnits() const;
            void                                    AddPictureParameterSetNALUnit( std::shared_ptr< NALUnit > nal_unit );


            ISOBMFF_EXPORT friend void swap( AVCC & o1, AVCC & o2 );

        private:

            class IMPL;

            std::unique_ptr< IMPL > impl;
    };
}

#endif /* ISOBMFF_AVCC_HPP */
