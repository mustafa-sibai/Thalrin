. "$PSScriptRoot/toolchain.ps1"

Push-Location ./Thalrin/dependencies/zlib
Write-Host "Building zlib..."
cmake -S . -B build -G "Visual Studio 18 2026" -A x64 -T "v145,version=$ToolsetVersion" `
    -DCMAKE_SYSTEM_VERSION="$SdkVersion" `
    -DZLIB_BUILD_SHARED=OFF `
    -DZLIB_BUILD_STATIC=ON `
    -DCMAKE_INSTALL_PREFIX="$PWD/output"
cmake --build build --config Debug --parallel
cmake --install build --config Debug
Pop-Location