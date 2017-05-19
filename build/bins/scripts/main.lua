-- setup MRT textures for deferred shading
local fbo = gl.Framebuffer.new()
fbo:addTexture {
   name     = 'position',
   location = 0,
   options  = {
      gpuFormat   = gl.enum.RGB16F,
      cpuFormat   = gl.enum.RGB,
      cpuDataType = gl.enum.FLOAT,
   },
}

-- setup glsl
-- Note: paths are relative to the BINARY, not this script
local shader = gl.Shader.new {
                  vertex   = "./models/suzanne/suzanne.vs",
                  fragment = "./models/suzanne/suzanne.fs"
               }

-- setup model
local model = gl.Model.loadFromWavefront {
                  filename = 'suzanne.obj',
                  baseDir  = './models/suzanne'
              }

imgui.setFontSize(24)
sdl2.setWindowSize(1000, 800, 1920, 1080)

function render()
   imgui.newFrame()
   imgui.enableSoftwareMouse()
   imgui.showTestWindow(true)
   imgui.render()

   fbo:bind()
   model:bind()
   shader:bind()
   shader:upload {
      { name = 'position', size = gl.enum.VEC3, data = model:getPosition()},
      { name = 'scale',    size = gl.enum.VEC3, data = model:getScale()},
      { name = 'rotation', size = gl.enum.VEC3, data = model:getRotation()},
   }
   model:render()
   shader:unbind()
   fbo:unbind()
   --fbo:render()
end
