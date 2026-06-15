# Zephyr-RTOS-Cookbook

Zephyr RTOS Cookbook, published by Packt.

This repository is a [west](https://docs.zephyrproject.org/latest/develop/west/index.html)
workspace. The example applications are organized per chapter (`chapter2/`,
`chapter3/`, ...), and each one is a standalone Zephyr application.

## Getting started

These instructions use the **Workbench for Zephyr** VS Code extension.

### 1. Install the prerequisites

1. Install the **Workbench for Zephyr** extension in VS Code.
2. Open the Workbench for Zephyr and **install the host tools** (the native
   dependencies needed to build Zephyr). Make sure this step completes before
   continuing.

### 2. Import the west workspace

1. In the Workbench for Zephyr, start **Import a west workspace**.
2. For the source, select the **Repository** option.
3. Set the URL to this repository.
4. Click **Import** and wait for west to clone the manifest and pull in the
   Zephyr tree and modules (downloaded under `deps/`).

### 3. Import the SDK

1. In the Workbench for Zephyr, choose **Import SDK**.
2. Import version **zephyr-sdk-1.0.1**.
3. Install the SDK **at the same level as the workspace, not inside the west
   workspace**, keep the SDK folder as a sibling of this repository, not a
   child of it.

### 4. Select a board

By default every application in this repository targets the **`frdm_mcxn236`**
board. To build for a different board:

1. In the Workbench for Zephyr, **right-click the application** you want to build.
2. Choose **Configure**.
3. Change the **board** to your target.

You can now build, flash, and debug the application from the Workbench for Zephyr.
