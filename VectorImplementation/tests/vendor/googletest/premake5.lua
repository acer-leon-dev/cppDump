project "googletest"
	kind "StaticLib"
	language "C++"
	targetdir ("%{wks.location}/bin/" .. outputdir .. "/%{cfg.shortname}/")
	objdir ("%{wks.location}/bin-int/" .. outputdir .. "/%{prj.name}_%{cfg.shortname}/")
        
        -- This premake file is relative to googletest/ directory
	files {
		"src/**.h", -- <googletest_repo_root>/googletest/src/
		"src/**.cc",  -- <googletest_repo_root/googletest/src/
		"include/**.h"  -- <googletest_repo_root/googletest/include/
	}

	includedirs {
		".", -- <googletest_repo_root/googletest/
		"include",  -- <googletest_repo_root/googletest/include

	}


	-- -------------------------------|All Platforms|------------------------------- --
	filter{}
	filter "configurations:Debug"
		defines "DEBUG"
		runtime "Debug"
		symbols "on"

	filter{}
	filter "configurations:PreRelease"
		defines "NDEBUG"
		runtime "Release"
		optimize "on"

	filter{}
	filter "configurations:Release"
		defines "NDEBUG"
		runtime "Release"
		optimize "on"
	-- -------------------------------|All Platforms|------------------------------- --


	filter{}
	filter "toolset:gcc or clang"
		buildoptions {
			"-Wall", "-Wshadow", "-Wno-error=dangling-else", 
			"-fno-exceptions", "-fno-rtti"
		}
		defines {
			"GTEST_HAS_RTTI=0"
		}
	
	filter{}
	filter "toolset:msc"
		buildoptions {
			"/GS", "/W4", "/WX", "/wd4251", "/wd4275", "/nologo", "/J",
			"/EHs/c/", "/GR/", "/wd4702", "/utf-8"
		}

	-- ----------------------------------|Windows|---------------------------------- --
	filter{}
	filter "system:Windows"
		defines {
			"_HAS_EXCEPTIONS=0",
			"UNICODE",
			"_UNICODE",
			"WIN32",
			"_WIN32",
			"GTEST_OS_WINDOWS"
		}
	-- ----------------------------------|Windows|---------------------------------- --


	-- -----------------------------------|Linux|----------------------------------- --
	filter{}
	filter "system:Linux"
		pic "On"
		defines {
			"GTEST_OS_LINUX"
		}
	-- -----------------------------------|Linux|----------------------------------- --