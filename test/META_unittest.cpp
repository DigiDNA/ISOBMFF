/*
 *  Copyright (c) Meta Platforms, Inc. and its affiliates.
 */
#include <ISOBMFF.hpp>                  // for various
#include <BinaryDataStream.hpp> // for BinaryDataStream
#include <Parser.hpp>           // for Parser

#include <gmock/gmock.h>
#include <gtest/gtest.h>

namespace ISOBMFF {

class ISOBMFFMetaTest : public ::testing::Test {
public:
  ISOBMFFMetaTest() {}
  ~ISOBMFFMetaTest() override {}
};

TEST_F(ISOBMFFMetaTest, TestMetaParser) {
  // fuzzer::conv: data
  const std::vector<uint8_t> &buffer = {
      // following example input is from a sample .mp4 video file
      // meta size: 118 bytes
      // 0x00, 0x00, 0x00, 0x76,
      // // meta
      // 0x6d, 0x65, 0x74, 0x61,
      // meta content
      0x00, 0x00, 0x00, 0x21, 0x68, 0x64, 0x6c, 0x72, 0x00, 0x00, 0x00,
      0x00, 0x00, 0x00, 0x00, 0x00, 0x6d, 0x64, 0x74, 0x61, 0x00, 0x00,
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
      0x00, 0x00, 0x00, 0x2b, 0x6b, 0x65, 0x79, 0x73, 0x00, 0x00, 0x00,
      0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x1b, 0x6d, 0x64,
      0x74, 0x61, 0x63, 0x6f, 0x6d, 0x2e, 0x61, 0x6e, 0x64, 0x72, 0x6f,
      0x69, 0x64, 0x2e, 0x76, 0x65, 0x72, 0x73, 0x69, 0x6f, 0x6e, 0x00,
      0x00, 0x00, 0x22, 0x69, 0x6c, 0x73, 0x74, 0x00, 0x00, 0x00, 0x1a,
      0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x12, 0x64, 0x61, 0x74,
      0x61, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x31, 0x32};

  // fuzzer::conv: begin
  ISOBMFF::BinaryDataStream stream(buffer);
  ISOBMFF::Parser parser;
  std::shared_ptr<ISOBMFF::Box> box = parser.CreateBox("meta");
  try {
    if (box != nullptr) {
      box->ReadData(parser, stream);
    }
  } catch (std::exception &e) {
    fprintf(stderr, "Caught exception: %s\n", e.what());
  }
  // fuzzer::conv: end

  // Validate meta box
  auto meta = std::dynamic_pointer_cast<ISOBMFF::META>(box);
  EXPECT_TRUE(meta != nullptr);

  // validate sub boxes
  std::vector<std::shared_ptr<Box>> boxes = meta->GetBoxes();
  for (auto &subbox : boxes) {
    const std::string name = subbox->GetName();
    if (name.compare("hdlr") == 0) {
      auto HDLR = std::dynamic_pointer_cast<ISOBMFF::HDLR>(subbox);
      EXPECT_TRUE(HDLR != nullptr);
    }

    if (name.compare("keys") == 0) {
      auto data = subbox->GetData();
      size_t length = data.size();
      EXPECT_EQ(length, 35);
    }

    if (name.compare("ilst") == 0) {
      auto data = subbox->GetData();
      size_t length = data.size();
      EXPECT_EQ(length, 26);
    }
  }
}
} // namespace ISOBMFF
