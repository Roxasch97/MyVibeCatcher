import subprocess

subprocess.run('find core/ -iname *.h -o -iname *.c | xargs clang-format -i', shell=True)
subprocess.run('find test/ -iname *.h -o -iname *.c | xargs clang-format -i', shell=True)
subprocess.run('ceedling verbosity[4] test:all', shell=True)
subprocess.run('cppcheck Core/ --template=gcc --inconclusive --force 2>CppcheckLog.txt', shell=True)
