local basic = require "scripts/demos/basic"
local prism = require "scripts/demos/basic"
local currentDemo = "Basic"

imgui.setFontSize(24)
sdl2.setWindowSize(32, 32, 3000, 2400)

function render()
   video.setViewport()
   video.clear(0.5,0.5,0.5)

   imgui.newFrame()
   imgui.begin("Demos:")
      if imgui.button("Basic") then currentDemo = "Basic" end
      if imgui.button("Prism") then currentDemo = "Prism" end
   imgui._end()

   if currentDemo == "Basic" then basic.render() end

   imgui.render()
   video.present()
end
