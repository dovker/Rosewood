from dearpygui.dearpygui import *
from dearpygui.demo import show_demo
import subprocess
import sys
import os
from pathlib import Path

#show_demo()

Configurations = ["debug", "release", "dist"]
Applications = ["TestGame", "GameClient", "GameServer"]
PremakeConfigs = ["gmake2", "vs2019", "xcode4"]

def get_platform():
    if sys.platform.startswith('win32'):
        return "windows"
    elif sys.platform.startswith('linux'):
        return "linux"
    elif sys.platform.startswith('darwin'):
        return "macosx"

def get_workspace_path():
    return str(Path(Path(__file__).parent).parent)

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

AppComboID = generate_uuid()
ConfigComboID = generate_uuid()
PremakeComboID = generate_uuid()


def call_command(workspace, command):
    process = subprocess.Popen(command, 
                           stdout=subprocess.PIPE,
                           universal_newlines=True, cwd=workspace)

    while True:
        output = process.stdout.readline()
        print(output.strip())

        return_code = process.poll()
        if return_code is not None:
            break

def build_callback(sender, app_data):
    call_command(get_workspace_path(), ['make', 'config=' + get_value(ConfigComboID)])

def premake_callback(sender, app_data):
    call_command(get_workspace_path(), [get_call_thing() + os.path.join("vendor", "bin", "premake", "premake5") + get_executable_ext(), get_value(PremakeComboID)])

def run_callback(sender, app_data):
    call_command(os.path.join(get_workspace_path(), 'bin', get_value(ConfigComboID).capitalize() + '-' + get_platform() + "-x86_64", get_value(AppComboID)), get_call_thing() + get_value(AppComboID) + get_executable_ext())

with window(label="Example Window") as main_window:
    add_combo(label="Config Combo", id=ConfigComboID, default_value="debug", items=Configurations)
    add_combo(label="App Combo", id=AppComboID, default_value="TestGame", items=Applications)
    add_button(label="Build", callback=build_callback)
    add_same_line()
    add_button(label="Run", callback=run_callback)
    add_combo(label="Premake Combo", id=PremakeComboID, default_value="gmake2", items=PremakeConfigs)
    add_button(label="Remake Premake", callback=premake_callback)

set_primary_window(main_window, True)

setup_viewport()
start_dearpygui()