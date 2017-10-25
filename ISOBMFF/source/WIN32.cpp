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
 * @file        WIN32.cpp
 * @copyright   (c) 2017, DigiDNA - www.digidna.net
 * @author      Jean-David Gadina - www.digidna.net
 */

#include <ISOBMFF/WIN32.hpp>
#include <vector>

#ifdef _WIN32
#include <Windows.h>
#endif

namespace ISOBMFF
{
    #ifdef _WIN32

    std::string WideStringToString( const std::wstring & ws )
    {
        std::string         s;
        int                 l;
        std::vector< char > v;
        
        l = WideCharToMultiByte( CP_UTF8, 0, ws.c_str(), -1, 0, 0, 0, 0 );
        
        if( l  > 0)
        {
            v = std::vector< char >( l );
            
            WideCharToMultiByte( CP_UTF8, 0, ws.c_str(), -1, &( v[ 0 ] ), l, 0, 0 );
            s.assign( v.begin(), v.end() - 1 );
        }
        
        return s;
    }
    
    std::wstring StringToWideString( const std::string & s )
    {
        std::wstring           ws;
        int                    l;
        std::vector< wchar_t > v;
        
        l = MultiByteToWideChar( CP_UTF8, 0, s.c_str(), -1, 0, 0 );
        
        if( l > 0 )
        {
            v = std::vector< wchar_t >( l );
            
            MultiByteToWideChar( CP_UTF8, 0, s.c_str(), -1, &( v[ 0 ] ), l );
            ws.assign( v.begin(), v.end() - 1 );
        }
        
        return ws;
    }
    
    #endif
}
