local Engine = _G["Engine"]
local EE = _G["EE"]
local Interface = EE["Interface"]
local Util = Interface["Utilities"]
local debug = _G["debug"]
local TGL = _T

require "Lotus.Interface.Libs.TimerMgr"

if (Engine == nil) then
    print("Engine not found.")
end

if (Util == nil) then
    print("Utilities not found.")
end

if (Util.ShowMessage == nil) then
    print("ShowMessage not found.")
end

if (Engine.OkCancel == nil) then
    print("OkCancel not found.")
end

if (debug.getinfo == nil) then
    print("debug.getinfo not found.")
end

-- /Lotus/Language/Dojo/UpdateMessageConfirm
print("WFEx loaded.")
print("-------------------------------------------------")
if _G.Sleep == nil then
    print("Sleep is somewhere else.")
end

print(AddTimer)