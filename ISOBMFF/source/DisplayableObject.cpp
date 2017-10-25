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
 * @file        DisplayableObject.cpp
 * @copyright   (c) 2017, DigiDNA - www.digidna.net
 * @author      Jean-David Gadina - www.digidna.net
 */

#include <ISOBMFF/DisplayableObject.hpp>

namespace ISOBMFF
{
    DisplayableObject::~DisplayableObject( void )
    {}
    
    void DisplayableObject::WriteDescription( std::ostream & os, std::size_t indentLevel ) const
    {
        std::string i( indentLevel * 4, ' ' );
        size_t      length;
        auto        props( this->GetDisplayableProperties() );
        
        os << i << "[ " << this->GetName() << " ]";
        
        length = 0;
        
        for( const auto & p: props )
        {
            length = ( p.first.size() > length ) ? p.first.size() : length;
        }
        
        if( props.size() )
        {
            os << std::endl << i << "{";
        }
        
        for( const auto & p: props )
        {
            os << std::endl << i << "    - " << Utils::Pad( p.first + ": ", length + 2 ) << p.second;
        }
        
        if( props.size() )
        {
            os << std::endl << i << "}";
        }
    }
    
    std::string DisplayableObject::ToString( void ) const
    {
        std::stringstream ss;
        
        this->WriteDescription( ss, 0 );
        
        return ss.str();
    }
    
    std::vector< std::pair< std::string, std::string > > DisplayableObject::GetDisplayableProperties( void ) const
    {
        return {};
    }
    
    std::ostream & operator << ( std::ostream & os, const DisplayableObject & o )
    {
        o.WriteDescription( os, 0 );
        
        return os;
    }
}
