
function Clean-Build-Folder {
    if (Test-Path -Path "build")
    {
        remove-item build -R
        new-item -Path build -ItemType Directory
    } else {
        new-item -Path build -ItemType Directory
    }
}

$NDKPath = Get-Content $PSScriptRoot/ndkpath.txt

Clean-Build-Folder
# build tests
cd build

& cmake -G "Ninja" -DCMAKE_BUILD_TYPE="Release" -DTEST_BUILD=a ../
& cmake --build .

$ExitCode = $LastExitCode
cd ..

if (-not ($ExitCode -eq 0)) {
    $msg = "ExitCode: " + $ExitCode
    Write-Output $msg
    exit $ExitCode
}

# clean folder
Clean-Build-Folder
# build mod
cd build

& cmake -G "Ninja" -DCMAKE_BUILD_TYPE="Release" ../
& cmake --build .

$ExitCode = $LastExitCode
cd ..

exit $ExitCode