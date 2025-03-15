-- premake5.lua
workspace "Login-Interface"
    configurations { "Debug", "Release" }

outputdir = "%{cfg.system}-%{cfg.architecture}-%{cfg.buildcfg}"

project "Login-Interface"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++17"
    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin/obj/" .. outputdir .. "/%{prj.name}")

    files { 
        "**.h", 
        "**.cpp" 
    }

    filter "configurations:Debug"
        defines { "DEBUG" }
        symbols "On"

    filter "configurations:Release"
        defines { "NDEBUG" }
        optimize "On"