"""
symlink.py

Creates a symbolic link in the default sketchbook directory to this
Arduino library.

symlinks.py usage:

    python symlink.py --install  # Creates or refreshes links to this library
    python symlink.py --remove   # Removes link to this library

Authors:
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

def create_symlink():

    # Create library directory if it doesn't exist
    if not os.path.isdir(LIBDIR):
        print('libraries directory does not exist - creating')
        os.makedirs(LIBDIR)

    # Create symbolic link
    src, dst = get_paths()
    if os.path.exists(dst):
        if not os.path.islink(dst):
            print('{0} exists and in not a symbolic link - not overwriting'.format(dst))
        else:
            print('unlinking {0}'.format(dst))
            os.unlink(dst)
    # Create symbolic link
    print('creating new symbolic link {0}'.format(dst))
    os.symlink(src,dst)

def remove_symlink():

    if not os.path.isdir(LIBDIR):
        return

    # Remove symbolic links
    src, dst = get_paths()
    if os.path.islink(dst):
        print('removing symbolic link {0}'.format(dst))
        os.unlink(dst)

def get_paths():
    """
    Get source and destination paths for symbolic link
    """
    src_path = os.path.abspath(os.path.curdir)
    dst_path = os.path.join(LIBDIR,"ModularDevice")
    return src_path, dst_path


# -----------------------------------------------------------------------------
if __name__ == '__main__':
    parser = argparse.ArgumentParser(description='Arduino Library Symlink')
    parser.add_argument('-i','--install',
                        help='Install this Arduino library to the default sketchbook directory as a symbolic link.',
                        action='store_true')
    parser.add_argument('-r','--remove',
                        help='Remove this Arduino library symbolic link from the default sketchbook directory.',
                        action='store_true')

    if len(sys.argv)==1:
        parser.print_help()
        sys.exit(1)
    args = parser.parse_args()
    if args.install:
        create_symlink()
    elif args.remove:
        remove_symlink()
