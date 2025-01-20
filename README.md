# ProcessSpawnControl_GUI
PSC GUI is a tool to suspend newly created processes.  
Can be useful for malware analysis and research of unknown executables.  
![gui](https://github.com/xoreaxecx/ProcessSpawnControl_GUI/blob/main/_pics/psc_main.png)  
USE WITH CAUTION.  
Do not remove all exclusions, especially task manager.  
There is a possibility of system softlock.  

---  

### Usage  
Click "Start" to catch all spawned processes.  
![gui_off](https://github.com/xoreaxecx/ProcessSpawnControl_GUI/blob/main/_pics/psc_main_off.png)  

If target exe is specified, PSC will catch only child processes of the specified target.  
But if the "control all" checkbox is set, PSC will again catch all spawned processes.  
![target](https://github.com/xoreaxecx/ProcessSpawnControl_GUI/blob/main/_pics/target_settings_marked.png)  

Processes in the exclusion list will be ignored for suspension.  
The exclusion list can be changed at any time, either manually or by loading a saved list.  
![exclusions](https://github.com/xoreaxecx/ProcessSpawnControl_GUI/blob/main/_pics/exclusions.png)  

---  

### Notes  
Built with wxWidgets 3.2.6.  
Project contains gui.fbp file for wxFormBuilder.  
