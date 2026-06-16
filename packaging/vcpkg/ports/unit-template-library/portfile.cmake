vcpkg_from_github(
    OUT_SOURCE_PATH SOURCE_PATH
    REPO adamek727/Unit-Template-Library
    REF "v${VERSION}"
    SHA512 267755eff3c94dd1db0f9ac9a696a958915d4a8ce8d9a6ac24322554ed7a5bc5907e165b2f6b952fbf20b8ca3495a87ef3f98698841f97047f0c2e0c389b8273
    HEAD_REF main
)

# Header-only: install the headers and the license, nothing to build.
file(INSTALL "${SOURCE_PATH}/include/" DESTINATION "${CURRENT_PACKAGES_DIR}/include")

vcpkg_install_copyright(FILE_LIST "${SOURCE_PATH}/License.txt")
