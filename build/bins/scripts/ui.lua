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
-- Display a window with an editable matrix view,
-- Args:
--    @title:   (string)
--    @matrix:  (gml.mat4)
-- Returns:
--    The modified matrix
-- Notes:
--    Matrix is COLUMN MAJOR
-----------------------------------------------------

ui.matrixEdit = function(title, matrix)
   imgui.begin(title)

   --- Matrix View
   imgui.text("Matrix:")
   local id=1
   for y=1, 4 do
      for x=1, 4 do
         imgui.pushItemWidth(100)
         imgui.pushID(id)
         _, v = imgui.inputFloat("", matrix[x][y])
         imgui.popID(id)
         if x % 4 ~= 0 then imgui.sameLine(0, 10) end
         imgui.popItemWidth()
         id = id + 1
      end
   end

   --- Controls
   imgui.text("Controls:")

   imgui.sliderFloat("X ", matrix[1][1], -3.0, 3.0, "%.3f", 1)
   imgui.sliderFloat("Y ", matrix[2][2], -3.0, 3.0, "%.3f", 1)
   imgui.sliderFloat("Z ", matrix[3][3], -3.0, 3.0, "%.3f", 1)

   imgui._end()
end

return ui;
