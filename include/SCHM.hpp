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
 * @header      SCHM.hpp
 * @copyright   (c) 2017, DigiDNA - www.digidna.net
 * @author      Jean-David Gadina - www.digidna.net
 */

#ifndef ISOBMFF_SCHM_HPP
#define ISOBMFF_SCHM_HPP

#include <memory>
#include <algorithm>
#include <Macros.hpp>
#include <FullBox.hpp>
#include <string>

namespace ISOBMFF
{
    class ISOBMFF_EXPORT SCHM: public FullBox
    {
        public:

            SCHM();
            SCHM( const SCHM & o );
            SCHM( SCHM && o ) noexcept;
            virtual ~SCHM() override;

            SCHM & operator =( SCHM o );

            void                                                 ReadData( Parser & parser, BinaryStream & stream ) override;
            std::vector< std::pair< std::string, std::string > > GetDisplayableProperties() const override;

            std::string GetSchemeType()    const;
            uint32_t    GetSchemeVersion() const;
            std::string GetSchemeURI()     const;

            void SetSchemeType( const std::string & value );
            void SetSchemeVersion( uint32_t value );
            void SetSchemeURI( const std::string & value );

            ISOBMFF_EXPORT friend void swap( SCHM & o1, SCHM & o2 );

        private:

            class IMPL;

            std::unique_ptr< IMPL > impl;
    };
}

#endif /* ISOBMFF_SCHM_HPP */
