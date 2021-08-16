from dearpygui.dearpygui import *
from dearpygui.demo import show_demo
import subprocess
import os
from CustomLogger import *
from PlatformInfo import *
from pathlib import Path
from threading import Thread
#show_demo()

Configurations = ["debug", "release", "dist"]
Applications = ["TestGame", "GameClient", "GameServer", "Sandbox2D", "Sandbox3D"]
PremakeConfigs = ["gmake2", "vs2019", "xcode4"]

AppComboID = generate_uuid()
WindowID = generate_uuid()
ConfigComboID = generate_uuid()
PremakeComboID = generate_uuid()
GroupID = generate_uuid()

logger = None

SubProcessList = {}
SubProcessUI = {}

def get_workspace_path():
    return str(Path(Path(__file__).parent).parent)

def del_subprocess(index, killBool):
    if(index in SubProcessList):
        if killBool: SubProcessList[index][0].terminate()
        SubProcessList.pop(index)
        for i in SubProcessUI[index]:
            delete_item(i)
        SubProcessUI.pop(index)

def add_subprocess(index):
    id_text = add_text('[' + str(SubProcessList[index][0].pid) + '] ' + str(SubProcessList[index][1]), parent=GroupID)
    id_sl = add_same_line(parent=GroupID)
    id_button = add_button(label="Terminate", parent=GroupID, callback=lambda: del_subprocess(index, True))
    id_sep = add_separator(parent=GroupID)
    SubProcessUI[index] = [id_text, id_sl, id_button, id_sep]

def process_callback(process, command):
    while True:
        output = process.stdout.readline()
        if output != "": logger.log(output.strip())

        return_code = process.poll()
        if return_code is not None:
            logger.log_tool("----------------")
            logger.log_tool("Finished calling " + command[0])
            logger.log_tool("----------------")
            del_subprocess(process.pid, False)
            break

def call_command(workspace, command):
    process = subprocess.Popen(command, stdout=subprocess.PIPE, universal_newlines=True, cwd=workspace, stderr=subprocess.STDOUT)
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
    with group(label="Build", id=GroupID):
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
    add_same_line()
    group = add_group(label="Log")
    logger = Logger(group)

    #set_primary_window_size(300, 500)
    

set_primary_window(main_window, True)

setup_viewport()
set_viewport_title(title='Rosewood Build Tool')
set_viewport_width(800)
set_viewport_height(600)

start_dearpygui()