# Auto-Generating Fuzzers and Corpus from Unittests

We decided to use the unittests (which show how to test each of the
parsers, and even provides some interesting input cases) to auto-generate
both the fuzzers (the cpp files that contain the fuzzing glue) and the
corpus.

We provide a script (`converter.py`) that parses unittests in order to
auto-generate both the fuzzers (in the libfuzzer's case this means the
`LLVMFuzzerTestOneInput()` function), and the corpus used as fuzzing
seed. The idea is to allow the user to signal the parts of the unittest
that are useful for fuzzing, including code that needs to be fuzzed
(in order to generate fuzzers), and the unittest buffers (which can be
used for the corpus).

* In order to signal the code that needs to be fuzzed, the unittest writer
can use the following syntax:

```
$ cat ISOBMFF-Tests/Parser_unittest.cpp
...
  // fuzzer::conv: begin
  ISOBMFF::Parser parser;
  parser.Parse(buffer);
  // fuzzer::conv: end
...
```

This tells the autogen script to put all the code between the
"fuzzer::conv: begin" and "fuzzer::conv: end" tags into a fuzzer
function (libfuzzer's `LLVMFuzzerTestOneInput()` function). The
script does a couple of other fixes, including copying the include
files, fixing the parameter names, and doing some minor namespace
adjustments. The latter should be formalizable if there is interest
in reusing the infra for another project.

* In order to signal the buffer(s) that can be used as seed, the unittest
writer can use the following syntax:

```
$ cat ISOBMFF-Tests/Parser_unittest.cpp
...
  // fuzzer::conv: data
  const std::vector<uint8_t> &buffer = {
      0x00, 0x00, 0x00, 0x18,
      0x66, 0x74, 0x79, 0x70,
      ...
  };
...
```

The script will look for C++-defined buffers, extract all the hexadecimal
constants, and put them into a binary file.


# Operation

(1) In order to re-generate a fuzzing files, use the converter script:

```
$ ./converter.py ../ISOBMFF-Tests/Parser_unittest.cpp ./
```

The script will parse the input file (`../ISOBMFF-Tests/Parser_unittest.cpp`)
and generate a similarly-named fuzzer (`Parser_fuzzer.cpp`) in the
output directory (`./`). It will also generate some cases in the per-fuzzer
corpus directory (`corpus/Parser_fuzzer/unittest.*.bin`).

(2) Build the excutable
* After build of ISOBMFF main project
```
$ cd fuzz
$ make
```

(3) In order to run the fuzzers, use:

```
$ cd fuzz
$ make fuzz
...
```

This will run each of the generated fuzzers a fixed number of times, and
produce new cases in the per-fuzzer corpus directory.
