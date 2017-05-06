-- create fbo
local fbo = gl.Framebuffer.new()

--- setup MRT textures for deferred shading
fbo:addTexture {
   name     = 'position',
   location = 0,
   options  = {
      gpuFormat   = gl.enum.RGB16F,
      cpuFormat   = gl.enum.RGB,
      cpuDataType = gl.enum.FLOAT,
   },
}

function render()
   fbo:bind()
   fbo:unbind()

   imgui.NewFrame()
   imgui.Begin("Hi", true, 0)
   imgui.EnableSoftwareMouse()
   imgui.ShowTestWindow(true)
   imgui.End()
   imgui.Render();
end
