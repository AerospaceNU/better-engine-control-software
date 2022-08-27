include(FetchContent)

FetchContent_Declare(libserial                              # name of the content
        GIT_REPOSITORY https://github.com/crayzeewulf/libserial.git  # the repository
        GIT_TAG        1d1e47a2faae0470f93eb291263b0ce7ea119a81                        # the tag
        )

add_subdirectory(libserial)