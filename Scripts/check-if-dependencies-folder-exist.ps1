if (-not (Test-Path -Path ".\Thalrin\Dependencies")) {
    New-Item -Path "./Thalrin/Dependencies" -ItemType Directory
    exit
}
