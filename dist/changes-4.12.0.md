Qt Creator 4.12
===============

Qt Creator version 4.12 contains bug fixes and new features.

The most important changes are listed in this document. For a complete
list of changes, see the Git log for the Qt Creator sources that
you can check out from the public Git repository. For example:

    git clone git://code.qt.io/qt-creator/qt-creator.git
    git log --cherry-pick --pretty=oneline origin/4.11..v4.12.0

General
-------

* Added `Restart Now` option when changing settings that require restart
* Added option for linking Qt Creator to a Qt installation, sharing
  auto-detected Qt versions and kits
* Added guard against crashing plugins at startup, providing the option
  to temporarily disable the offending plugin
* Added locator filter for searching in Qt Project bug tracker
* Added option to create custom URL template locator filters
* Added browser for Marketplace items to Welcome mode (QTCREATORBUG-23452)
* Fixed various theming issues

Help
----

* Added tool button for changing target for context help (QTCREATORBUG-17667)
* Added option to register documentation only for highest Qt version, and made that default
  (QTCREATORBUG-21482, QTCREATORBUG-22799, QTCREATORBUG-10004)

Editing
-------

* Added `Go to Last Edit`
* Added option for default line terminator style (QTCREATORBUG-3590)
* Improved performance of syntax highlighting (QTCREATORBUG-23281)
* Fixed that wizards ignored default file encoding
* Fixed that only restricted number of sizes were allowed for font size (QTCREATORBUG-22536)

### Language Client

* Added support for Markdown in tooltips
* Added support for auto-formatting
* Added outline dropdown (QTCREATORBUG-21916)
* Fixed `Ctrl-click` for `Follow Symbol Under Cursor` (QTCREATORBUG-21848)

### QML

* Improved support for multiple imports into same namespace (QTCREATORBUG-15684)
* Added scanning of `app.qmltypes` and `lib.qmltypes` for type information

### Python

* Added wizards for Qt Quick Application and Qt Widgets Application with `.ui` file
  (QTCREATORBUG-21824)

### Diff Viewer

* Added support for staging only selected lines (QTCREATORBUG-19071)

Projects
--------

* Added option to hide "disabled" files in Projects tree (QTCREATORBUG-22821)
* Added option to filter output panes for lines that do not match expression (QTCREATORBUG-19596)
* Added option for default build configuration settings (debug information, QML debugging, Qt Quick
  Compiler) (QTCREATORBUG-16458)
* Added option to only build target for active run configuration (qmake & Qbs)
* Added option to only stop the target of active run configuration on build (QTCREATORBUG-16470)
* Added option for project specific environment (QTCREATORBUG-21862)
* Added option to remove items from `Recent Projects` list in Welcome mode
* Added option to start run configurations directly from target selector (QTCREATORBUG-21799)
* Added option to build project for all configured kits (QTCREATORBUG-16815)
* Added `-ensure-kit-for-binary` command line option that creates a kit for a binary's
  architecture if needed (QTCREATORBUG-8216)
* Added GitHub build workflow to `Qt Creator Plugin` wizard template
* Improved UI responsiveness while parsing projects (QTCREATORBUG-18533)
* Fixed build directory after cloning target (QTCREATORBUG-23462)
* Fixed copying of filtered text from output pane (QTCREATORBUG-23425)

### QMake

* Improved renaming of files (QTCREATORBUG-19257)
* Fixed handling of `object_parallel_to_source` (QTCREATORBUG-18136)
* Fixed crash with circular includes (QTCREATORBUG-23567)

### CMake

* Improved handling of `source_group` (QTCREATORBUG-23372)
* Added support for `Add build library search path to LD_LIBRARY_PATH` (QTCREATORBUG-23464)
* Added automatic registration of CMake documentation, if available (QTCREATORBUG-21338)
* Fixed issues with `snap` on Ubuntu Linux (QTCREATORBUG-23376)
* Fixed handling of `Enable QML` in debugger settings (QTCREATORBUG-23541)

### Qbs

* Changed to use separate Qbs executable instead of direcly linking to Qbs (QTCREATORBUG-20622)
* Added option for default install root (QTCREATORBUG-12983)

### Python

* Added option to disable buffered output (QTCREATORBUG-23539)

### Generic

* Improved performance for large file trees (QTCREATORBUG-20652)
* Fixed that only first line of `.cflags` and `.cxxflags` was considered

### Compilation Database

* Fixed that project was reparsed if compilation database contents did not change
  (QTCREATORBUG-22574)

### Nim

* Added support for Nimble build system
* Added support for `Follow Symbol Under Cursor`

Debugging
---------

* Added option to hide columns from views (QTCREATORBUG-23342)

Analyzer
--------

### Clang

* Improved filtering
* Added context menu item that opens help on diagnostics

### CppCheck

* Added option to trigger Cppcheck manually

### Chrome Traces

* Added more details for counter items
* Added option to restrict view to selected threads
* Added information about percentage of total time for events

### Heob

* Added support for settings profiles (QTCREATORBUG-23209)

Qt Quick Designer
-----------------

* Added locking and pinning of animation curves (QDS-550, QDS-551)
* Fixed dragging of keyframes in curve editor (QDS-1405)

Version Control Systems
-----------------------

### Git

* Added option to create branch when trying to push to a non-existing branch (QTCREATORBUG-21154)
* Added option to start interactive rebase from log view (QTCREATORBUG-11200)
* Added information about upstream status to `Git Branches` view

Test Integration
----------------

* Added support for colored test output (QTCREATORBUG-22297)

### Google Test

* Added support for internal logging (QTCREATORBUG-23354)

Platforms
---------

### Windows

### macOS

* Fixed parsing of Apple Clang specific linker message (QTCREATORBUG-19766)
* Fixed `Run in Terminal` and `Open Terminal` when user has different shell configured
  (QTCREATORBUG-21712)

### Android

* Added auto-detection of Java JDK (QTCREATORBUG-23407)
* Added option to automatically download and install required Android tools (QTCREATORBUG-23285)
* Fixed several issues with AVD manager (QTCREATORBUG-23284, QTCREATORBUG-23448)

### Remote Linux

* Added option to use custom command for install step (QTCREATORBUG-23320)
* Added option to override deployment data (QTCREATORBUG-21854)

### Bare Metal

* Added support for RL78 architecture
* Added support for J-Link and EBlink GDB servers
* Added support for KEIL uVision v5.x debugger

Credits for these changes go to:
--------------------------------
Alessandro Portale  
Alexandru Croitor  
Andre Hartmann  
Andrey Sobol  
André Pönitz  
Assam Boudjelthia  
Camila San  
Christian Kandeler  
Christian Stenger  
Cristian Adam  
David Schulz  
Denis Shienkov  
Dmitry Kovalev  
Eike Ziller  
Federico Guerinoni  
Filippo Cucchetto  
Halfdan Ingvarsson  
Hannes Domani  
Igor Sidorov  
Jaroslaw Kobus  
Jochen Becher  
Knud Dollereder  
Leander Schulten  
Leena Miettinen  
Lucie Gérard  
Mahmoud Badri  
Mariana Meireles  
Marius Sincovici  
Maximilian Goldstein  
Miikka Heikkinen  
Miklós Márton  
Mitch Curtis  
Mitja Kleider  
Nikolai Kosjar  
Nikolay Panov  
Oliver Wolff  
Orgad Shaneh  
Robert Löhning  
Sergey Morozov  
Tasuku Suzuki  
Thiago Macieira  
Thomas Hartmann  
Tim Henning  
Tim Jenssen  
Tobias Hunger  
Topi Reinio  
Ulf Hermann  
Ville Voutilainen  
Volodymyr Samokhatko  
zarelaky  
