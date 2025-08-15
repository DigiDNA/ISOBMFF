/*
 *  Copyright (c) Meta Platforms, Inc. and its affiliates.
 */

#include <ISOBMFF.hpp>                  // for various
#include <BinaryDataStream.hpp> // for BinaryDataStream
#include <Parser.hpp>           // for Parser

#include <gmock/gmock.h>
#include <gtest/gtest.h>

namespace ISOBMFF {

class ISOBMFFCTTSTest : public ::testing::Test {
public:
  ISOBMFFCTTSTest() {}
  ~ISOBMFFCTTSTest() override {}
};

TEST_F(ISOBMFFCTTSTest, TestCTTSParser) {
  // fuzzer::conv: data
  const std::vector<uint8_t> &buffer = {
      // following example input is from a sample .mp4 video file
      // ctts size: 344 bytes
      // 0x00, 0x00, 0x01, 0x58,
      // ctts
      // 0x63, 0x74, 0x74, 0x73,
      // ctts content:
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x29,
      0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x04, 0x00,
      0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x0a, 0x00,
      0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x04, 0x00,
      0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00,
      0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x02, 0x00,
      0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x0a, 0x00,
      0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x04, 0x00,
      0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00,
      0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x02, 0x00,
      0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x0a, 0x80,
      0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x04, 0x80,
      0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00,
      0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x02, 0x00,
      0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x0a, 0x00,
      0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x04, 0x00,
      0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00,
      0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x02, 0x00,
      0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x0a, 0x00,
      0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x04, 0x00,
      0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00,
      0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x02, 0x00,
      0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x0a, 0x00,
      0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x04, 0x00,
      0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00,
      0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x02, 0x00,
      0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x0a, 0x00,
      0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x04, 0x00,
      0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00,
      0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x02, 0x00,
      0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x0a, 0x00,
      0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x04, 0x00,
      0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00,
      0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x02, 0x00,
      0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x0a, 0x00,
      0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x04, 0x00,
      0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00,
      0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x02, 0x00,
      0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x08, 0x00,
      0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x02, 0x00,
      0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x06, 0x00,
      0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x02, 0x00
    };

  // fuzzer::conv: begin
  ISOBMFF::BinaryDataStream stream(buffer);
  ISOBMFF::Parser parser;
  std::shared_ptr<ISOBMFF::Box> box = parser.CreateBox("ctts");

  try {
    if (box != nullptr) {
      box->ReadData(parser, stream);
    }
  } catch (std::exception &e) {
    fprintf(stderr, "Caught exception: %s\n", e.what());
  }
  // fuzzer::conv: end

  // Validate CTTS box
  auto ctts = std::dynamic_pointer_cast<ISOBMFF::CTTS>(box);
  ASSERT_NE(ctts, nullptr) << "Failed to cast to CTTS";

  // Validate version and flags
  EXPECT_EQ(ctts->GetVersion(), 0);
  EXPECT_EQ(ctts->GetFlags(), 0);

  // Validate entry count
  EXPECT_EQ(ctts->GetEntryCount(), 41);

  // Validate some sample counts and offsets
  EXPECT_EQ(ctts->GetEntryCount(), 41);

  EXPECT_EQ(ctts->GetSampleCount(0), 1);
  EXPECT_EQ(ctts->GetSampleOffset(0), 1024);

  EXPECT_EQ(ctts->GetSampleCount(1), 1);
  EXPECT_EQ(ctts->GetSampleOffset(1), 2560);

  EXPECT_EQ(ctts->GetSampleCount(2), 1);
  EXPECT_EQ(ctts->GetSampleOffset(2), 1024);

  EXPECT_EQ(ctts->GetSampleCount(3), 1);
  EXPECT_EQ(ctts->GetSampleOffset(3), 0);

  EXPECT_EQ(ctts->GetSampleCount(4), 1);
  EXPECT_EQ(ctts->GetSampleOffset(4), 512);

  EXPECT_EQ(ctts->GetSampleCount(5), 1);
  EXPECT_EQ(ctts->GetSampleOffset(5), 2560);

  EXPECT_EQ(ctts->GetSampleCount(6), 1);
  EXPECT_EQ(ctts->GetSampleOffset(6), 1024);

  EXPECT_EQ(ctts->GetSampleCount(7), 1);
  EXPECT_EQ(ctts->GetSampleOffset(7), 0);

  EXPECT_EQ(ctts->GetSampleCount(8), 1);
  EXPECT_EQ(ctts->GetSampleOffset(8), 512);

  EXPECT_EQ(ctts->GetSampleCount(9), 1);
  EXPECT_EQ(ctts->GetSampleOffset(9), 2688);

  EXPECT_EQ(ctts->GetSampleCount(10), 1);
  EXPECT_EQ(ctts->GetSampleOffset(10), 1152);

  EXPECT_EQ(ctts->GetSampleCount(11), 1);
  EXPECT_EQ(ctts->GetSampleOffset(11), 0);

  EXPECT_EQ(ctts->GetSampleCount(12), 1);
  EXPECT_EQ(ctts->GetSampleOffset(12), 512);

  EXPECT_EQ(ctts->GetSampleCount(13), 1);
  EXPECT_EQ(ctts->GetSampleOffset(13), 2560);

  EXPECT_EQ(ctts->GetSampleCount(14), 1);
  EXPECT_EQ(ctts->GetSampleOffset(14), 1024);

  EXPECT_EQ(ctts->GetSampleCount(15), 1);
  EXPECT_EQ(ctts->GetSampleOffset(15), 0);

  EXPECT_EQ(ctts->GetSampleCount(16), 1);
  EXPECT_EQ(ctts->GetSampleOffset(16), 512);

  EXPECT_EQ(ctts->GetSampleCount(17), 1);
  EXPECT_EQ(ctts->GetSampleOffset(17), 2560);

  EXPECT_EQ(ctts->GetSampleCount(18), 1);
  EXPECT_EQ(ctts->GetSampleOffset(18), 1024);

  EXPECT_EQ(ctts->GetSampleCount(19), 1);
  EXPECT_EQ(ctts->GetSampleOffset(19), 0);

  EXPECT_EQ(ctts->GetSampleCount(20), 1);
  EXPECT_EQ(ctts->GetSampleOffset(20), 512);

  EXPECT_EQ(ctts->GetSampleCount(21), 1);
  EXPECT_EQ(ctts->GetSampleOffset(21), 2560);

  EXPECT_EQ(ctts->GetSampleCount(22), 1);
  EXPECT_EQ(ctts->GetSampleOffset(22), 1024);

  EXPECT_EQ(ctts->GetSampleCount(23), 1);
  EXPECT_EQ(ctts->GetSampleOffset(23), 0);

  EXPECT_EQ(ctts->GetSampleCount(24), 1);
  EXPECT_EQ(ctts->GetSampleOffset(24), 512);

  EXPECT_EQ(ctts->GetSampleCount(25), 1);
  EXPECT_EQ(ctts->GetSampleOffset(25), 2560);

  EXPECT_EQ(ctts->GetSampleCount(26), 1);
  EXPECT_EQ(ctts->GetSampleOffset(26), 1024);

  EXPECT_EQ(ctts->GetSampleCount(27), 1);
  EXPECT_EQ(ctts->GetSampleOffset(27), 0);

  EXPECT_EQ(ctts->GetSampleCount(28), 1);
  EXPECT_EQ(ctts->GetSampleOffset(28), 512);

  EXPECT_EQ(ctts->GetSampleCount(29), 1);
  EXPECT_EQ(ctts->GetSampleOffset(29), 2560);

  EXPECT_EQ(ctts->GetSampleCount(30), 1);
  EXPECT_EQ(ctts->GetSampleOffset(30), 1024);

  EXPECT_EQ(ctts->GetSampleCount(31), 1);
  EXPECT_EQ(ctts->GetSampleOffset(31), 0);

  EXPECT_EQ(ctts->GetSampleCount(32), 1);
  EXPECT_EQ(ctts->GetSampleOffset(32), 512);

  EXPECT_EQ(ctts->GetSampleCount(33), 1);
  EXPECT_EQ(ctts->GetSampleOffset(33), 2560);

  EXPECT_EQ(ctts->GetSampleCount(34), 1);
  EXPECT_EQ(ctts->GetSampleOffset(34), 1024);

  EXPECT_EQ(ctts->GetSampleCount(35), 1);
  EXPECT_EQ(ctts->GetSampleOffset(35), 0);

  EXPECT_EQ(ctts->GetSampleCount(36), 1);
  EXPECT_EQ(ctts->GetSampleOffset(36), 512);

  EXPECT_EQ(ctts->GetSampleCount(37), 1);
  EXPECT_EQ(ctts->GetSampleOffset(37), 2048);

  EXPECT_EQ(ctts->GetSampleCount(38), 2);
  EXPECT_EQ(ctts->GetSampleOffset(38), 512);

  EXPECT_EQ(ctts->GetSampleCount(39), 1);
  EXPECT_EQ(ctts->GetSampleOffset(39), 1536);

  EXPECT_EQ(ctts->GetSampleCount(40), 1);
  EXPECT_EQ(ctts->GetSampleOffset(40), 512);
}
} // namespace ISOBMFF
