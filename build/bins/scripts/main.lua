local inspect = require "scripts/inspect"
local      ui = require "scripts/ui"

local shader = gl.Shader.new {
                  vertex   = "./models/suzanne/suzanne.vs",
                  fragment = "./models/suzanne/suzanne.fs"
               }

local monkey = gl.Model.loadFromWavefront {
                  filename    = 'suzanne.obj',
                  baseDir     = './models/suzanne',
              }

imgui.setFontSize(30)
sdl2.setWindowSize(1000, 800, 800, 600)
monkey:setScale(gl.vec3.new(0.5,0.5,0.5))

local proj  = gl.mat4.projection(120, 16/9, 0.1, 50)
local view  = gl.mat4.identity()
local model = monkey:getTransformationMatrix()

function render()
   video.setViewport()
   video.clear(0.3,0.3,0.3)
   shader:upload {
      { name = 'proj',  data = gl.mat4.projection(120, 16/9, 0.1, 100)},
      { name = 'view',  data = gl.mat4.identity()},
      { name = 'model', data = monkey:getTransformationMatrix()},
   }

   monkey:render()
   imgui.newFrame()
      print(inspect(proj[1]))
      --proj  = ui.matrixEdit("Proj",  gl.mat4.toVector(gl.mat4.projection(120, 16/9, 0.1, 100)));
      --view  = ui.matrixEdit("View",  gl.mat4.toVector(gl.mat4.identity()));
      --model = ui.matrixEdit("Model", gl.mat4.toVector(monkey:getTransformationMatrix()))
   imgui.render()

   video.present()
end
