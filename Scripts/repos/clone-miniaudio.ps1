Set-Location ./Thalrin/dependencies

git clone git@github.com:mackron/miniaudio.git
Set-Location miniaudio
Write-Host "Checking out miniaudio 0.11.25..."
git checkout 0.11.25
