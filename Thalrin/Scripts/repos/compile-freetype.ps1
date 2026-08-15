Set-Location ./dependencies/freetype
Write-Host "Building FreeType..."
& "C:\Program Files\Microsoft Visual Studio\2022\Community\MSBuild\Current\Bin\MSBuild.exe" MSBuild.sln /t:freetype /p:Configuration="Debug Static" /p:Platform=x64