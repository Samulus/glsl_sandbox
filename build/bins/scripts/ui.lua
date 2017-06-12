local inspect = require "scripts/inspect"
local ui = {}

-----------------------------------------------------
-- Display a global menu
-----------------------------------------------------

ui.globalMenu = function()
   local item;
   if imgui.beginMainMenuBar() then
      if imgui.beginMenu("Matrices") then
         if imgui.menuItem("Proj",  false, true) then item = "Proj"  end
         if imgui.menuItem("View",  false, true) then item = "View"  end
         if imgui.menuItem("Model", false, true) then item = "Model" end
         imgui.endMenu()
      end
      imgui.endMainMenuBar()
   end
   return item;
end

-----------------------------------------------------
-- Matrix 4x4 Manipulator View
-- Args:
--    @title Window Title
--    @data: An array of tables in the following format:
--       local data = {
--          { uniformName = 'proj',  tabName = 'Projection', matrix = proj},
--          { uniformName = 'view',  tabName = 'View',       matrix = view},
--          { uniformName = 'model', tabName = 'Model',      matrix = model}
--          { ... }
--       }
-- Warnings:
--    The 'title' parameter must be unique for every invocation of
--    this method.  We use it internally to cache the state
--    of the translate / scale / rotate sliders.
-----------------------------------------------------
do
   local state = {}
   ui.matrixEdit = function(title, data)
      assert(type(title) == 'string', "arg[1] should be the window title")
      assert(type(data) == 'table', "Expected { {uniformName=, tabName=, matrix=,}, {...}})")
      assert(#data >= 1, "")

      imgui.begin(title)

      -- generate the vectors for matrix manipulation
      if not state[title] then
         state[title] = {}
         state[title].activeTab = 1
         for i=1, #data do
            state[title][i] = {}
            state[title][i].translate = gml.vec3.new(0,0,0)
            state[title][i].scale     = gml.vec3.new(1,1,1)
            state[title][i].rotate    = gml.vec3.new(0,0,0)
            state[title][i].pi        = 0
         end
      end

      -- allow user to click on tabs to switch them
      for i=1, #data do
         if imgui.button(data[i].tabName) then
            state[title].activeTab = i
            break;
         end
         imgui.sameLine(0, 10)
      end

      local matrix = data[state[title].activeTab].matrix

      -- generate the 'original matrix',
      -- We ca nuse the address
      if not state[title][matrix:address()] then
         state[title][matrix:address()] = {}
         if not state[title][matrix:address()].original then
            state[title][matrix:address()].original  = gml.deepcopy(matrix)
         end
      end

      -- draw the selected panel
      imgui.text("Matrix:")
      local id = 1
      for y=1, 4 do
         for x=1, 4 do
            imgui.pushItemWidth(100)
            imgui.pushID(id)
            imgui.inputFloat("##" .. title, matrix[x][y])
            imgui.popID(id)
            if x % 4 ~= 0 then
               imgui.sameLine(0, 10)
            end
            imgui.popItemWidth()
            id = id + 1
         end
      end

      local translate = state[title][state[title].activeTab].translate
      local rotate    = state[title][state[title].activeTab].rotate
      local scale     = state[title][state[title].activeTab].scale

      -- draw scale / rotate / translate controls for the selected matrix
      imgui.text("Translate:")
      a = imgui.sliderFloat("X##trans" .. title, translate[1], -5.0, 5.0, "%f", 4)
      b = imgui.sliderFloat("Y##trans" .. title, translate[2], -5.0, 5.0, "%f", 4)
      c = imgui.sliderFloat("Z##trans" .. title, translate[3], -5.0, 5.0, "%f", 4)

      imgui.text("Rotate:")
      d = imgui.sliderFloat("X##rotate" .. title, rotate[1], -5.0, 5.0, "%f", 4)
      e = imgui.sliderFloat("Y##rotate" .. title, rotate[2], -5.0, 5.0, "%f", 4)
      f = imgui.sliderFloat("Z##rotate" .. title, rotate[3], -5.0, 5.0, "%f", 4)

      imgui.text("Scale:")
      g = imgui.sliderFloat("X##scale" .. title, scale[1], -5.0, 5.0, "%f", 4)
      h = imgui.sliderFloat("Y##scale" .. title, scale[2], -5.0, 5.0, "%f", 4)
      i = imgui.sliderFloat("Z##scale" .. title, scale[3], -5.0, 5.0, "%f", 4)

      -- add an auto rotate button --
      --if imgui.button("Auto Rotate") then
      if data[state[title].activeTab].tabName == 'View' then
         local pi = state[title][state[title].activeTab]
         local x, y = math.cos(os.clock()), math.sin(os.clock())
         rotate[1] = x
         rotate[3] = y
      end

      --- generate a new transformation matrix for the active matrix
      local original = state[title][matrix:address()].original
      --if a or b or c or d or e or f or g or h or i then
         matrix.assign = original * (gml.rotate(rotate) * gml.translate(translate) * gml.scale(scale))
      --end

      imgui._end()
   end
end

return ui
