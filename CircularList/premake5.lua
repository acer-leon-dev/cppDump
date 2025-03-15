-- premake5.lua
workspace "LinkedList"
    configurations { "Debug", "Release" }

outputdir = "%{cfg.system}-%{cfg.architecture}-%{cfg.buildcfg}"

include "Test"
