local human = {}

human.shader = gl.Shader.new {
                  vertex   = "./models/human/human.vs",
                  fragment = "./models/human/human.fs"
               }

human.obj    = gl.Model.loadFromWavefront {
                  filename    = 'human.obj',
                  baseDir     = './models/human',
              }

human.model = human.obj:getTransformationMatrix()

human.render = function()
   human.shader:upload {
      { name = 'proj',  data = human.proj},
      { name = 'view',  data = human.view},
      { name = 'model', data = human.model},
   }

   human.obj:render()
end



return human
