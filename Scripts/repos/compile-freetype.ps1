. "$PSScriptRoot/toolchain.ps1"

Set-Location ./Thalrin/dependencies/freetype
Write-Host "Building FreeType..."
& "C:\Program Files\Microsoft Visual Studio\18\Community\MSBuild\Current\Bin\MSBuild.exe" MSBuild.sln /t:freetype /p:Configuration="Debug Static" /p:Platform=x64 /p:PlatformToolset=v145 /p:VCToolsVersion=$ToolsetVersion /p:WindowsTargetPlatformVersion=$SdkVersion