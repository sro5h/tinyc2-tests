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
                buildoptions { "-Wpedantic", "-Wall" }

        filter "configurations:Release"
                defines { "_RELEASE" }
                symbols "Off"
                links { "sfml-system", "sfml-window", "sfml-graphics" }
                buildoptions { "-Wpedantic", "-Wall" }

project "AABBToPolygon"
        files { "aabb/AABBToPolygon.cpp" }

project "AABBToRay"
        files { "aabb/AABBToRay.cpp" }

project "AABBToCapsule"
        files { "aabb/AABBToCapsule.cpp" }

project "CapsuleToCapsule"
        files { "capsule/CapsuleToCapsule.cpp" }

project "CapsuleToPolygon"
        files { "capsule/CapsuleToPolygon.cpp" }

project "CircleToAABB"
        files { "circle/CircleToAABB.cpp" }

project "CircleToCapsule"
        files { "circle/CircleToCapsule.cpp" }

project "CircleToCircle"
        files { "circle/CircleToCircle.cpp" }

project "CircleToRay"
        files { "circle/CircleToRay.cpp" }

project "CircleToPolygon"
        files { "circle/CircleToPolygon.cpp" }

project "PolygonToRay"
        files { "polygon/PolygonToRay.cpp" }

project "RayToAABB"
        files { "ray/RayToAABB.cpp" }

project "RayToCapsule"
        files { "ray/RayToCapsule.cpp" }

project "RayToCircle"
        files { "ray/RayToCircle.cpp" }

project "RayToPoly"
        files { "ray/RayToPoly.cpp" }

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
