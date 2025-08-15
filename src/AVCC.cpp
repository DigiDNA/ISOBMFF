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
 * @file        AVCC.cpp
 * @copyright   (c) 2017, DigiDNA - www.digidna.net
 * @author      Jean-David Gadina - www.digidna.net
 */

#include <AVCC.hpp>
#include <Utils.hpp>
#include <Parser.hpp>

namespace ISOBMFF
{
    class AVCC::IMPL
    {
        public:

            IMPL();
            IMPL( const IMPL & o );
            ~IMPL();

            uint8_t                                 _configurationVersion;
            uint8_t                                 _AVCProfileIndication;
            uint8_t                                 _profileCompatibility;
            uint8_t                                 _AVCLevelIndication;
            uint8_t                                 _lengthSizeMinusOne;
            uint8_t                                 _numOfSequenceParameterSets;
            std::vector< std::shared_ptr< NALUnit > > _sequence_parameter_set_nal_units;
            uint8_t                                 _numOfPictureParameterSets;
            std::vector< std::shared_ptr< NALUnit > > _picture_parameter_set_nal_units;

    };

    AVCC::AVCC():
        Box( "avcC" ),
        impl( std::make_unique< IMPL >() )
    {}

    AVCC::AVCC( const AVCC & o ):
        Box( o ),
        impl( std::make_unique< IMPL >( *( o.impl ) ) )
    {}

    AVCC::AVCC( AVCC && o ) noexcept:
        Box( std::move( o ) ),
        impl( std::move( o.impl ) )
    {
        o.impl = nullptr;
    }

    AVCC::~AVCC()
    {}

    AVCC & AVCC::operator =( AVCC o )
    {
        Box::operator=( o );
        swap( *( this ), o );

        return *( this );
    }

    void swap( AVCC & o1, AVCC & o2 )
    {
        using std::swap;

        swap( static_cast< Box & >( o1 ), static_cast< Box & >( o2 ) );
        swap( o1.impl, o2.impl );
    }

    void AVCC::ReadData( Parser & parser, BinaryStream & stream )
    {
        uint8_t  u8;
        uint8_t  count;
        uint8_t  i;

        ( void )parser;

        this->SetConfigurationVersion( stream.ReadUInt8() );
        this->SetAVCProfileIndication( stream.ReadUInt8() );
        this->SetProfileCompatibility( stream.ReadUInt8() );
        this->SetAVCLevelIndication( stream.ReadUInt8() );
        u8 = stream.ReadUInt8();
        this->SetLengthSizeMinusOne( u8 & 0x3 );
        u8 = stream.ReadUInt8();

        this->SetNumOfSequenceParameterSets( u8 & 0x1f );
        count = this->GetNumOfSequenceParameterSets();
        for( i = 0; i < count; i++ )
        {
            if( stream.HasBytesAvailable() == false )
            {
                /*
                 * Shouldn't happen in theory, but happens on some files...
                 * So simply don't process next NAL unit if we don't have any data
                 * available...
                 */
                break;
            }

            this->AddSequenceParameterSetNALUnit( std::make_shared< NALUnit >( stream ) );
        }

        this->SetNumOfPictureParameterSets( stream.ReadUInt8() );
        count = this->GetNumOfPictureParameterSets();
        for( i = 0; i < count; i++ )
        {
            if( stream.HasBytesAvailable() == false )
            {
                /*
                 * Shouldn't happen in theory, but happens on some files...
                 * So simply don't process next NAL unit if we don't have any data
                 * available...
                 */
                break;
            }

            this->AddPictureParameterSetNALUnit( std::make_shared< NALUnit >( stream ) );
        }
    }

    void AVCC::WriteDescription( std::ostream & os, std::size_t indentLevel ) const
    {
        Box::WriteDescription( os, indentLevel );
        DisplayableObjectContainer::WriteDescription( os, indentLevel );
    }

    std::vector< std::shared_ptr< DisplayableObject > > AVCC::GetDisplayableObjects() const
    {
        auto sps( this->GetSequenceParameterSetNALUnits() );
        auto vsps = std::vector< std::shared_ptr< DisplayableObject > >( sps.begin(), sps.end() );
        auto pps( this->GetPictureParameterSetNALUnits() );
        auto vpps = std::vector< std::shared_ptr< DisplayableObject > >( pps.begin(), pps.end() );
        vsps.insert(vsps.end(), vpps.begin(), vpps.end());
        return vsps;
    }

    std::vector< std::pair< std::string, std::string > > AVCC::GetDisplayableProperties() const
    {
        auto props( Box::GetDisplayableProperties() );

        props.push_back( { "Configuration version",               std::to_string( this->GetConfigurationVersion() ) } );
        props.push_back( { "AVC profile",               std::to_string( this->GetAVCProfileIndication() ) } );
        props.push_back( { "Profile compatibility",               std::to_string( this->GetProfileCompatibility() ) } );
        props.push_back( { "AVC level",               std::to_string( this->GetAVCLevelIndication() ) } );
        props.push_back( { "Length size (minus one)",               std::to_string( this->GetLengthSizeMinusOne() ) } );
        props.push_back( { "Number of Sequence Parameter Sets",               std::to_string( this->GetNumOfSequenceParameterSets() ) } );
        props.push_back( { "Number of Picture Parameter Sets",               std::to_string( this->GetNumOfPictureParameterSets() ) } );
        props.push_back( { "SPS NAL Units",                              std::to_string( this->GetSequenceParameterSetNALUnits().size() ) } );
        props.push_back( { "PPS NAL Units",                              std::to_string( this->GetPictureParameterSetNALUnits().size() ) } );

        return props;
    }

    uint8_t AVCC::GetConfigurationVersion() const
    {
        return this->impl->_configurationVersion;
    }

    uint8_t AVCC::GetAVCProfileIndication() const
    {
        return this->impl->_AVCProfileIndication;
    }

    uint8_t AVCC::GetProfileCompatibility() const
    {
        return this->impl->_profileCompatibility;
    }

    uint8_t AVCC::GetAVCLevelIndication() const
    {
        return this->impl->_AVCLevelIndication;
    }

    uint8_t AVCC::GetLengthSizeMinusOne() const
    {
        return this->impl->_lengthSizeMinusOne;
    }

    uint8_t AVCC::GetNumOfSequenceParameterSets() const
    {
        return this->impl->_numOfSequenceParameterSets;
    }

    uint8_t AVCC::GetNumOfPictureParameterSets() const
    {
        return this->impl->_numOfPictureParameterSets;
    }


    void AVCC::SetConfigurationVersion( uint8_t value )
    {
        this->impl->_configurationVersion = value;
    }

    void AVCC::SetAVCProfileIndication( uint8_t value )
    {
        this->impl->_AVCProfileIndication = value;
    }

    void AVCC::SetProfileCompatibility( uint8_t value )
    {
        this->impl->_profileCompatibility = value;
    }

    void AVCC::SetAVCLevelIndication( uint8_t value )
    {
        this->impl->_AVCLevelIndication = value;
    }

    void AVCC::SetLengthSizeMinusOne( uint8_t value )
    {
        this->impl->_lengthSizeMinusOne = value;
    }

    void AVCC::SetNumOfSequenceParameterSets( uint8_t value )
    {
        this->impl->_numOfSequenceParameterSets = value;
    }

    void AVCC::SetNumOfPictureParameterSets( uint8_t value )
    {
        this->impl->_numOfPictureParameterSets = value;
    }


    std::vector< std::shared_ptr< AVCC::NALUnit > > AVCC::GetSequenceParameterSetNALUnits() const
    {
        return this->impl->_sequence_parameter_set_nal_units;
    }

    std::vector< std::shared_ptr< AVCC::NALUnit > > AVCC::GetPictureParameterSetNALUnits() const
    {
        return this->impl->_picture_parameter_set_nal_units;
    }


    void AVCC::AddSequenceParameterSetNALUnit( std::shared_ptr< NALUnit > nal_unit )
    {
        this->impl->_sequence_parameter_set_nal_units.push_back( nal_unit );
    }

    void AVCC::AddPictureParameterSetNALUnit( std::shared_ptr< NALUnit > nal_unit )
    {
        this->impl->_picture_parameter_set_nal_units.push_back( nal_unit );
    }

    AVCC::IMPL::IMPL():
        _configurationVersion( 0 ),
        _AVCProfileIndication( 0 ),
        _profileCompatibility( 0 ),
        _AVCLevelIndication( 0 ),
        _lengthSizeMinusOne( 0 ),
        _numOfSequenceParameterSets( 0 ),
        _numOfPictureParameterSets( 0 )
    {}

    AVCC::IMPL::IMPL( const IMPL & o ):
        _configurationVersion( o._configurationVersion ),
        _AVCProfileIndication( o._AVCProfileIndication ),
        _profileCompatibility( o._profileCompatibility ),
        _AVCLevelIndication( o._AVCLevelIndication ),
        _lengthSizeMinusOne( o._lengthSizeMinusOne ),
        _numOfSequenceParameterSets( o._numOfSequenceParameterSets ),
        _sequence_parameter_set_nal_units( o._sequence_parameter_set_nal_units ),
        _numOfPictureParameterSets( o._numOfPictureParameterSets ),
        _picture_parameter_set_nal_units( o._picture_parameter_set_nal_units )
    {}

    AVCC::IMPL::~IMPL()
    {}
}
