-- premake5.lua
workspace "Mathlang"
   architecture "x64"
   configurations { "Debug", "Release" }

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

project "HexatridecimalGenerator"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++23"
    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin/obj/" .. outputdir .. "/%{prj.name}")
    targetname "hexatridecimal"

    files {  
        "src/**.cpp" 
    }

    filter "configurations:Debug"
        defines { "DEBUG" }
        symbols "On"

    filter "configurations:Release"
        defines { "NDEBUG" }
        optimize "On"