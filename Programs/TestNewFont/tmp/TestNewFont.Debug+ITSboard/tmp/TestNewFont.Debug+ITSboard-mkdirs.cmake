# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION ${CMAKE_VERSION}) # this file comes with cmake

# If CMAKE_DISABLE_SOURCE_CHANGES is set to true and the source directory is an
# existing directory in our source tree, calling file(MAKE_DIRECTORY) on it
# would cause a fatal error, even though it would be a no-op.
if(NOT EXISTS "C:/GS_Labor/ITS-BRD-VSC/Programs/TestNewFont/tmp/TestNewFont.Debug+ITSboard")
  file(MAKE_DIRECTORY "C:/GS_Labor/ITS-BRD-VSC/Programs/TestNewFont/tmp/TestNewFont.Debug+ITSboard")
endif()
file(MAKE_DIRECTORY
  "C:/GS_Labor/ITS-BRD-VSC/Programs/TestNewFont/tmp/1"
  "C:/GS_Labor/ITS-BRD-VSC/Programs/TestNewFont/tmp/TestNewFont.Debug+ITSboard"
  "C:/GS_Labor/ITS-BRD-VSC/Programs/TestNewFont/tmp/TestNewFont.Debug+ITSboard/tmp"
  "C:/GS_Labor/ITS-BRD-VSC/Programs/TestNewFont/tmp/TestNewFont.Debug+ITSboard/src/TestNewFont.Debug+ITSboard-stamp"
  "C:/GS_Labor/ITS-BRD-VSC/Programs/TestNewFont/tmp/TestNewFont.Debug+ITSboard/src"
  "C:/GS_Labor/ITS-BRD-VSC/Programs/TestNewFont/tmp/TestNewFont.Debug+ITSboard/src/TestNewFont.Debug+ITSboard-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "C:/GS_Labor/ITS-BRD-VSC/Programs/TestNewFont/tmp/TestNewFont.Debug+ITSboard/src/TestNewFont.Debug+ITSboard-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "C:/GS_Labor/ITS-BRD-VSC/Programs/TestNewFont/tmp/TestNewFont.Debug+ITSboard/src/TestNewFont.Debug+ITSboard-stamp${cfgdir}") # cfgdir has leading slash
endif()
