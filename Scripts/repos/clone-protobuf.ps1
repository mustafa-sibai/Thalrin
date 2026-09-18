Set-Location ./Thalrin/dependencies

git clone --recurse-submodules git@github.com:protocolbuffers/protobuf.git
Set-Location protobuf
Write-Host "Checking out protobuf v36.1..."
git checkout v36.1
git submodule update --init --recursive