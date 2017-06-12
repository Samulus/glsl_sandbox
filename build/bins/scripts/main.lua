local inspect = require "scripts/inspect"
local      ui = require "scripts/ui"
local   human = require "scripts/human"
local suzanne = require "scripts/suzanne"

imgui.setFontSize(30)
sdl2.setWindowSize(30, 30, 3380, 2000)

local proj = gml.perspective(120, 16/9, 0.1, 50)
local view = gml.lookAt(
                 gml.vec3.new(0, 0, 5),
                 gml.vec3.new(0,0,0),
                 gml.vec3.new(0,1,0)
              )

human.view   = view;
suzanne.view = view;
human.proj   = proj;
suzanne.proj = proj;


function render()
   video.setViewport()
   video.clear(0.0,0.0,0.0)

   human.render()
   suzanne.render()

   imgui.newFrame()

   --print(suzanne.proj)

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
