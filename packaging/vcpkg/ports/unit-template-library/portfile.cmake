vcpkg_from_github(
    OUT_SOURCE_PATH SOURCE_PATH
    REPO adamek727/Unit-Template-Library
    REF "v${VERSION}"
    SHA512 1b5bf2d7db4ad4a4725ba3576c4eedcba0184f9e12a731885eff92b6264c9fa79af7f6c380a96f362e732982ba9ace84fb8c4aa4439c3c30512be6fb6c251cd7
    HEAD_REF main
)

# Header-only: install the headers and the license, nothing to build.
file(INSTALL "${SOURCE_PATH}/include/" DESTINATION "${CURRENT_PACKAGES_DIR}/include")

vcpkg_install_copyright(FILE_LIST "${SOURCE_PATH}/License.txt")
