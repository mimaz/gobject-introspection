/************************************************************/
/* THIS FILE IS GENERATED DO NOT EDIT */
/************************************************************/

/**
 * GModule:
 *
 * The #GModule struct is an opaque data structure to represent a
 * [dynamically-loaded module][glib-Dynamic-Loading-of-Modules].
 * It should only be accessed via the following functions.
 */


/**
 * GModuleCheckInit:
 * @module: the #GModule corresponding to the module which has just been loaded
 *
 * Specifies the type of the module initialization function.
 * If a module contains a function named g_module_check_init() it is called
 * automatically when the module is loaded. It is passed the #GModule structure
 * and should return %NULL on success or a string describing the initialization
 * error.
 *
 * Returns: %NULL on success, or a string describing the initialization error
 */


/**
 * GModuleFlags:
 * @G_MODULE_BIND_LAZY: specifies that symbols are only resolved when
 *     needed. The default action is to bind all symbols when the module
 *     is loaded.
 * @G_MODULE_BIND_LOCAL: specifies that symbols in the module should
 *     not be added to the global name space. The default action on most
 *     platforms is to place symbols in the module in the global name space,
 *     which may cause conflicts with existing symbols.
 * @G_MODULE_BIND_MASK: mask for all flags.
 *
 * Flags passed to g_module_open().
 * Note that these flags are not supported on all platforms.
 */


/**
 * GModuleUnload:
 * @module: the #GModule about to be unloaded
 *
 * Specifies the type of the module function called when it is unloaded.
 * If a module contains a function named g_module_unload() it is called
 * automatically when the module is unloaded.
 * It is passed the #GModule structure.
 */


/**
 * G_MODULE_EXPORT:
 *
 * Used to declare functions exported by modules. This is a no-op on Linux
 * and Unices, but when compiling for Windows, it marks a symbol to be
 * exported from the library or executable being built.
 */


/**
 * G_MODULE_IMPORT:
 *
 * Used to declare functions imported from modules.
 */


/**
 * G_MODULE_SUFFIX:
 *
 * Expands to the proper shared library suffix for the current platform
 * without the leading dot. For most Unices and Linux this is "so", and
 * for Windows this is "dll".
 */


/**
 * SECTION:modules
 * @title: Dynamic Loading of Modules
 * @short_description: portable method for dynamically loading 'plug-ins'
 *
 * These functions provide a portable way to dynamically load object files
 * (commonly known as 'plug-ins'). The current implementation supports all
 * systems that provide an implementation of dlopen() (e.g. Linux/Sun), as
 * well as Windows platforms via DLLs.
 *
 * A program which wants to use these functions must be linked to the
 * libraries output by the command `pkg-config --libs gmodule-2.0`.
 *
 * To use them you must first determine whether dynamic loading
 * is supported on the platform by calling g_module_supported().
 * If it is, you can open a module with g_module_open(),
 * find the module's symbols (e.g. function names) with g_module_symbol(),
 * and later close the module with g_module_close().
 * g_module_name() will return the file name of a currently opened module.
 *
 * If any of the above functions fail, the error status can be found with
 * g_module_error().
 *
 * The #GModule implementation features reference counting for opened modules,
 * and supports hook functions within a module which are called when the
 * module is loaded and unloaded (see #GModuleCheckInit and #GModuleUnload).
 *
 * If your module introduces static data to common subsystems in the running
 * program, e.g. through calling
 * `g_quark_from_static_string ("my-module-stuff")`,
 * it must ensure that it is never unloaded, by calling g_module_make_resident().
 *
 * Example: Calling a function defined in a GModule
 * |[<!-- language="C" -->
 * // the function signature for 'say_hello'
 * typedef void (* SayHelloFunc) (const char *message);
 *
 * gboolean
 * just_say_hello (const char *filename, GError **error)
 * {
 *   SayHelloFunc  say_hello;
 *   GModule      *module;
 *
 *   module = g_module_open (filename, G_MODULE_BIND_LAZY);
 *   if (!module)
 *     {
 *       g_set_error (error, FOO_ERROR, FOO_ERROR_BLAH,
 *                    "%s", g_module_error ());
 *       return FALSE;
 *     }
 *
 *   if (!g_module_symbol (module, "say_hello", (gpointer *)&say_hello))
 *     {
 *       g_set_error (error, SAY_ERROR, SAY_ERROR_OPEN,
 *                    "%s: %s", filename, g_module_error ());
 *       if (!g_module_close (module))
 *         g_warning ("%s: %s", filename, g_module_error ());
 *       return FALSE;
 *     }
 *
 *   if (say_hello == NULL)
 *     {
 *       g_set_error (error, SAY_ERROR, SAY_ERROR_OPEN,
 *                    "symbol say_hello is NULL");
 *       if (!g_module_close (module))
 *         g_warning ("%s: %s", filename, g_module_error ());
 *       return FALSE;
 *     }
 *
 *   // call our function in the module
 *   say_hello ("Hello world!");
 *
 *   if (!g_module_close (module))
 *     g_warning ("%s: %s", filename, g_module_error ());
 *   return TRUE;
 *  }
 * ]|
 */


/**
 * g_module_build_path:
 * @directory: (nullable): the directory where the module is. This can be
 *     %NULL or the empty string to indicate that the standard platform-specific
 *     directories will be used, though that is not recommended
 * @module_name: the name of the module
 *
 * A portable way to build the filename of a module. The platform-specific
 * prefix and suffix are added to the filename, if needed, and the result
 * is added to the directory, using the correct separator character.
 *
 * The directory should specify the directory where the module can be found.
 * It can be %NULL or an empty string to indicate that the module is in a
 * standard platform-specific directory, though this is not recommended
 * since the wrong module may be found.
 *
 * For example, calling g_module_build_path() on a Linux system with a
 * @directory of `/lib` and a @module_name of "mylibrary" will return
 * `/lib/libmylibrary.so`. On a Windows system, using `\Windows` as the
 * directory it will return `\Windows\mylibrary.dll`.
 *
 * Returns: the complete path of the module, including the standard library
 *     prefix and suffix. This should be freed when no longer needed
 */


/**
 * g_module_close:
 * @module: a #GModule to close
 *
 * Closes a module.
 *
 * Returns: %TRUE on success
 */


/**
 * g_module_error:
 *
 * Gets a string describing the last module error.
 *
 * Returns: a string describing the last module error
 */


/**
 * g_module_make_resident:
 * @module: a #GModule to make permanently resident
 *
 * Ensures that a module will never be unloaded.
 * Any future g_module_close() calls on the module will be ignored.
 */


/**
 * g_module_name:
 * @module: a #GModule
 *
 * Returns the filename that the module was opened with.
 *
 * If @module refers to the application itself, "main" is returned.
 *
 * Returns: (transfer none): the filename of the module
 */


/**
 * g_module_open:
 * @file_name: (nullable): the name of the file containing the module, or %NULL
 *     to obtain a #GModule representing the main program itself
 * @flags: the flags used for opening the module. This can be the
 *     logical OR of any of the #GModuleFlags
 *
 * Opens a module. If the module has already been opened,
 * its reference count is incremented.
 *
 * First of all g_module_open() tries to open @file_name as a module.
 * If that fails and @file_name has the ".la"-suffix (and is a libtool
 * archive) it tries to open the corresponding module. If that fails
 * and it doesn't have the proper module suffix for the platform
 * (#G_MODULE_SUFFIX), this suffix will be appended and the corresponding
 * module will be opended. If that fails and @file_name doesn't have the
 * ".la"-suffix, this suffix is appended and g_module_open() tries to open
 * the corresponding module. If eventually that fails as well, %NULL is
 * returned.
 *
 * Returns: a #GModule on success, or %NULL on failure
 */


/**
 * g_module_supported:
 *
 * Checks if modules are supported on the current platform.
 *
 * Returns: %TRUE if modules are supported
 */


/**
 * g_module_symbol:
 * @module: a #GModule
 * @symbol_name: the name of the symbol to find
 * @symbol: (out): returns the pointer to the symbol value
 *
 * Gets a symbol pointer from a module, such as one exported
 * by #G_MODULE_EXPORT. Note that a valid symbol can be %NULL.
 *
 * Returns: %TRUE on success
 */



/************************************************************/
/* THIS FILE IS GENERATED DO NOT EDIT */
/************************************************************/
