import os
import time
import sys


# requirements pywin32

current_time = time.time()
created = current_time - 3600
modified = current_time - 1800

if os.name == 'nt':
    import win32con
    import win32file
    import pywintypes

    def set_creation_file(path, creation_time):
        wintime = pywintypes.Time(creation_time)
        fh = win32file.CreateFile(
            path,
            win32con.GENERIC_WRITE,
            win32con.FILE_SHARE_READ | win32con.FILE_SHARE_WRITE | win32con.FILE_SHARE_DELETE,
            None,
            win32con.OPEN_EXISTING,
            win32con.FILE_ATTRIBUTE_NORMAL,
            None
        )
        win32file.SetFileTime(fh, wintime)
        fh.close()
    
else:

    def set_creation_file(path, creation_time):
        os.utime(path, times=(created, modified))

if __name__ == '__main__':
    if len(sys.argv) >= 2:
        full_path = os.path.join(os.getcwd(), sys.argv[1])
        set_creation_file(full_path, creation_time=created)
        print("Done.")
    else:
        print("Usage: python {} filename.jpg".format(sys.argv[0]))
