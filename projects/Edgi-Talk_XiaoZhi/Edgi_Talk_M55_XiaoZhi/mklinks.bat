@echo off

cd /d "%~dp0"
@echo on
mklink /D rt-thread ..\..\..\rt-thread
mklink /D libraries ..\..\..\libraries
mklink /D libs ..\libs
mklink /D tools ..\..\..\tools