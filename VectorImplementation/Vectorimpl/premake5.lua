project "Vectorimpl"
    kind "StaticLib"
    language "C++"
    cppdialect "C++23"
    targetdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
    objdir ("%{wks.location}/bin/int/" .. outputdir .. "/%{prj.name}")
    
    includedirs {
        "include",
        "src",
    }

    files { 
        "include/**.hpp",
        "src/**.cpp",
        "src/**.hpp",
        "src/**.h",
        "src/**.c",
    }

    filter "toolset:gcc or clang"
        buildoptions {
            "-Wall",
            "-Wextra",
            "-Wno-unused",
        }

    filter "configurations:Debug"
        defines { "DEBUG" }
        symbols "On"

    filter "configurations:Release"
        defines { "NDEBUG" }
        optimize "On"