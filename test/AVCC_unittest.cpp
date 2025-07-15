/*
 *  Copyright (c) Meta Platforms, Inc. and its affiliates.
 */

#include <ISOBMFF.hpp>                  // for various
#include <BinaryDataStream.hpp> // for BinaryDataStream
#include <Parser.hpp>           // for Parser

#include <gmock/gmock.h>
#include <gtest/gtest.h>

namespace ISOBMFF {

class ISOBMFFAVCCTest : public ::testing::Test {
public:
  ISOBMFFAVCCTest() {}
  ~ISOBMFFAVCCTest() override {}
};

TEST_F(ISOBMFFAVCCTest, TestAVCCParser) {
  // fuzzer::conv: data
  const std::vector<uint8_t> &buffer = {
      // following example input is from a sample .mp4 video file
      // avcC size: 57 bytes
      // 0x00, 0x00, 0x00, 0x39,
      // avcC
      // 0x61, 0x76, 0x63, 0x43,
      // avcC content:
      0x01, 0x64, 0x00, 0x34, 0xff, 0xe1, 0x00, 0x1c,
      0x67, 0x64, 0x00, 0x34, 0xac, 0xd9, 0x40, 0x6c,
      0x01, 0x21, 0xa6, 0xa1, 0x22, 0x41, 0x28, 0x00,
      0x00, 0x03, 0x00, 0x08, 0x00, 0x00, 0x07, 0x80,
      0x78, 0xc1, 0x8c, 0xb0, 0x01, 0x00, 0x06, 0x68,
      0xeb, 0xe3, 0xcb, 0x22, 0xc0, 0xfd, 0xf8, 0xf8,
      0x00
    };

  // fuzzer::conv: begin
  ISOBMFF::BinaryDataStream stream(buffer);
  ISOBMFF::Parser parser;
  std::shared_ptr<ISOBMFF::Box> box = parser.CreateBox("avcC");

  try {
    if (box != nullptr) {
      box->ReadData(parser, stream);
    }
  } catch (std::exception &e) {
    fprintf(stderr, "Caught exception: %s\n", e.what());
  }
  // fuzzer::conv: end

  // Validate AVCC box
  auto avcc = std::dynamic_pointer_cast<ISOBMFF::AVCC>(box);
  ASSERT_NE(avcc, nullptr) << "Failed to cast to AVCC";

  // Validate configuration version
  EXPECT_EQ(avcc->GetConfigurationVersion(), 1);

  // Validate AVC profile indication
  EXPECT_EQ(avcc->GetAVCProfileIndication(), 0x64);

  // Validate profile compatibility
  EXPECT_EQ(avcc->GetProfileCompatibility(), 0x00);

  // Validate AVC level indication
  EXPECT_EQ(avcc->GetAVCLevelIndication(), 52);

  // Validate length size minus one
  EXPECT_EQ(avcc->GetLengthSizeMinusOne(), 3);

  // Validate number of sequence parameter sets
  EXPECT_EQ(avcc->GetNumOfSequenceParameterSets(), 1);

  // Validate number of picture parameter sets
  EXPECT_EQ(avcc->GetNumOfPictureParameterSets(), 1);

  // Validate SPS NAL units
  EXPECT_EQ(avcc->GetSequenceParameterSetNALUnits().size(), 1);
  EXPECT_EQ(avcc->GetSequenceParameterSetNALUnits()[0]->GetData().size(), 28);

  // Validate PPS NAL units
  EXPECT_EQ(avcc->GetPictureParameterSetNALUnits().size(), 1);
  EXPECT_EQ(avcc->GetPictureParameterSetNALUnits()[0]->GetData().size(), 6);
}
} // namespace ISOBMFF
