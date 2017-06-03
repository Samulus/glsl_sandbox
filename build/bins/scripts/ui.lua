local ui = {}

function globalMenu()
   imgui.newFrame()
   imgui.enableSoftwareMouse()

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

   imgui.render()
   return item;
end

-----------------------------------------------------
-- Display a window with an editable matrix view,
-- Args:
--    Title: (string)
--    mat4:  (float[16])
-- Returns:
--    The modified matrix
-----------------------------------------------------

ui.matrixEdit = function(title, mat4)
   imgui.begin(title)
   for i=1, 16 do
      imgui.pushItemWidth(100)
      imgui.pushID(i)
      _, mat4[i] = imgui.inputFloat("", mat4[i])
      imgui.popID(i)
      if i % 4 ~= 0 then
         imgui.sameLine(0, 10)
      end
      imgui.popItemWidth()
   end

   imgui._end()

   return mat4
end

return ui;
