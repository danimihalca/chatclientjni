# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.3

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = "C:\Program Files (x86)\CMake\bin\cmake.exe"

# The command to remove a file.
RM = "C:\Program Files (x86)\CMake\bin\cmake.exe" -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = D:\thesis\repositories\chatClientJNI

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = D:\thesis\repositories\chatClientJNI\build\Android-armeabi-Debug

# Include any dependencies generated for this target.
include CMakeFiles/chatClientJNI.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/chatClientJNI.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/chatClientJNI.dir/flags.make

CMakeFiles/chatClientJNI.dir/src/dm_chatclient_controller_NativeChatClientController.cpp.o: CMakeFiles/chatClientJNI.dir/flags.make
CMakeFiles/chatClientJNI.dir/src/dm_chatclient_controller_NativeChatClientController.cpp.o: ../../src/dm_chatclient_controller_NativeChatClientController.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=D:\thesis\repositories\chatClientJNI\build\Android-armeabi-Debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/chatClientJNI.dir/src/dm_chatclient_controller_NativeChatClientController.cpp.o"
	C:\android-ndk-r10e\toolchains\arm-linux-androideabi-4.9\prebuilt\windows-x86_64\bin\arm-linux-androideabi-g++.exe   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles\chatClientJNI.dir\src\dm_chatclient_controller_NativeChatClientController.cpp.o -c D:\thesis\repositories\chatClientJNI\src\dm_chatclient_controller_NativeChatClientController.cpp

CMakeFiles/chatClientJNI.dir/src/dm_chatclient_controller_NativeChatClientController.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/chatClientJNI.dir/src/dm_chatclient_controller_NativeChatClientController.cpp.i"
	C:\android-ndk-r10e\toolchains\arm-linux-androideabi-4.9\prebuilt\windows-x86_64\bin\arm-linux-androideabi-g++.exe  $(CXX_DEFINES) $(CXX_FLAGS) -E D:\thesis\repositories\chatClientJNI\src\dm_chatclient_controller_NativeChatClientController.cpp > CMakeFiles\chatClientJNI.dir\src\dm_chatclient_controller_NativeChatClientController.cpp.i

CMakeFiles/chatClientJNI.dir/src/dm_chatclient_controller_NativeChatClientController.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/chatClientJNI.dir/src/dm_chatclient_controller_NativeChatClientController.cpp.s"
	C:\android-ndk-r10e\toolchains\arm-linux-androideabi-4.9\prebuilt\windows-x86_64\bin\arm-linux-androideabi-g++.exe  $(CXX_DEFINES) $(CXX_FLAGS) -S D:\thesis\repositories\chatClientJNI\src\dm_chatclient_controller_NativeChatClientController.cpp -o CMakeFiles\chatClientJNI.dir\src\dm_chatclient_controller_NativeChatClientController.cpp.s

CMakeFiles/chatClientJNI.dir/src/dm_chatclient_controller_NativeChatClientController.cpp.o.requires:

.PHONY : CMakeFiles/chatClientJNI.dir/src/dm_chatclient_controller_NativeChatClientController.cpp.o.requires

CMakeFiles/chatClientJNI.dir/src/dm_chatclient_controller_NativeChatClientController.cpp.o.provides: CMakeFiles/chatClientJNI.dir/src/dm_chatclient_controller_NativeChatClientController.cpp.o.requires
	$(MAKE) -f CMakeFiles\chatClientJNI.dir\build.make CMakeFiles/chatClientJNI.dir/src/dm_chatclient_controller_NativeChatClientController.cpp.o.provides.build
.PHONY : CMakeFiles/chatClientJNI.dir/src/dm_chatclient_controller_NativeChatClientController.cpp.o.provides

CMakeFiles/chatClientJNI.dir/src/dm_chatclient_controller_NativeChatClientController.cpp.o.provides.build: CMakeFiles/chatClientJNI.dir/src/dm_chatclient_controller_NativeChatClientController.cpp.o


CMakeFiles/chatClientJNI.dir/src/JNIChatClientListener.cpp.o: CMakeFiles/chatClientJNI.dir/flags.make
CMakeFiles/chatClientJNI.dir/src/JNIChatClientListener.cpp.o: ../../src/JNIChatClientListener.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=D:\thesis\repositories\chatClientJNI\build\Android-armeabi-Debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/chatClientJNI.dir/src/JNIChatClientListener.cpp.o"
	C:\android-ndk-r10e\toolchains\arm-linux-androideabi-4.9\prebuilt\windows-x86_64\bin\arm-linux-androideabi-g++.exe   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles\chatClientJNI.dir\src\JNIChatClientListener.cpp.o -c D:\thesis\repositories\chatClientJNI\src\JNIChatClientListener.cpp

CMakeFiles/chatClientJNI.dir/src/JNIChatClientListener.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/chatClientJNI.dir/src/JNIChatClientListener.cpp.i"
	C:\android-ndk-r10e\toolchains\arm-linux-androideabi-4.9\prebuilt\windows-x86_64\bin\arm-linux-androideabi-g++.exe  $(CXX_DEFINES) $(CXX_FLAGS) -E D:\thesis\repositories\chatClientJNI\src\JNIChatClientListener.cpp > CMakeFiles\chatClientJNI.dir\src\JNIChatClientListener.cpp.i

CMakeFiles/chatClientJNI.dir/src/JNIChatClientListener.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/chatClientJNI.dir/src/JNIChatClientListener.cpp.s"
	C:\android-ndk-r10e\toolchains\arm-linux-androideabi-4.9\prebuilt\windows-x86_64\bin\arm-linux-androideabi-g++.exe  $(CXX_DEFINES) $(CXX_FLAGS) -S D:\thesis\repositories\chatClientJNI\src\JNIChatClientListener.cpp -o CMakeFiles\chatClientJNI.dir\src\JNIChatClientListener.cpp.s

CMakeFiles/chatClientJNI.dir/src/JNIChatClientListener.cpp.o.requires:

.PHONY : CMakeFiles/chatClientJNI.dir/src/JNIChatClientListener.cpp.o.requires

CMakeFiles/chatClientJNI.dir/src/JNIChatClientListener.cpp.o.provides: CMakeFiles/chatClientJNI.dir/src/JNIChatClientListener.cpp.o.requires
	$(MAKE) -f CMakeFiles\chatClientJNI.dir\build.make CMakeFiles/chatClientJNI.dir/src/JNIChatClientListener.cpp.o.provides.build
.PHONY : CMakeFiles/chatClientJNI.dir/src/JNIChatClientListener.cpp.o.provides

CMakeFiles/chatClientJNI.dir/src/JNIChatClientListener.cpp.o.provides.build: CMakeFiles/chatClientJNI.dir/src/JNIChatClientListener.cpp.o


# Object files for target chatClientJNI
chatClientJNI_OBJECTS = \
"CMakeFiles/chatClientJNI.dir/src/dm_chatclient_controller_NativeChatClientController.cpp.o" \
"CMakeFiles/chatClientJNI.dir/src/JNIChatClientListener.cpp.o"

# External object files for target chatClientJNI
chatClientJNI_EXTERNAL_OBJECTS =

libchatClientJNI.so: CMakeFiles/chatClientJNI.dir/src/dm_chatclient_controller_NativeChatClientController.cpp.o
libchatClientJNI.so: CMakeFiles/chatClientJNI.dir/src/JNIChatClientListener.cpp.o
libchatClientJNI.so: CMakeFiles/chatClientJNI.dir/build.make
libchatClientJNI.so: CMakeFiles/chatClientJNI.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=D:\thesis\repositories\chatClientJNI\build\Android-armeabi-Debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX shared library libchatClientJNI.so"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\chatClientJNI.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/chatClientJNI.dir/build: libchatClientJNI.so

.PHONY : CMakeFiles/chatClientJNI.dir/build

CMakeFiles/chatClientJNI.dir/requires: CMakeFiles/chatClientJNI.dir/src/dm_chatclient_controller_NativeChatClientController.cpp.o.requires
CMakeFiles/chatClientJNI.dir/requires: CMakeFiles/chatClientJNI.dir/src/JNIChatClientListener.cpp.o.requires

.PHONY : CMakeFiles/chatClientJNI.dir/requires

CMakeFiles/chatClientJNI.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\chatClientJNI.dir\cmake_clean.cmake
.PHONY : CMakeFiles/chatClientJNI.dir/clean

CMakeFiles/chatClientJNI.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" D:\thesis\repositories\chatClientJNI D:\thesis\repositories\chatClientJNI D:\thesis\repositories\chatClientJNI\build\Android-armeabi-Debug D:\thesis\repositories\chatClientJNI\build\Android-armeabi-Debug D:\thesis\repositories\chatClientJNI\build\Android-armeabi-Debug\CMakeFiles\chatClientJNI.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/chatClientJNI.dir/depend

