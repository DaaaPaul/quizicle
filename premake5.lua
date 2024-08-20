workspace "quizicle"
	configurations "Debug"

project "quizicle"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++20"
	files {"**.cpp", "**.h"}
	targetdir "bin/%{cfg.buildcfg}"

	filter "configurations:Debug"
		defines "DEBUG"
		symbols "On"
