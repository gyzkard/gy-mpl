# To update the gy-mpl version, from a working directory that is clean except for an
# updated docs/release_notes.md file, update the version numbers below. This makefile will
# generate a new version.hpp, *AMEND THE MOST RECENT COMMIT*, and git-tag the commit.

set(GYMPL_VERSION_MAJOR 0)
set(GYMPL_VERSION_MINOR 1)
set(GYMPL_VERSION_PATCHLEVEL 0)

# prefix with - if set
set(GYMPL_VERSION_PRERELEASE_ID "")
# prefix with + if set
set(GYMPL_VERSION_BUILD_METADATA "")
