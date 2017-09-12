local basic = {}

local ui = dofile(system.prependAbsolutePath("ui.lua"))

local human = {
   shader = gl.Shader.new {
               vertex   = system.prependAbsolutePath("models\\basic.vs"),
               fragment = system.prependAbsolutePath("models\\basic.fs")
            },
   obj = gl.Model.loadFromWavefront {
               filename    = 'human.obj',
               baseDir     = system.prependAbsolutePath('models\\human'),
              -- instanced   = true, disable instancing for now it makes the models look like slenderman on windows
            },
}

local suzanne = {
  shader = gl.Shader.new {
               vertex   = system.prependAbsolutePath("models\\basic.vs"),
               fragment = system.prependAbsolutePath("models\\basic.fs")
            },

   obj = gl.Model.loadFromWavefront {
               filename    = 'suzanne.obj',
               baseDir     = system.prependAbsolutePath('models\\suzanne'),
            }
}

local teapot = {
  shader = gl.Shader.new {
               vertex   = system.prependAbsolutePath("models\\basic.vs"),
               fragment = system.prependAbsolutePath("models\\basic.fs")
            },

   obj = gl.Model.loadFromWavefront {
               filename    = 'teapot.obj',
               baseDir     = system.prependAbsolutePath('models\\teapot'),
            },
}


-- setup matrices
local proj = gml.perspective(120, 19, 0.1, 50)
local view = gml.lookAt(gml.vec3.new(0, 0, 5),
                        gml.vec3.new(0,0,0),
                        gml.vec3.new(0,1,0))

human.view     = view
suzanne.view   = view
teapot.view    = view
human.proj     = proj
suzanne.proj   = proj
teapot.proj    = proj
human.model    = human.obj:getTransformationMatrix()
suzanne.model  = suzanne.obj:getTransformationMatrix()
teapot.model   = teapot.obj:getTransformationMatrix()


basic.render = function()
   human.shader:upload {
      { name = 'proj',  data = human.proj},
      { name = 'view',  data = human.view},
      { name = 'model', data = human.model},
   }
   human.obj:render()

   suzanne.shader:upload {
      { name = 'proj',  data = suzanne.proj},
      { name = 'view',  data = suzanne.view},
      { name = 'model', data = suzanne.model},
   }
   suzanne.obj:render()

   teapot.shader:upload {
      { name = 'proj',  data = teapot.proj},
      { name = 'view',  data = teapot.view},
      { name = 'model', data = teapot.model},
   }
   teapot.obj:render()

   -- draw objects (glDrawArrays glDrawElements)
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

   ui.matrixEdit ("Teapot", {
      { uniformName = 'proj',  tabName = 'Projection', matrix = teapot.proj},
      { uniformName = 'view',  tabName = 'View',       matrix = teapot.view},
      { uniformName = 'model', tabName = 'Model',      matrix = teapot.model}
   })

end

return basic