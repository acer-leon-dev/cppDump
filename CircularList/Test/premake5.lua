project "LinkedListTest"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++17"
    targetdir ("../bin/" .. outputdir .. "/%{prj.name}")
    objdir ("../bin/obj/" .. outputdir .. "/%{prj.name}")

    includedirs {
        "../LinkedList/include"
    }

    files {
        "src/test.cpp" 
    }

    filter "configurations:Debug"
        defines { "DEBUG" }
        symbols "On"

    filter "configurations:Release"
        defines { "NDEBUG" }
        optimize "On"