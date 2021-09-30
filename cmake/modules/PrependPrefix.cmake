# taken from https://stackoverflow.com/questions/4346412/how-to-prepend-all-filenames-on-the-list-with-common-path/27630120
function(Prepend_Prefix var prefix)
    set(temp_list "")
    foreach(opt ${${var}})
        list(APPEND temp_list "${prefix}${opt}")
    endforeach(opt)
    set(${var} "${temp_list}" PARENT_SCOPE)
endfunction(Prepend_Prefix)

