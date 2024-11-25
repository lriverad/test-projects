BUILD_TYPE=release
PROJECT_NAME=app

.DEFAULT_GOAL := linux

.PHONY: configure_linux
configure_linux:
	cmake -S . -B build/linux/$(BUILD_TYPE) -DCMAKE_TOOLCHAIN_FILE=tools/linux-toolchain.cmake -DCMAKE_BUILD_TYPE=$(BUILD_TYPE) -DCMAKE_EXPORT_COMPILE_COMMANDS=ON -DPROJECT_NAME=$(PROJECT_NAME)
	cp build/linux/$(BUILD_TYPE)/compile_commands.json . -rf

.PHONY: linux
linux: configure_linux
	cmake --build build/linux/$(BUILD_TYPE)

.PHONY: configure_windows
configure_windows:
	cmake -S . -B build/windows/$(BUILD_TYPE) -DCMAKE_TOOLCHAIN_FILE=tools/windows-toolchain.cmake -DCMAKE_BUILD_TYPE=$(BUILD_TYPE) -DCMAKE_EXPORT_COMPILE_COMMANDS=ON -DPROJECT_NAME=$(PROJECT_NAME)
	cp build/windows/$(BUILD_TYPE)/compile_commands.json . -rf

.PHONY: windows
windows: configure_windows
	cmake --build build/windows/$(BUILD_TYPE) --config $(BUILD_TYPE)

.PHONY: configure_wasm
configure_wasm:
	emcmake cmake -S . -B build/wasm/$(BUILD_TYPE) -DCMAKE_TOOLCHAIN_FILE=tools/wasm-toolchain.cmake -DCMAKE_BUILD_TYPE=$(BUILD_TYPE) -DCMAKE_EXPORT_COMPILE_COMMANDS=ON -DPROJECT_NAME=$(PROJECT_NAME)
	cp build/wasm/$(BUILD_TYPE)/compile_commands.json . -rf

.PHONY: wasm
wasm: configure_wasm
	cmake --build build/wasm/$(BUILD_TYPE)
	cp src/web/* bin/wasm