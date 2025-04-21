workspace "BoostRegexTest"
    configurations { "Debug", "Release" }

project "BoostRegexTest"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++23"

    targetname "regextest"
    targetdir "bin"
    objdir "bin/obj"
    
    files { 
        "pch.hpp",
        "regex.cpp"
    }

    pchheader "pch.hpp"

    filter { "configurations:Debug" }
        defines { "DEBUG" }
        symbols "On"

    filter { "configurations:Release" }
        defines { "NDEBUG" }
        optimize "On"