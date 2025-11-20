# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "C:/GS_Labor/ITS-BRD-VSC/Programs/TestGS1/tmp/TestGS1.Debug+ITSboard"
  "C:/GS_Labor/ITS-BRD-VSC/Programs/TestGS1/tmp/1"
  "C:/GS_Labor/ITS-BRD-VSC/Programs/TestGS1/tmp/TestGS1.Debug+ITSboard"
  "C:/GS_Labor/ITS-BRD-VSC/Programs/TestGS1/tmp/TestGS1.Debug+ITSboard/tmp"
  "C:/GS_Labor/ITS-BRD-VSC/Programs/TestGS1/tmp/TestGS1.Debug+ITSboard/src/TestGS1.Debug+ITSboard-stamp"
  "C:/GS_Labor/ITS-BRD-VSC/Programs/TestGS1/tmp/TestGS1.Debug+ITSboard/src"
  "C:/GS_Labor/ITS-BRD-VSC/Programs/TestGS1/tmp/TestGS1.Debug+ITSboard/src/TestGS1.Debug+ITSboard-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "C:/GS_Labor/ITS-BRD-VSC/Programs/TestGS1/tmp/TestGS1.Debug+ITSboard/src/TestGS1.Debug+ITSboard-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "C:/GS_Labor/ITS-BRD-VSC/Programs/TestGS1/tmp/TestGS1.Debug+ITSboard/src/TestGS1.Debug+ITSboard-stamp${cfgdir}") # cfgdir has leading slash
endif()
