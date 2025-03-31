workspace "Vectorimpl"
   architecture "x64"
   configurations { 
      "Debug",
      "Release"
   }
   flags {
      "MultiProcessorCompile"
   }

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"
testsdir = outputdir .. "/tests"

IncludeDir = {}
IncludeDir["vectorimpl"] = "%{wks.location}/Vectorimpl/include"
IncludeDir["googletest"] = "%{wks.location}/tests/vendor/googletest/include"

include "Vectorimpl"

group "dependencies"
   include "tests/vendor/googletest"
group ""

group "tests"
   include "tests/unit/exampletest"
group ""