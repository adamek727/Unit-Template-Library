vcpkg_from_github(
    OUT_SOURCE_PATH SOURCE_PATH
    REPO adamek727/Unit-Template-Library
    REF "v${VERSION}"
    SHA512 e1ca87abc42ba0de13ffe8028fb39b93803bac39a845b0a67afe769087ef4f1bd2303ef0c86a31322b7c457e74a908de7edac668c732211de28f8ce45dd48177
    HEAD_REF main
)

# Header-only: install the headers and the license, nothing to build.
file(INSTALL "${SOURCE_PATH}/include/" DESTINATION "${CURRENT_PACKAGES_DIR}/include")

vcpkg_install_copyright(FILE_LIST "${SOURCE_PATH}/License.txt")
