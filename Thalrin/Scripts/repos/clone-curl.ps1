Set-Location ./dependencies

git clone git@github.com:curl/curl.git
Set-Location curl
Write-Host "Checking out curl 8.18.0..."
git checkout curl-8_18_0