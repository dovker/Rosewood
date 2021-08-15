from dearpygui.dearpygui import *
from dearpygui.demo import show_demo
import subprocess
import sys
import os
import signal
from pathlib import Path
from threading import Thread
#show_demo()

Configurations = ["debug", "release", "dist"]
Applications = ["TestGame", "GameClient", "GameServer", "Sandbox2D", "Sandbox3D"]
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
WindowID = generate_uuid()
ConfigComboID = generate_uuid()
PremakeComboID = generate_uuid()

SubProcessList = {}
SubProcessUI = {}

def del_subprocess(index, killBool):
    if(index in SubProcessList):
        if killBool: SubProcessList[index][0].terminate()
        SubProcessList.pop(index)
        for i in SubProcessUI[index]:
            delete_item(i)
        SubProcessUI.pop(index)

def add_subprocess(index):
    print(SubProcessList[index][0].pid)
    id_text = add_text('[' + str(SubProcessList[index][0].pid) + '] ' + str(SubProcessList[index][1]), parent=WindowID)
    id_sl = add_same_line(parent=WindowID)
    id_button = add_button(label="Terminate", parent=WindowID, callback=lambda: del_subprocess(index, True))
    id_sep = add_separator(parent=WindowID)
    SubProcessUI[index] = [id_text, id_sl, id_button, id_sep]

def process_callback(process, command):
    while True:
        output = process.stdout.readline()
        if output != "": print(output.strip())

        return_code = process.poll()
        if return_code is not None:
            print("----------------")
            print("Finished calling", command[0])
            print("----------------")
            del_subprocess(process.pid, False)
            break

def call_command(workspace, command):
    process = subprocess.Popen(command, 
                           stdout=subprocess.PIPE,
                           universal_newlines=True, cwd=workspace)
    SubProcessList[process.pid] = [process, command];
    add_subprocess(process.pid)
    thread = Thread(target=process_callback, args=[process, command])
    thread.start()
    

def build_callback(sender, app_data):
    call_command(get_workspace_path(), ['make', 'config=' + get_value(ConfigComboID)])

def premake_callback(sender, app_data):
    call_command(get_workspace_path(), [get_call_thing() + os.path.join("vendor", "bin", "premake", "premake5") + get_executable_ext(), get_value(PremakeComboID)])

def run_callback(sender, app_data):
    call_command(os.path.join(get_workspace_path(), 'bin', get_value(ConfigComboID).capitalize() + '-' + get_platform() + "-x86_64", get_value(AppComboID)), [get_call_thing() + get_value(AppComboID) + get_executable_ext()])

FontScale = 1

with window(label="Example Window", id=WindowID) as main_window:
    set_global_font_scale(FontScale)
    add_separator()
    add_text("Build Project")
    add_combo(label="Configurations", id=ConfigComboID, default_value="debug", items=Configurations, width=200)
    add_combo(label="Project", id=AppComboID, default_value="TestGame", items=Applications, width=200)
    add_button(label="Build", callback=build_callback, width = 100, height=40)
    add_same_line()
    add_button(label="Run", callback=run_callback, width = 100, height=40)
    add_separator()
    add_text("Generate Project")
    add_combo(label="Project generator type", id=PremakeComboID, default_value="gmake2", items=PremakeConfigs, width=200)
    add_button(label="Generate project files", callback=premake_callback, width = 200, height=40)
    add_separator()
    add_separator()
    add_text("SubProcesses:")
    add_separator()

set_primary_window(main_window, True)

setup_viewport()
start_dearpygui()