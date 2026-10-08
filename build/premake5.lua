-- wizards1 build script. Shared logic lives in the ely-arcade-sdk submodule (sdk/).
dofile("../sdk/premake/arcade_sdk.lua")

arcade.prepare_dirs()
arcade.workspace("wizards1")
arcade.raylib_project()
arcade.sdk_project("../sdk")
arcade.app_project("wizards1", "../src", "../sdk")