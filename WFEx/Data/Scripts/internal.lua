print("Script started.")

-- Print anything - including nested tables
local function table_print (tt, indent, done)
  done = done or {}
  indent = indent or 0
  if type(tt) == "table" then
    for key, value in pairs (tt) do
      -- io.write(string.rep (" ", indent)) -- indent it
      if type (value) == "table" and not done [value] then
        done [value] = true
        print(string.rep (" ", indent) .. string.format("[%s] => table", tostring (key)));
        print(string.rep (" ", indent) .. string.rep (" ", indent+4) .. "{")
        table_print (value, indent + 7, done)
        print(string.rep (" ", indent) .. string.rep (" ", indent+4) .. "}")
      else
        print(string.rep (" ", indent) .. string.format("[%s] => %s", tostring (key), tostring(value)))
      end
    end
  else
    print(tt .. "")
  end
end

table_print(_G, 0, {})