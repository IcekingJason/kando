//////////////////////////////////////////////////////////////////////////////////////////
//   _  _ ____ _  _ ___  ____                                                           //
//   |_/  |__| |\ | |  \ |  |    This file belongs to Kando, the cross-platform         //
//   | \_ |  | | \| |__/ |__|    pie menu. Read more on github.com/kando-menu/kando     //
//                                                                                      //
//////////////////////////////////////////////////////////////////////////////////////////

// SPDX-FileCopyrightText: Simon Schneegans <code@simonschneegans.de>
// SPDX-FileCopyrightText: Jason Ice <IcekingJason@outlook.com>
// SPDX-License-Identifier: MIT

import { DialEvent } from '../../../../common';

export type Native = {
  /**
   * This uses Win32 API calls to get the name and the class of the currently focused
   * application window, as well as the current pointer position.
   */
  getWMInfo(): { app: string; window: string; pointerX: number; pointerY: number };

  /**
   * Returns an array of all currently open windows, each with an 'app' (executable name)
   * and a 'window' (window title) property.
   */
  getOpenWindows(): Array<{ app: string; window: string }>;

  /**
   * Focuses the window with the given title and app name.
   *
   * @param windowName The window title.
   * @param appName The executable name of the app.
   */
  focusWindow(windowName: string, appName: string): void;

  /**
   * This simulates a mouse movement.
   *
   * @param dx The horizontal movement in pixels.
   * @param dy The vertical movement in pixels.
   */
  movePointer(dx: number, dy: number): void;

  /**
   * This simulates a key press or release.
   *
   * @param keycode The Win32 key code of the key to simulate.
   * @param down If true, a key press is simulated. Otherwise, a key release is simulated.
   */
  simulateKey(keycode: number, down: boolean): void;

  /**
   * This fixes the acrylic effect on Windows after the window has been resized. See here:
   * https://github.com/electron/electron/issues/42393
   *
   * @param hwnd The window handle.
   */
  fixAcrylicEffect(hwnd: number): void;

  /**
   * This lists all installed applications.
   *
   * @returns An array of objects containing the application's ID, name, and
   *   base64-encoded icon.
   */
  listInstalledApplications(): {
    id: string;
    name: string;
    base64Icon: string;
  }[];

  /**
   * This starts capturing input from a wheel device such as the Surface Dial. The events
   * are forwarded to the given callback. The capture is bound to the given window, so
   * events are only received while this window is the currently active window. See also
   * stopDialCapture().
   *
   * @param hwnd A buffer containing the native window handle of the window to bind the
   *   capture to.
   * @param degreesPerStep The minimum rotation in degrees required for a rotation event.
   * @param useHaptics Whether the device should provide haptic feedback.
   * @param callback The callback which is called for each event of the wheel device.
   * @returns True if the capture was started successfully.
   */
  startDialCapture(
    hwnd: Buffer,
    degreesPerStep: number,
    useHaptics: boolean,
    callback: (event: DialEvent) => void
  ): boolean;

  /**
   * This stops the capture which was started by startDialCapture() and restores the
   * default behavior of the wheel device.
   */
  stopDialCapture(): void;
};

const native: Native = require('./../../../../../build/Release/NativeWin32.node');

export { native };
