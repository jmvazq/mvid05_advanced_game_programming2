local project_list = {
    "AG_01",
    "EJ0"
}

local function new_project(name)
    project(name)
        kind("ConsoleApp")
        includedirs {
            "include"
        }
        files {
            "tests/"..name.."/*.cpp",
            "tests/"..name.."/*.h",
            "src/*.cpp"
        }
        vpaths {
            ["Headers"] = "include/*.h",
            ["Tests"] = {
                "tests/"..name.."/*.cpp",
                "tests/"..name.."/*.h"
            },
            ["Source"] = "src/*.cpp"
        }
        configuration {"debug"}
            flags {"Symbols"}
            targetsuffix ("_d")
        configuration {"release"}
            flags {"Optimize"}
            targetsuffix ("_r")
        configuration {"windows"}
            flags {"NoEditAndContinue"}
            windowstargetplatformversion "10.0.17134.0"
end

solution "05MVID_Classes"
    configurations  {"debug", "release"}
    language        ("c++")
    platforms       {"x64"}
    location        ("build")
    debugdir        ("build")
    targetdir       ("bin")
    flags           {"ExtraWarnings"}

for k,v in pairs(project_list) do
    new_project(v)
end