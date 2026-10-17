//////////////////////////////////////////////////////////////////////////////////////////
//   _  _ ____ _  _ ___  ____                                                           //
//   |_/  |__| |\ | |  \ |  |    This file belongs to Kando, the cross-platform         //
//   | \_ |  | | \| |__/ |__|    pie menu. Read more on github.com/kando-menu/kando     //
//                                                                                      //
//////////////////////////////////////////////////////////////////////////////////////////

// SPDX-FileCopyrightText: Simon Schneegans <code@simonschneegans.de>
// SPDX-FileCopyrightText: Jason Ice <IcekingJason@outlook.com>
// SPDX-License-Identifier: MIT

#ifndef NATIVE_HPP
#define NATIVE_HPP

#include <napi.h>

#include <memory>

/**
 * This class allows moving the mouse pointer, simulating key presses, and getting the
 * active window's name and app on Windows.
 */
class Native : public Napi::Addon<Native> {
 public:
  Native(Napi::Env env, Napi::Object exports);
  virtual ~Native();

 private:
  /**
   * This function is called when the movePointer function is called from JavaScript. It
   * expects two numbers which are used for the relative movement of the pointer.
   * If something goes wrong, it throws a JavaScript exception.
   *
   * @param info The arguments passed to the movePointer function. It should contain two
   *             numbers.
   */
  void movePointer(const Napi::CallbackInfo& info);

  /**
   * This function is called when the simulateKey function is called from JavaScript. It
   * expects a number which is used as the scan code of the key to be pressed and a
   * boolean which indicates whether the key should be pressed or released.
   * If something goes wrong, it throws a JavaScript exception.
   *
   * @param info The arguments passed to the simulateKey function. It should contain a
   *             number and a boolean.
   */
  void simulateKey(const Napi::CallbackInfo& info);

  /**
   * This function is called when the getWMInfo function is called from JavaScript.
   * It returns the app and class of the currently active window, as well as the
   * current pointer position.
   *
   * @param info The arguments passed to the getWMInfo function. It should contain
   *            no arguments.
   */
  Napi::Value getWMInfo(const Napi::CallbackInfo& info);

  /**
   * This function is called when the getOpenWindows function is called from JavaScript.
   * It returns an array of objects, each with an 'app' and a 'window' property,
   * representing all currently open windows.
   *
   * @param info The arguments passed to the getOpenWindows function. It should contain
   *             no arguments.
   */
  Napi::Value getOpenWindows(const Napi::CallbackInfo& info);

  /**
   * This function is called when the focusWindow function is called from JavaScript.
   * It focuses the window with the given window title and app name.
   *
   * @param info The arguments passed to the focusWindow function. It should contain
   *             two strings: the window title and the app name.
   */
  void focusWindow(const Napi::CallbackInfo& info);

  /**
   * After maximizing a window, the acrylic effect is sometimes broken. This function
   * is called after window creation to fix the acrylic effect. See here:
   * https://github.com/electron/electron/issues/42393
   *
   * @param info The arguments passed to the fixAcrylicEffect function. It should contain
   *           the window handle.
   */
  void fixAcrylicEffect(const Napi::CallbackInfo& info);

  /**
   * This function returns a list of all installed applications.
   *
   * @param info The arguments passed to the listInstalledApplications function. It should
   * contain no arguments.
   */
  Napi::Value listInstalledApplications(const Napi::CallbackInfo& info);

  /**
   * This function is called when the startDialCapture function is called from JavaScript.
   * It expects a buffer which contains the native window handle of the window to bind the
   * capture to, the rotation resolution in degrees, a boolean which indicates whether the
   * wheel device should provide haptic feedback, and a callback which is called for each
   * event of the wheel device. It returns true if the capture was started successfully.
   *
   * @param info The arguments passed to the startDialCapture function. It should contain
   *             a buffer, a number, a boolean and a function.
   */
  Napi::Value startDialCapture(const Napi::CallbackInfo& info);

  /**
   * This function is called when the stopDialCapture function is called from JavaScript.
   * It stops the capture which was started by startDialCapture and restores the default
   * behavior of the wheel device. It expects no arguments.
   *
   * @param info The arguments passed to the stopDialCapture function. It should contain
   *             no arguments.
   */
  void stopDialCapture(const Napi::CallbackInfo& info);

  /**
   * This struct contains the state required to capture input from a wheel device such as
   * the Surface Dial. It is defined in Native.cpp.
   */
  struct DialCapture;

  /** This is used to capture input from a wheel device such as the Surface Dial. */
  std::unique_ptr<DialCapture> mDialCapture;
};

#endif // NATIVE_HPP