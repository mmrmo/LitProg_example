# These AWK constructs use regular expression (and their negation, via ! in front) to extract the new tags:
# A.Marmodoro, Ludwig-Maximilians-Universitaet Muenchen, 2018.

# === AUTOMATIC LATEX SOURCE FILES CONSTRUCTION: ===
# Everything between:  %start_latex   and:   %stop_latex 
# is legitimate Latex. 
# The rest is also kept, but commented out, so as not to break
# lines numbering for possible errors reporting by the LATEX compiler:
#
# Duplicated dollar sign just to escape Makefile expansion.
MAKE_PADDED_LATEX = awk '/^%start_latex$$/,/^%stop_latex$$/ { if ($$0 != "%start*" && $$0 !="%stop_*") print $$0; next }    !/^! %start_latex$$/,!/^! %stop_latex$$/ {print "% not_Latex: "$$0;next}'
# ============================================================================


# === AUTOMATIC FORTRAN 77 SOURCE FILES CONSTRUCTION: ===
# Everything between:   %start_f77   and:   %stop_f90 
# is legitimate Fortran 77. 
# The rest is also kept, but commented out, so as not to break
# lines numbering for possible errors reporting by the FORTRAN77 compiler:
#
# Duplicated dollar sign just to escape Makefile expansion.
MAKE_PADDED_F77 = awk '/^%start_f77$$/,/^%stop_f77$$/ { if ($$0 == "%start_f77" ) print "! %start_f77"; else if( $$0 =="%stop_f77" ) print "! %stop_f77"; else print $$0; next }    !/^! %start_f77$$/,!/^! %stop_f77$$/ {print "! not_F77: "$$0;next}'

# Same as above, except that target is terser Fortran 77, suitable for inclusion within LaTex via \lstinputlisting{filename.f_pruned}:
MAKE_UNPADDED_F77 = awk '/^%start_f77$$/,/^%stop_f77$$/ { if ($$0 !="%start_f77" && $$0 !="%stop_f77") print $$0; next }'
# ============================================================================


# === AUTOMATIC FORTRAN 90 SOURCE FILES CONSTRUCTION: ===
# Everything between:   %start_f90   and:   %stop_f90 
# is legitimate Fortran 90. 
# The rest is also kept, but commented out, so as not to break
# lines numbering for possible errors reporting by the FORTRAN77 compiler:
#
# Duplicated dollar sign just to escape Makefile expansion.
MAKE_PADDED_F90 = awk '/^%start_f90$$/,/^%stop_f90$$/ { if ($$0 == "%start_f90" ) print "! %start_f90"; else if( $$0 =="%stop_f90" ) print "! %stop_f90"; else print $$0; next }    !/^! %start_f90$$/,!/^! %stop_f90$$/ {print "! not_F90: "$$0;next}'

# Same as above, except that target is terser Fortran 90, 
# i.e. devoid of (commented out) LaTex source, as required 
# for inclusion within LaTex via \lstinputlisting{filename.F90_pruned} and no duplications:
MAKE_UNPADDED_F90 = awk '/^%start_f90$$/,/^%stop_f90$$/ { if ($$0 !="%start_f90" && $$0 !="%stop_f90") print $$0; next }'
# ============================================================================

# Extract selected portion of source, for inclusion within LaTex
# of only relevant portion to comment:
SPLIT_SOURCE_SNIPPETS = awk '/^.start_source_snippet/,/^.stop_source_snippet/ { snippet_nr +=1 ; snippet_identifier = snippet_nr-NR ; { if ( snippet_identifier != snippet_previous_identifier ) { snippet_previous_identifier = snippet_identifier ; block_identifier +=1 } }; print $$0 > FILENAME"_snippet_"block_identifier".snippet" }'
# For inclusion within LaTex via \lstinputlisting{filename.F90_snippet_pruned} and no duplications:
# ============================================================================

# === AUTOMATIC OpenCL SOURCE FILES CONSTRUCTION: ===
# Everything between:   %start_opencl and:   %stop_opencl 
# is legitimate OpenCL. The rest is also kept, but commented out, to maintain lines numbering:
# Duplicated dollar sign just to escape Makefile expansion.
MAKE_PADDED_OPENCL = awk '/^%start_opencl$$/,/^%stop_opencl$$/ { if ($$0 == "%start_opencl" ) print "// %start_opencl"; else if( $$0 =="%stop_opencl" ) print "// %stop_opencl"; else print $$0; next }    !/^! %start_opencl$$/,!/^! %stop_opencl$$/ {print "// not_OpenCL: "$$0;next}'

# Same as above, except that target is terser OpenCL, suitable for inclusion within LaTex via \lstinputlisting{filename.cl_pruned}:
MAKE_UNPADDED_OPENCL = awk '/^%start_opencl$$/,/^%stop_opencl$$/ { if ($$0 != "%start_opencl" && $$0 != "%stop_opencl") print $$0; next }'
# ============================================================================


# === AUTOMATIC C SOURCE FILES CONSTRUCTION: ===
# Everything between %start_c and %stop_c is legitimate C99. The rest is also kept, but commented out, to maintain lines numbering:
# Duplicated dollar sign just to escape Makefile expansion.
MAKE_PADDED_C = awk '/^%start_c$$/,/^%stop_c$$/ { if ($$0 == "%start_c" ) print "// %start_c"; else if( $$0 =="%stop_c" ) print "// %stop_c"; else print $$0; next }    !/^! %start_c$$/,!/^! %stop_c$$/ {print "// not_C: "$$0;next}'

# Same as above, except that target is terser C99, suitable for inclusion within LaTex via \lstinputlisting{filename.c_pruned}:
MAKE_UNPADDED_C = awk '/^%start_c$$/,/^%stop_c$$/ { if ($$0 != "%start_c" && $$0 != "%stop_c") print $$0; next }'
# ============================================================================

# If just a single subroutine per file: look inside it for its number, as useful for debugging:
# EXTRACT_SUBROUTINE_IOUNIT = grep "subroutine_iounit=" | awk -F"subroutine_iounit=" '{print "Selective debug: \\texttt{DEBUGLEVEL="$$2"}"}'
# If just a single subroutine per file: look inside it for its number, as useful for debugging:
# EXTRACT_SUBROUTINE_IOUNIT = grep "subroutine_iounit=" | awk -F"subroutine_iounit=" '{print "Selective debug: \\texttt{DEBUGLEVEL="$$2"}"}'

# === AUTOMATIC GOING BACK FROM SPAG: ===
# DESPAG_FTEX = sed s/"C %stop_f77"/"%stop_f77"/ | sed s/"C %start_f77"/"%start_f77"/ | sed s/"C not_F77: "// | sed s/"C not_F77:"//

# ==================================================================
# Re-import SPAG'ed F90 source 
# without touching LaTex or other tags:
SPAG_F90TEX = sed s/"! not_F90:"// | sed s/"\!\*=="/"\% \!\*=="/ | sed s/"! %start_f90"/"%start_f90"/ | sed s/"! %stop_f90"/"%stop_f90"/ | sed s/" %start_latex"/"%start_latex"/ | sed s/" %stop_latex"/"%stop_latex"/
