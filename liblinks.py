"""
liblinks.py

Creates a set of symbolic link in the HOME/sketchbook/libraries directory for
all subdirectories of the current directory. The purpose is to make it easy to
install a set of Arduino libraries.

Usage:

    python liblinks.py install  # Creates links to the libraries
    python liblinks.py remove   # Removes links to the libraries


Author: Will Dickson
"""
import sys
import os
import os.path

USERDIR = os.path.expanduser('~')
LIBDIR = os.path.join(USERDIR,'sketchbook','libraries')

def create_symlinks():

    # Create library dircetory if it doesn't exist
    if not os.path.isdir(LIBDIR):
        print('libraries directory does not exist - creating')
        os.makedirs(LIBDIR)

    # Create symbolic links
    src_paths, dst_paths = get_paths()
    for src, dst in zip(src_paths, dst_paths):
        if os.path.exists(dst):
            if not os.path.islink(dst):
                print('{0} exists and in not a symbolic link - not overwriting'.format(dst))
                continue
            else:
                print('unlinking {0}'.format(dst))
                os.unlink(dst)
        # Create symbolic link
        print('creating new symbolic link {0}'.format(dst))
        os.symlink(src,dst)

def remove_symlinks():

    if not os.path.isdir(LIBDIR):
        return

    # Remove symbolic links
    src_paths, dst_paths = get_paths()
    for dst in dst_paths:
        if os.path.islink(dst):
            print('removing symbolic link {0}'.format(dst))
            os.unlink(dst)

def get_paths():
    """
    Get source and destination paths for symbolic links
    """
    curdir = os.path.abspath(os.path.curdir)
    dir_list = os.listdir(curdir)
    src_paths = []
    dst_paths = []
    for item in dir_list:
        if os.path.isdir(item):
            if item == '.hg':
                continue
            src = os.path.join(curdir,item)
            dst = os.path.join(LIBDIR,item)
            src_paths.append(src)
            dst_paths.append(dst)
    return src_paths, dst_paths


# -----------------------------------------------------------------------------
if __name__ == '__main__':

    # Get command - either 'create' or 'remove'
    if len(sys.argv) < 2:
        print('Error: two few arguments')
        sys.exit(0)

    cmd = sys.argv[1]

    # Take action based of command
    if cmd.lower() == 'install':
        create_symlinks()
    elif cmd.lower() == 'remove':
        remove_symlinks()
    else:
        print("Error: unknown argument {0} - should be 'install' or 'remove'".format(cmd))



