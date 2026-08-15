Set-Location ./dependencies

git clone git@github.com:freetype/freetype.git
Set-Location freetype
Write-Host "Checking out freetype v2.14.1..."
git checkout VER-2-14-1