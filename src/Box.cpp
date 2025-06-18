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
 * @file        Box.cpp
 * @copyright   (c) 2017, DigiDNA - www.digidna.net
 * @author      Jean-David Gadina - www.digidna.net
 */

#include <Box.hpp>
#include <Utils.hpp>
#include <DisplayableObjectContainer.hpp>
#include <Parser.hpp>

namespace ISOBMFF
{
    class Box::IMPL
    {
        public:

            IMPL( const std::string & name = "????" );
            IMPL( const IMPL & o );
            ~IMPL();

            std::string            _name;
            std::vector< uint8_t > _data;
            bool                   _hasData;
    };

    Box::Box( const std::string & name ):
        impl( std::make_unique< IMPL >( name ) )
    {}

    Box::Box( const Box & o ):
        impl( std::make_unique< IMPL >( *( o.impl ) ) )
    {}

    Box::Box( Box && o ) noexcept:
        impl( std::move( o.impl ) )
    {
        o.impl = nullptr;
    }

    Box::~Box()
    {}

    Box & Box::operator =( Box o )
    {
        swap( *( this ), o );

        return *( this );
    }

    void swap( Box & o1, Box & o2 )
    {
        using std::swap;

        swap( o1.impl, o2.impl );
    }

    std::string Box::GetName() const
    {
        return this->impl->_name;
    }

    void Box::ReadData( Parser & parser, BinaryStream & stream )
    {
        ( void )parser;

        this->impl->_data    = stream.ReadAllData();
        this->impl->_hasData = true;
    }

    std::vector< uint8_t > Box::GetData() const
    {
        return this->impl->_data;
    }

    std::vector< std::pair< std::string, std::string > > Box::GetDisplayableProperties() const
    {
        return {};
    }

    Box::IMPL::IMPL( const std::string & name ):
        _name( name ),
        _hasData( false )
    {}

    Box::IMPL::IMPL( const IMPL & o ):
        _name( o._name ),
        _data( o._data ),
        _hasData( o._hasData )
    {}

    Box::IMPL::~IMPL()
    {}
}
