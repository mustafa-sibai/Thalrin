Set-Location ./dependencies/BLAKE3
Write-Host "Building BLAKE3..."
cmake -S c -B build -DCMAKE_INSTALL_PREFIX="$PWD/output" -DCMAKE_INSTALL_LIBDIR="lib/x64/debug" -DCMAKE_INSTALL_INCLUDEDIR="include" -DBLAKE3_USE_TBB=1 -DBLAKE3_FETCH_TBB=1
cmake --build build --config Debug --parallel
cmake --install build --config Debug