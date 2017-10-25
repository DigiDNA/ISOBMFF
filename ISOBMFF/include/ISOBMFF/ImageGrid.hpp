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
 * @header      ImageGrid.hpp
 * @copyright   (c) 2017, DigiDNA - www.digidna.net
 * @author      Jean-David Gadina - www.digidna.net
 */

#ifndef ISOBMFF_IMAGE_GRID_HPP
#define ISOBMFF_IMAGE_GRID_HPP

#include <XS/PIMPL/Object.hpp>
#include <ISOBMFF/Macros.hpp>
#include <ISOBMFF/BinaryStream.hpp>
#include <ISOBMFF/DisplayableObject.hpp>
#include <cstdint>
#include <ostream>

namespace ISOBMFF
{
    class ISOBMFF_EXPORT ImageGrid: public XS::PIMPL::Object< ImageGrid >, public DisplayableObject
    {
        public:
            
            using XS::PIMPL::Object< ImageGrid >::impl;
            
            ImageGrid( void );
            ImageGrid( BinaryStream & stream );
            
            std::string GetName( void ) const override;
            
            uint8_t  GetVersion( void )      const;
            uint8_t  GetFlags( void )        const;
            uint8_t  GetRows( void )         const;
            uint8_t  GetColumns( void )      const;
            uint64_t GetOutputWidth( void )  const;
            uint64_t GetOutputHeight( void ) const;
            
            void SetVersion( uint8_t value );
            void SetFlags( uint8_t value );
            void SetRows( uint8_t value );
            void SetColumns( uint8_t value );
            void SetOutputWidth( uint64_t value );
            void SetOutputHeight( uint64_t value );
            
            virtual std::vector< std::pair< std::string, std::string > > GetDisplayableProperties( void ) const override;
    };
}

#endif /* ISOBMFF_IMAGE_GRID_HPP */
