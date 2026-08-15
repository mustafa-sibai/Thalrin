Set-Location ./dependencies

git clone git@github.com:syoyo/tinygltf.git
Set-Location tinygltf
Write-Host "Checking out tinygltf v2.9.7..."
git checkout v2.9.7