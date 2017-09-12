--- Paths are local -- 
local basic = dofile(system.prependAbsolutePath("basic.lua"))
local inspect = dofile(system.prependAbsolutePath("inspect.lua"))

--local currentDemo = "Basic"

imgui.setFontSize(24)
sdl2.setWindowSize(32, 32, 1920, 1080)


function render()
   video.clear(0.5,0.5,0.5)
   imgui.newFrame();
   basic.render();
   imgui.render()
   video.present()
end
	