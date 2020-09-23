import subprocess
import sys

reqs = subprocess.check_output([sys.executable, '-m', 'pip', 'freeze'])
installed_packages = [r.decode().split('==')[0] for r in reqs.split()]

check_package = sys.argv[1]
if check_package in installed_packages:
  result = 0
else:
  result = 1

sys.exit(result)
