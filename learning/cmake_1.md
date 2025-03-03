Yes, absolutely! CMake has features to help you automatically find source files, which is much better than manually listing them, especially for larger or evolving projects. Here's a breakdown of the common approaches and best practices:

**1. `file(GLOB ...)` (Simple, but Less Recommended):**

   The simplest way is to use `file(GLOB ...)` to find files matching a pattern.  *However*, this approach is generally **discouraged** for reasons we'll explain below.

   ```cmake
   cmake_minimum_required(VERSION 3.10)
   project(MyProject)

   file(GLOB SOURCES "src/*.cpp")  # Find all .cpp files in the 'src' directory
   add_executable(myprogram ${SOURCES})
   ```

* **`file(GLOB SOURCES "src/*.cpp")`**: This finds all files ending in `.cpp` within the `src` directory (you'd need to create a `src` directory and move your `.cpp` files there). The found files are stored in a list variable named `SOURCES`.
* **`add_executable(myprogram ${SOURCES})`**:  Uses the `SOURCES` list variable to specify the source files for the executable.

   **Why `file(GLOB ...)` is Discouraged:**

* **CMake Doesn't Track Changes:** The crucial problem is that CMake doesn't automatically detect *new* files added to your `src` directory.  If you add a new `.cpp` file, CMake *won't* reconfigure the build until you manually re-run CMake. This leads to build errors that are hard to track down ("undefined reference" errors are a common symptom).  CMake only rebuilds based on changes to files that it *knows* about.
* **Can Be Too Broad:**  `GLOB` can sometimes include files you *don't* want (e.g., backup files, temporary files).

**2. `file(GLOB_RECURSE ...)` (Even Less Recommended):**

   `file(GLOB_RECURSE ...)` is similar to `file(GLOB ...)`, but it searches *recursively* through subdirectories.  This has the same drawbacks as `GLOB` and can be even more problematic if your project has a complex directory structure.  Avoid this.

   ```cmake
   file(GLOB_RECURSE SOURCES "src/*.cpp") # Recursively find .cpp files
   ```

**3. `aux_source_directory` (Better, but Still Not Ideal):**

   `aux_source_directory` is another way to find source files in a directory.  It's slightly better than `GLOB` because it doesn't rely on shell globbing, but it still suffers from the same change-tracking issue: CMake won't reconfigure automatically when new files are added.

   ```cmake
   cmake_minimum_required(VERSION 3.10)
   project(MyProject)

   aux_source_directory(src SOURCES)
   add_executable(myprogram ${SOURCES})
   ```

**4. Explicitly List Files (Recommended for Small Projects):**

   For smaller projects, or when you need very precise control, explicitly listing the source files is often the simplest and most reliable approach.  Yes, it's a bit more manual, but it avoids the problems of the automatic methods.

   ```cmake
   cmake_minimum_required(VERSION 3.10)
   project(MyProject)

   add_executable(myprogram
       src/ShittyStack.cpp
       src/main.cpp
   )
   ```

**5. `target_sources` (Best Practice for Modern CMake):**

   `target_sources` is the recommended approach for modern CMake (version 3.1 and later). It allows you to add source files to a *specific target* (like your executable), and it handles change tracking correctly.  This is the most robust and maintainable solution.

   ```cmake
   cmake_minimum_required(VERSION 3.10)
   project(MyProject)

   # Create the executable target (without specifying sources initially)
   add_executable(myprogram)

   # Add source files to the target
   target_sources(myprogram
       PRIVATE
           src/ShittyStack.cpp
           src/main.cpp
   )
   ```

* You can add to your list incrementally.

   ```cmake
   cmake_minimum_required(VERSION 3.10)
   project(MyProject)
   add_executable(myprogram)

   target_sources(myprogram
      PRIVATE
         src/main.cpp
         src/ShittyStack.cpp
   )
   target_sources(myprogram
      PRIVATE
         src/otherFile.cpp
   )
   ```

* **`add_executable(myprogram)`**: Creates the executable target *without* specifying source files yet.
* **`target_sources(myprogram PRIVATE ...)`**: Adds the listed source files to the `myprogram` target.  `PRIVATE` means these sources are only used for building `myprogram` (not for other targets that might depend on it).  You could also use `PUBLIC` or `INTERFACE` for different visibility levels.
* The great thing about target_sources is that cmake *will* reconfigure itself upon the addition/removal of new files.

**6. Using `target_sources` with a Helper Function (For Larger Projects):**

   For larger projects with many source files, you can combine `target_sources` with a helper function to organize your source files more cleanly. This avoids long lists of files in your main `CMakeLists.txt`.

   ```cmake
   # CMakeLists.txt
   cmake_minimum_required(VERSION 3.10)
   project(MyProject)

   # Helper function to add sources to a target
   function(add_sources_to_target target_name)
       foreach(source_file ${ARGN})
           target_sources(${target_name} PRIVATE ${source_file})
       endforeach()
   endfunction()

   add_executable(myprogram)

   # Use the helper function
   add_sources_to_target(myprogram
       src/ShittyStack.cpp
       src/main.cpp
   )

   # You could also group sources in subdirectories and use the function multiple times
   add_sources_to_target(myprogram src/utils/helper1.cpp src/utils/helper2.cpp)
   ```

**Summary of Recommendations:**

* **Best Practice (Most Cases):** Use `target_sources` to explicitly list your source files. This is the most reliable and maintainable approach, especially for modern CMake.
* **Small Projects:** Explicitly listing files in `add_executable` is also fine.
* **Larger Projects:** Use `target_sources` with a helper function to organize your source files.
* **Avoid:**  `file(GLOB ...)` and `file(GLOB_RECURSE ...)` and `aux_source_directory` are generally discouraged due to their change-tracking limitations.

The `target_sources` method is the best way to ensure that CMake correctly tracks your source files and rebuilds your project when necessary, preventing unexpected build errors. It also integrates well with other CMake features like creating libraries and managing dependencies. Using a helper function, as demonstrated in example 6, further enhances organization and readability, especially as projects grow.
