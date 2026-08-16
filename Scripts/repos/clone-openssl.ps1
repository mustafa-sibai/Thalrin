Set-Location ./dependencies

git clone git@github.com:openssl/openssl.git
Set-Location openssl
Write-Host "Checking out openssl v3.6.1..."
git checkout openssl-3.6.1