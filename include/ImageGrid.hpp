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

#include <memory>
#include <algorithm>
#include <Macros.hpp>
#include <BinaryStream.hpp>
#include <DisplayableObject.hpp>
#include <cstdint>
#include <ostream>

namespace ISOBMFF
{
    class ISOBMFF_EXPORT ImageGrid: public DisplayableObject
    {
        public:

            ImageGrid();
            ImageGrid( BinaryStream & stream );
            ImageGrid( const ImageGrid & o );
            ImageGrid( ImageGrid && o ) noexcept;
            virtual ~ImageGrid() override;

            ImageGrid & operator =( ImageGrid o );

            std::string GetName() const override;

            uint8_t  GetVersion()      const;
            uint8_t  GetFlags()        const;
            uint8_t  GetRows()         const;
            uint8_t  GetColumns()      const;
            uint64_t GetOutputWidth()  const;
            uint64_t GetOutputHeight() const;

            void SetVersion( uint8_t value );
            void SetFlags( uint8_t value );
            void SetRows( uint8_t value );
            void SetColumns( uint8_t value );
            void SetOutputWidth( uint64_t value );
            void SetOutputHeight( uint64_t value );

            virtual std::vector< std::pair< std::string, std::string > > GetDisplayableProperties() const override;

            ISOBMFF_EXPORT friend void swap( ImageGrid & o1, ImageGrid & o2 );

        private:

            class IMPL;

            std::unique_ptr< IMPL > impl;
    };
}

#endif /* ISOBMFF_IMAGE_GRID_HPP */
