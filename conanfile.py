import os

from conan import ConanFile
from conan.tools.files import copy


class UnitTemplateLibraryConan(ConanFile):
    name = "unit-template-library"
    version = "2.0.0"
    description = "Header-only C++17 compile-time SI units / dimensional-analysis library"
    license = "MIT"
    author = "Adam Ligocki <ligocki.a@gmail.com>"
    url = "https://github.com/adamek727/Unit-Template-Library"
    homepage = "https://github.com/adamek727/Unit-Template-Library"
    topics = ("units", "dimensional-analysis", "si", "header-only", "constexpr", "cpp17")

    package_type = "header-library"
    settings = "os", "arch", "compiler", "build_type"
    no_copy_source = True
    exports_sources = "include/*", "License.txt"

    def package_id(self):
        self.info.clear()

    def package(self):
        copy(self, "*.hpp",
             src=os.path.join(self.source_folder, "include"),
             dst=os.path.join(self.package_folder, "include"))
        copy(self, "License.txt",
             src=self.source_folder,
             dst=os.path.join(self.package_folder, "licenses"))

    def package_info(self):
        self.cpp_info.set_property("cmake_file_name", "utl")
        self.cpp_info.set_property("cmake_target_name", "utl::utl")
        self.cpp_info.bindirs = []
        self.cpp_info.libdirs = []
