. "$PSScriptRoot/toolchain.ps1"

Push-Location ./Thalrin/dependencies/openssl
Write-Host "Building OpenSSL..."
$installDir = "$PWD\install"
perl Configure VC-WIN64A no-shared --prefix="$installDir" --openssldir="$installDir\ssl" -d
cmd /c "call `"C:\Program Files\Microsoft Visual Studio\18\Community\VC\Auxiliary\Build\vcvarsall.bat`" amd64 $SdkVersion -vcvars_ver=$ToolsetVersion && nmake clean && nmake && nmake install"
Pop-Location