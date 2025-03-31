project "exampletest"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++23"
    targetdir ("%{wks.location}/bin/" .. testsdir .. "/%{prj.name}")
    objdir ("%{wks.location}/bin/int/" .. testsdir .. "/%{prj.name}")
    
    includedirs {
        IncludeDir["vectorimpl"],
        IncludeDir["googletest"],
    }

    links {
        "Vectorimpl",
        "googletest",
    }

    links {
        "projectname"
    }

    files {
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
