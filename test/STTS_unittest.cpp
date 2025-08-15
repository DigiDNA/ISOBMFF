/*
 *  Copyright (c) Meta Platforms, Inc. and its affiliates.
 */

#include <ISOBMFF.hpp>                  // for various
#include <BinaryDataStream.hpp> // for BinaryDataStream
#include <Parser.hpp>           // for Parser

#include <gmock/gmock.h>
#include <gtest/gtest.h>

namespace ISOBMFF {

class ISOBMFFSTTSTest : public ::testing::Test {
public:
  ISOBMFFSTTSTest() {}
  ~ISOBMFFSTTSTest() override {}
};

TEST_F(ISOBMFFSTTSTest, TestSTTSParser) {
  // fuzzer::conv: data
  const std::vector<uint8_t> &buffer = {
      // following example input is from a sample .mp4 video file
      // stts size: 88 bytes
      // 0x00, 0x00, 0x00, 0x58,
      // stts
      // 0x73, 0x74, 0x74, 0x73,
      // stts content:
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x09,
      0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x0b, 0xb8,
      0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x0e, 0xa2,
      0x00, 0x00, 0x00, 0x14, 0x00, 0x00, 0x0b, 0xb8,
      0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x0b, 0xaf,
      0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x0b, 0xc0,
      0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x0b, 0xb0,
      0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x0b, 0xbf,
      0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x0b, 0xb0,
      0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x0b, 0xbf
    };

  // fuzzer::conv: begin
  ISOBMFF::BinaryDataStream stream(buffer);
  ISOBMFF::Parser parser;
  std::shared_ptr<ISOBMFF::Box> box = parser.CreateBox("stts");

  try {
    if (box != nullptr) {
      box->ReadData(parser, stream);
    }
  } catch (std::exception &e) {
    fprintf(stderr, "Caught exception: %s\n", e.what());
  }
  // fuzzer::conv: end

  // Validate STTS box
  auto stts = std::dynamic_pointer_cast<ISOBMFF::STTS>(box);
  ASSERT_NE(stts, nullptr) << "Failed to cast to STTS";

  // Validate entry count
  EXPECT_EQ(stts->GetEntryCount(), 9);
  
  // Validate sample counts and offsets
  EXPECT_EQ(stts->GetSampleCount(0), 8);
  EXPECT_EQ(stts->GetSampleOffset(0), 3000);
  EXPECT_EQ(stts->GetSampleCount(1), 1);
  EXPECT_EQ(stts->GetSampleOffset(1), 3746);
  EXPECT_EQ(stts->GetSampleCount(2), 20);
  EXPECT_EQ(stts->GetSampleOffset(2), 3000);
  EXPECT_EQ(stts->GetSampleCount(3), 2);
  EXPECT_EQ(stts->GetSampleOffset(3), 2991);
  EXPECT_EQ(stts->GetSampleCount(4), 2);
  EXPECT_EQ(stts->GetSampleOffset(4), 3008);
  EXPECT_EQ(stts->GetSampleCount(5), 2);
  EXPECT_EQ(stts->GetSampleOffset(5), 2992);
  EXPECT_EQ(stts->GetSampleCount(6), 2);
  EXPECT_EQ(stts->GetSampleOffset(6), 3007);
  EXPECT_EQ(stts->GetSampleCount(7), 2);
  EXPECT_EQ(stts->GetSampleOffset(7), 2992);
  EXPECT_EQ(stts->GetSampleCount(8), 3);
  EXPECT_EQ(stts->GetSampleOffset(8), 3007);
}
} // namespace ISOBMFF
