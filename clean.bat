rmdir /S /Q build
rmdir /S /Q ipch
rmdir /S /Q bin
rmdir /S /Q Setup\Release
rmdir /S /Q Setup\Debug

del /S /F /Q *.aps
del /S /F /Q *.sdf
del /S /F /Q /A:H *.suo