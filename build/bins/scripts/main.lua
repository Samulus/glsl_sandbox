local inspect = require "scripts/inspect"
local      ui = require "scripts/ui"
local   human = require "scripts/human"
local suzanne = require "scripts/suzanne"

imgui.setFontSize(24)
sdl2.setWindowSize(1000, 1000, 1280, 720)

local proj = gml.perspective(120, 16/9, 0.1, 50)
local view = gml.lookAt(
                 gml.vec3.new(0, 0, 5),
                 gml.vec3.new(0,0,0),
                 gml.vec3.new(0,1,0)
              )

human.view   = view
suzanne.view = view
human.proj   = proj
suzanne.proj = proj

function render()
   video.setViewport()
   video.clear(0.5,0.5,0.5)

   human.render()
   suzanne.render()

   imgui.newFrame()

   ui.matrixEdit ("Human", {
      { uniformName = 'proj',  tabName = 'Projection', matrix = human.proj},
      { uniformName = 'view',  tabName = 'View',       matrix = human.view},
      { uniformName = 'model', tabName = 'Model',      matrix = human.model}
   })

   ui.matrixEdit ("Suzanne", {
      { uniformName = 'proj',  tabName = 'Projection', matrix = suzanne.proj},
      { uniformName = 'view',  tabName = 'View',       matrix = suzanne.view},
      { uniformName = 'model', tabName = 'Model',      matrix = suzanne.model}
   })

   imgui.render()
   video.present()
end
