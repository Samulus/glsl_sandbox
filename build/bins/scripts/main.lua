-- setup MRT textures for deferred shading
local fbo = gl.Framebuffer.new()
fbo:addTexture {
   name     = 'position',
   location = 0,
   options  = {
      gpuFormat   = gl.RGB16F,
      cpuFormat   = gl.RGB,
      cpuDataType = gl.FLOAT,
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
                  filename    = 'suzanne.obj',
                  baseDir     = './models/suzanne',
                  triangulate = true,
                  attributes  = {
                     gl.GLAttrib.Position,
                     gl.GLAttrib.Normal,
                     gl.GLAttrib.Color,
                  }
              }

imgui.setFontSize(32)
sdl2.setWindowSize(1000, 800, 1920, 1080)

function render()
   imgui.newFrame()
   imgui.enableSoftwareMouse()
   imgui.showTestWindow(true)
   imgui.render()

   fbo:bind()
   --model:bind()
   shader:bind()
   shader:upload {
      { name = 'position', vec3 = model:getPosition()},
      { name = 'scale',    vec3 = model:getScale()},
      { name = 'rotation', vec3 = model:getRotation()},
   }
   --model:render()
   shader:unbind()
   fbo:unbind()
   --fbo:render()
end
