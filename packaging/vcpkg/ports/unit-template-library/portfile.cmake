vcpkg_from_github(
    OUT_SOURCE_PATH SOURCE_PATH
    REPO adamek727/Unit-Template-Library
    REF "v${VERSION}"
    SHA512 da522688b28492d6bde5505dfcfee9498ec5b0d31a96794e55fea674db68718b763374a4db5c8a6d56b1ed4cb449a65eef249f362d1aa71cb6f52a68f223ecfc
    HEAD_REF main
)

# Header-only: install the headers and the license, nothing to build.
file(INSTALL "${SOURCE_PATH}/include/" DESTINATION "${CURRENT_PACKAGES_DIR}/include")

vcpkg_install_copyright(FILE_LIST "${SOURCE_PATH}/License.txt")
