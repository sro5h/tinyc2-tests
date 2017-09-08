-- Make gmake the default action
if not _ACTION then
        _ACTION = "gmake"
end

workspace "Tests"
        configurations { "Debug", "Release" }
        kind "ConsoleApp"
        language "C++"
        basedir "build"
        includedirs { "." }

        filter "configurations:Debug"
                defines { "_DEBUG" }
                symbols "On"
                links { "sfml-system", "sfml-window", "sfml-graphics" }

        filter "configurations:Release"
                defines { "_RELEASE" }
                symbols "Off"
                links { "sfml-system", "sfml-window", "sfml-graphics" }

project "AabbToPolygon"
        files { "aabb/AabbToPolygon.cpp" }

project "CircleToCircle"
        files { "circle/CircleToCircle.cpp" }

project "CircleToPolygon"
        files { "circle/CircleToPolygon.cpp" }

project "RayToAabb"
        files { "ray/RayToAabb.cpp" }

project "RayToCircle"
        files { "ray/RayToCircle.cpp" }

project "RayToPolygon"
        files { "ray/RayToPolygon.cpp" }

-- Removes all generated and compiled files
newaction {
        trigger = "clean",
        description = "Clean the software.",
        execute = function ()
                os.rmdir("./build")
                os.rmdir("./bin")
                os.rmdir("./obj")
                os.remove("./Makefile")
                os.remove("./*.make")
                print("Done.")
        end
}
