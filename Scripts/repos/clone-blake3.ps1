Set-Location ./dependencies

git clone git@github.com:BLAKE3-team/BLAKE3.git
Set-Location BLAKE3
Write-Host "Checking out BLAKE3 1.8.3..."
git checkout 1.8.3