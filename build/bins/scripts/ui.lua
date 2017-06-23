local inspect = require "scripts/lib/inspect"
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

-----------------------------------------------------------------------------
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
--    this method.  We use it internally to cache the winState
--    of the translate / scale / rotate sliders.
-----------------------------------------------------------------------------
do
   local fnState = {}
   ui.matrixEdit = function(title, data)
      assert(type(title) == 'string', "arg[1] should be the window title")
      assert(type(data) == 'table', "Expected { {uniformName=, tabName=, matrix=,}, {...}})")
      assert(#data >= 1, "")

      --
      -- winState
      --

      local winState, activeTab
      if not fnState[title] then
         fnState[title] = {}
         winState = fnState[title]
         winState.activeTab = 1
         for i=1, #data do
            local id = data[i].matrix:address()
            if not fnState[id] then
               fnState[id] = {}
               fnState[id][i] = {}
               fnState[id][i].translate = gml.vec3.new(0,0,0)
               fnState[id][i].scale     = gml.vec3.new(1,1,1)
               fnState[id][i].rotate    = gml.vec3.new(0,0,0)
            end
         end
      end

      -- setup local variables --
      winState = fnState[title]
      local activeTab = winState.activeTab
      local matrix    = data[activeTab].matrix
      local translate = fnState[matrix:address()][activeTab].translate
      local rotate    = fnState[matrix:address()][activeTab].rotate
      local scale     = fnState[matrix:address()][activeTab].scale
      if not winState[matrix:address()] then
         winState[matrix:address()] = {}
         if not winState[matrix:address()].original then
            winState[matrix:address()].original = gml.deepcopy(matrix)
         end
      end

      local original = winState[matrix:address()].original

      --
      -- ui
      --

      imgui.begin(title)

      -- draw tabs for user to select
      for i=1, #data do
         if imgui.button(data[i].tabName) then
            winState.activeTab = i
         end
         imgui.sameLine(0, 10)
      end

      imgui.text("(" .. data[activeTab].tabName .. ")")
      imgui.newLine()

      -- draw the selected panel imgui.text("Matrix:")
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

      local drawElements = {
         {'Translate (xyz)', translate,},
         {'Rotate (xyz)',    rotate,   },
         {'Scale (xyz)',     scale,    }
      }

      imgui.text("Address: " .. matrix:address())

      local dimen = {"X", "Y", "Z"}
      local updateMatrix = false;

      for i=1, #drawElements do
         imgui.text(drawElements[i][1])
         for d=1, #dimen do
            imgui.pushID(d)
            if imgui.sliderFloat("##" .. drawElements[i][1] .. title, drawElements[i][2][d], -10.0, 10.0, "%f", 1)
               and not updateMatrix then
               updateMatrix = true
            end
            imgui.popID(d)
            imgui.sameLine(0,10)
            if imgui.inputFloat("##" .. drawElements[i][1]  .. title .. d, drawElements[i][2][d]) then
               updateMatrix = true
            end
            imgui.sameLine(0,100)
            if imgui.button("Auto") then
               print("honey")
            end
         end
      end

      --- generate a new transformation matrix for the active matrix
      if updateMatrix then
         matrix.assign = original * (gml.translate(translate) * gml.rotate(rotate) * gml.scale(scale))
      end

      imgui._end()
   end
end

return ui
