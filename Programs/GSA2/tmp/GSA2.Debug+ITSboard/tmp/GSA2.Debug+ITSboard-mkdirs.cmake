# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "C:/GS_Labor/ITS-BRD-VSC/Programs/GSA2/tmp/GSA2.Debug+ITSboard"
  "C:/GS_Labor/ITS-BRD-VSC/Programs/GSA2/tmp/1"
  "C:/GS_Labor/ITS-BRD-VSC/Programs/GSA2/tmp/GSA2.Debug+ITSboard"
  "C:/GS_Labor/ITS-BRD-VSC/Programs/GSA2/tmp/GSA2.Debug+ITSboard/tmp"
  "C:/GS_Labor/ITS-BRD-VSC/Programs/GSA2/tmp/GSA2.Debug+ITSboard/src/GSA2.Debug+ITSboard-stamp"
  "C:/GS_Labor/ITS-BRD-VSC/Programs/GSA2/tmp/GSA2.Debug+ITSboard/src"
  "C:/GS_Labor/ITS-BRD-VSC/Programs/GSA2/tmp/GSA2.Debug+ITSboard/src/GSA2.Debug+ITSboard-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "C:/GS_Labor/ITS-BRD-VSC/Programs/GSA2/tmp/GSA2.Debug+ITSboard/src/GSA2.Debug+ITSboard-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "C:/GS_Labor/ITS-BRD-VSC/Programs/GSA2/tmp/GSA2.Debug+ITSboard/src/GSA2.Debug+ITSboard-stamp${cfgdir}") # cfgdir has leading slash
endif()
