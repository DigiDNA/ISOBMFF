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
 * @header      DisplayableObject.hpp
 * @copyright   (c) 2017, DigiDNA - www.digidna.net
 * @author      Jean-David Gadina - www.digidna.net
 */

#ifndef ISOBMFF_DISPLAYABLE_OBJECT_HPP
#define ISOBMFF_DISPLAYABLE_OBJECT_HPP

#include <ISOBMFF/Macros.hpp>
#include <ISOBMFF/Utils.hpp>
#include <ostream>
#include <sstream>
#include <vector>
#include <utility>
#include <string>

namespace ISOBMFF
{
    /*!
     * @class       DisplayableObject
     * @abstract    Interface for displayable objects.
     */
    class ISOBMFF_EXPORT DisplayableObject
    {
        public:
            
            /*! 
             * @function    ~DisplayableObject
             * @abstarct    Destructor.
             */
            virtual ~DisplayableObject( void );
            
            /*!
             * @function    GetDisplayableProperties
             * @abstract    Returns the object's displayable properties and values.
             * @result      The object's properties/values.
             */
            virtual std::vector< std::pair< std::string, std::string > > GetDisplayableProperties( void ) const = 0;
            
            /*!
             * @function    GetName
             * @abstract    Returns the object's displayable name.
             * @result      The object's name.
             */
            virtual std::string GetName( void ) const = 0;
            
            /*!
             * @function    WriteDescription
             * @abstract    Writes the object's description to an output stream.
             * @param       os              The output stream in which to write the description.
             * @param       indentLevel     The requested indent level.
             * @discussion  This will write the object's name followed by its
             *              displayable properties.
             * @see         GetName
             * @see         GetDisplayableProperties
             */
            virtual void WriteDescription( std::ostream & os, std::size_t indentLevel ) const;
            
            /*!
             * @function    ToString
             * @abstract    Returns a string representation of the object.
             * @result      A string representation of the object.
             * @see         WriteDescription
             */
            virtual std::string ToString( void ) const;
            
            /*!
             * @function    operator <<
             * @abstract    Writes the description of an object to an output stream.
             * @param       os  The output stream.
             * @param       o   The object to write.
             * @result      The output stream.
             * @see         WriteDescription
             */
            ISOBMFF_EXPORT friend std::ostream & operator << ( std::ostream & os, const DisplayableObject & o );
    };
}

#endif /* ISOBMFF_DISPLAYABLE_OBJECT_HPP */


