--[[
    Project: SAMP-API.lua <https://github.com/imring/SAMP-API.lua>
    Developers: imring, LUCHARE, FYP

    Special thanks:
        SAMemory (https://www.blast.hk/threads/20472/) for implementing the basic functions.
        SAMP-API (https://github.com/BlastHackNet/SAMP-API) for the structures and addresses.
]]

local sampapi = require 'sampapi'
local shared = sampapi.shared
local mt = require 'sampapi.metatype'
local ffi = require 'ffi'

shared.ffi.cdef[[
enum {
    MAX_EXCEPTIONS = 9,
};
]]

local function RefCount() return ffi.cast('int*', sampapi.GetAddress(0x125A58))[0] end
local function RefContextRecord() return ffi.cast('void**', sampapi.GetAddress(0x121A50))[0] end
local function ArrayCrashDialogText() return ffi.cast('char* ', sampapi.GetAddress(0x121A58)) end
local Print = ffi.cast('BOOL(__stdcall*)(int, void*, const char*)', sampapi.GetAddress(0x609B0))
local SendCrashReport = ffi.cast('void(__cdecl*)()', sampapi.GetAddress(0x607A0))
local CrashDialogProc = ffi.cast('BOOL(__stdcall*)(void*, unsigned int, unsigned int, long)', sampapi.GetAddress(0x60870))
local ConstructCrashDialogText = ffi.cast('void(__cdecl*)(BOOL)', sampapi.GetAddress(0x605B0))
local Handler = ffi.cast('long(__stdcall*)(void*)', sampapi.GetAddress(0x60970))

return {
    RefCount = RefCount,
    RefContextRecord = RefContextRecord,
    ArrayCrashDialogText = ArrayCrashDialogText,
    Print = Print,
    SendCrashReport = SendCrashReport,
    CrashDialogProc = CrashDialogProc,
    ConstructCrashDialogText = ConstructCrashDialogText,
    Handler = Handler,
}