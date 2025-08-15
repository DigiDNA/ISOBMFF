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
 * @header      PIXI.hpp
 * @copyright   (c) 2017, DigiDNA - www.digidna.net
 * @author      Jean-David Gadina - www.digidna.net
 */

#ifndef ISOBMFF_PIXI_HPP
#define ISOBMFF_PIXI_HPP

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
    class ISOBMFF_EXPORT PIXI: public FullBox, public DisplayableObjectContainer
    {
        public:

            PIXI();
            PIXI( const PIXI & o );
            PIXI( PIXI && o ) noexcept;
            virtual ~PIXI() override;

            PIXI & operator =( PIXI o );

            void ReadData( Parser & parser, BinaryStream & stream ) override;
            void WriteDescription( std::ostream & os, std::size_t indentLevel ) const override;

            virtual std::vector< std::shared_ptr< DisplayableObject > >  GetDisplayableObjects()    const override;
            virtual std::vector< std::pair< std::string, std::string > > GetDisplayableProperties() const override;

            class ISOBMFF_EXPORT Channel: public DisplayableObject
            {
                public:

                    Channel();
                    Channel( BinaryStream & stream );
                    Channel( const Channel & o );
                    Channel( Channel && o ) noexcept;
                    virtual ~Channel() override;

                    Channel & operator =( Channel o );

                    std::string GetName() const override;

                    uint8_t GetBitsPerChannel() const;
                    void    SetBitsPerChannel( uint8_t value );

                    virtual std::vector< std::pair< std::string, std::string > > GetDisplayableProperties() const override;

                    ISOBMFF_EXPORT friend void swap( Channel & o1, Channel & o2 );

                private:

                    class IMPL;

                    std::unique_ptr< IMPL > impl;
            };

            std::vector< std::shared_ptr< Channel > > GetChannels() const;
            void                                      AddChannel( std::shared_ptr< Channel > array );

            ISOBMFF_EXPORT friend void swap( PIXI & o1, PIXI & o2 );

        private:

            class IMPL;

            std::unique_ptr< IMPL > impl;
    };
}

#endif /* ISOBMFF_PIXI_HPP */
