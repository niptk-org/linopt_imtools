/**
 * @file    linopt_imtools.h
 * @brief   Function prototypes for linear algebra tools
 *
 * CPU-based lineal algebra tools: decomposition, SVD etc...
 *
 */



#ifndef _LINOPTIMTOOLS_H
#define _LINOPTIMTOOLS_H



/* =============================================================================================== */
/* =============================================================================================== */
/** @name 1. INITIALIZATION
 *  register CLI functions
 */
///@{
/* =============================================================================================== */
/* =============================================================================================== */

void __attribute__((constructor)) libinit_linopt_imtools();

///@}




/* =============================================================================================== */
/* =============================================================================================== */
/** @name 2. CONVERSION
 *
 */
///@{
/* =============================================================================================== */
/* =============================================================================================== */

long linopt_imtools_mask_to_pixtable(const char *IDmask_name,
                                     const char *IDpixindex_name, const char *IDpixmult_name);


imageID linopt_imtools_Image_to_vec(
    const char *ID_name,
    const char *IDpixindex_name,
    const char *IDpixmult_name,
    const char *IDvec_name
);

imageID linopt_imtools_vec_to_2DImage(
    const char *IDvec_name,
    const char *IDpixindex_name,
    const char *IDpixmult_name,
    const char *ID_name,
    long        xsize,
    long        ysize
);
///@}






/* =============================================================================================== */
/* =============================================================================================== */
/** @name 3. CREATE MODES
 *  create mode basis
 */
///@{
/* =============================================================================================== */
/* =============================================================================================== */

imageID linopt_imtools_make1Dpolynomials(
    const char *IDout_name,
    long        NBpts,
    long        MaxOrder,
    float       r0pix
);


imageID linopt_imtools_makeCosRadModes(
    const char *ID_name,
    long        size,
    long        kmax,
    float       radius,
    float       radfactlim
);


long linopt_imtools_makeCPAmodes(
    const char *ID_name,
    long        size,
    float       CPAmax,
    float       deltaCPA,
    float       radius,
    float       radfactlim,
    int         writeMfile
);

///@}






/* =============================================================================================== */
/* =============================================================================================== */
/** @name 4. LINEAR DECOMPOSITION
 *
 */
///@{
/* =============================================================================================== */
/* =============================================================================================== */



imageID linopt_imtools_image_construct(
    const char *IDmodes_name,
    const char *IDcoeff_name,
    const char *ID_name
);


imageID linopt_imtools_image_construct_stream(
    const char *IDmodes_name,
    const char *IDcoeff_name,
    const char *IDout_name
);


long linopt_compute_SVDdecomp(const char *IDin_name, const char *IDout_name,
                              const char *IDcoeff_name);


imageID linopt_compute_SVDpseudoInverse(
    const char *ID_Rmatrix_name,
    const char *ID_Cmatrix_name,
    double      SVDeps,
    long        MaxNBmodes,
    const char *ID_VTmatrix_name
);


imageID linopt_compute_1Dfit(
    const char *fnamein,
    long        NBpt,
    long        MaxOrder,
    const char *fnameout,
    int         MODE
);


imageID linopt_imtools_image_fitModes(
    const char *ID_name,
    const char *IDmodes_name,
    const char *IDmask_name,
    double      SVDeps,
    const char *IDcoeff_name,
    int         reuse
);



double linopt_imtools_match_slow(
    const char *ID_name,
    const char *IDref_name,
    const char *IDmask_name,
    const char *IDsol_name,
    const char *IDout_name
);


double linopt_imtools_match(
    const char *ID_name,
    const char *IDref_name,
    const char *IDmask_name,
    const char *IDsol_name,
    const char *IDout_name
);

///@}





/* =============================================================================================== */
/* =============================================================================================== */
/** @name 5. OPTIMIZATION
 *
 */
///@{
/* =============================================================================================== */
/* =============================================================================================== */


/**
 * @brief Solve for response matrix given a series of input and output
 *
 *  initial value of RM should be best guess
 *  inmask = 0 over input that are known to produce no response
 */
long linopt_compute_linRM_from_inout(const char *IDinput_name,
                                     const char *IDinmask_name, const char *IDoutput_name, const char *IDRM_name);


///@}






#endif
