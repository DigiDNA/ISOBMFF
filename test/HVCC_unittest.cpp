/*
 *  Copyright (c) Meta Platforms, Inc. and its affiliates.
 */

#include <ISOBMFF.hpp>                  // for various
#include <BinaryDataStream.hpp> // for BinaryDataStream
#include <Parser.hpp>           // for Parser

#include <gmock/gmock.h>
#include <gtest/gtest.h>

namespace ISOBMFF {

class ISOBMFFHVCCTest : public ::testing::Test {
public:
  ISOBMFFHVCCTest() {}
  ~ISOBMFFHVCCTest() override {}
};

TEST_F(ISOBMFFHVCCTest, TestHVCCParser) {
  // fuzzer::conv: data
  const std::vector<uint8_t> &buffer = {
      // following example input is from a sample .mp4 video file
      // hvcC size: 135 bytes
      // 0x00, 0x00, 0x00, 0x87,
      // hvcC
      // 0x68, 0x76, 0x63, 0x43,
      // hvcC content:
      0x01, 0x01, 0x60, 0x00, 0x00, 0x00, 0xb0, 0x00,
      0x00, 0x00, 0x00, 0x00, 0x99, 0xf0, 0x00, 0xfc,
      0xfd, 0xf8, 0xf8, 0x00, 0x00, 0x03, 0x03, 0xa0,
      0x00, 0x01, 0x00, 0x20, 0x40, 0x01, 0x0c, 0x01,
      0xff, 0xff, 0x01, 0x60, 0x00, 0x00, 0x03, 0x00,
      0xb0, 0x00, 0x00, 0x03, 0x00, 0x00, 0x03, 0x00,
      0x99, 0xac, 0x0c, 0x07, 0xf2, 0x81, 0x54, 0xee,
      0x6b, 0x28, 0x01, 0x40, 0xa1, 0x00, 0x01, 0x00,
      0x2e, 0x42, 0x01, 0x01, 0x01, 0x60, 0x00, 0x00,
      0x03, 0x00, 0xb0, 0x00, 0x00, 0x03, 0x00, 0x00,
      0x03, 0x00, 0x99, 0xa0, 0x03, 0x60, 0x80, 0x09,
      0x01, 0x65, 0xae, 0xe4, 0xc9, 0x2e, 0xa6, 0xa1,
      0x22, 0x41, 0x20, 0x80, 0xfe, 0x50, 0x2a, 0x9d,
      0xcd, 0x65, 0x00, 0x17, 0x68, 0x50, 0x94, 0xa2,
      0x00, 0x01, 0x00, 0x0b, 0x44, 0x01, 0xc0, 0xe3,
      0x0f, 0x09, 0xc1, 0x50, 0xaf, 0xb0, 0x84
    };

  // fuzzer::conv: begin
  ISOBMFF::BinaryDataStream stream(buffer);
  ISOBMFF::Parser parser;
  std::shared_ptr<ISOBMFF::Box> box = parser.CreateBox("hvcC");

  try {
    if (box != nullptr) {
      box->ReadData(parser, stream);
    }
  } catch (std::exception &e) {
    fprintf(stderr, "Caught exception: %s\n", e.what());
  }
  // fuzzer::conv: end

  // Validate HVCC box
  auto hvcc = std::dynamic_pointer_cast<ISOBMFF::HVCC>(box);
  ASSERT_NE(hvcc, nullptr) << "Failed to cast to HVCC";

  // Validate HVCC box fields
  EXPECT_EQ(hvcc->GetConfigurationVersion(), 1);
  EXPECT_EQ(hvcc->GetGeneralProfileSpace(), 0);
  EXPECT_EQ(hvcc->GetGeneralTierFlag(), 0x00);
  EXPECT_EQ(hvcc->GetGeneralProfileIDC(), 1);
  EXPECT_EQ(hvcc->GetGeneralProfileCompatibilityFlags(), 0x60000000);
  EXPECT_EQ(hvcc->GetGeneralConstraintIndicatorFlags(), 193514046488576);
  EXPECT_EQ(hvcc->GetGeneralLevelIDC(), 153);
  EXPECT_EQ(hvcc->GetMinSpatialSegmentationIDC(), 0);
  EXPECT_EQ(hvcc->GetParallelismType(), 0);
  EXPECT_EQ(hvcc->GetChromaFormat(), 1);
  EXPECT_EQ(hvcc->GetBitDepthLumaMinus8(), 0);
  EXPECT_EQ(hvcc->GetBitDepthChromaMinus8(), 0);
  EXPECT_EQ(hvcc->GetAvgFrameRate(), 0);
  EXPECT_EQ(hvcc->GetConstantFrameRate(), 0);
  EXPECT_EQ(hvcc->GetNumTemporalLayers(), 0);
  EXPECT_EQ(hvcc->GetTemporalIdNested(), 0);
  EXPECT_EQ(hvcc->GetLengthSizeMinusOne(), 3);

  // Validate arrays
  auto arrays = hvcc->GetArrays();
  ASSERT_EQ(arrays.size(), 3);

  // Validate first array
  EXPECT_TRUE(arrays[0]->GetArrayCompleteness());
  EXPECT_EQ(arrays[0]->GetNALUnitType(), 32);
  ASSERT_EQ(arrays[0]->GetNALUnits().size(), 1);
  EXPECT_EQ(arrays[0]->GetNALUnits()[0]->GetData().size(), 32);

  // Validate second array
  EXPECT_TRUE(arrays[1]->GetArrayCompleteness());
  EXPECT_EQ(arrays[1]->GetNALUnitType(), 33);
  ASSERT_EQ(arrays[1]->GetNALUnits().size(), 1);
  EXPECT_EQ(arrays[1]->GetNALUnits()[0]->GetData().size(), 46);

  // Validate third array
  EXPECT_TRUE(arrays[2]->GetArrayCompleteness());
  EXPECT_EQ(arrays[2]->GetNALUnitType(), 34);
  ASSERT_EQ(arrays[2]->GetNALUnits().size(), 1);
  EXPECT_EQ(arrays[2]->GetNALUnits()[0]->GetData().size(), 11);
}
} // namespace ISOBMFF
