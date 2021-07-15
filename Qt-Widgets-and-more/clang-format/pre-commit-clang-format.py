import subprocess
output = str(subprocess.check_output(["git", "clang-format", "--diff"]))
 
if 'clang-format did not modify any files' not in output and 'no modified files to format' not in output:
    print("Run git clang-format, add the modified files, then commit.\n")
    exit(1)
else:
    exit(0)
