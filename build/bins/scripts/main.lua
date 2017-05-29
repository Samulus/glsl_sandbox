-- setup glsl
local shader = gl.Shader.new {
                  vertex   = "./models/suzanne/suzanne.vs",
                  fragment = "./models/suzanne/suzanne.fs"
               }

-- setup model
local model = gl.Model.loadFromWavefront {
                  filename    = 'suzanne.obj',
                  baseDir     = './models/suzanne/',
              }

-- setup projection matrix
imgui.setFontSize(30)
sdl2.setWindowSize(1000, 800, 1920, 1080)

function ui()
   imgui.newFrame()
   imgui.enableSoftwareMouse()
   --imgui.showTestWindow(true)
   imgui.render()
end

function monkey()
   shader:upload {
      { name = 'proj',  data = gl.mat4.projection(45, 16/9, 0.1, 25)},
      { name = 'view',  data = gl.mat4.identity()},
      { name = 'model', data = model:getTransformationMatrix()},
   }
   model:render()
end

function render()
   video.setViewport()
   video.clear(0.3,0.3,0.3)
   monkey()
   ui()
   video.present()
end
