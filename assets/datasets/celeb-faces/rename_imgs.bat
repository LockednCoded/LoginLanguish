@echo off
setlocal enabledelayedexpansion

rem Loop through each folder in the current directory
for /d %%F in (*) do (
    set "folder=%%F"
    set "count=1"
    
    rem Loop through image files in the folder
    for %%I in ("!folder!\*.jpg") do (
        set "new_name=!folder!_!count!.jpg"
        ren "%%I" "!new_name!"
        set /a "count+=1"
    )
)

endlocal