local suzanne = {}

suzanne.shader = gl.Shader.new {
                  vertex   = "./models/suzanne/suzanne.vs",
                  fragment = "./models/suzanne/suzanne.fs"
               }

suzanne.obj    = gl.Model.loadFromWavefront {
                  filename    = 'suzanne.obj',
                  baseDir     = './models/suzanne',
              }

suzanne.model = suzanne.obj:getTransformationMatrix()

suzanne.render = function()
   suzanne.shader:upload {
      { name = 'proj',  data = suzanne.proj},
      { name = 'view',  data = suzanne.view},
      { name = 'model', data = suzanne.model},
   }

   suzanne.obj:render()
end



return suzanne
