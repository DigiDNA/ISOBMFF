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
 * @header      WIN32.hpp
 * @copyright   (c) 2017, DigiDNA - www.digidna.net
 * @author      Jean-David Gadina - www.digidna.net
 */

#ifndef ISOBMFF_WIN32_HPP
#define ISOBMFF_WIN32_HPP

#include <string>
#include <ISOBMFF/Macros.hpp>

namespace ISOBMFF
{
    #ifdef _WIN32
    
    /*!
     * @function    WideStringToString
     * @abstract    Converts a wide-string to a string.
     * @param       ws  The wide-string to convert.
     * @result      The converted string.
     * @discussion  Windows only, as conversion is necessary for file streams.
     */
    ISOBMFF_EXPORT std::string  WideStringToString( const std::wstring & ws );
    
    /*!
     * @function    StringToWideString
     * @abstract    Converts a string to a wide-string.
     * @param       ws  The string to convert.
     * @result      The converted wide-string.
     * @discussion  Windows only, as conversion is necessary for file streams.
     */
    ISOBMFF_EXPORT std::wstring StringToWideString( const std::string  & s );
    
    #endif
}

#endif /* ISOBMFF_WIN32_HPP */
