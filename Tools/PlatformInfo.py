import sys


def get_platform():
    if sys.platform.startswith('win32'):
        return "windows"
    elif sys.platform.startswith('linux'):
        return "linux"
    elif sys.platform.startswith('darwin'):
        return "macosx"


def get_executable_ext():
    if sys.platform.startswith('win32'):
        return ".exe"
    else:
        return ""

def get_call_thing():
    if sys.platform.startswith('win32'):
        return ""
    else:
        return "./"