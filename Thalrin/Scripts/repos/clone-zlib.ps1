Set-Location ./dependencies

git clone git@github.com:madler/zlib.git
Set-Location zlib
Write-Host "Checking out zlib v1.3.1..."
git checkout v1.3.1