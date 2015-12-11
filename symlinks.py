"""
symlinks.py

Creates a set of symbolic links in the default sketchbook directory for
all Arduino libraries in this repository. The purpose is to make it easy to
install a set of Arduino libraries.

symlinks.py usage:

    python symlinks.py --install  # Creates or refreshes links to the libraries
    python symlinks.py --remove   # Removes links to the libraries

Authors:
Will Dickson will@iorodeo.com
Peter Polidoro polidorop@janelia.hhmi.org
"""
import sys
import os
import argparse
import platform

USERDIR = os.path.expanduser('~')
if platform.system() == 'Linux':
    # LIBDIR = os.path.join(USERDIR,'sketchbook','libraries')
    LIBDIR = os.path.join(USERDIR,'Arduino','libraries')
elif platform.system() == 'Darwin':
    LIBDIR = os.path.join(USERDIR,'Documents','Arduino','libraries')
elif platform.system() == 'Windows':
    sys.exit(0)

def create_symlinks():

    # Create library directory if it doesn't exist
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
            if (item == '.hg') or (item == '.git'):
                continue
            src = os.path.join(curdir,item)
            dst = os.path.join(LIBDIR,item)
            src_paths.append(src)
            dst_paths.append(dst)
    return src_paths, dst_paths


# -----------------------------------------------------------------------------
if __name__ == '__main__':
    parser = argparse.ArgumentParser(description='Arduino Libraries Symlinks')
    parser.add_argument('-i','--install',
                        help='Install all of the Arduino libraries in this repository to the default sketchbook directory as a set of symbolic links.',
                        action='store_true')
    parser.add_argument('-r','--remove',
                        help='Remove all of the Arduino library symbolic links from the default sketchbook directory.',
                        action='store_true')

    if len(sys.argv)==1:
        parser.print_help()
        sys.exit(1)
    args = parser.parse_args()
    if args.install:
        create_symlinks()
    elif args.remove:
        remove_symlinks()
