#!/usr/bin/python
# run gcov coverage checker on all tests.
# filter uninteresting errors and known false positives
#

import re
from os import system, remove, environ, defpath, path, pathsep, X_OK, access, sep
from sys import exit, stdout
from subprocess import Popen, PIPE

re_file = re.compile("File '([^']+)'")
re_exec = re.compile("Lines executed:([\d.]+)% of ([\d])+$")

print_string = ' \'{0}\' coverage {1}% (of {2} lines) - {3}\n'

def gcov(note_file, prefix):
    ''' run gcov on note_file and return output as list '''
    note_name = path.basename(note_file)

    g = find_gcov()
    cmd = g + ' -r -s ' + prefix + ' ' + note_file + " 1>{0}.txt 2>{0}.err".format(note_name)
#    print(cmd)
    system(cmd)
    out = open("{0}.txt".format(note_name)).readlines()
    return out

def parse_errors(out):
    ''' extract the interesting gcov errors from the list 'out'.
    return errors as a list '''
    errors = []
    current = ''
    state = 0
    for line in out:
        if state == 0:
            match = re_file.search(line)
            if match:
                current = match.group(1)
                state = 1
        elif state == 1:
            match = re_exec.search(line)
            if match:
                percent = float(match.group(1))
                number = int(match.group(2))

                if percent < 100.00:
                    errors.append(len(errors))
                    sys.stderr.write(print_string.format(current, percent, number, 'FAIL'))
                else:
                    sys.stdout.write(print_string.format(current, percent, number, 'PASS'))
                state = 0


    return errors

#from: http://mail.python.org/pipermail/python-list/2002-August/157829.html
def which (filename):
    if 'PATH' not in environ or environ['PATH'] == '':
        p = defpath
    else:
        p = environ['PATH']

    pathlist = p.split (pathsep)

    for thepath in pathlist:
        f = thepath+sep+filename
        if access(f, X_OK):
            return f
    return None

def find_gcov():
    gcov = which('gcov')
    if gcov != None:
        return gcov
    else:
        print("gcov NOT FOUND")
        exit(2)

def find_find():
    find = which('find')
    if find != None:
        return find
    else:
        print("find NOT FOUND")
        exit(2)

def run_single_test(note_file, prefix):
    sys.stdout.write(' >> running gcov on:')
    out = gcov(note_file, prefix)
    errors = parse_errors(out)

    return len(errors) == 0

def find_note_files(file_path):
    find_exe = find_find()
    from subprocess import check_output
    res = check_output([find_exe, file_path, '-name', '*.gcno', '-type', 'f'])

    if isinstance(res, bytes):
        res = res.decode("utf-8")
    if not isinstance(res, list):
        res = [res]

    return res


################### ENTRY ####################################################

if __name__ == '__main__':
    import sys
    if len(sys.argv) > 2:
        exit_code = 0
        analysis_path = sys.argv[1]
        note_files = find_note_files(analysis_path)
        for note_file in note_files:
            for prefix_path in sys.argv[2:]:
                result = run_single_test(note_file.strip(), prefix_path)
                if not result:
                    exit_code = 2

        exit(exit_code)
    else:
        print("usage: ./gcovcoverage.py analysis_path file_prefix_1 [file_prefix_2 ...]")
        exit(1)

