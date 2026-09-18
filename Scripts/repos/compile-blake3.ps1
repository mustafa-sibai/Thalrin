. "$PSScriptRoot/toolchain.ps1"

Set-Location ./Thalrin/dependencies/BLAKE3
Write-Host "Building BLAKE3..."
cmake -S c -B build -G "Visual Studio 18 2026" -A x64 -T "v145,version=$ToolsetVersion" `
    -DCMAKE_SYSTEM_VERSION="$SdkVersion" `
    -DCMAKE_INSTALL_PREFIX="$PWD/output" -DCMAKE_INSTALL_LIBDIR="lib/x64/debug" -DCMAKE_INSTALL_INCLUDEDIR="include" -DBLAKE3_USE_TBB=1 -DBLAKE3_FETCH_TBB=1
cmake --build build --config Debug --parallel
cmake --install build --config Debug