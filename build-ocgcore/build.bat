cd windows
msbuild "ocgcoredll.sln" /p:Configuration=Release /p:Platform="Win32" /m
msbuild "ocgcoredll.sln" /p:Configuration=Release /p:Platform="x64" /m
