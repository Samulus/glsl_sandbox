local inspect = require "scripts/inspect"
local      ui = require "scripts/ui"

local shader = gl.Shader.new {
                  vertex   = "./models/human/human.vs",
                  fragment = "./models/human/human.fs"
               }

local monkey = gl.Model.loadFromWavefront {
                  filename    = 'human.obj',
                  baseDir     = './models/human',
              }

imgui.setFontSize(30)
sdl2.setWindowSize(30, 30, 3340, 1800)
monkey:setScale(gml.vec3.new(0.5,0.5,0.5))

local proj  = gml.perspective(120, 16/9, 0.1, 50)
local view  = gml.lookAt(
      gml.vec3.new(0, 0, 5),
      gml.vec3.new(0,0,0),
      gml.vec3.new(0,1,0)
      )

local model = monkey:getTransformationMatrix()

function render()
   video.setViewport()
   video.clear(0.0,0.0,0.0)

   shader:upload {
      { name = 'proj',  data = proj},
      { name = 'view',  data = view},
      { name = 'model', data = model},
   }

   monkey:render()


   imgui.newFrame()
   ui.globalMenu()
   imgui.showTestWindow()
      ui.matrixEdit("Proj",  proj)
      ui.matrixEdit("View",  view)
      ui.matrixEdit("Model", model)
   imgui.render()
   video.present()
end
