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
                  cat  = './models/suzanne'
              }

--("suzanne.obj", "./models/suzanne")
--model:useVertexShader(vert);
--model:useFragmentShader(frag);

-- setup camera
--local camera = gl.Camera.new()
--camera:translate()
--]]

function render()
   fbo:bind()
   --model:render()
   fbo:unbind()

   imgui.NewFrame()
   --imgui.Begin("Hi", true, 0)
   imgui.EnableSoftwareMouse()
   imgui.ShowTestWindow(true)
   --imgui.End()
   imgui.Render();
end
