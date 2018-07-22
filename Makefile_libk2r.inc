# ==============================
# Handle composite source files:
# ==============================
include Makefile_f90tex.inc

FORTCOMP=ifort
LINK=ifort
INCLUDE_DIR=./
CCOMP = gcc

CFLAGS += -cpp # pre-processor

QUICKPDFLATEXOPTS = -draftmode -interaction=batchmode # Incomplete but faster, for first pass.

# ======================================================================================================
# Monitor this Makefile too: if compilation options are changed, previous object files may need redoing.
# ======================================================================================================
# MAKEFILE_NAME = Makefile

# ==================
# Parent Latex file:
# ==================
TEX_MASTER_DOC = main_doc_example.tex


#.PHONY: all setlibraryopts clean cleandoc cleancode fullarchive doc fulldoc lib manpages listobj everything
.PHONY: makefile_ends_without_errors objs_depend

.SUFFIXES: .f90tex .F90 .F90_pruned \
           .ftex   .f   .f_pruned \
           .ctex   .c   .c_pruned \
           .cltex  .cl  .cl_pruned \
           .snippet \
           .f90tex-SPAGGED \
           .o .mod .3 .h

#           .f-SPAGGED .FTEX
# ----------------------------------------------------------------------------------------------
# Tell make that *.mod files are not to be handled by the default implicit function of Modula-2:
%.o: %.mod

# Tell make that these module are necessary first and for everything:
# Create a dependency list using makedepf90.  All files
# that needs to be compiled to build the program,
# i.e all source files except include files, should
# be given on the command line to makedepf90.
#
# The argument to the '-o' option will be the name of the
# resulting program when running 'make'
# The include implies that the dependencies tree is always prepared, even when issuing make clean.

# include objs_depend
# objs_depend: $(F_SRC) $(F90_SRC)
# 	$(MAKE) $(F_SRC) $(F90_SRC) ; makedepf90 -l "" $(F_SRC) $(F90_SRC) > objs_depend

#	makedepf90 -o $(STANDALONE_EXE) -l "$(FC) -o $@ $(FFLAGS) $(LDFLAGS) $(FOBJ) $(LIBS)" \
#    $(F_SRC) $(F90_SRC) > objs_depend
# ----------------------------------------------------------------------------------------------

# ===========================
# DEFAULT COMPILATION TARGET:
# ===========================
# all: objs_depend
all: 
#	# $(MAKE) dynlib && $(MAKE) doc && echo "" && echo "Dynamic library: "$(DYNLIB_NAME)" and PDF documentation: "`basename $(TEX_MASTER_DOC) .tex`.pdf" prepared." && echo ""
	$(MAKE) exe && $(MAKE) doc && echo "" && echo "Standalone EXE: "$(STANDALONE_EXE)" and PDF documentation: "`basename $(TEX_MASTER_DOC) .tex`.pdf" prepared." && echo ""

# =======================
# Composite source files:
# -----------------------
FTEX_SRC = $(wildcard *.ftex)
list_ftex:
	@echo "List of composite source Fortran 77 / LaTex *.ftex files found: "$(FTEX_SRC)

F90TEX_SRC = $(wildcard *.f90tex)
list_f90tex:
	@echo "List of composite source Fortran 90 / LaTex *.f90tex files found: "$(F90TEX_SRC)

# F90TEX_SRC_SPAGGED = $(wildcard *.f90tex-SPAGGED)
#	@echo "List of composite source Fortran 90 / LaTex *.f90tex SPAGGED files found: "$(F90TEX_SRC_SPAGGED)

CTEX_SRC = $(wildcard *.ctex)
list_ctex:
	@echo "List of composite source C / LaTex *.ctex files found: "$(CTEX_SRC)

CLTEX_SRC = $(wildcard *.cltex)
list_cltex:
	@echo "List of composite source OpenCL / LaTex *.cltex files found: "$(CLTEX_SRC)

# Only used for \lstinputlisting{*.cl_pruned} pretty-printed reinclusion.
CL_SRC_PRUNED = $(CLTEX_SRC:.cltex=.cl_pruned)
list_CLs_pruned:
	@echo "List of *.cl_pruned files that will be made: "$(CL_SRC_PRUNED)

# Only used for \lstinputlisting{*.c_pruned} pretty-printed reinclusion.
C_SRC_PRUNED = $(CTEX_SRC:.ctex=.c_pruned)
list_Cs_pruned:
	@echo "List of *.c_pruned files that will be made: "$(C_SRC_PRUNED)

# Only used for \lstinputlisting{*.f_pruned} pretty-printed reinclusion.
F_SRC_PRUNED = $(FTEX_SRC:.ftex=.f_pruned)
list_Fs_pruned:
	@echo "List of *.f_pruned files that will be made: "$(F_SRC_PRUNED)

# Only used for \lstinputlisting{*.F90_pruned} pretty-printed reinclusion.
F90_SRC_PRUNED = $(F90TEX_SRC:.f90tex=.F90_pruned)
list_F90s_pruned:
	@echo "List of *.F90_pruned files that will be made: "$(F90_SRC_PRUNED)

# Only used for Polyhedron SPAG support:
# F-SPAGGED_SRC = $(wildcard *.f-SPAGGED)
# F-SPAGGED_SRC = $(FTEX_SRC:.ftex=.f-SPAGGED)
# list_ftex-SPAGGED:
#	@echo "List of SPAGGED composite & SPAG'ged source Fortran 77 / LaTex *.ctex files found: "$(F-SPAGGED_SRC)

# =======================
# Extracted source files:
# -----------------------
F90_SRC = $(F90TEX_SRC:.f90tex=.F90)
list_F90s:
	@echo "List of *.F90 files that will be made: "$(F90_SRC)

F_SRC = $(FTEX_SRC:.ftex=.f)
list_Fs:
	@echo "List of *.f files that will be made: "$(F_SRC)

C_SRC = $(CTEX_SRC:.ctex=.c)
list_Cs:
	@echo "List of *.c files that will be made: "$(C_SRC)

CL_SRC = $(CLTEX_SRC:.cltex=.cl)
list_CLs:
	@echo "List of *.cl files that will be made: "$(CL_SRC)

TEX_SRC = $(F90TEX_SRC:.f90tex=.tex) $(CTEX_SRC:.ctex=.tex) $(FTEX_SRC:.ftex=.tex) $(CLTEX_SRC:.cltex=.tex)
list_texs:
	@echo "List of *.tex files that will be made: "$(TEX_SRC)

# ------------------------------------------
# Actual compilation rules for OBJECT files:
# ------------------------------------------
OBJS = $(F90_SRC:.F90=.o) $(C_SRC:.c=.o) $(F_SRC:.f=.o)
list_objs:
	@echo "List of *.o files that will be made: "$(OBJS)

# -----------------------------------------------------
# Actual compilation rules for SPAGGED composite files:
# -----------------------------------------------------
RESPAGGED_F90TEX_SRC = $(F90TEX_SRC:.f90tex=.f90tex-SPAGGED)
list_respagged_F90TEXs:
	@echo "List of *.f90tex files that will be REPLACED by their RESPAGGED version: "$(RESPAGGED_F90TEX_SRC)

# MODS = $(F90_SRC:.F90=.mod)
# list_mods:
# 	@echo "List of *.mod files that will be made (only if needed): "$(MODS)

# =====================================================================================
$(DYNLIB_NAME): $(OBJS) 
	@echo "" ; 

# Implicit target for *.mod from Fortran:
.F90.mod: $(F90_SRC) ;

#.F77.mod: $(F_SRC) ;


# ==========================================================
# Implicit targets for Makefile dependences of OBJECT files:
# ----------------------------------------------------------
# ----------------------------------------
# Implicit target for *.o from Fortran 90:
# ----------------------------------------
# .F90.o .F90.mod: $(F90_SRC) 

.F90.o: $(F90_SRC) 
	$(FORTCOMP) $(FFLAGS) $(DEBUG) -I $(INCLUDE_DIR) $(FREE-FORM) -c $< -o $@

# ----------------------------------------
# Implicit target for *.o from Fortran 77:
# ----------------------------------------
# .f.o .f.mod: $(F_SRC) 
.f.o: $(F_SRC) 
	$(FORTCOMP) $(FFLAGS) $(DEBUG) -I $(INCLUDE_DIR) -c $< -o $@

# -------------------------------
# Implicit target for *.o from C:
# -------------------------------
.c.o: $(C_SRC)
	$(CCOMP) $(CFLAGS) $(DEBUG) -I $(INCLUDE_DIR) -c $< -o $@

# ------------------------------------
# Implicit target for *.o from OpenCL:
# ------------------------------------
.cl.cl: $(CL_SRC)
# No handling by a compiler:
#  the content will be read-in and bytecode-compiled at runtime.

# ================================================================
# Implicit targets for Makefile dependences of LATEX source files:
# ----------------------------------------------------------------
# --------------------------------------
# Implicit target for *.tex from *.ftex:
# --------------------------------------
.ftex.tex: 
	@cat $< | $(MAKE_PADDED_LATEX) > $@

# ----------------------------------------
# Implicit target for *.tex from *.f90tex:
# ----------------------------------------
.f90tex.tex: 
	@cat $< | $(MAKE_PADDED_LATEX) > $@

# --------------------------------------
# Implicit target for *.tex from *.ctex:
# --------------------------------------
.ctex.tex: 
	@cat $< | $(MAKE_PADDED_LATEX) > $@

# --------------------------------------
# Implicit target for *.tex from *.cltex:
# --------------------------------------
.cltex.tex: 
	@cat $< | $(MAKE_PADDED_LATEX) > $@

# =====================================================================
# Implicit targets for Makefile dependences of SPAGGED composite files:
# ---------------------------------------------------------------------
# ---------------------------------------------------
# Implicit target for *.f90tex-SPAGGED from *.f90tex:
# ---------------------------------------------------
ACCEPTABLE_SPAG_EXITCODE = 3 # Up to what level of EXITCODE != 0 to consider the run a success.
                             # From the online manual:
			     # 0: No messages.
                             # 1: Nothing more serious than an informational message issued.
                             # 2: Nothing more serious than an warning message issued.
                             # 4: plusFORT found an error in the input, but was able to continue.
                             # 8: plusFORT found an error in the input, and was not able to continue.
                             # 16: Assertion failure. A serious error which could result from previously reported errors.

.f90tex.f90tex-SPAGGED: $(F90TEX_SRC)
	$(MAKE) $(basename $<).F90
	cp $< Before_SPAG/
	spag FIG=spag_config.fig $(basename $<).F90 ; [ $$? -le $(ACCEPTABLE_SPAG_EXITCODE) ] && cat output/$(basename $<).f | $(SPAG_F90TEX) > $@ && \
  echo "" && mv $@ $< && echo "" ; fi

respag_all: $(RESPAGGED_F90TEX_SRC)
	@echo "All *.f90tex files RESPAGGED; originals saved within Before_SPAG."

# ====================================================================
# Implicit targets for Makefile dependence of COMPILABLE SOURCE files:
# --------------------------------------------------------------------
# ------------------------------------
# Implicit target for *.f from *.ftex:
# ------------------------------------
.ftex.f:
	@cat $< | $(MAKE_PADDED_F77) > $@

# -------------------------------------------
# Implicit target for *.f_pruned from *.ftex:
# -------------------------------------------
.ftex.f_pruned:
	@cat $< | $(MAKE_UNPADDED_F77) > $@
# Individual snippets:	
# (the output name is determined within the AWK script)
	@$(SPLIT_SOURCE_SNIPPETS) $<

# ----------------------------------------
# Implicit target for *.F90 from *.f90tex:
# ----------------------------------------
.f90tex.F90:
	@cat $< | $(MAKE_PADDED_F90) > $@

# -----------------------------------------------
# Implicit target for *.F90_pruned from *.f90tex:
# -----------------------------------------------
.f90tex.F90_pruned:
	@cat $< | $(MAKE_UNPADDED_F90) > $@
# Individual snippets:	
# (the output name is determined within the AWK script)
	@$(SPLIT_SOURCE_SNIPPETS) $<

# ------------------------------------
# Implicit target for *.c from *.ctex:
# ------------------------------------
.ctex.c:
	@cat $< | $(MAKE_PADDED_C) > $@

# -------------------------------------------
# Implicit target for *.c_pruned from *.ctex:
# -------------------------------------------
.ctex.c_pruned:
	@cat $< | $(MAKE_UNPADDED_C) > $@
# Individual snippets:	
# (the output name is determined within the AWK script)
	@$(SPLIT_SOURCE_SNIPPETS) $<

# --------------------------------------
# Implicit target for *.cl from *.cltex:
# --------------------------------------
.cltex.cl:
	@cat $< | $(MAKE_PADDED_OPENCL) > $@

# ---------------------------------------------
# Implicit target for *.cl_pruned from *.cltex:
# ---------------------------------------------
.cltex.cl_pruned:
	@cat $< | $(MAKE_UNPADDED_OPENCL) > $@
# Individual snippets:	
# (the output name is determined within the AWK script)
	@$(SPLIT_SOURCE_SNIPPETS) $<

# ===============================
# Compilation of executable code:
# ===============================
# --------------------
# --------------------
dynlib: $(DYNLIB_NAME)
	$(FORTCOMP) $(FFLAGS) $(DYNLIB_OPTIONS) $(OBJS) -o $(DYNLIB_NAME) \
 && cp $(DYNLIB_NAME) $(DESTINATION_DIR)/ && echo "" && echo "All done for "$(DYNLIB_NAME) && echo ""


exe: $(OBJS)
# objs_depend
	$(LINK) $(OBJS) $(LIBS) -o $(STANDALONE_EXE) && $(MAKE) makefile_ends_without_errors

# ==================================
# Compilation of documentation:
# ==============================

doc_files: $(TEX_SRC)
	@echo "Latex source files: "$(TEX_SRC) " prepared."

# $(F90_SRC_PRUNED) and $(C_SRC_PRUNED) and $(F_SRC_PRUNED) are only placed as a dependency, for their possible incorporation within the Latex for pretty-printing.
doc: $(TEX_SRC) $(COMPSITESRC) $(F90_SRC_PRUNED) $(C_SRC_PRUNED) $(CL_SRC_PRUNED) $(F_SRC_PRUNED)
	@latexmk -pdf -pdflatex="pdflatex -file-line-error" $(TEX_MASTER_DOC) \
		&& echo "" && echo "PDF documentation: "`basename $(TEX_MASTER_DOC) .tex`.pdf" prepared." && echo ""

# ========================
# Assist with compilation:
# ========================
help:
	@echo "Use 'DEBUGLEVEL=6 make all' to compile everything with a preferred level of debugging code (current default: DEBUGLEVEL="$(DEBUGLEVEL)")"
	@echo "Use 'make check_latex' to check & report references issues"

# ==============================================================================
archive:
	tar cvfj archive.tar.bz2 $(F90TEX_SRC) $(CTEX_SRC) Images/ Makefile Makefile_f90tex.inc spag_config.fig Incorporated/

# ===============================================================================
clean_exes:
	rm *.x

clean_objs:
	rm *.o *.mod *.so

clean_source:
	rm *.tex \
    *.F90 *.F90_pruned *_genmod.f90 \
    *.f *.f_pruned \
    *.c *.c_pruned \
    *.cl *.cl_pruned \
    objs_depend \
    spag.log \
    *-SPAGGED \
    *.snippet
#     *.FTEX *.f-SPAGGED 

clean_doc:
	rm *.tex *.mtc* *.toc *.idx *.maf *.out *.aux *.log \
	*.fdb_latexmk \
  *.fls *.fdb_latexmk \
  *.ind *.ilg *.bbl \
  *.smb \
  *.blg *.dvi *.pdf

clean: 
	$(MAKE) clean_exes ; $(MAKE) clean_objs ; $(MAKE) clean_doc ; $(MAKE) clean_source
	@echo "All derivative source and object files removed"

check_latex: check_multiple_defined_labels check_missing_labels
	@echo "LaTeX source checked."

check_multiple_defined_labels: doc
	@echo "\nChecking for multiply-defined labels inside *.tex files..."
	@if `grep -q "multiply-defined" *.log`; then \
  echo "\n Multiply defined LaTeX labels found\n" \
  && grep -A2 -B2 "multiply defined." *.log && false ; fi \
  && $(MAKE) makefile_ends_without_errors

check_missing_labels: doc
	@echo "Now checking for missing labels inside *.tex files..." \
  && if `grep -q "undefined references" *.log`; then \
  echo "\n References to missing LaTeX labels found:\n" \
  && grep -A2 -B2 "Warning: Reference" *.log && false ; fi \
  || if `grep -q "LaTeX Warning: Citation" *.log`; then \
  echo "\n References to missing BibTeX citations found:\n" \
  && grep -A2 -B2 "undefined" *.log && false ; fi \
	&& $(MAKE) makefile_ends_without_errors

makefile_ends_without_errors:
	@echo "" && echo "No problems during make." && echo ""
