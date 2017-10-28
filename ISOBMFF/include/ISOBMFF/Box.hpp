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
 * @header      Box.hpp
 * @copyright   (c) 2017, DigiDNA - www.digidna.net
 * @author      Jean-David Gadina - www.digidna.net
 */

#ifndef ISOBMFF_BOX_HPP
#define ISOBMFF_BOX_HPP

#include <XS/PIMPL/Object.hpp>
#include <ISOBMFF/Macros.hpp>
#include <ISOBMFF/BinaryStream.hpp>
#include <ISOBMFF/DisplayableObject.hpp>
#include <string>
#include <ostream>
#include <vector>
#include <utility>

namespace ISOBMFF
{
    class Parser;
    
    /*!
     * @class       Box
     * @abstract    Base interface for ISOBMFF boxes.
     */
    class ISOBMFF_EXPORT Box: public XS::PIMPL::Object< Box >, public DisplayableObject
    {
        public:
            
            using XS::PIMPL::Object< Box >::impl;
            
            /*!
             * @function    Box
             * @abstract    Constructor
             * @param       name    The name of the box.
             */
            Box( const std::string & name );
            
            /*!
             * @function    GetName
             * @abstract    Gets the box name.
             * @result      The box name.
             */
            std::string GetName( void ) const override;
            
            /*!
             * @function    GetDisplayableProperties
             * @abstract    Gets the box displayable properties.
             * @result      The box displayable properties.
             * @see         DisplayableObject
             */
            virtual std::vector< std::pair< std::string, std::string > > GetDisplayableProperties( void ) const override;
            
            /*!
             * @function    ReadData
             * @abstract    Reads box data from a stream.
             * @param       parser  The parser currently being used.
             * @param       stream  The binary stream from which to read the box data.
             * @discussion  Reading will discard all previous box data.
             */
            virtual void ReadData( Parser & parser, BinaryStream & stream );
            
            /*!
             * @function    GetData
             * @abstract    Gets the box data.
             * @result      The box data, as a vector of bytes.
             */
            virtual std::vector< uint8_t > GetData( void ) const;
    };
}

#endif /* ISOBMFF_BOX_HPP */
