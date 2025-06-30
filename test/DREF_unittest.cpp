/*
 *  Copyright (c) Meta Platforms, Inc. and its affiliates.
 */

#include <ISOBMFF.hpp>                  // for various
#include <BinaryDataStream.hpp> // for BinaryDataStream
#include <Parser.hpp>           // for Parser

#include <gmock/gmock.h>
#include <gtest/gtest.h>

namespace ISOBMFF {

class ISOBMFFDREFTest : public ::testing::Test {
public:
  ISOBMFFDREFTest() {}
  ~ISOBMFFDREFTest() override {}
 };

 TEST_F(ISOBMFFDREFTest, TestDREFParser) {
  // fuzzer::conv: data
  const std::vector<uint8_t> &buffer = {
      // following example input is from a sample .mp4 video file
      // dref size: 28 bytes
      0x00, 0x00, 0x00, 0x1c,
      // dref
      0x64, 0x72, 0x65, 0x66,
      // dref content:
      0x00, 0x00, 0x00, 0x00,
      0x00, 0x00, 0x00, 0x01,
      0x00, 0x00, 0x00, 0x0c,
      0x75, 0x72, 0x6c, 0x20,
      0x00, 0x00, 0x00, 0x01
    };

  // fuzzer::conv: begin
  ISOBMFF::BinaryDataStream stream(buffer);
  ISOBMFF::Parser parser;
  std::shared_ptr<ISOBMFF::Box> box = parser.CreateBox("dref");

  try {
    if (box != nullptr) {
      box->ReadData(parser, stream);
    }
  } catch (std::exception &e) {
    fprintf(stderr, "Caught exception: %s\n", e.what());
  }
  // fuzzer::conv: end

  // Validate DREF box
  auto dref = std::dynamic_pointer_cast<ISOBMFF::DREF>(box);
  ASSERT_NE(dref, nullptr) << "Failed to cast to DREF";

  EXPECT_EQ(dref->GetVersion(), 0) << "Unexpected DREF version";
  EXPECT_EQ(dref->GetFlags(), 28) << "Unexpected DREF flags";

  // Validate sub-boxes inside DREF
  std::vector<std::shared_ptr<Box>> boxes = dref->GetBoxes();
  ASSERT_EQ(boxes.size(), 1) << "Expected 1 sub-box, but found " << boxes.size();
  for (const auto &subbox : boxes) {
    const std::string type = subbox->GetName();
    if (type == "url ") {
      auto urlBox = std::dynamic_pointer_cast<ISOBMFF::URL>(subbox);
      ASSERT_NE(urlBox, nullptr) << "Failed to cast to URL box";
      EXPECT_EQ(urlBox->GetVersion(), 0) << "Unexpected URL box version";
      EXPECT_EQ(urlBox->GetFlags(), 1) << "Unexpected URL box flags";
    } else {
      FAIL() << "Unexpected sub-box type: " << type;
    }
  }
}
} // namespace
