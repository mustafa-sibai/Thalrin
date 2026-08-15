Push-Location ./dependencies/zlib
Write-Host "Building zlib..."
cmake -S . -B build -G "Visual Studio 17 2022" -A x64 `
    -DZLIB_BUILD_SHARED=OFF `
    -DZLIB_BUILD_STATIC=ON `
    -DCMAKE_INSTALL_PREFIX="$PWD/output"
cmake --build build --config Debug --parallel
cmake --install build --config Debug
Pop-Location