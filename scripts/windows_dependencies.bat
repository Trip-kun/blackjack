powershell "Set-ExecutionPolicy -ExecutionPolicy RemoteSigned -Scope CurrentUser"
powershell "Invoke-RestMethod -Uri https://get.scoop.sh | Invoke-Expression"
scoop update
scoop bucket add main
scoop install main/cmake
scoop install main/make
